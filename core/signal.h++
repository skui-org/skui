/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Ruben Van Boxem
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

#include <algorithm>
#include <functional>
#include <mutex>
#include <utility>
#include <vector>

namespace skui
{
  namespace core
  {
    namespace implementation
    {
      template<typename... ArgTypes>
      class signal_base
      {
      public:
        using function_type = void(*)(ArgTypes...);
        using slot_type = std::function<void(ArgTypes...)>;
        using object_slot_type = std::pair<const volatile void*, slot_type>;

        signal_base() = default;

        signal_base(const signal_base& other) : slots(other.slots) {}
        signal_base(signal_base&& other) : slots(std::move(other.slots)) {}
        signal_base& operator=(signal_base other) { swap(slots, other.slots); return *this; }

        void connect(slot_type&& slot)
        {
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);
          slots.emplace_back(nullptr, slot);
        }

        void disconnect(slot_type&& slot)
        {
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);
          auto function_pointer = slot.template target<function_type>();
          slots.erase(std::remove_if(begin(slots), end(slots),
                                     [&function_pointer](const object_slot_type& object_slot)
                                     {
                                       return function_pointer == object_slot.second.template target<function_type>();
                                     }));
        }

        template<typename Class>
        void connect(Class* object, void(Class::* slot)(ArgTypes...))
        {
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);

          slots.emplace_back(object, [object, slot](ArgTypes... args) { (object->*slot)(std::forward(args)...); } );
        }

        template<typename Class>
        void connect(const Class* object, void(Class::* slot)(ArgTypes...) const)
        {
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);

          slots.emplace_back(object, [object, slot](ArgTypes... args) { (object->*slot)(std::forward(args)...); } );
        }

        template<typename Class>
        void connect(volatile Class* object, void(Class::* slot)(ArgTypes...) volatile)
        {
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);

          slots.emplace_back(object, [object, slot](ArgTypes... args) { (object->*slot)(std::forward(args)...); } );
        }

        template<typename Class>
        void connect(const volatile Class* object, void(Class::* slot)(ArgTypes...) const volatile)
        {
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);

          slots.emplace_back(object, [object, slot](ArgTypes... args) { (object->*slot)(std::forward(args)...); } );
        }

        // removes all connections to an object
        void disconnect(const volatile void* object)
        {
          slots.erase(std::remove_if(slots.begin(), slots.end(),
                                     [object](const object_slot_type& object_slot)
                                     {
                                       return object == object_slot.first;
                                     }));
        }

        void disconnect_all()
        {
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);
          slots.clear();
        }

      protected:
        // mutable here allows to connect to a const object's signals
        mutable std::vector<object_slot_type> slots;
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
          object_slot.second(arguments...);
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
          object_slot.second();
        }
      }
    };
  }
}

#endif
