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
 * Key
 * Does not include the any key.
 * Keys are mapped to their ASCII values where possible.
 */

#ifndef SKUI_GUI_INPUT_KEY_H
#define SKUI_GUI_INPUT_KEY_H

namespace skui
{
  namespace gui
  {
    enum class key
    {
      // ASCII codes
      backspace = 8,
      tab = 9, horizontal_tab = tab,
      newline = 10,
      vertical_tab = 11,
      carriage_return = 13, return_key = carriage_return,
      escape = 27,
      space = 32,
      exclamation_point = 33,
      double_quote = 34,
      hash = 35, number_sign = hash,
      dollar_sign = 36,
      percent = 37,
      ampersand = 38,
      single_quote = 39, quote = single_quote,
      left_parenthesis = 40,
      right_parenthesis = 41,
      asterisk = 42,
      plus = 43,
      comma = 44,
      dash = 45, minus = dash,
      period = 46, full_stop = 46,
      slash = 47, forward_slash = slash,
      zero = 48,
      one,
      two,
      three,
      four,
      five,
      six,
      seven,
      eight,
      nine,
      colon = 58,
      semicolon = 59,
      less_than = 60,
      equals = 61,
      greater_than = 62,
      question_mark = 63,
      at = 64,
      A = 65,
      B,
      C,
      D,
      E,
      F,
      G,
      H,
      I,
      J,
      K,
      L,
      M,
      N,
      O,
      P,
      Q,
      R,
      S,
      T,
      U,
      V,
      W,
      X,
      Y,
      Z,
      left_bracket = 91,
      backslash = 92,
      right_bracket = 93,
      hat = 94,
      underscore = 95,
      backtick = 96,
      a = 97,
      b,
      c,
      d,
      e,
      f,
      g,
      h,
      i,
      j,
      k,
      l,
      m,
      n,
      o,
      p,
      q,
      r,
      s,
      t,
      u,
      v,
      w,
      x,
      y,
      z,
      left_curly_brace = 123,
      pipe = 124,
      right_curly_brace = 125,
      tilde = 126,
      delete_key = 127,

      // Non-ASCII keys
      up,
      down,
      left,
      right,

      shift_left,
      shift_right,
      control_left,
      control_right,
      alt_left,
      alt_right, alt_gr = alt_right,
      caps_lock,
      insert,
      home,
      end,
      page_down,
      page_up,
      pause, break_key = pause,
      F1,
      F2,
      F3,
      F4,
      F5,
      F6,
      F7,
      F8,
      F9,
      F10,
      F11,
      F12,

      // Numeric keypad
      numpad_up,
      numpad_down,
      numpad_left,
      numpad_right,
      numpad_1,
      numpad_2,
      numpad_3,
      numpad_4,
      numpad_5,
      numpad_6,
      numpad_7,
      numpad_8,
      numpad_9,
      numpad_0,

      volume_down,
      volume_up,

      // Media controls
      media_play,
      media_stop,
      media_pause,
      media_previous,
      media_next,
      media_record,
      media_playpause
    };
  }
}
#endif
