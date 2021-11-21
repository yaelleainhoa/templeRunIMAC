#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNorm;
layout(location = 2) in vec2 aVertexTextCoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition;
out vec3 vNormale;
out vec2 vTexture;

void main() {
  vec4 vertexPosition=vec4(aVertexPosition,1);
  vec4 vertexNormale=vec4(aVertexNorm,0);

  vPosition=vec3(uMVMatrix * vertexPosition);
  vNormale=vec3(uNormalMatrix * vertexNormale);
  vTexture=aVertexTextCoords;

  gl_Position=uMVPMatrix * vertexPosition;
};