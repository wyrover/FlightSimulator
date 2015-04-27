#version 430

layout (binding = 0) uniform sampler2D texColour;

in vec2 outUV;
in vec4 outDayAndNight;

layout (location = 0) out vec4 outFrag;

void main()
{
	if (texture(texColour, outUV).a <= 0.15)
	{
		discard;
	}
	outFrag = texture(texColour, outUV) * outDayAndNight;
}
