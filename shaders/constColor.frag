#version 330 core
in vec3 oriPos;
out vec4 FragColor;
void main()
{
    FragColor = vec4(sin(oriPos.y), cos(oriPos.y), sin(oriPos.y) * cos(oriPos.y), 1.0f);
};
