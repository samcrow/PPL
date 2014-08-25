#ifndef IMAGEDATA_H
#define IMAGEDATA_H
#include <vector>
#include "../namespaces.h"

namespace PPLNAMESPACE {

/**
 * @brief The IMAGEDATA struct contains an image.
 */
struct IMAGEDATA
{
    std::vector<unsigned char> pData;
    int32_t    Width;
    int32_t    Height;
    int32_t    Padding;
    int16_t   Channels;
    unsigned int bpp;
};

}
#endif // IMAGEDATA_H
