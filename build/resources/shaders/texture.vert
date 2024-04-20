#version 330 core
//3,2,1
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in float texIndex;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec4 gl_Position;
out vec2 texCoord;
out uint texIndexInt;

void main()
{
   gl_Position = proj * view * model * vec4(aPos, 1.0);
   texCoord = aTex;
   texIndexInt = uint(texIndex);
}