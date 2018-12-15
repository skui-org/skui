/**
 * The MIT License (MIT)
 *
 * Copyright © 2018 Ruben Van Boxem
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

#include <core/debug.h++>
#include <core/string.h++>

#include <boost/spirit/home/x3.hpp>

namespace skui::test
{
  using skui::test::check;
  using skui::core::string;

  template<typename Rule>
  void check_rule_success(const Rule& rule,
                          const string& input,
                          const typename Rule::attribute_type& expected_value)
  {
    using boost::spirit::x3::phrase_parse;
    using boost::spirit::x3::space;

    typename Rule::attribute_type result;
    auto first = input.begin();
    auto last = input.end();
    bool success = phrase_parse(first, last,
                                rule,
                                space,
                                result);

    const string rule_name = rule.name;
    check(success, "Rule " + rule_name + " parsed input succesfully; " + input);
    check(first == last, "Rule " + rule_name + " matched complete input: " + input);
    check(result == expected_value, "Rule " + rule_name + " matched expected result for input: " + input);
    if constexpr(std::is_same_v<typename Rule::attribute_type, unsigned char>)
      core::debug_print("result: ", +result, '\n');
    else
      core::debug_print("result: ", result, '\n');
  }

  template<typename Rule>
  void check_rule_failure(const Rule& rule,
                          const string& input)
  {
    using boost::spirit::x3::phrase_parse;
    using boost::spirit::x3::space;

    typename Rule::attribute_type result;
    auto first = input.begin();
    auto last = input.end();
    bool success = phrase_parse(first, last,
                                rule,
                                space,
                                result);

    const string rule_name = rule.name;
    bool failure = !success || first != last;
    check(failure, "Rule " + rule_name + " parsed input unsuccesfully: " + input);
    if constexpr(std::is_same_v<typename Rule::attribute_type, unsigned char>)
      core::debug_print("result: ", +result, '\n');
    else
      core::debug_print("result: ", result, '\n');
  }
}
