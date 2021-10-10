#version 330 core

layout(location = 0) in vec3 pos;
uniform mat4 model;

out vec3 normal;

void main()
{
    normal = pos;
    gl_Position = model * vec4(pos, 1.0f);
}
