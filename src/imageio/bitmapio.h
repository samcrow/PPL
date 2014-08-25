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

#ifndef BITMAPIO_H
#define BITMAPIO_H
#include "../namespaces.h"
#include <string>

namespace PPLNAMESPACE {

struct IMAGEDATA;

class BitmapIO
{
public:
    
    static void read(IMAGEDATA& image, const std::string& file_name);
    
private:
    
    
#pragma pack(push, ident, 2)

    struct BMPFILEHEADER
    {
        int16_t   bfType;
        int32_t   bfSize;
        int16_t   bfReserved1;
        int16_t   bfReserved2;
        int32_t    bfOffBits;
    };

    struct BMPINFOHEADER
    {
        int32_t    biSize;
        int32_t    biWidth;
        int32_t    biHeight;
        int16_t   biPlanes;
        int16_t   biBitCount;
        int32_t    biCompression;
        int32_t    biSizeImage;
        int32_t    biXPelsPerMeter;
        int32_t    biYPelsPerMeter;
        int32_t    biClrUsed;
        int32_t    biClrImportant;
    };


#pragma pack(pop, ident)


    // Endian swap functions
    static void SwapEndian(int16_t *Data);
    static void SwapEndian(int32_t *Data);
#if APL && defined(__ppc__)
    static int32_t Endian(int32_t Data);
    static int16_t Endian(int16_t Data);
#endif
    
    
    BitmapIO() {}
};

}
#endif // BITMAPIO_H
