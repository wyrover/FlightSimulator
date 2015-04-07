#version 430

layout (binding = 0) uniform sampler2D texColour;

in vec2 outUV;		//input: texcoords
in vec3 outNormal;
in vec3 outPosition;
in vec3 outCameraPosition;

layout (location = 0) out vec4 outFrag;

void main()
{
	float angle;
	vec4 diffuse;
	vec4 specular;

	// ===== Temporary ===== \\
	vec3 light = vec3(0.0f, 10.0f, -10.0f);
	vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);
	
	// ===== Diffuse ===== \\
	angle = dot(normalize((light - outPosition)), vec3(outNormal));
	//diffuse = texture(texColour, outUV) * vec4(lightColour, 0) * angle;

	outFrag = texture(texColour, outUV);
}
