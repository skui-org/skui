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

#include "graphics/skia_gl_canvas.h++"

#include <GrBackendSurface.h>
#include <GrContext.h>
#include <GrGLInterface.h>

#include <SkCanvas.h>
#include <SkColor.h>
#include <SkGradientShader.h>
#include <SkSurface.h>

#ifdef _WIN32
#include <windows.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <GL/glext.h>

namespace skui
{
  namespace graphics
  {
    namespace
    {
      std::unique_ptr<SkSurface> create_gl_surface(const pixel_size& size,
                                                   const GrGLInterface& gl_interface,
                                                   GrContext& gr_context)
      {
        // Wrap the frame buffer object attached to the screen in a Skia render target so Skia can
        // render to it
        GrGLFramebufferInfo framebuffer_info;
        GrGLint buffer;
        gl_interface.fFunctions.fGetIntegerv(GL_FRAMEBUFFER_BINDING, &buffer);
        framebuffer_info.fFBOID = static_cast<GrGLuint>(buffer);
        framebuffer_info.fFormat = GL_RGBA8;

        GrBackendRenderTarget render_target(static_cast<int>(size.width),
                                            static_cast<int>(size.height),
                                            0,
                                            8,
                                            framebuffer_info);

        // setup SkSurface
        SkSurfaceProps props(SkSurfaceProps::kUseDeviceIndependentFonts_Flag, // distance field text
                              SkSurfaceProps::kLegacyFontHost_InitType);

        return std::unique_ptr<SkSurface>(SkSurface::MakeFromBackendRenderTarget(&gr_context,
                                                                                 render_target,
                                                                                 kBottomLeft_GrSurfaceOrigin,
                                                                                 kRGBA_8888_SkColorType,
                                                                                 nullptr,
                                                                                 &props).release());
      }
    }

    skia_gl_canvas::skia_gl_canvas(const pixel_size& size,
                                   const GrGLInterface* gr_gl_interface,
                                   canvas_flags flags)
      : skia_canvas(flags)
      , gr_context(GrContext::MakeGL(sk_sp<const GrGLInterface>(gr_gl_interface)).release())
    {
      SkASSERT(gr_context);

      gr_gl_interface->ref();
      surface = create_gl_surface(size, *gr_gl_interface, *gr_context);
    }

    skia_gl_canvas::~skia_gl_canvas()
    {
      surface.reset();
    }
  }
}
