#version 330

// Input vertex data, different for all executions of this shader.
in vec3 vertexPosition;
in vec4 vertexColour;
in vec2 vertexTexCoords;
in vec3 vertexNormal;


// Output data ; will be interpolated for each fragment.
out vec4 vertexColourOut;
out vec2 vertexTexCoordsOut;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;
out vec4 ShadowCoord;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightInvDirection;
uniform mat4 DepthBiasMVP;


void main(){

	// Output position of the vertex, in clip space : MVP * position
	gl_Position = MVP * vec4(vertexPosition, 1);
	vertexColourOut = vertexColour;
	ShadowCoord = DepthBiasMVP * vec4(vertexPosition, 1);

	// Position of the vertex, in worldspace : M * position
	Position_worldspace = (M * vec4(vertexPosition, 1)).xyz;

	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	EyeDirection_cameraspace = vec3(0, 0, 0) - (V * M * vec4(vertexPosition, 1)).xyz;

	// Vector that goes from the vertex to the light, in camera space
	LightDirection_cameraspace = (V*vec4(LightInvDirection, 0)).xyz;

	// Normal of the the vertex, in camera space
	Normal_cameraspace = (V * M * vec4(vertexPosition, 0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
	//Normal_cameraspace = normalize(V * M * vec4(vertexPosition, 0)).xyz;
	// UV of the vertex. No special space for this one.
	vertexTexCoordsOut = vertexTexCoords;
}

