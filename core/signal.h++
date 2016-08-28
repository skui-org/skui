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

#include <algorithm>
#include <functional>
#include <mutex>
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

        signal_base() = default;

        signal_base(const signal_base& other) : slots(other.slots) {}
        signal_base(signal_base&& other) : slots(std::move(other.slots)) {}
        signal_base& operator=(signal_base other) { swap(slots, other.slots); return *this; }

        void connect(slot_type&& slot)
        {
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);
          slots.emplace_back(slot);
        }

        bool disconnect(slot_type&& slot)
        {
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);
          auto function_pointer = slot.template target<function_type>();
          const auto result_it = std::find_if(begin(slots), end(slots),
                                              [&function_pointer](slot_type& connected_slot)
                                              {
                                                return function_pointer == connected_slot.template target<function_type>();
                                              });
          if(result_it != end(slots))
          {
            slots.erase(result_it);
            return true;
          }
          return false;
        }

        void disconnect_all()
        {
          const std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);
          slots.clear();
        }

      protected:
        // mutable here allows to connect to a const object's signals
        mutable std::vector<slot_type> slots;
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
        for(auto&& slot : this->slots)
        {
          slot(arguments...);
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
        for(auto&& slot : this->slots)
        {
          slot();
        }
      }
    };
  }
}


