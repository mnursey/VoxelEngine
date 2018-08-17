#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec3 normal;

out vec4 v_Color;
out vec3 v_Normal;
out vec3 v_FragPosition;

uniform mat4 u_MVP;
uniform mat4 u_model;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);
	v_Color = color;
	v_Normal = mat3(transpose(inverse(u_model))) * normal;
	v_FragPosition = vec3(u_model * vec4(position, 1.0));
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec3 v_Normal;
in vec3 v_FragPosition;

uniform vec3 u_viewPos;
uniform vec3 u_lightColor;
uniform vec3 u_lightPosition;

void main() 
{
	vec3 normal = normalize(v_Normal);
	vec3 lightDir = normalize(u_lightPosition - v_FragPosition);

	float ambientStrength = 0.4;
	vec3 ambient = ambientStrength * vec3(1.0);

	float specularStrength = 0.15;
	vec3 viewDir = normalize(u_viewPos - v_FragPosition);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4);
	vec3 specular = specularStrength * spec * u_lightColor;

	float diffuse = max(dot(normal, lightDir), 0.0);

	//color = vec4(ambient + diffuse + specular, 1.0) * v_Color;
	color = vec4(ambient + 0.75 * diffuse * u_lightColor + specular * u_lightColor, 1.0) * v_Color;
};