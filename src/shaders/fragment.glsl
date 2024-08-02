#version 330 core

in vec2 fragmentTexCoord;

out vec4 fragColour;

uniform sampler2D material;

void main(){
    fragColour = texture(material, fragmentTexCoord);
}
