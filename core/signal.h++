/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Ruben Van Boxem
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
      {
      public:
        using function_type = void(*)(ArgTypes...);
        using slot_type = slot<void, ArgTypes...>;
        using object_slot_type = std::pair<const trackable*, value_ptr<slot_type>>;
        using connection_type = typename std::list<object_slot_type>::const_iterator;

        signal_base() = default;
        ~signal_base() { disconnect_all(); }

        signal_base(const signal_base& other)
          : slots(other.slots.begin(), other.slots.end())
        {}

        signal_base(signal_base&& other) : slots(std::move(other.slots)) {}
        signal_base& operator=(signal_base other) { swap(slots, other.slots); return *this; }

        virtual void trackable_deleted(const trackable* tracker) override
        {
          disconnect(tracker);
        }

        virtual void trackable_moved(const trackable* old_object, const trackable* new_object) override
        {
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);
          std::for_each(slots.begin(), slots.end(),
                        [&old_object, &new_object](object_slot_type& object_slot)
                        {
                          if(object_slot.first == old_object)
                            object_slot.first = new_object;
                        });
        }

        virtual void trackable_copied(const trackable* old_object, const trackable* new_object) override
        {
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);
          std::for_each(slots.begin(), slots.end(),
                        [&old_object, &new_object, this](const object_slot_type& object_slot)
                        {
                          if(object_slot.first == old_object)
                            slots.push_back({new_object, object_slot.second});
                        });

        }

        template<typename Callable, typename ReturnType = void>
        connection_type connect(Callable&& callable)
        {
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);
          slots.emplace_back(nullptr, make_value<function_slot<Callable, ReturnType, ArgTypes...>>(callable));
          return --slots.end();
        }

        template<typename Class, typename ReturnType>
        connection_type connect(Class* object, ReturnType(Class::* slot)(ArgTypes...))
        {
          static_assert(std::is_base_of<trackable, Class>::value,
                        "You can only connect to member functions of a trackable object.");

          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);

          slots.emplace_back(object, make_value<member_function_slot<Class, ReturnType, ArgTypes...>>(slot));
          object->track(this);

          return --slots.end();
        }

        template<typename Class, typename ReturnType>
        connection_type connect(const Class* object, ReturnType(Class::* slot)(ArgTypes...) const)
        {
          static_assert(std::is_base_of<trackable, Class>::value,
                        "You can only connect to member functions of a trackable object");
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);

          object_slot_type object_slot(object, make_value<const_member_function_slot<Class, ReturnType, ArgTypes...>>(slot));
          slots.emplace_back(std::move(object_slot));
          object->track(this);

          return --slots.end();
        }

        // connects first object like first object
        void connect(trackable* /*first*/, trackable* /*second*/)
        {
          // trackable copy constructor makes second->track(this) unnecessary
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);
        }

        // removes a previously made connection, handles lifetime tracking if it was the last connection to a specific object
        void disconnect(connection_type connection)
        {
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);
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
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);
          object->untrack(this);
          slots.remove_if([object](const object_slot_type& object_slot)
                          {
                            return object == object_slot.first;
                          });
        }

        // removes all connections
        void disconnect_all()
        {
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);
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
        mutable std::mutex slots_mutex;
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
          (*object_slot.second)(object_slot.first, arguments...);
        }
      }
    };

    // Parameterless specialization
    template<> class signal<> : public implementation::signal_base<>
    {
    public:
      signal() = default;

      void emit() const
      {
        std::lock_guard<decltype(this->slots_mutex)> lock(this->slots_mutex);
        for(auto&& object_slot : this->slots)
        {
          (*object_slot.second)(object_slot.first);
        }
      }
    };
  }
}

#endif
