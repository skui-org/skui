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

#ifndef SKUI_GRAPHICS_COLOR_H
#define SKUI_GRAPHICS_COLOR_H

#include <core/utility.h++>

#include <cstdint>

namespace skui
{
  namespace graphics
  {
    class color
    {
    public:
      explicit constexpr color(std::uint8_t red,
                               std::uint8_t green,
                               std::uint8_t blue,
                               std::uint8_t alpha = 1)
        : alpha{alpha}
        , red{red}
        , green{green}
        , blue{blue}
      {}
      explicit constexpr color(std::uint32_t argb)
        : alpha{static_cast<std::uint8_t>(argb >> 24)}
        , red{static_cast<std::uint8_t>(argb >> 16)}
        , green{static_cast<std::uint8_t>(argb >> 8)}
        , blue{static_cast<std::uint8_t>(argb)}
      {}

      explicit constexpr operator std::uint32_t() const
      {
        return static_cast<std::uint32_t>(alpha << 24 | red << 16 | green << 8 | blue);
      }

      std::uint8_t alpha;
      std::uint8_t red;
      std::uint8_t green;
      std::uint8_t blue;
    };

    inline std::ostream& operator<<(std::ostream& os, const color& color)
    {
      core::ostream_format_keeper keeper(os);

      return os << std::hex << std::uint32_t(color) << '\n';
    }

    namespace colors
    {
      static constexpr color transparent {0, 0, 0, 0};

      static constexpr color alice_blue              {0xFFF0F8FF};
      static constexpr color antique_white           {0xFFFAEBD7};
      static constexpr color aqua                    {0XFF00FFFF};
      static constexpr color aquamarine              {0XFF7FFFD4};
      static constexpr color azure                   {0xFFF0FFFF};
      static constexpr color beige                   {0xFFF5F5DC};
      static constexpr color bisque                  {0xFFFFE4C4};
      static constexpr color black                   {0xFF000000};
      static constexpr color blanched_almond         {0xFFFFEBCD};
      static constexpr color blue                    {0xFF0000FF};
      static constexpr color blue_violet             {0xFF8A2BE2};
      static constexpr color brown                   {0xFFA52A2A};
      static constexpr color burly_wood              {0xFFDEB887};
      static constexpr color cadet_blue              {0xFF5F9EA0};
      static constexpr color chartreuse              {0xFF7FFF00};
      static constexpr color chocolate               {0xFFD2691E};
      static constexpr color coral                   {0xFFFF7F50};
      static constexpr color cornflower_blue         {0xFF6495ED};
      static constexpr color cornsilk                {0xFFFFF8DC};
      static constexpr color crimson                 {0xFFDC143C};
      static constexpr color cyan                    {0xFF00FFFF};
      static constexpr color dark_blue               {0xFF00008B};
      static constexpr color dark_cyan               {0xFF008B8B};
      static constexpr color dark_golden_rod         {0xFFB8860B};
      static constexpr color dark_gray               {0xFFA9A9A9};
      static constexpr color dark_grey               {0xFFA9A9A9};
      static constexpr color dark_green              {0xFF006400};
      static constexpr color dark_khaki              {0xFFBDB76B};
      static constexpr color dark_magenta            {0xFF8B008B};
      static constexpr color dark_olive_green        {0xFF556B2F};
      static constexpr color dark_orange             {0xFFFF8C00};
      static constexpr color dark_orchid             {0xFF9932CC};
      static constexpr color dark_red                {0xFF8B0000};
      static constexpr color dark_salmon             {0xFFE9967A};
      static constexpr color dark_sea_green          {0xFF8FBC8F};
      static constexpr color dark_slate_blue         {0xFF483D8B};
      static constexpr color dark_slate_gray         {0xFF2F4F4F};
      static constexpr color dark_slate_grey         {0xFF2F4F4F};
      static constexpr color dark_turquoise          {0xFF00CED1};
      static constexpr color dark_violet             {0xFF9400D3};
      static constexpr color deep_pink               {0xFFFF1493};
      static constexpr color deep_sky_blue           {0xFF00BFFF};
      static constexpr color dim_gray                {0xFF696969};
      static constexpr color dim_grey                {0xFF696969};
      static constexpr color dodger_blue             {0xFF1E90FF};
      static constexpr color fire_brick              {0xFFB22222};
      static constexpr color floral_white            {0xFFFFFAF0};
      static constexpr color forest_green            {0xFF228B22};
      static constexpr color fuchsia                 {0xFFFF00FF};
      static constexpr color gainsboro               {0xFFDCDCDC};
      static constexpr color ghost_white             {0xFFF8F8FF};
      static constexpr color gold                    {0xFFFFD700};
      static constexpr color golden_rod              {0xFFDAA520};
      static constexpr color gray                    {0xFF808080};
      static constexpr color grey                    {0xFF808080};
      static constexpr color green                   {0xFF008000};
      static constexpr color green_yellow            {0xFFADFF2F};
      static constexpr color honey_dew               {0xFFF0FFF0};
      static constexpr color hot_pink                {0xFFFF69B4};
      static constexpr color indian_red              {0xFFCD5C5C};
      static constexpr color indigo                  {0xFF4B0082};
      static constexpr color ivory                   {0xFFFFFFF0};
      static constexpr color khaki                   {0xFFF0E68C};
      static constexpr color lavender                {0xFFE6E6FA};
      static constexpr color lavender_blush          {0xFFFFF0F5};
      static constexpr color lawn_green              {0xFF7CFC00};
      static constexpr color lemon_chiffon           {0xFFFFFACD};
      static constexpr color light_blue              {0xFFADD8E6};
      static constexpr color light_coral             {0xFFF08080};
      static constexpr color light_cyan              {0xFFE0FFFF};
      static constexpr color light_golden_rod_yellow {0xFFFAFAD2};
      static constexpr color light_gray              {0xFFD3D3D3};
      static constexpr color light_grey              {0xFFD3D3D3};
      static constexpr color light_green             {0xFF90EE90};
      static constexpr color light_pink              {0xFFFFB6C1};
      static constexpr color light_salmon            {0xFFFFA07A};
      static constexpr color light_sea_green         {0xFF20B2AA};
      static constexpr color light_sky_blue          {0xFF87CEFA};
      static constexpr color light_slate_gray        {0xFF778899};
      static constexpr color light_slate_grey        {0xFF778899};
      static constexpr color light_steel_blue        {0xFFB0C4DE};
      static constexpr color light_yellow            {0xFFFFFFE0};
      static constexpr color lime                    {0xFF00FF00};
      static constexpr color lime_green              {0xFF32CD32};
      static constexpr color linen                   {0xFFFAF0E6};
      static constexpr color magenta                 {0xFFFF00FF};
      static constexpr color maroon                  {0xFF800000};
      static constexpr color medium_aqua_marine      {0xFF66CDAA};
      static constexpr color medium_blue             {0xFF0000CD};
      static constexpr color medium_orchid           {0XFFBA55D3};
      static constexpr color medium_purple           {0xFF9370DB};
      static constexpr color medium_sea_green        {0xFF3CB371};
      static constexpr color medium_slate_blue       {0xFF7B68EE};
      static constexpr color medium_spring_green     {0xFF00FA9A};
      static constexpr color medium_turqoise         {0xFF48D1CC};
      static constexpr color medium_violet_red       {0xFFC71585};
      static constexpr color midnight_blue           {0xFF191970};
      static constexpr color mint_cream              {0xFFF5FFFA};
      static constexpr color misty_rose              {0xFFFFE4E1};
      static constexpr color moccasin                {0xFFFFE4B5};
      static constexpr color navajo_white            {0xFFFFDEAD};
      static constexpr color navy                    {0xFF000080};
      static constexpr color old_lace                {0xFFFDF5E6};
      static constexpr color olive                   {0xFF808000};
      static constexpr color olive_drab              {0xFF6B8E23};
      static constexpr color orange                  {0xFFFFA500};
      static constexpr color orange_red              {0xFFFF4500};
      static constexpr color orchid                  {0xFFDA70D6};
      static constexpr color pale_golden_rod         {0xFFEEE8AA};
      static constexpr color pale_green              {0xFF98FB98};
      static constexpr color pale_turquoise          {0xFFAFEEEE};
      static constexpr color pale_violet_red         {0xFFDB7093};
      static constexpr color papaya_whip             {0xFFFFEFD5};
      static constexpr color peach_puff              {0xFFFFC0CB};
      static constexpr color peru                    {0xFFCD853F};
      static constexpr color pink                    {0xFFFFC0CB};
      static constexpr color plum                    {0xFFDDA0DD};
      static constexpr color powder_blue             {0xFFB0E0E6};
      static constexpr color purple                  {0xFF800080};
      static constexpr color rebecca_purple          {0xFF663399};
      static constexpr color red                     {0xFFFF0000};
      static constexpr color rosy_brown              {0xFFBC8F8F};
      static constexpr color royal_blue              {0xFF4169E1};
      static constexpr color saddle_brown            {0xFF8B4513};
      static constexpr color salmon                  {0xFFFA8072};
      static constexpr color sandy_brown             {0xFFF4A460};
      static constexpr color sea_green               {0xFF2E8B57};
      static constexpr color sea_shell               {0xFFFFF5EE};
      static constexpr color sienna                  {0xFFA0522D};
      static constexpr color silver                  {0xFFC0C0C0};
      static constexpr color sky_blue                {0xFF87CEEB};
      static constexpr color slate_blue              {0xFF6A5ACD};
      static constexpr color slate_gray              {0xFF708090};
      static constexpr color slate_grey              {0xFF708090};
      static constexpr color snow                    {0xFFFFFAFA};
      static constexpr color spring_green            {0xFF00FF7F};
      static constexpr color steel_blue              {0xFF4682B4};
      static constexpr color tan                     {0xFFD2B48C};
      static constexpr color teal                    {0xFF008080};
      static constexpr color thistle                 {0xFFD8BFD8};
      static constexpr color tomato                  {0xFFFF6347};
      static constexpr color turquoise               {0xFF40E0D0};
      static constexpr color violet                  {0xFFEE82EE};
      static constexpr color wheat                   {0xFFF5DEB3};
      static constexpr color white                   {0xFFFFFFFF};
      static constexpr color white_smoke             {0xFFF5F5F5};
      static constexpr color yellow                  {0xFFFFFF00};
      static constexpr color yellow_green            {0xFF9ACD32};
    }
  }
}

#endif
