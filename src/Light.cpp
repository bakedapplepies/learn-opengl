#include "pch/pch.h"

#include "Debug.h"
#include "Light.h"


Light::Light(const glm::vec3& position, const glm::vec3& color)
{
    this->position = position;
    vertices = m_vertices;
    colors = m_colors;
    indices = m_indices;
    ConstructMesh();

    EnableVertexAttribPostion(true);
    EnableVertexAttribColor(true);

    shader = Shader(
        "../resources/shaders/lightvertex.vert",
        "../resources/shaders/lightfragment.frag"
    );

    shader.Use();
}

Light::Light(Light&& other) noexcept
{
    std::cout << "Move constructor of Light called." << '\n';

    position = other.position;
    m_color = other.m_color;
    shader = std::move(other.shader);
}

Light& Light::operator=(Light&& other) noexcept
{
    std::cout << "Move assignment operator of Light called." << '\n';

    position = other.position;
    m_color = other.m_color;
    shader = std::move(other.shader);

    return *this;
}

Light::~Light()
{
    std::cout << "Deleting light" << '\n';
}

glm::vec3& Light::GetColor()
{
    return m_color;
}