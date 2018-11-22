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
 * Color, stored as RGBA.
 */

#ifndef SKUI_CSS_COLOR_H
#define SKUI_CSS_COLOR_H

#include <core/utility.h++>

#include <cstdint>

namespace skui::css
{
  class color
  {
  public:
    color()
      : color{0,0,0,0}
    {}
    explicit constexpr color(std::uint8_t red,
                             std::uint8_t green,
                             std::uint8_t blue,
                             std::uint8_t alpha = 255)
      : red{red}
      , green{green}
      , blue{blue}
      , alpha{alpha}
    {}
    explicit constexpr color(std::uint32_t argb)
      : red{static_cast<std::uint8_t>(argb >> 24)}
      , green{static_cast<std::uint8_t>(argb >> 16)}
      , blue{static_cast<std::uint8_t>(argb >> 8)}
      , alpha{static_cast<std::uint8_t>(argb)}
    {}

    explicit constexpr operator std::uint32_t() const
    {
      return static_cast<std::uint32_t>(red << 24 | green << 16 | blue << 8 | alpha);
    }

    std::uint8_t red;
    std::uint8_t green;
    std::uint8_t blue;
    std::uint8_t alpha;
  };

  constexpr bool operator==(const color& left, const color& right)
  {
    return std::uint32_t(left) == std::uint32_t(right);
  }
  constexpr bool operator!=(const color& left, const color& right)
  {
    return std::uint32_t(left) != std::uint32_t(right);
  }

  constexpr color operator+(const color& left, const color& right)
  {
    const auto alpha = left.alpha + right.alpha*(255-left.alpha);
    return color{static_cast<std::uint8_t>((left.alpha*left.red + right.alpha*right.red*(255-left.alpha))/alpha),
                 static_cast<std::uint8_t>((left.alpha*left.green + right.alpha*right.green*(255-left.alpha))/alpha),
                 static_cast<std::uint8_t>((left.alpha*left.blue + right.alpha*right.blue*(255-left.alpha))/alpha),
                 static_cast<std::uint8_t>(alpha)};
  }

  constexpr color semi_transparent(const color& color)
  {
    return css::color{ color.red, color.green, color.blue, static_cast<std::uint8_t>(color.alpha / 2)};
  }

  inline std::ostream& operator<<(std::ostream& os, const color& color)
  {
    core::ostream_format_keeper keeper(os);

    return os << std::hex << std::uint32_t(color) << '\n';
  }

  namespace colors
  {
    static constexpr color transparent {0, 0, 0, 0};

    static constexpr color alice_blue              {0xF0F8FFFF};
    static constexpr color antique_white           {0xFAEBD7FF};
    static constexpr color aqua                    {0X00FFFFFF};
    static constexpr color aquamarine              {0X7FFFD4FF};
    static constexpr color azure                   {0xF0FFFFFF};
    static constexpr color beige                   {0xF5F5DCFF};
    static constexpr color bisque                  {0xFFE4C4FF};
    static constexpr color black                   {0x000000FF};
    static constexpr color blanched_almond         {0xFFEBCDFF};
    static constexpr color blue                    {0x0000FFFF};
    static constexpr color blue_violet             {0x8A2BE2FF};
    static constexpr color brown                   {0xA52A2AFF};
    static constexpr color burly_wood              {0xDEB887FF};
    static constexpr color cadet_blue              {0x5F9EA0FF};
    static constexpr color chartreuse              {0x7FFF00FF};
    static constexpr color chocolate               {0xD2691EFF};
    static constexpr color coral                   {0xFF7F50FF};
    static constexpr color cornflower_blue         {0x6495EDFF};
    static constexpr color cornsilk                {0xFFF8DCFF};
    static constexpr color crimson                 {0xDC143CFF};
    static constexpr color cyan                    {0x00FFFFFF};
    static constexpr color dark_blue               {0x00008BFF};
    static constexpr color dark_cyan               {0x008B8BFF};
    static constexpr color dark_golden_rod         {0xB8860BFF};
    static constexpr color dark_gray               {0xA9A9A9FF};
    static constexpr color dark_grey               {0xA9A9A9FF};
    static constexpr color dark_green              {0x006400FF};
    static constexpr color dark_khaki              {0xBDB76BFF};
    static constexpr color dark_magenta            {0x8B008BFF};
    static constexpr color dark_olive_green        {0x556B2FFF};
    static constexpr color dark_orange             {0xFF8C00FF};
    static constexpr color dark_orchid             {0x9932CCFF};
    static constexpr color dark_red                {0x8B0000FF};
    static constexpr color dark_salmon             {0xE9967AFF};
    static constexpr color dark_sea_green          {0x8FBC8FFF};
    static constexpr color dark_slate_blue         {0x483D8BFF};
    static constexpr color dark_slate_gray         {0x2F4F4FFF};
    static constexpr color dark_slate_grey         {0x2F4F4FFF};
    static constexpr color dark_turquoise          {0x00CED1FF};
    static constexpr color dark_violet             {0x9400D3FF};
    static constexpr color deep_pink               {0xFF1493FF};
    static constexpr color deep_sky_blue           {0x00BFFFFF};
    static constexpr color dim_gray                {0x696969FF};
    static constexpr color dim_grey                {0x696969FF};
    static constexpr color dodger_blue             {0x1E90FFFF};
    static constexpr color fire_brick              {0xB22222FF};
    static constexpr color floral_white            {0xFFFAF0FF};
    static constexpr color forest_green            {0x228B22FF};
    static constexpr color fuchsia                 {0xFF00FFFF};
    static constexpr color gainsboro               {0xDCDCDCFF};
    static constexpr color ghost_white             {0xF8F8FFFF};
    static constexpr color gold                    {0xFFD700FF};
    static constexpr color golden_rod              {0xDAA520FF};
    static constexpr color gray                    {0x808080FF};
    static constexpr color grey                    {0x808080FF};
    static constexpr color green                   {0x008000FF};
    static constexpr color green_yellow            {0xADFF2FFF};
    static constexpr color honey_dew               {0xF0FFF0FF};
    static constexpr color hot_pink                {0xFF69B4FF};
    static constexpr color indian_red              {0xCD5C5CFF};
    static constexpr color indigo                  {0x4B0082FF};
    static constexpr color ivory                   {0xFFFFF0FF};
    static constexpr color khaki                   {0xF0E68CFF};
    static constexpr color lavender                {0xE6E6FAFF};
    static constexpr color lavender_blush          {0xFFF0F5FF};
    static constexpr color lawn_green              {0x7CFC00FF};
    static constexpr color lemon_chiffon           {0xFFFACDFF};
    static constexpr color light_blue              {0xADD8E6FF};
    static constexpr color light_coral             {0xF08080FF};
    static constexpr color light_cyan              {0xE0FFFFFF};
    static constexpr color light_golden_rod_yellow {0xFAFAD2FF};
    static constexpr color light_gray              {0xD3D3D3FF};
    static constexpr color light_grey              {0xD3D3D3FF};
    static constexpr color light_green             {0x90EE90FF};
    static constexpr color light_pink              {0xFFB6C1FF};
    static constexpr color light_salmon            {0xFFA07AFF};
    static constexpr color light_sea_green         {0x20B2AAFF};
    static constexpr color light_sky_blue          {0x87CEFAFF};
    static constexpr color light_slate_gray        {0x778899FF};
    static constexpr color light_slate_grey        {0x778899FF};
    static constexpr color light_steel_blue        {0xB0C4DEFF};
    static constexpr color light_yellow            {0xFFFFE0FF};
    static constexpr color lime                    {0x00FF00FF};
    static constexpr color lime_green              {0x32CD32FF};
    static constexpr color linen                   {0xFAF0E6FF};
    static constexpr color magenta                 {0xFF00FFFF};
    static constexpr color maroon                  {0x800000FF};
    static constexpr color medium_aqua_marine      {0x66CDAAFF};
    static constexpr color medium_blue             {0x0000CDFF};
    static constexpr color medium_orchid           {0XBA55D3FF};
    static constexpr color medium_purple           {0x9370DBFF};
    static constexpr color medium_sea_green        {0x3CB371FF};
    static constexpr color medium_slate_blue       {0x7B68EEFF};
    static constexpr color medium_spring_green     {0x00FA9AFF};
    static constexpr color medium_turqoise         {0x48D1CCFF};
    static constexpr color medium_violet_red       {0xC71585FF};
    static constexpr color midnight_blue           {0x191970FF};
    static constexpr color mint_cream              {0xF5FFFAFF};
    static constexpr color misty_rose              {0xFFE4E1FF};
    static constexpr color moccasin                {0xFFE4B5FF};
    static constexpr color navajo_white            {0xFFDEADFF};
    static constexpr color navy                    {0x000080FF};
    static constexpr color old_lace                {0xFDF5E6FF};
    static constexpr color olive                   {0x808000FF};
    static constexpr color olive_drab              {0x6B8E23FF};
    static constexpr color orange                  {0xFFA500FF};
    static constexpr color orange_red              {0xFF4500FF};
    static constexpr color orchid                  {0xDA70D6FF};
    static constexpr color pale_golden_rod         {0xEEE8AAFF};
    static constexpr color pale_green              {0x98FB98FF};
    static constexpr color pale_turquoise          {0xAFEEEEFF};
    static constexpr color pale_violet_red         {0xDB7093FF};
    static constexpr color papaya_whip             {0xFFEFD5FF};
    static constexpr color peach_puff              {0xFFC0CBFF};
    static constexpr color peru                    {0xCD853FFF};
    static constexpr color pink                    {0xFFC0CBFF};
    static constexpr color plum                    {0xDDA0DDFF};
    static constexpr color powder_blue             {0xB0E0E6FF};
    static constexpr color purple                  {0x800080FF};
    static constexpr color rebecca_purple          {0x663399FF};
    static constexpr color red                     {0xFF0000FF};
    static constexpr color rosy_brown              {0xBC8F8FFF};
    static constexpr color royal_blue              {0x4169E1FF};
    static constexpr color saddle_brown            {0x8B4513FF};
    static constexpr color salmon                  {0xFA8072FF};
    static constexpr color sandy_brown             {0xF4A460FF};
    static constexpr color sea_green               {0x2E8B57FF};
    static constexpr color sea_shell               {0xFFF5EEFF};
    static constexpr color sienna                  {0xA0522DFF};
    static constexpr color silver                  {0xC0C0C0FF};
    static constexpr color sky_blue                {0x87CEEBFF};
    static constexpr color slate_blue              {0x6A5ACDFF};
    static constexpr color slate_gray              {0x708090FF};
    static constexpr color slate_grey              {0x708090FF};
    static constexpr color snow                    {0xFFFAFAFF};
    static constexpr color spring_green            {0x00FF7FFF};
    static constexpr color steel_blue              {0x4682B4FF};
    static constexpr color tan                     {0xD2B48CFF};
    static constexpr color teal                    {0x008080FF};
    static constexpr color thistle                 {0xD8BFD8FF};
    static constexpr color tomato                  {0xFF6347FF};
    static constexpr color turquoise               {0x40E0D0FF};
    static constexpr color violet                  {0xEE82EEFF};
    static constexpr color wheat                   {0xF5DEB3FF};
    static constexpr color white                   {0xFFFFFFFF};
    static constexpr color white_smoke             {0xF5F5F5FF};
    static constexpr color yellow                  {0xFFFF00FF};
    static constexpr color yellow_green            {0x9ACD32FF};
  }
}

#endif
