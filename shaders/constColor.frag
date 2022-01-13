#version 330 core
in vec3 oriPos;
out vec4 FragColor;
void main()
{
    FragColor = vec4(0.3, 0.5, sin(oriPos.y) * cos(oriPos.y), 1.0f);
};
