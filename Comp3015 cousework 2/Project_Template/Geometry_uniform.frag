#version 460 

struct LightInfo {
vec4 Position;
vec3 Intensity;
};
uniform struct LightInfo Light; 

struct MaterialInfo{
vec3 Ka;
vec3 Kd;
vec3 Ks;
float Shininess;
};
uniform struct MaterialInfo Material;

uniform struct LineInfo {
float Width;
vec4 Color;
} Line;

in vec3 GPosition;
in vec3 GNormal;
noperspective in vec3 GEdgeDistance; 

 vec3 phongModel(vec3 position, vec3 normal){

 return normal + position ;
}

layout ( location = 0 ) out vec4 FragColor;

void main (){
vec4 color = vec4 ( phongModel(GPosition, GNormal), 1.0f);

float d = min (GEdgeDistance.x , GEdgeDistance.y);
d = min ( d, GEdgeDistance.z);

float mixVal;
if (d < Line.Width - 1){
mixVal = 0.0;
}
else {
float x = d - (Line.Width - 1);
mixVal = exp2 ( -2.0 * (x*x));
}
FragColor = mix ( color, Line.Color, mixVal);