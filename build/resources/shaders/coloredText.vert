#version 330 core
//2,2
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

uniform mat4 model;

out vec4 gl_Position;
out vec2 texCoord;

void main()
{
   gl_Position = model * vec4(aPos, 0.0, 1.0);
   texCoord = aTex;
}