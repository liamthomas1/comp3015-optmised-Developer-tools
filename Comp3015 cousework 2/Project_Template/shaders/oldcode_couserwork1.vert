#version 460


//in variables, this are in model coordinates
layout (location = 0) in vec3 VertexPosition; 
layout (location = 1) in vec3 VertexNormal; 
layout (location = 2) in vec2 VertexTexCoord;

//out vector needed for the fragment shader
out vec3 LightIntensity; 
out vec3 Colour;
out vec3 Position;
out vec3 Normal;
out vec2 Texcoord;


 //light information struct
uniform struct LightInfo 
{
  vec4 Position; // Light position in eye coords.
  vec3 La;
vec3 L;       // Diffuse light intensity
} lights[3];

//material information struct
uniform struct MaterialInfo 
{
vec3 Ka;
  vec3 Kd;
vec3 Ks;
float Shininess;      // Diffuse reflectivity
} Material;

//uniforms for matrices required in the shader
uniform mat4 ModelViewMatrix;   //model view matrix
uniform mat3 NormalMatrix;		//normal matrix
uniform mat4 MVP;
uniform mat4 ProjectionMatrix;				//model view projection matrix
vec3 phongModel(int light, vec3 position, vec3 n) {
lights[light].La;
vec3 ambient = lights[light].La;
vec3 s = Material.Ks;
float sDotN = max (dot(s,n),0.0);
vec3 diffuse = Material.Kd * sDotN;
vec3 spec = vec3(0.0);
if(sDotN > 0.0){

 vec3 v = normalize(-position.xyz);
 vec3 r = reflect( -s, n );
spec = Material.Ks * pow( max( dot(r,v), 0.0 ),
Material.Shininess );
}
return ambient + lights[light].L * (diffuse * spec);
}
void getCamSpaceValues ( out vec3 norm, out vec3 position )
{
 norm = normalize( NormalMatrix * VertexNormal);
 position = (ModelViewMatrix * vec4(VertexPosition,1.0)).xyz;
}


void main() 
{ 
vec3 camNorm,camPosition;
 getCamSpaceValues(camNorm,camPosition);
  //transfrom normal from model coordinates to view coordinates
  vec3 n = normalize( NormalMatrix * VertexNormal);

 vec3 camCoords =  camPosition;
  //transform vertex position from model coordinates to view coordinates
  vec4 pos = ModelViewMatrix * vec4(VertexPosition,1.0);

//Color
Colour = vec3 (0.0);
for(int i = 0; i<3; i++)
Colour += phongModel ( i,camCoords, n);
// normal and position
 Normal = normalize( NormalMatrix * VertexNormal);
 Position = (ModelViewMatrix * vec4(VertexPosition,1.0)).xyz;
  gl_Position = MVP * vec4(VertexPosition,1.0); 
Texcoord= VertexTexCoord;
} 