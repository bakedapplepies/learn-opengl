#include <glad/glad.h>
#include <stb/stb_image.h>

#include <iostream>

#include "Debug.h"
#include "Texture.h"

void Texture::CreateTexture(const std::string& texturePath)
{
    GLCall(glGenTextures(1, &m_textureID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    int width, height, nrChannels;
    unsigned char* data = stbi_load(
        texturePath.c_str(), &width, &height, &nrChannels, 4);
    
    if (data)
    {
        // Generate texture
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    }
    else
    {
        std::cout << "Texture failed to load." << '\n';
        std::cout << stbi_failure_reason() << '\n';
    }

    stbi_image_free(data);
}

GLuint Texture::getID() const
{
    return m_textureID;
}

void Texture::Bind() const
{
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::Delete() const
{
    GLCall(glDeleteTextures(1, &m_textureID));
}