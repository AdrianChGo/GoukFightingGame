#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoord;

uniform vec3 viewPos; 
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform sampler2D texture1;
//uniform sampler2D texture2;

void main()
{
    // ambient
    float ambientI = 0.35;
    vec3 ambient = ambientI * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

	//Speculas
	float specularStrength = 1.0;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
	vec3 specular = specularStrength * spec * lightColor;
    
    vec3 result;

    result = (ambient + diffuse + specular) * objectColor;

    //FragColor = vec4(result, 1.0);
    vec4 aux = vec4(result, 1.0);
    gl_FragColor = aux * texture(texture1, TexCoord);
    //if(gl_FragColor.rgb == vec3(0,0,0)) discard;
    //FragColor = vec4(1.0);
    //FragColor = aux * mix(texture(texture1, TexCoord),texture(texture2, TexCoord), 0.3);
        

}