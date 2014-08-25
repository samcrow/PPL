#include "targaio.h"
#include "imagedata.h"
#include <vector>
#include <stdexcept>



namespace PPLNAMESPACE {

void TargaIO::read(IMAGEDATA& image, GLuint& type, const std::string& file_name) {
    
    
    GLubyte TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};    // Uncompressed TGA Header
    GLubyte TGAcompare[12];                             // Used To Compare TGA Header
    GLubyte header[6];                                  // First 6 Useful Bytes From The Header
    GLuint  bytesPerPixel;                              // Holds Number Of Bytes Per Pixel Used In The TGA File
    GLuint  imageSize;                                  // Used To Store The Image Size When Setting Aside Ram
    GLuint  temp;                                       // Temporary Variable
    type=GL_RGBA;                                       // Set The Default GL Mode To RBGA (32 BPP)


    FILE *file = fopen(file_name.c_str(), "rb");        // Open The TGA File

    if(    file==NULL ||                                                        // Does File Even Exist?
            fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||  // Are There 12 Bytes To Read?
            memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0                || // Does The Header Match What We Want?
            fread(header,1,sizeof(header),file)!=sizeof(header))                // If So Read Next 6 Header Bytes
    {
        if (file == NULL)                               // Did The File Even Exist? *Added Jim Strong*
            throw std::runtime_error("File could not be opened: "+file_name);
        else                                            // Otherwise
        {
            fclose(file);                               // If Anything Failed, Close The File
            throw std::runtime_error("Images is not a valid TGA file: "+file_name);
        }
    }

    image.Width  = header[1] * 256 + header[0];   // Determine The TGA Width    (highbyte*256+lowbyte)
    image.Height = header[3] * 256 + header[2];   // Determine The TGA Height    (highbyte*256+lowbyte)

    if(    image.Width    <=0    ||               // Is The Width Less Than Or Equal To Zero
            image.Height    <=0    ||             // Is The Height Less Than Or Equal To Zero
            (header[4]!=24 && header[4]!=32))           // Is The TGA 24 or 32 Bit?
    {
        fclose(file);                                   // If Anything Failed, Close The File
        throw std::runtime_error("File is not a vaid TGA file: "+file_name);
    }

    image.bpp = header[4];                        // Grab The TGA's Bits Per Pixel (24 or 32)
    bytesPerPixel   = image.bpp/8;                // Divide By 8 To Get The Bytes Per Pixel
    imageSize       = image.Width*image.Height*bytesPerPixel;   // Calculate The Memory Required For The TGA Data

    try {
        unsigned char* buffer = new unsigned char[imageSize];
        if (fread(reinterpret_cast<char*>(buffer), 1, imageSize, file) == imageSize)
        {
            image.pData.assign(buffer, buffer+imageSize);
            delete[] buffer;
        } else {
            throw std::runtime_error("Image size of tga doesn't match");
        }
    } catch (std::bad_alloc&)
    {
        throw std::runtime_error("Could not allocate memory for tga data");
    }

    for(GLuint i=0; i<(imageSize); i+=bytesPerPixel)        // Loop Through The Image Data
    {                                                       // Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
        temp = image.pData[i];                        // Temporarily Store The Value At Image Data 'i'
        image.pData[i] = image.pData[i + 2];    // Set The 1st Byte To The Value Of The 3rd Byte
        image.pData[i + 2] = temp;                    // Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
    }

    fclose (file);
    if (image.bpp==24)                                // Was The TGA 24 Bits
    {
        type=GL_RGB;                                        // If So Set The 'type' To GL_RGB
    }
}

}
