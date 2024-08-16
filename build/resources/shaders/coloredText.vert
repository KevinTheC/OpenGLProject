#version 330 core
//3,2
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

uniform vec3 offset;

out vec4 gl_Position;
out vec2 texCoord;

void main()
{
   gl_Position = vec4(aPos + offset, 1.0);
   texCoord = aTex;
}