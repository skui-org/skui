#ifndef SKUI_CSS_GRAMMAR_AS_H
#define SKUI_CSS_GRAMMAR_AS_H

#include <boost/spirit/home/x3.hpp>

namespace skui::css::grammar
{
  namespace x3 = boost::spirit::x3;

  template<typename AttributeType>
  inline auto as = [](auto&& parser) { return x3::rule<struct _, AttributeType>{} %= as_parser(parser); };
}
#endif
