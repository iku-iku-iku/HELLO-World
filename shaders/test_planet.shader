#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 u_MVP;

out vec4 varyingColor;

void main()
{
    gl_Position = u_MVP * vec4(position, 1.f);
    varyingColor = vec4(position, 1.f) * 0.5f + vec4(0.5f, 0.5f, 0.5f, 0.5f);
}

#shader fragment
#version 330 core

in vec4 varyingColor;

out vec4 color;

void main()
{
    color = varyingColor;
}
