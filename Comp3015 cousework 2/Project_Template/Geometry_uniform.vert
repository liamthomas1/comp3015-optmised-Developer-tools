#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexcoord;
// wire frame
out vec3 VNormal;
out vec3 VPosition;

//phong
out vec3 LightIntensity; 
out vec3 Colour;
out vec3 Position;
out vec3 Normal;
out vec2 Texcoord;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;
void main(){
VNormal = normalize(NormalMatrix * VertexNormal);
VPosition = vec3(ModelViewMatrix * vec4(VertexPosition,1.0));
gl_Position = MVP * vec4(VertexPosition,1.0);
}
// for point sprites gl_Position = ModelViewMatrix * vec4(VertexPosition,1.0);