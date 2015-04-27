#version 430

layout (location = 0) uniform mat4 modelview;
layout (location = 1) uniform mat4 projection;
layout (location = 2) uniform mat4 localToWorld;
layout (location = 3) uniform vec3 cameraPosition;
layout (location = 4) uniform mat4 rotation;
layout (location = 5) uniform bool calculateSpecular;
layout (location = 6) uniform vec3 lightPosition;
layout (location = 7) uniform vec3 lightColour;
layout (location = 8) uniform bool calculateNormal;
layout (location = 9) uniform vec4 dayAndNight;

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inUV;
layout (location = 3) in vec3 inTangent;

flat out int bCalculateSpecular;
flat out int bCalculateNormal;

out vec3 CameraPosition;

struct VertexInfo {
	vec2 UV;
	vec3 Normal;
	vec3 Position;
};

out VertexInfo Vertex;

struct LightInfo {
	vec3 Position;
	vec3 Colour;
};

out LightInfo Light;
out vec4 outDayAndNight;
out mat4 normalToWorld;

void main()
{	
	gl_Position = projection * modelview * (localToWorld * position);
	
	CameraPosition = vec3(projection * modelview * vec4(cameraPosition, 0));
	
	vec3 biTangent = cross(inNormal, inTangent);

	normalToWorld = rotation * mat4(vec4(inTangent, 0), vec4(biTangent, 0), vec4(inNormal, 0), vec4(0, 0, 0, 1));

	Vertex.UV = inUV;
	Vertex.Position = vec3(localToWorld * position);
	Vertex.Normal = vec3(rotation * vec4(inNormal, 0));
	
	Light.Colour = lightColour;
	Light.Position = lightPosition;

	bCalculateSpecular = int(calculateSpecular);
	bCalculateNormal = int(calculateNormal);

	outDayAndNight = dayAndNight;
}
