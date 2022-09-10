#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

out vec4 pp;

void main()
{
    gl_Position = u_MVP * position;
    pp = gl_Position;
    v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

in vec2 v_TexCoord;
in vec4 pp;

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
void main()
{
    color = texture(u_Texture, v_TexCoord);
}
