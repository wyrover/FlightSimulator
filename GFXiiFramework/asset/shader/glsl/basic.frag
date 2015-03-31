#version 430

layout (binding = 0) uniform sampler2D texColour;

in vec2 outUV;		//input: texcoords

layout (location = 0) out vec4 outFrag;

void main()
{
	vec4 white = vec4(1.0,1.0, 1.0, 1.0);

	outFrag = texture(texColour, outUV);
}
