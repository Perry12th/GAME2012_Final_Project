#version 430 core

in vec3 Colour;
in vec2 UV;

in vec3 Normal_cameraspace;
in vec3 FragPos_worldspace;

uniform mat4 view;

uniform sampler2D texture0;

uniform vec3 ambientColour;
uniform float ambientStrength;

uniform vec3 lightPosition;
uniform vec3 eyePosition;
uniform vec3 eyeDirection;
uniform vec3 diffuseColour;
uniform float diffuseStrength;

uniform float specularStrength;
uniform float shininess;

uniform float falloffStart;
uniform float falloffEnd;

out vec4 frag_colour;

void main()
{
	// Calculate ambient lighting
	vec4 ambient = vec4(ambientColour * ambientStrength, 1.0f);
	
	vec4 totalLight = ambient;

	// Caculate diffuse lighting
	// Distance to the light
	float distance = length(lightPosition - FragPos_worldspace);
	// Range test
	if(distance <= falloffEnd)
	{
		// Get the light direction
		vec3 lightDirection = vec3((view * vec4(lightPosition, 1.0f)) + (view * vec4(eyeDirection, 1.0f)));

		// Get the diffuseFactor
		float diffuseFactor = max(dot(normalize(Normal_cameraspace), normalize(lightDirection)), 0.0f);
		vec4 diffuse = vec4(diffuseColour * diffuseStrength * diffuseFactor * ((falloffEnd - distance) / (falloffEnd - falloffStart)),1.0f);
		totalLight += diffuse;

		// Calculate specular lighting
		vec3 fragToEye = normalize(eyePosition - FragPos_worldspace);
		vec3 reflectedVertex = normalize(reflect(lightDirection, normalize(Normal_cameraspace)));

		float CosAlpha = max( dot(fragToEye, reflectedVertex), 0.0f);
		if (CosAlpha > 0.0f)
		{
			float specularFactor = pow(CosAlpha, shininess) / (distance * distance);
			vec4 specular = vec4(diffuseColour * specularStrength * specularFactor, 1.0f);
			totalLight += specular;
		}

	}

	frag_colour = texture(texture0, UV) * (totalLight);
}


// Caculate diffuse lighting
// Distance to the light
//float distance = length(lightPosition - FragPos_worldspace);
//// Range test
//if(distance <= falloffEnd)
//{
//	// Get the light direction
//	vec3 lightDirection = vec3((view * vec4(lightPosition, 1.0f)) + (vec4(EyeDirection_cameraspace, 1.0f)));
//
//	// Get the diffuseFactor
//	float diffuseFactor = max(dot(normalize(Normal_cameraspace), normalize(lightDirection)), 0.0f);
//	vec4 diffuse = vec4 (diffuseColour, 1.0f) * diffuseStrength * diffuseFactor;
//
//	// Calculate specular lighting
//	vec3 fragToEye = normalize(eyePosition - FragPos_worldspace);
//	vec3 reflectedVertex = normalize(reflect(lightDirection, normalize(Normal_cameraspace)));
//
//	float specularFactor = dot (fragToEye, reflectedVertex);
//		if (specularFactor > 0.0f)
//		{
//			specularFactor = pow(specularFactor, shininess);
//			specular = vec4(diffuseColour * specularStrength * specularFactor, 1.0f);
//		}
//
//}