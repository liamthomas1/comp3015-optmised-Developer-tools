#version 460

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;


uniform float size2; // half the width of the quad
uniform mat4 ProjectionMatrix;

out vec2 texCoord; //fragment

void main(){
mat4 m = ProjectionMatrix;

gl_Position = m*