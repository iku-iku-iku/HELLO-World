#ifndef __RENDERER__H_
#define __RENDERER__H_

#include <GL/glew.h>
#include <memory>
#include "Shader.h"
#include "Shape.h"
#include "FrameBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"

class Renderer {
public:
    Renderer();
    static void Clear();

    static void ClearColor();

    void Render(const Shader &shader) const;

    void RenderDepthMap();

    void RenderShape(Shape &shape, const Shader &shader);
protected:
    std::unique_ptr<FrameBuffer> m_FrameBuffer;
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<Texture> m_DepthMap;
    std::unique_ptr<Shader> m_DepthRenderingShader;

    void InitOpenGLEnv();
};

#endif