#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragVertex;
layout(location = 3) in mat4 model;

layout(location = 0) out vec4 outColor;

struct DirectionalLight
{
	vec3 position;
	vec3 color;
};

vec3 directionalLight(DirectionalLight light, vec3 vertex, vec3 normal)
{
	return light.color * dot(normal, light.position);
}

void main()
{
	vec3 normal = normalize(vec3((model * vec4(fragNormal, 0.0)).xyz));
	
	/* Fragment position */
	vec3 vertex = (model * vec4(fragVertex, 1.0)).xyz;

	/* Directional light */
	DirectionalLight direct;
	direct.color = vec3(0.5, 0.5, 0.5);
	direct.position = vec3(0.0, 2.0, 1.0);
	vec3 directional = directionalLight(direct, vertex, normal);

	/* Ambient light */
	vec3 ambient = vec3(0.6, 0.6, 0.6);

    outColor = texture(texSampler, fragTexCoord);
    outColor.rgb *= (ambient + directional);
}