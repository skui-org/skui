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

#include "test.h++"

#include "core/trackable.h++"

#include <memory>

namespace
{
  using skui::test::check;

  struct mock_trackable : public skui::core::trackable
  {
  };

  struct mock_tracker : public skui::core::implementation::tracker
  {
    void trackable_deleted(const skui::core::trackable*) override { informed_deleted = true; }
    void trackable_copied(const skui::core::trackable*, const skui::core::trackable*) override { informed_copied = true; }
    void trackable_moved(const skui::core::trackable*, const skui::core::trackable*) override { informed_moved = true; }

    bool informed_deleted = false;
    bool informed_copied = false;
    bool informed_moved = false;
  };

  void test_trackable_deleted()
  {
    mock_tracker tracker;
    {
      mock_trackable trackable;
      trackable.track(&tracker);
    }

    check(tracker.informed_deleted, "tracker informed when trackable was deleted");
    check(!tracker.informed_copied, "tracker not informed of copy when trackable was deleted");
    check(!tracker.informed_moved, "tracker not informed of move when trackable was deleted");
  }

  void test_trackable_copy()
  {
    mock_tracker tracker; // tracker should outlive trackable, so create it first
    mock_trackable trackable;
    trackable.track(&tracker);

    mock_trackable other_trackable(trackable);
    check(tracker.informed_copied, "tracker informed when trackable was copied");
    check(!tracker.informed_moved, "tracker not informed of move when trackable was copied");
    check(!tracker.informed_deleted, "tracker not informed of delete when trackable was copied");
  }

  void test_trackable_move()
  {
    mock_tracker tracker; // tracker should outlive trackable, so create it first
    mock_trackable trackable;
    trackable.track(&tracker);

    mock_trackable other_trackable(std::move(trackable));
    check(tracker.informed_moved, "tracker informed when trackable was moved");
    check(!tracker.informed_copied, "tracker not informed of copy when trackable was moved");
    check(!tracker.informed_deleted, "tracker not informed of delete when trackable was moved");
  }
}

int main()
{
  test_trackable_deleted();
  test_trackable_copy();
  test_trackable_move();

  return skui::test::exit_code;
}
