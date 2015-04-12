#version 430

layout (binding = 0) uniform sampler2D texColour;
layout (binding = 1) uniform sampler2D specColour;

in vec2 outUV;		//input: texcoords
in vec3 outNormal;
in vec3 outPosition;
in vec3 outCameraPosition;
flat in int outCalculateSpecular;

layout (location = 0) out vec4 outFrag;

void main()
{
	float angle;
	vec4 diffuse;
	vec4 specular;

	// ===== Temporary ===== \\
	vec3 light = vec3(0.0f, 10.0f, -10.0f);
	vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);

	if (outCalculateSpecular == 1)
	{
		// ===== Diffuse ===== \\
		angle = dot(normalize((light - outPosition)), vec3(outNormal));
		diffuse = texture(texColour, outUV) * vec4(lightColour, 0) * angle;

		// ==== Specular ===== \\
		vec3 halfVector = normalize((light - outPosition) + (outCameraPosition - outPosition));
		float power = pow(max(dot(halfVector, outNormal), 0.0f), 20.0f);
		specular = texture(specColour, outUV) * vec4(lightColour, 0) * power;

		outFrag = diffuse + specular;
	}
	else
	{
		// ===== Diffuse ===== \\
		angle = dot(normalize((light - outPosition)), vec3(outNormal));
		outFrag = texture(texColour, outUV) * vec4(lightColour, 0) * angle;
	}
}
