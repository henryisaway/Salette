#version 330 core

// Input from the vertex shader
in vec4 v_Color;

// Output color
out vec4 FragColor;

void main()
{
    // Set the output color to the interpolated color from the vertex shader
    FragColor = v_Color;
}