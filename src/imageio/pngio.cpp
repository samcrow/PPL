// Copyright (c) 2014, Sam Crow samcrow@uw.edu
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

#include "pngio.h"
#include <png.h>
#include <cstdio>
#include <stdexcept>
#include <memory>
#include <iostream>
#include "imagedata.h"

namespace PPLNAMESPACE {

void PngIO::read(IMAGEDATA& image, GLuint& type, const std::string& path) {
    
    FILE* file = std::fopen(path.c_str(), "rb");
    
    if(file == 0) {
        throw std::runtime_error("Failed to open image file "+path);
    }
    
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                                 NULL, NULL, NULL);
    
    if(png_ptr == 0) {
        fclose(file);
        throw std::runtime_error("Failed to create PNG data structure");
    }
    
    png_infop info_ptr = png_create_info_struct(png_ptr);
    
    if(info_ptr == 0) {
        fclose(file);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        throw std::runtime_error("Failed to create PNG info data structure");
    }
    
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(file);
        /* If we get here, we had a
             * problem reading the file */
        throw std::runtime_error("Problem reading image file "+path);
    }
    
    png_init_io(png_ptr, file);
    
    unsigned int sig_read = 0;
    png_set_sig_bytes(png_ptr, sig_read);
    
    // Read
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
    
    png_uint_32 width, height;
    int color_type, interlace_type;
    int bit_depth;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                 &interlace_type, NULL, NULL);
    
    // Set image parameters
    image.Width = width;
    image.Height = height;
    image.bpp = bit_depth;
    
    // Process color type
    switch(color_type) {
    
    case PNG_COLOR_TYPE_RGB:
        type = GL_RGB;
        break;
        
    case PNG_COLOR_TYPE_RGB_ALPHA:
        type = GL_RGBA;
        break;
        
    default:
        // Not supported
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(file);
        throw std::runtime_error("Unsupported PNG image format: Not RGB or RGB+alpha in file "+path);
    }
    
    
    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    image.pData.reserve(row_bytes * image.Height);
    unsigned char* dataPtr1 = & image.pData[0];
    unsigned char** outData = & dataPtr1;
 
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
 
    for (int i = 0; i < image.Height; i++) {
        // note that png is ordered top to
        // bottom, but OpenGL expect it bottom to top
        // so the order or swapped
        memcpy(*outData+(row_bytes * (image.Height-1-i)), row_pointers[i], row_bytes);
    }
 
    /* Clean up after the read,
     * and free any memory allocated */
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
 
    /* Close the file */
    fclose(file);
 
    
}

}
