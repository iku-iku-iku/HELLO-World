#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

out vec3 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
    v_TexCoord = position;
    gl_Position = u_MVP * vec4(position, 1.f);
}

#shader fragment
#version 330 core

in vec3 v_TexCoord;

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform samplerCube u_Texture;
void main()
{
    color = texture(u_Texture, v_TexCoord);
}

