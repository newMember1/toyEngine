#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 oriPos;
out vec2 texCoord;

void main()
{
    oriPos = aPos;
    texCoord = tCoord;
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
};