#version 460

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

out vec3 GNormal; 
out vec3 GPosition;

noperspective out vec3 GEdgeDistance; // distance from the edge

in vec3 VNormal[];
in vec3 VPosition[];
uniform mat4 ViewportMatrix; 

void main(){
vec2 p0 = vec2(ViewportMatrix * (gl_in[0].gl_Position / gl_in[0].gl_Position.w));
vec2 p1 = vec2(ViewportMatrix * (gl_in[1].gl_Position / gl_in[1].gl_Position.w));
vec2 p2 = vec2(ViewportMatrix * (gl_in[2].gl_Position / gl_in[2].gl_Position.w));


float a = length(p1 - p2);
float b = length(p2 - p0);
float c = length(p1 - p0);

float aplpha = acos( ( b*b + c*c - a*a) / (2.0*b*c));
float beta = acos( (   a*a + c*c - b*b) / (2.0 * a *c)  );






































// don't think about it 
//uniform float Size2; // half the width of the quad
//uniform mat4 ProjectionMatrix;
//
//out vec2 TexCoord; //fragment
//
////void main(){
////mat4 m = ProjectionMatrix;
////
////gl_Position = m* (vec4(-Size2, -Size2,0.0,0.0) + gl_in[0].gl_Position);
////TexCoord = vec2 (0.0,0.0);
////EmitVertex();
////
//////setup vertex 2
////gl_Position = m * (vec4(Size2,-Size2,0.0,0.0) + gl_in[0].gl_Position);
////TexCoord = vec2(0.0,0.0);
////EmitVertex();
////
//////setup vertex 3
////gl_Position = m* (vec4(-Size2, -Size2, 0.0,0.0) + gl_Position);
////TexCoord = vec2(0.0,1.0);
////EmitVertex();
////
//////setup vertex 4
////gl_Position = m * (vec4(Size2, Size2,0.0,0.0) + gl_in[0].gl_Position);
////TexCoord = vec2(1.0,1.0);
////EmitVertex();
////
////EndPrimitive();
////}
//