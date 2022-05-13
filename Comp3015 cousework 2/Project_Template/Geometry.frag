#version 460 

in vec2 Texcoord;

uniform sampler2D SpriteTex;
layout(location = 0) out vec4 FragColor;

void Main(){
FragColor = texture(SpriteTex,Texcoord);
}