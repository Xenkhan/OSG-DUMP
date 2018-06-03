#version 330 compatibility

out float intensity;
out vec3 position;
out vec3 normal;
out vec4 color;

out vec3 eyeVec, lightDir;

void main(){
	vec4 vertexInEye = gl_ModelViewMatrix * gl_Vertex;
	eyeVec = -vertexInEye.xyz;
	lightDir = gl_LightSource[0].position.xyz - vertexInEye.xyz;
	normal = gl_NormalMatrix * gl_Normal;
	
	color = gl_Color;
	
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
