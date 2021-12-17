#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 vPosition_vs;
out vec3 vNormal_vs;
out vec2 TexCoords;

uniform mat4 uNormalMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

void main()
{
    vec4 vertexPosition = vec4(aPos, 1);
    vec4 vertexNormal = vec4(aNormal, 0);

    vPosition_vs = vec3(uViewMatrix * vertexPosition);
    vNormal_vs = vec3(uNormalMatrix * vertexNormal);
    TexCoords = aTexCoords;
    gl_Position = uProjectionMatrix * vertexPosition;
}