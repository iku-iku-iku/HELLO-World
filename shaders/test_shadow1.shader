#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 u_MVP;
//out vec4 p;

void main()
{
    gl_Position = u_MVP * vec4(position, 1.f);
//    p = gl_Position;
}

#shader fragment
#version 330 core
layout(location = 0) out float fragmentdepth;

void main(){
    // Not really needed, OpenGL does it anyway
    fragmentdepth = gl_FragCoord.z;
}