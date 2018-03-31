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
 * Trackable
 * Lifetime management base class for classes that connect to signals.
 * Only needed if e.g. a signal from outside the class connects to e.g. a member function.
 */

#ifndef SKUI_CORE_TRACKABLE_H
#define SKUI_CORE_TRACKABLE_H

#include <algorithm>
#include <mutex>
#include <string>
#include <unordered_set>

namespace skui
{
  namespace core
  {
    class trackable;

    namespace implementation
    {
      // Not part of the public interface because a derived class must ensure it untracks all its trackables manually in its destructor.
      class tracker
      {
      public:
        virtual void trackable_deleted(const trackable* object) = 0;
        virtual void trackable_copied(const trackable* old_object, const trackable* new_object) = 0;
        virtual void trackable_moved(const trackable* old_object, const trackable* new_object) = 0;

      protected:
        tracker() = default;
        virtual ~tracker() = default;
      };
    }

    class trackable
    {
    public:
      virtual ~trackable();

      trackable(const trackable& other);
      trackable(trackable&& other) noexcept;
      trackable& operator=(trackable other);

      void track(implementation::tracker* tracker) const;
      void untrack(implementation::tracker* tracker) const;

    protected:
      trackable() = default;

    private:
      // mutable so you can be track const objects
      mutable std::unordered_set<implementation::tracker*> trackers;
      mutable std::mutex trackers_mutex;
    };
  }
}

#endif
