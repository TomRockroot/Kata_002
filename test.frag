#version 330 core
in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D texture0;

out vec4 fragColor;

void main()
{
	fragColor = texture(texture0, TexCoord);
}