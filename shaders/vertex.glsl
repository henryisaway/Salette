#version 330 core

layout (location = 0) in vec3 aPos;   // Vertex position
layout (location = 1) in vec4 aColor; // Vertex color

uniform mat4 u_MVP; // Model-View-Projection matrix

// Output to the fragment shader
out vec4 v_Color;

void main()
{
    // Transform the vertex position by the MVP matrix
    gl_Position = u_MVP * vec4(aPos, 1.0);

    // Pass the vertex color to the fragment shader
    v_Color = aColor;
}
