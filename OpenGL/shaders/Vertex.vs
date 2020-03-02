#version 330 core
layout(location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout(location = 1) in vec3 aColor;   // the position variable has attribute position 0
layout(location = 2) in vec2 aTexCoord; // the color variable has attribute position 1
out vec2 TexCoord; // output a color to the fragment shader
out vec3 Color;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	Color = aColor;
	TexCoord = aTexCoord; // set ourColor to the input color we got from the vertex data
}