#version 330 core
out vec4 FragColor;

struct Material
{
	sampler2D diffuse1;
	sampler2D diffuse2;
	sampler2D diffuse3;
	sampler2D specular1;
	sampler2D specular2;
	int shininess;
};

struct DirLight
{
	vec3 direction;
	vec3 color;
};

#define NR_POINT_LIGHTS 1
struct PointLight
{
	vec3 position;
	vec3 color;

	// attenuation
	float constant;
	float linear;
	float quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform Material	material;

// Lights
uniform vec3		ambientLight;
uniform DirLight	dirLight;
uniform PointLight	pointLights[NR_POINT_LIGHTS];

uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	// Ambient Light
	vec3 result = ambientLight * vec3( texture(material.diffuse1, TexCoord));

	// Directional Light
	result += CalcDirLight(dirLight, norm, viewDir);

	// Point Lights
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	}

	// Spot Light (ToDo)
	//result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

	FragColor = vec4(result, 1.0) ;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	
	// diffuse
	float diff = max( dot(normal, lightDir), 0.0);

	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow( max( dot(viewDir, reflectDir), 0.0), material.shininess);

	// combine
	vec3 diffuse  = diff * vec3( texture(material.diffuse1, TexCoord));
	vec3 specular = spec * vec3( texture(material.specular1, TexCoord));
	return (diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	// diffuse
	float diff = max( dot(normal, lightDir), 0.0 );

	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow( max( dot(normal, lightDir), 0.0), material.shininess);

	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	// combine
	vec3 diffuse  = diff * vec3( texture(material.diffuse1, TexCoord));
	vec3 specular = spec * vec3( texture(material.specular1, TexCoord));
	return ((diffuse + specular) * light.color * attenuation);
}