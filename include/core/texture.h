#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "core/baseStructures.h"
#include "stb_image.h"

#include <iostream>
using std::cout;
using std::endl;

/*currently only support 2D texture*/
class Texture
{
public:
    unsigned int ID;

    Texture(const char* path, TextureTypes type, TextureMode *mode=nullptr)
    {
        if(type != TextureTypes::TWOD)
        {
            //do nothing but log error
            cout<<"Texture::ERROR:not supported types";
        }

        int width, height, nrChannels;
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        //wrap mode and filter mode
        //TODO move wrap mode and filter mode into inputs
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
        cout<<"nrChannels is: "<<nrChannels<<endl;
        if (data)
        {
            if(nrChannels == 4)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            else
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            cout << "Failed to load texture" << std::endl;
        }
    }

    void use()
    {
        glBindTexture(GL_TEXTURE_2D, ID);
    }

    void release()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};

#endif