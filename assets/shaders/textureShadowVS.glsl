#version 330 core

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexTexCoords;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightInvDirection;
uniform mat4 DepthBiasMVP;

out vec2 vertexTexCoordsOut;
out vec3 positionWorldSpace;
out vec3 normalCameraSpace;
out vec3 eyeDirectionCameraSpace;
out vec4 lightDirectionCameraSpace;
out vec4 ShadowCoord;



void main()
{
	gl_Position = MVP * vec4(vertexPosition, 1.0);
	ShadowCoord = DepthBiasMVP * vec4(vertexPosition, 1);
	positionWorldSpace = (M * vec4(vertexPosition, 1)).xyz;
	eyeDirectionCameraSpace = vec3(0, 0, 0) - (V * M * vec4(vertexPosition, 1)).xyz;
	lightDirectionCameraSpace = (V*vec4(LightInvDirection, 0)).xyz;
	normalCameraSpace = (V * M * vec4(vertexPosition, 0)).xyz;
	vertexTexCoordsOut = vertexTexCoords;

}