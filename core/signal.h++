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
        signal_base() = default;

        signal_base(const signal_base& other) : slots(other.slots) {}
        signal_base(signal_base&& other) : slots(std::move(other.slots)) {}
        signal_base& operator=(signal_base other) { swap(other); return *this; }

        template<typename Callable>
        void connect(Callable&& slot)
        {
          std::lock_guard<decltype(slots_mutex)> lock(slots_mutex);
          slots.emplace_back(slot);
        }

      protected:
        // mutable here allows to connect to a const object's signals
        mutable std::vector<std::function<void(ArgTypes...)>> slots;
        mutable std::mutex slots_mutex;

      private:
        void swap(signal_base& other) { std::swap(slots, other.slots); }
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


