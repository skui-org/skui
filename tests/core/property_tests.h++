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

#include "test.h++"

namespace skui
{
  namespace test
  {
    template<typename PropertyType>
    void test_value_changed_signal()
    {
      using value_type = typename PropertyType::value_type;

      value_type changed_value = 0;
      auto slot = [&changed_value](int i) { changed_value = i; };

      PropertyType property{0};
      property.value_changed.connect(slot);

      property = 1;
      check(changed_value == 1, "changed slot called on assignment");

      property = std::move(2);
      check(changed_value == 2, "moving value into property emits signal");
    }

    template<typename PropertyType>
    void test_relational_operators()
    {
      using value_type = typename PropertyType::value_type;

      bool slot_called = false;
      auto slot = [&slot_called](value_type) { slot_called = true; };

      PropertyType property{0};
      property.value_changed.connect(slot);

      check(property == 0, "==");
      check(0 == property, "== (reversed)");
      check(property <  1, "<" );
      check(property <= 0, "<=");
      check(property > -1, ">" );
      check(property >= 0, ">=");
      check(property != 1, "!=");
      check(!slot_called,  "operators don't emit value_changed");
    }

    template<typename PropertyType>
    void test_copy_construction_assignment()
    {
      using value_type = typename PropertyType::value_type;

      bool slot_called = false;
      auto slot = [&slot_called](value_type) { slot_called = true; };

      PropertyType property{1};
      property.value_changed.connect(slot);

      slot_called = false;
      PropertyType other_property{property};
      check(property == other_property && other_property == 1, "copy construction copies the value");
      check(!slot_called, "copy construction does not emit value_changed");

      slot_called = false;
      other_property = 0;
      check(slot_called, "connection copied");
    }

    template<typename PropertyType>
    void test_move_construction_assignment()
    {
      using value_type = typename PropertyType::value_type;

      bool slot_called = false;
      auto slot = [&slot_called](value_type) { slot_called = true; };

      slot_called = false;
      {
        PropertyType property{1};
        property.value_changed.connect(slot);

        PropertyType other_property(std::move(property));
        check(other_property == 1, "move construction moves value");

        slot_called = false;
        property = 2;
        check(!slot_called, "moved-from-initialization property is disconnected");

        slot_called = false;
        other_property = 3;
        check(slot_called, "moved-to-initialization property is connected");
      }
      {
        slot_called = false;
        PropertyType property{1};
        property.value_changed.connect(slot);

        PropertyType  other_property = std::move(property);
        check(other_property == 1, "move assignment moves value");
        check(!slot_called, "move constructor does not emit value_changed");

        slot_called = false;
        property = 2;
        check(!slot_called, "moved-from-assignment property is disconnected");

        slot_called = false;
        other_property = 3;
        check(slot_called, "moved-to-assignment property is connected");
      }
    }

    template<typename PropertyType>
    void run_all_property_tests()
    {
      skui::test::test_value_changed_signal<PropertyType>();
      skui::test::test_relational_operators<PropertyType>();
      skui::test::test_copy_construction_assignment<PropertyType>();
      skui::test::test_move_construction_assignment<PropertyType>();
    }
  }
}
