#version 460
// pbr
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

//out 
out vec3 Position;
out vec3 Normal;

//uniform
uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

//void
void main() {
Normal = normalize(NormalMatrix * VertexNormal);
Position = ( ModelViewMatrix * vec4(VertexPosition,1.0) ).xyz;


gl_Position = MVP* vec4 (VertexPosition,1.0); 

// the light time to add more folder as well menu 