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

#include "bitmapio.h"
#include "imagedata.h"
#include <stdexcept>
#include <fstream>

namespace PPLNAMESPACE {

void BitmapIO::read(IMAGEDATA& image, const std::string& file_name) {
    BMPFILEHEADER header;
    BMPINFOHEADER image_info;
    int32_t padding;

    std::ifstream fs(file_name.c_str(), std::ios_base::in | std::ios_base::binary);
    if (!fs)
        throw std::runtime_error("File could not be opened: "+file_name);
    fs.read(reinterpret_cast<char*>(&header), sizeof(header));
    if (!fs)
        throw std::runtime_error("Bitmap header could not be read: "+file_name);
    fs.read(reinterpret_cast<char*>(&image_info), sizeof(image_info));
    if (!fs)
        throw std::runtime_error("Image info could not be read: "+file_name);
  #if APL && defined(__ppc__)
    SwapEndian(&header.bfSize);
    SwapEndian(&header.bfOffBits);

    SwapEndian(&image_info.biWidth);
    SwapEndian(&image_info.biHeight);
    SwapEndian(&image_info.biBitCount);

    if (!(((header.bfType & 0xff) == 'M') &&
          (((header.bfType >> 8) & 0xff) == 'B') &&
  #else
    if (!(((header.bfType & 0xff) == 'B') &&
          (((header.bfType >> 8) & 0xff) == 'M') &&
  #endif
          (image_info.biBitCount == 24) &&
          (image_info.biWidth > 0) &&
          (image_info.biHeight > 0)))
        throw std::runtime_error("Image is not a bitmap: "+file_name);
    if (!((header.bfSize + image_info.biSize - header.bfOffBits) >= (image_info.biWidth * image_info.biHeight * 3)))
        throw std::runtime_error("Image size mismatch: "+file_name);
    padding = (image_info.biWidth * 3 + 3) & ~3;
    padding -= image_info.biWidth * 3;

    image.Width = image_info.biWidth;
    image.Height = image_info.biHeight;
    image.Padding = padding;

    /// Allocate memory for the actual image.
    image.Channels = 3;
    std::size_t bytes = image_info.biWidth * image_info.biHeight * image.Channels + image_info.biHeight * padding;
    try {
        image.pData.resize(bytes);

        fs.read(reinterpret_cast<char*>(&image.pData[0]), bytes);


    } catch (std::bad_alloc&)
    {
        throw std::runtime_error("Could not allocate memory for bitmap data");
    }
    
}

#if APL && defined(__ppc__)
int16_t BitmapIO::Endian(int16_t Data)
{
    unsigned char *pBuffer = (unsigned char *)&Data;
    int16_t Result = (int16_t)(pBuffer[0] & 0xff) + ( (int16_t)(pBuffer[1] & 0xff) << 8) ;
    return(Result);
}

int32_t BitmapIO::Endian(int32_t Data)
{
    unsigned char *pBuffer = (unsigned char *)&Data;

    int32_t Result =     (int32_t)(pBuffer[0] & 0xff)
            + ( (int32_t)(pBuffer[1] & 0xff) << 8)
            + ( (int32_t)(pBuffer[2] & 0xff) << 16)
            + ( (int32_t)(pBuffer[3] & 0xff) << 24);

    return(Result);
}

void BitmapIO::SwapEndian(int16_t *Data)
{
    *Data = Endian(*Data);
}

void BitmapIO::SwapEndian(int32_t *Data)
{
    *Data = Endian(*Data);
}
#else
/// Only the ppc mac needs these so dummy functions for x86.
void BitmapIO::SwapEndian(int16_t *){}
void BitmapIO::SwapEndian(int32_t *){}
#endif

}
