#include "pch/pch.h"

#include "Debug.h"
#include "ElementBuffer.h"


ElementBuffer::ElementBuffer(ElementBuffer&& other) noexcept
{
    std::cout << "Element Buffer Move constructor." << '\n';
    m_EBO_ID = other.m_EBO_ID;
    other.m_EBO_ID = 0;
}

ElementBuffer& ElementBuffer::operator=(ElementBuffer&& other) noexcept
{
    std::cout << "Element Buffer Move assignment." << '\n';
    m_EBO_ID = other.m_EBO_ID;
    other.m_EBO_ID = 0;

    return *this;
}

ElementBuffer::~ElementBuffer()
{
    GLCall(glDeleteBuffers(1, &m_EBO_ID));
}

void ElementBuffer::CreateEBO(unsigned int* data, unsigned int& dataSize, GLenum mode)
{
    GLCall(glGenBuffers(1, &m_EBO_ID));
    Bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, mode));
}

void ElementBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO_ID));
}

void ElementBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}