#version 460
//
const float pi = 3.14159265358979323846;
in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

layout(binding = 0) uniform sampler2D Tex1;

vec3 texColor = texture(Tex1, TexCoord).rgb;

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

vec3 microfacetModel (  int lightIdx, vec3 position, vec3 n) {
vec3 diffuseBrdf = vec3 (0.0);
if (!Material.Metal){
diffuseBrdf = Material.Color;
}

vec3 l = vec3(0.0),
Lightl = Light[lightIdx].L;
if (Light[lightIdx].Position.w == 0.0){
l = normalize(Light[lightIdx].Position.xyz);
}
else {
l = Light[lightIdx].Position.xyz - position;
float dist = length(l);
l = normalize(l);
Lightl /= (dist * dist);
}
vec3 v = normalize(-position);
vec3 h = normalize(v + 1);
float nDotH = dot(n,h);
float lDotH = dot( l,h);
float nDotL = max (dot(n,l),0.0);
float nDotV = dot ( n,v);
vec3 specBrdf = 0.25 * ggxDistribution(nDotH) * schlickFresbel(lDotH) * geomSmith(nDotL);

return (diffuseBrdf + pi * specBrdf) * Lightl * nDotL;
}

void main(){
vec3 sum = vec3(0);
vec3 n = normalize(Normal);
for (int i = 0; i< 3; i++){
sum += microfacetModel( i, Position, n);
}

sum = pow( sum, vec3(1.0/2.2));
FragColor = vec4 (sum, 1); 
} 



//struct LightInfo {
//vec4 Position;
//vec3 Intensity;
//};
//uniform struct LightInfo Light; 
//
//struct MaterialInfo{
//vec3 Ka;
//vec3 Kd;
//vec3 Ks;
//float Shininess;
//};
//uniform struct MaterialInfo Material;
//
//uniform struct LineInfo {
//float Width;
//vec4 Color;
//} Line;
//
//in vec3 GPosition;
//in vec3 GNormal;
//noperspective in vec3 GEdgeDistance; 
//
// vec3 phongModel(vec3 position, vec3 normal){
//
// return normal + position ;
//}
//
//layout ( location = 0 ) out vec4 FragColor;
//
//void main (){
//vec4 color = vec4 ( phongModel(GPosition, GNormal), 1.0f);
//
//float d = min (GEdgeDistance.x , GEdgeDistance.y);
//d = min ( d, GEdgeDistance.z);
//
//float mixVal;
//if (d < Line.Width - 1){
//mixVal = 0.0;
//}
//else {
//float x = d - (Line.Width - 1);
//mixVal = exp2 ( -2.0 * (x*x));
//}
//FragColor = mix ( color, Line.Color, mixVal);
//} 