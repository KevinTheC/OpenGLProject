#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D tex[10];

void main()
{
   FragColor = texture(tex[0], texCoord);
}