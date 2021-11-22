#version 330

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTexCoord;

out vec2 vTexCoord;

void main() {
    vTexCoord = aVertexTexCoord;
    gl_Position = vec4(aVertexPosition, 0, 1);
}
