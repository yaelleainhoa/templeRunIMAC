#version 330 core
layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNorm;
layout(location = 2) in vec2 aVertexTextCoords;

out vec2 TexCoords;

uniform mat4 uMVPMatrix;

void main()
{
    TexCoords = aVertexTextCoords;  

    vec4 vertexPosition=vec4(aVertexPosition,1);

    gl_Position=uMVPMatrix * vertexPosition;  
}
