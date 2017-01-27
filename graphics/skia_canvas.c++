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

#include "skia_canvas.h++"

#include <core/debug.h++>

#include <GL/gl.h>

#include <GrContext.h>
#include <GrGLInterface.h>

#include <SkCanvas.h>
#include <SkGradientShader.h>

namespace skui
{
  namespace graphics
  {
    namespace implementation
    {
      sk_sp<SkSurface> create_surface(const pixel_size& size,
                                      const GrGLInterface& gl_interface,
                                      GrContext& gr_context)
      {
        // Wrap the frame buffer object attached to the screen in a Skia render target so Skia can
        // render to it
        GrBackendRenderTargetDesc desc;
        desc.fWidth = static_cast<int>(size.width);
        desc.fHeight = static_cast<int>(size.height);
        desc.fConfig = kSkia8888_GrPixelConfig;
        desc.fOrigin = kBottomLeft_GrSurfaceOrigin;
        desc.fSampleCnt = 0;
        desc.fStencilBits = 8;
        GrGLint buffer;
        gl_interface.fFunctions.fGetIntegerv(GL_FRAMEBUFFER_BINDING, &buffer);
        desc.fRenderTargetHandle = buffer;
        core::debug_print("buffer: ", buffer, '\n');

        // setup SkSurface
        // To use distance field text, use commented out SkSurfaceProps instead
        SkSurfaceProps props(SkSurfaceProps::kUseDeviceIndependentFonts_Flag, // distance field text
                              SkSurfaceProps::kLegacyFontHost_InitType);

        return SkSurface::MakeFromBackendRenderTarget(&gr_context, desc, &props);
      }
    }
    skia_canvas::skia_canvas(const pixel_size& size, const GrGLInterface& gr_gl_interface)
      : gr_context(GrContext::Create(kOpenGL_GrBackend, reinterpret_cast<GrBackendContext>(&gr_gl_interface)))
      , surface(implementation::create_surface(size, gr_gl_interface, *gr_context))
    {
      SkASSERT(gr_context);
    }

    void skia_canvas::draw()
    {
      auto canvas = surface->getCanvas();

      // Clear background
      canvas->drawColor(SK_ColorWHITE);

      SkPaint paint;
      paint.setColor(SK_ColorRED);

      // Draw a rectangle with red paint
      SkRect rect = SkRect::MakeXYWH(10, 10, 128, 128);
      canvas->drawRect(rect, paint);

      // Set up a linear gradient and draw a circle
      {
          SkPoint linearPoints[] = {
                  {0, 0},
                  {300, 300}
          };
          SkColor linearColors[] = {SK_ColorGREEN, SK_ColorBLACK};

          paint.setShader(SkGradientShader::MakeLinear(
                  linearPoints, linearColors, nullptr, 2,
                  SkShader::kMirror_TileMode));
          paint.setFlags(SkPaint::kAntiAlias_Flag);

          canvas->drawCircle(200, 200, 64, paint);

          // Detach shader
          paint.setShader(nullptr);
      }

      // Draw a message with a nice black paint.
      paint.setFlags(
              SkPaint::kAntiAlias_Flag |
              SkPaint::kSubpixelText_Flag |  // ... avoid waggly text when rotating.
              SkPaint::kUnderlineText_Flag);
      paint.setColor(SK_ColorBLACK);
      paint.setTextSize(20);

      canvas->save();

      static const char message[] = "Hello World";

      // Translate and rotate
      canvas->translate(300, 300);
      SkScalar fRotationAngle = -40.f;
      if (fRotationAngle > 360) {
          fRotationAngle -= 360;
      }
      canvas->rotate(fRotationAngle);

      // Draw the text:
      canvas->drawText(message, strlen(message), 0, 0, paint);

      canvas->restore();
    }
  }
}
