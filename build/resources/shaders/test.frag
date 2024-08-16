#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform vec3 rgb;
uniform sampler2D tex[1];

void main()
{
    vec4 sampled = texture(tex[0], texCoord);
    FragColor = vec4(rgb, 1.0) * sampled;
}