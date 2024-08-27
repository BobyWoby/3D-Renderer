#include "VertexBuffer.h"
#include "Renderer.h"
#include <iostream>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STREAM_DRAW); // could also use sizeof(positions) for size input
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW); // could also use sizeof(positions) for size input
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
