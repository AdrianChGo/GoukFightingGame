#version 330 core

//in vec3 ourColor;
uniform vec3 color;

void main()

{
//gl_FragColor = vec4 (1.0f, 1.0f, 0.0f,1.0f);

gl_FragColor = vec4 (color,1.0f);
}