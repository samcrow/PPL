// Copyright (c) 2013, Philipp Muenzel mail@philippmuenzel.de
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// The views and conclusions contained in the software and documentation are those
// of the authors and should not be interpreted as representing official policies,
// either expressed or implied, of the FreeBSD Project.

#include <fstream>
#include <stdexcept>
#include <cstring>
#include "texture.h"
#ifndef BUILD_FOR_STANDALONE
#include "XPLMUtilities.h"
#include "XPLMGraphics.h"
#endif

#if IBM
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#elif LIN
#include <GL/gl.h>
#include <GL/glu.h>
#else
#if __GNUC__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <gl.h>
#include <glu.h>
#endif
#endif

#include "imageio/targaio.h"
#include "imageio/bitmapio.h"
#ifdef PPL_ENABLE_PNG
#include "imageio/pngio.h"
#endif

using namespace PPLNAMESPACE;



Texture::Texture(const std::string& file_name)
{
    if (file_name.rfind(".bmp") != std::string::npos)
    {
        BitmapIO::read(m_imagedata, file_name);
        
        swapRedBlue();


#ifdef BUILD_FOR_STANDALONE
        glGenTextures(1, (GLuint*)&m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
#else
        /// Do the opengl stuff using XPLM functions for a friendly Xplane existence.
        XPLMGenerateTextureNumbers(&m_id, 1);
        XPLMBindTexture2d(m_id, 0);
#endif


        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_imagedata.Width, m_imagedata.Height, GL_RGB, GL_UNSIGNED_BYTE, &m_imagedata.pData[0]);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        
        
    }
#ifdef PPL_ENABLE_PNG
    // PNG
    else if (file_name.rfind(".png") != std::string::npos) {
        GLuint type;
        PngIO::read(m_imagedata, type, file_name);
        
#ifdef BUILD_FOR_STANDALONE
        glGenTextures(1, (GLuint*)&m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
#else
        /// Do the opengl stuff using XPLM functions for a friendly Xplane existence.
        XPLMGenerateTextureNumbers(&m_id, 1);
        XPLMBindTexture2d(m_id, 0);
#endif
        glTexImage2D(GL_TEXTURE_2D, 0, type, m_imagedata.Width, m_imagedata.Height, 0, type, GL_UNSIGNED_BYTE, &m_imagedata.pData[0]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        
    }
#endif
    else if (file_name.rfind(".tga") != std::string::npos)
    {
        GLuint type;
        
        TargaIO::read(m_imagedata, type, file_name);
        
#ifdef BUILD_FOR_STANDALONE
        glGenTextures(1, (GLuint*)&m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
#else
        /// Do the opengl stuff using XPLM functions for a friendly Xplane existence.
        XPLMGenerateTextureNumbers(&m_id, 1);
        XPLMBindTexture2d(m_id, 0);
#endif
        glTexImage2D(GL_TEXTURE_2D, 0, type, m_imagedata.Width, m_imagedata.Height, 0, type, GL_UNSIGNED_BYTE, &m_imagedata.pData[0]);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    } else {
        throw std::runtime_error("The texture file is neither a BMP, a PNG, nor a TGA. Other file formats are not supported.");
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, (GLuint*)&m_id);
}

int Texture::id() const
{
    return m_id;
}

int Texture::width() const
{
    return m_imagedata.Width;
}

int Texture::height() const
{
    return m_imagedata.Height;
}

void Texture::swapRedBlue()
{
    int32_t x,y;

    /// Does not support 4 channels.
    if (m_imagedata.Channels == 4)
        return;

    /// Do the swap
    std::size_t i = 0;
    for (y = 0; y < m_imagedata.Height; ++y)
    {
        for (x = 0; x < m_imagedata.Width; ++x)
        {
            std::swap(m_imagedata.pData[i], m_imagedata.pData[i+2]);
            i += 3;
            if (x == (m_imagedata.Width - 1))
                i += m_imagedata.Padding;
        }
    }
}

void Texture::drawTex(float left, float top, float right, float bottom, float alpha)
{
#ifdef BUILD_FOR_STANDALONE
    glBindTexture(GL_TEXTURE_2D, m_id);
#else
    XPLMBindTexture2d(m_id, 0);
    XPLMSetGraphicsState(0,1,0,0,1,0,0);
#endif

    glColor4f(1,1,1,alpha);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glBegin(GL_QUADS);
            glTexCoord2f(1, 0.0f); glVertex2f(right, bottom);
            glTexCoord2f(0, 0.0f); glVertex2f(left, bottom);
            glTexCoord2f(0, 1.0f); glVertex2f(left, top);
            glTexCoord2f(1, 1.0f); glVertex2f(right, top);
    glEnd();

#ifndef BUILD_FOR_STANDALONE
    XPLMSetGraphicsState(0,0,0,0,1,0,0);
#endif
}

void Texture::drawColoredTex(float left, float top, float right, float bottom, float color[4])
{
#ifdef BUILD_FOR_STANDALONE
    glBindTexture(GL_TEXTURE_2D, m_id);
#else
    XPLMBindTexture2d(m_id, 0);
    XPLMSetGraphicsState(0,1,0,0,1,0,0);
#endif

    glColor4f(color[0],color[1],color[2],color[3]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glBegin(GL_QUADS);
            glTexCoord2f(1, 0.0f); glVertex2f(right, bottom);
            glTexCoord2f(0, 0.0f); glVertex2f(left, bottom);
            glTexCoord2f(0, 1.0f); glVertex2f(left, top);
            glTexCoord2f(1, 1.0f); glVertex2f(right, top);
    glEnd();

#ifndef BUILD_FOR_STANDALONE
    XPLMSetGraphicsState(0,0,0,0,1,0,0);
#endif
}
