#version 330 core
//2,2
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

uniform vec3 offset;

out vec4 gl_Position;
out vec2 texCoord;

void main()
{
   gl_Position = vec4(vec3(aPos, 0.0) + offset, 1.0);
   texCoord = aTex;
}