/**
 * The MIT License (MIT)
 *
 * Copyright © 2017-2019 Ruben Van Boxem
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

#include <algorithm>
#include <functional>
#include <iterator>
#include <list>
#include <memory>
#include <mutex>
#include <utility>

namespace skui::core
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
      using connection_type = typename std::list<slot_type>::const_iterator;

      signal_base() = default;
      ~signal_base() override { disconnect_all(); }

      signal_base(const signal_base& other)
        : trackable{other}
        , slots{other.slots.begin(), other.slots.end()}
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
        for(auto& slot : slots)
        {
          if(slot.template get_target<const trackable>() == old_object)
            slot.reseat(new_object);
        }
      }

      void trackable_copied(const trackable* old_object, const trackable* new_object) override
      {
        mutex_lock lock(slots_mutex);
        for(auto& slot : slots)
        {
          if(slot.template get_target<const trackable>() == old_object)
          {
            auto copy = slot;
            copy.reseat(new_object);
            slots.push_back(std::move(copy));
          }
        }
      }

      template<typename Callable, typename ReturnType = void>
      connection_type connect(Callable&& callable)
      {
        mutex_lock lock(slots_mutex);
        slots.emplace_back(nullptr, std::forward<Callable>(callable));
        return --slots.end();
      }

      template<typename Class, class FunctionClass, typename ReturnType, typename... FunctionArgTypes>
      connection_type connect(Class* object, ReturnType(FunctionClass::* member_function_pointer)(FunctionArgTypes...))
      {
        static_assert(std::is_base_of<trackable, Class>::value,
                      "You can only connect to member functions of a trackable subclass.");

        mutex_lock lock(slots_mutex);

        slots.emplace_back(object, slot<ReturnType, ArgTypes...>{object, member_function_pointer});
        object->track(this);

        return --slots.end();
      }

      template<typename Class, typename FunctionClass, typename ReturnType, typename... FunctionArgTypes>
      connection_type connect(const Class* object, ReturnType(FunctionClass::* const_member_function_pointer)(FunctionArgTypes...) const)
      {
        static_assert(std::is_base_of<trackable, Class>::value,
                      "You can only connect to member functions of a trackable subclass");

        mutex_lock lock(slots_mutex);

        slots.emplace_back(object, slot<ReturnType, ArgTypes...>{object, const_member_function_pointer});
        object->track(this);

        return --slots.end();
      }

      template<typename Signal>
      connection_type relay(const Signal& signal)
      {
        mutex_lock lock(slots_mutex);
        slots.emplace_back(&signal, slot<void, ArgTypes...>{&signal, &Signal::template emit<ArgTypes...>});
        signal.track(this);
        return --slots.end();
      }

      // removes a previously made connection, handles lifetime tracking if it was the last connection to a specific object
      void disconnect(connection_type connection)
      {
        mutex_lock lock(slots_mutex);
        const trackable* object = static_cast<const trackable*>(connection->target);

        slots.erase(connection);
        if(object && std::any_of(slots.begin(), slots.end(),
                                 [&object](const slot_type& slot)
                                 { return static_cast<const trackable*>(slot.target) == object; }))
          object->untrack(this);
      }

      // removes all connections to an object
      void disconnect(const trackable* object)
      {
        mutex_lock lock(slots_mutex);
        object->untrack(this);
        slots.remove_if([object](const slot_type& slot)
                        { return object == slot.template get_target<const trackable>(); });
      }

      // removes all connections
      void disconnect_all()
      {
        mutex_lock lock(slots_mutex);
        for(auto&& slot : slots)
        {
          auto trackable = slot.template get_target<const core::trackable>();
          if(trackable)
            trackable->untrack(this);
        }
        slots.clear();
      }

    protected:
      // mutable here allows to connect to a const object's signals
      mutable std::list<slot_type> slots;
      mutable mutex_type slots_mutex;
    };
  }

  template<typename... ArgTypes>
  class signal : public implementation::signal_base<ArgTypes...>
  {
  public:
    signal() = default;

    template<typename... EmitArgTypes>
    void emit(EmitArgTypes&&... arguments) const
    {
      std::lock_guard<decltype(this->slots_mutex)> lock(this->slots_mutex);
      for(auto&& slot : this->slots)
      {
        slot(std::forward<EmitArgTypes>(arguments)...);
      }
    }

    template<typename... EmitArgTypes>
    void operator()(EmitArgTypes&&... arguments) const
    {
      emit(std::forward<EmitArgTypes>(arguments)...);
    }
  };
}

#endif
