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
 * Trackable
 * Lifetime management base class for classes that connect to signals.
 * Only needed if e.g. a signal from outside the class connects to e.g. a member function.
 */

#include "trackable.h++"

#include <vector>

namespace skui
{
  namespace core
  {
    trackable::~trackable()
    {
      // trackable_deleted will most likely erase elements in this->trackers, so iterate through a copy made up front.
      const std::vector<implementation::tracker*> trackers_copy(trackers.begin(), trackers.end());
      for(auto tracker : trackers_copy)
      {
        tracker->trackable_deleted(this);
      }
    }

    trackable::trackable(const trackable& other)
    : trackers(other.trackers)
    {
      for(auto tracker : trackers)
      {
        tracker->trackable_copied(&other, this);
      }
    }

    trackable::trackable(trackable&& other)
    : trackers(other.trackers)
    {
      for(auto tracker : trackers)
      {
        tracker->trackable_moved(&other, this);
      }
    }

    trackable& trackable::operator=(trackable other)
    {
      swap(trackers, other.trackers);
      return *this;
    }

    void trackable::track(implementation::tracker* tracker) const
    {
      const std::lock_guard<decltype(trackers_mutex)> lock(trackers_mutex);
      trackers.insert(tracker);
    }

    void trackable::untrack(implementation::tracker* tracker) const
    {
      const std::lock_guard<decltype (trackers_mutex)> lock(trackers_mutex);
      trackers.erase(tracker);
    }
  }
}
