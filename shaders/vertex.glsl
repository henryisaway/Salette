#version 330 core

layout (location = 0) in vec3 vPos;
//layout (location = 1) in vec4 _vColor;

// uniform mat4 u_MVP;

// Output to the fragment shader
//out vec4 vColor;

void main()
{
    gl_Position = vec4(vPos, 1.0);

    //vColor = _vColor;
}
