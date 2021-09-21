#version 330 core
in vec3 oriPos;
out vec4 FragColor;
void main()
{
    FragColor = vec4(cos(oriPos.x), sin(oriPos.y), sin(oriPos.z) * cos(oriPos.z), 1.0f);
};
