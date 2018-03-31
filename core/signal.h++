/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2018 Ruben Van Boxem
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **/

/*
 * Signal
 * Registers observers.
 * Notifies registered observers.
 */

#ifndef SKUI_CORE_SIGNAL_H
#define SKUI_CORE_SIGNAL_H

#include "core/slot.h++"
#include "core/trackable.h++"
#include "core/value_ptr.h++"

#include <algorithm>
#include <functional>
#include <iterator>
#include <list>
#include <memory>
#include <mutex>
#include <utility>

namespace skui
{
  namespace core
  {
    namespace implementation
    {
      template<typename... ArgTypes>
      class signal_base : public tracker
                        , public trackable
      {
        using mutex_type = std::mutex;
        using mutex_lock = const std::lock_guard<mutex_type>;

      public:
        using function_type = void(*)(ArgTypes...);
        using slot_type = slot<void, ArgTypes...>;
        using object_slot_type = std::pair<const trackable*, value_ptr<slot_type>>;
        using connection_type = typename std::list<object_slot_type>::const_iterator;

        signal_base() = default;
        ~signal_base() override { disconnect_all(); }

        signal_base(const signal_base& other)
          : trackable(other)
          , slots(other.slots.begin(), other.slots.end())
        {}

        signal_base(signal_base&& other) noexcept : slots(std::move(other.slots)) {}
        signal_base& operator=(signal_base other) { swap(slots, other.slots); return *this; }

        void trackable_deleted(const trackable* tracker) override
        {
          disconnect(tracker);
        }

        void trackable_moved(const trackable* old_object, const trackable* new_object) override
        {
          mutex_lock lock(slots_mutex);
          for(auto& object_slot : slots)
          {
            if(object_slot.first == old_object)
              object_slot.first = new_object;
          }
        }

        void trackable_copied(const trackable* old_object, const trackable* new_object) override
        {
          mutex_lock lock(slots_mutex);
          for(const auto& object_slot : slots)
          {
            if(object_slot.first == old_object)
              slots.emplace_back(new_object, object_slot.second);
          }
        }

        template<typename Callable, typename ReturnType = void>
        connection_type connect(Callable&& callable)
        {
          mutex_lock lock(slots_mutex);
          slots.emplace_back(nullptr, make_value<callable_slot<Callable, ReturnType, ArgTypes...>>(callable));
          return --slots.end();
        }

        template<typename Class, class FunctionClass, typename ReturnType, typename... FunctionArgTypes>
        connection_type connect(Class* object, ReturnType(FunctionClass::* slot)(FunctionArgTypes...))
        {
          static_assert(std::is_base_of<trackable, Class>::value,
                        "You can only connect to member functions of a trackable subclass.");
          static_assert(std::is_base_of<FunctionClass, Class>::value,
                        "You can only connect to member functions of a related object.");

          mutex_lock lock(slots_mutex);

          slots.emplace_back(object, make_value<member_function_slot<Class, ReturnType(FunctionClass::*)(FunctionArgTypes...), ReturnType, ArgTypes...>>(slot));
          object->track(this);

          return --slots.end();
        }

        template<typename Class, typename FunctionClass, typename ReturnType, typename... FunctionArgTypes>
        connection_type connect(const Class* object, ReturnType(FunctionClass::* slot)(FunctionArgTypes...) const)
        {
          static_assert(std::is_base_of<trackable, Class>::value,
                        "You can only connect to member functions of a trackable subclass");
          static_assert(std::is_base_of<FunctionClass, Class>::value,
                        "You can only connect to member functions of a related object.");

          mutex_lock lock(slots_mutex);

          slots.emplace_back(object, make_value<const_member_function_slot<Class, ReturnType(FunctionClass::*)(FunctionArgTypes...) const, ReturnType, ArgTypes...>>(slot));
          object->track(this);

          return --slots.end();
        }

        template<typename Signal>
        connection_type relay(const Signal& signal)
        {
          mutex_lock lock(slots_mutex);
          slots.emplace_back(&signal, make_value<const_member_function_slot<Signal, void(Signal::*)(ArgTypes...) const, void, ArgTypes...>>(&Signal::emit));
          signal.track(this);
          return --slots.end();
        }

        // removes a previously made connection, handles lifetime tracking if it was the last connection to a specific object
        void disconnect(connection_type connection)
        {
          mutex_lock lock(slots_mutex);
          const trackable* object = connection->first;

          slots.erase(connection);
          if(object && std::any_of(slots.begin(), slots.end(),
                                   [&object](const object_slot_type& object_slot)
                                   { return object_slot.first == object; }))
            object->untrack(this);
        }

        // removes all connections to an object
        void disconnect(const trackable* object)
        {
          mutex_lock lock(slots_mutex);
          object->untrack(this);
          slots.remove_if([object](const object_slot_type& object_slot)
                          {
                            return object == object_slot.first;
                          });
        }

        // removes all connections
        void disconnect_all()
        {
          mutex_lock lock(slots_mutex);
          for(object_slot_type& object_slot : slots)
          {
            auto trackable = object_slot.first;
            if(trackable)
              trackable->untrack(this);
          }
          slots.clear();
        }

      protected:
        // mutable here allows to connect to a const object's signals
        mutable std::list<object_slot_type> slots;
        mutable mutex_type slots_mutex;
      };
    }

    template<typename... ArgTypes>
    class signal : public implementation::signal_base<ArgTypes...>
    {
    public:
      signal() = default;

      void emit(ArgTypes... arguments) const
      {
        std::lock_guard<decltype(this->slots_mutex)> lock(this->slots_mutex);
        for(auto&& object_slot : this->slots)
        {
          // This needs a dynamic_cast<const void*> e.g. when trackable is not the first parent class
          object_slot.second->operator()(dynamic_cast<const void*>(object_slot.first), arguments...);
        }
      }
    };
  }
}

#endif
