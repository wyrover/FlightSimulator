#version 430

layout (location = 0) uniform mat4 modelview;	//modelview matrix
layout (location = 1) uniform mat4 projection;	//projection matrix
layout (location = 2) uniform mat4 localToWorld; // transformations
layout (location = 3) uniform vec3 cameraPosition;
layout (location = 4) uniform mat4 rotation;
layout (location = 5) uniform bool calculateSpecular;

layout (location = 0) in vec4 position;	//vertex attribute: position
layout (location = 1) in vec3 inNormal;	//vertex attribute: normal
layout (location = 2) in vec2 inUV;		//vertex attribute: texcoords

out vec2 outUV;			//output: texcoords
out vec3 outNormal;
out vec3 outPosition;
out vec3 outCameraPosition;
flat out int outCalculateSpecular;

void main()
{	
	gl_Position = projection * modelview * (localToWorld * position);
		
	outUV = inUV;
	outNormal = vec3(rotation * vec4(inNormal, 0));
	outPosition = vec3(localToWorld * position);
	outCameraPosition = vec3(projection * modelview * vec4(cameraPosition, 0));
	outCalculateSpecular = int(calculateSpecular);
}
