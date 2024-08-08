#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform vec3 rgb;
uniform sampler2D tex;

void main()
{
    vec4 sampled = texture(tex, texCoord);
    FragColor = vec4(rgb, 1.0) * sampled;
}