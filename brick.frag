#version 330 compatibility

out vec4 fragColor;

in float intensity;
in vec3 position;
in vec3 normal;
in vec4 color;

in vec3 eyeVec, lightDir;

void main(){
	vec4 finalColor = color;
	
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	float lambert = dot(N,L);
	
	if(lambert > 0.0){
		finalColor *= lambert;
		vec3 E = normalize(eyeVec);
		vec3 R = reflect(-L, N);
		float specular = pow(max(dot(R, E), 0.0), 64.0);
		finalColor += vec4(1.0f, 1.0f, 1.0f, 1.0f) * specular;
	}
	
		
	
	fragColor = finalColor;



}

		
		