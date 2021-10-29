#version 410

//in vec2 fragUV;
in vec3 fragNormal;

out vec4 outColor;
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 meshColor;
uniform vec3 ambientColor;

void main()
{
	vec3 normal = normalize(fragNormal);
	float nDotL = max(0,dot(normal, lightDir));

	// how much light the surface effectively recieve
	vec3 irradiance = ambientColor + lightColor * nDotL; 

	vec3 linearColor = meshColor * irradiance;

    outColor = vec4(pow(linearColor, vec3(1.0 / 2.2)), 1.0);
}