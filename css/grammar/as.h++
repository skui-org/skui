#ifndef SKUI_CSS_GRAMMAR_AS_H
#define SKUI_CSS_GRAMMAR_AS_H

#include <boost/spirit/home/x3.hpp>

namespace skui::css::grammar
{
  using namespace boost::spirit::x3;

  template<typename AttributeType>
  inline auto as = [](auto&& parser) { return rule<struct _, AttributeType>{} %= as_parser(parser); };
}
#endif
