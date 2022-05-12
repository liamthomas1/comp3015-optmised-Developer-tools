#version 460


//in variable that receives the diffuse calculation from the vertex shader
in vec3 LightIntensity;
in vec2 TexCoord;
in vec3 Normal;
in vec3 Position;

layout(binding=0) uniform sampler2D Tex1;
//layout(binding
//in vec3 Ambient;
//out variable, this typical for all fragment shaders
layout (location = 0) out vec4 FragColor;
 vec3 phongModel(vec3 position, vec3 normal){
vec3 texcolor = texture(Tex1, TexCoord).rgb;
 return normal + position ;
}
void main()
{
    //we pass LightInyensity to outr FragColor, notice the difference between vector types
    // vec3 and vec4 and how we solved the problem
    FragColor = vec4 (phongModel(Position, normalize(Normal)),1);
}