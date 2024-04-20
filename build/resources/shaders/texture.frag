#version 330 core

out vec4 FragColor;

in vec2 texCoord;

in uint texIndexInt;

uniform sampler2D tex[10];

void main()
{
   FragColor = texture(tex[texIndexInt], texCoord);
}