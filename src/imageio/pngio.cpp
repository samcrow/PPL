#include "pngio.h"
#include <png.h>
#include <cstdio>
#include <stdexcept>
#include <memory>
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
        
    case PNG_COLOR_TYPE_RGBA:
        type = GL_RGBA;
    
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
