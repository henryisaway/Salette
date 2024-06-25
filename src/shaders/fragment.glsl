#version 330 core

in vec2 fragmentTexCoord;

out vec4 screenColour;

uniform sampler2D material;
uniform sampler2D mask;

void main(){
    vec3 baseColour = texture(material, fragmentTexCoord).rgb;
    float alpha = texture(mask, fragmentTexCoord).r;
    screenColour = vec4(baseColour, alpha);
}
