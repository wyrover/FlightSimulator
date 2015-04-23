#version 430

layout (location = 0) uniform mat4 modelview;
layout (location = 1) uniform mat4 projection;
layout (location = 2) uniform mat4 localToWorld;

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inUV;

out vec2 outUV;

void main()
{	
	gl_Position = projection * modelview * (localToWorld * position);
		
	outUV = inUV;
}
