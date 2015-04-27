#version 430

layout (binding = 0) uniform sampler2D DiffuseTexture;
layout (binding = 1) uniform sampler2D SpecularTexture;
layout (binding = 2) uniform sampler2D NormalTexture;

flat in int bCalculateSpecular;
flat in int bCalculateNormal;

in vec3 CameraPosition;

struct VertexInfo {
	vec2 UV;
	vec3 Normal;
	vec3 Position;
};

in VertexInfo Vertex;

struct LightInfo {
	vec3 Position;
	vec3 Colour;
};

in LightInfo Light;

in vec4 outDayAndNight;
in mat4 normalToWorld;

layout (location = 0) out vec4 outFrag;

vec3 phongModel(LightInfo _Light)
{
	vec3 normal;

	if (bCalculateNormal == 1)
	{
		normal = (texture(NormalTexture, Vertex.UV) * normalToWorld).xyz;
	}
	else
	{
		normal = Vertex.Normal;
	}
	
	vec3 Kd = texture(DiffuseTexture, Vertex.UV).xyz;
	vec3 Ks = texture(SpecularTexture, Vertex.UV).xyz;	

	vec3 diffuse;
	vec3 specular;

	vec3 s = normalize(_Light.Position - Vertex.Position);
	vec3 halfVector = normalize((_Light.Position - Vertex.Position) + (CameraPosition - Vertex.Position));

	float sDotN = max(dot(s, normal), 0.0f);

	diffuse = Kd * sDotN;

	specular = vec3(0.0);

	// check if there is a specular texutre
	if (bCalculateSpecular == 1)
	{
		if (sDotN > 0.0f)
		{
			specular = Ks * pow(max(dot(halfVector, normal), 0.0f), 1.0f);
		}
	}
	else
	{
			specular = vec3(0.8f, 0.8f, 0.8f) * pow(max(dot(halfVector, normal), 0.0f), 10.0f);
	}

	float dist = length(_Light.Position - Vertex.Position);
	float attenuation = 1.0f / (1.0f + (0.01f * dist) + (0.0001f * dist * dist));

	vec3 LightIntensity = _Light.Colour * (diffuse + specular);

	return LightIntensity * attenuation;
}

void main()
{
	LightInfo Light1, Light2, Light3, Light4, Light5, Light6, Light7;

	Light1.Colour = vec3(1.0f, 1.0f, 1.0f);
	Light1.Position = vec3(-50.0f, 200.0f, 0.0f);

	Light2.Colour = vec3(1.0f, 1.0f, 1.0f);
	Light2.Position = vec3(200.0f, 200.0f, 0.0f);

	Light3.Colour = vec3(1.0f, 1.0f, 1.0f);
	Light3.Position = vec3(-50.0f, 200.0f, -200.0f);

	Light4.Colour = vec3(1.0f, 1.0f, 1.0f);
	Light4.Position = vec3(200.0f, 200.0f, -200.0f);

	Light5.Colour = vec3(1.0f, 1.0f, 0.95f);
	Light5.Position = vec3(100.0f, 50.0f, -80.0f);

	Light6.Colour = vec3(1.0f, 1.0f, 0.95f);
	Light6.Position = vec3(0.0f, 50.0f, -80.0f);

	vec3 Colour = vec3(0.0);

	Colour += phongModel(Light1);
	Colour += phongModel(Light2);
	Colour += phongModel(Light3);
	Colour += phongModel(Light4);
	Colour += phongModel(Light5);
	Colour += phongModel(Light6);
	
	// Add dayAndNight vector to simulate the day-night cycle. It's not perfect.
	outFrag = vec4(Colour, 1.0f) * outDayAndNight;

	// debug normals
	//if (bCalculateNormal == 1)
	//{
	//	outFrag = (texture(NormalTexture, Vertex.UV) * normalToWorld);
	//}
	//else
	//{
	//	outFrag = vec4(Vertex.Normal, 0);
	//}
}