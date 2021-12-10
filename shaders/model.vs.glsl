#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 normal;

uniform mat4 uNormalMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

void main()
{
    vec4 vertexPosition = vec4(aPos, 1);
    vec4 vertexNormal = vec4(aNormal, 0);
    TexCoords = aTexCoords;
    
    normal = vec3(uNormalMatrix * vertexNormal);
    gl_Position = uProjectionMatrix * vertexPosition;
}