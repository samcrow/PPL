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
