#version 460

const float pi = 3.14159265358979323846;
in vec3 Position;
in vec3 Normal;

uniform struct LightInfo {
vec4 Position;
vec3 L;
}Light[3];

uniform struct MaterialInfo {
float Rough;
bool Metal;
vec3 Color;
} Material;

layout (location = 0) out vec4 FragColor;

float ggxDistribution (float nDotH){
float alpha2 = Material.Rough * Material.Rough * Material.Rough * Material.Rough;
float d =(nDotH *nDotH) * (alpha2 - 1) +1;
return alpha2 / (pi *d*d);
} 
float geomSmith(float dotprod) {
float k = (Material.Rough + 1.0) * (Material.Rough + 1.0)/8.0;
float denom = dotprod * (1-k) + k;
return 1.0/ denom;
}

vec3 schlickFresbel (float lDotH){
vec3 f0 = vec3 (0.04);
if (Material.Metal) {
f0 = Material.Color;
}
return f0 + (1 - f0) * pow(1.0 - lDotH, 5);
}

vec3 microfacetModel ( 
 