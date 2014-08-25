#ifndef TARGAIO_H
#define TARGAIO_H
#include "../namespaces.h"
#include <string>


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

namespace PPLNAMESPACE {

struct IMAGEDATA;

/**
 * @brief The TargaIO class reads TGA (TARGA) images into OpenGL textures
 */
class TargaIO
{
public:
    
    /**
     * @brief Reads an image from the file at the given path and stores it
     * in the given image data structure
     * @param image
     * @param type This value is set to the type of the image after it is read
     * @param path
     */
    static void read(IMAGEDATA& image, GLuint& type, const std::string& path);
    
private:
    TargaIO() {}
};

}
#endif // TARGAIO_H
