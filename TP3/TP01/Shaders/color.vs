#version 140

in vec3 position;
in vec3 color;
in vec3 speed;
in float age;

uniform mat4 mvp;
//uniform int type; 
//Type is: 0:fire ; 1:smoke ; 2:liquid; -1 is the box

out vec3 fColor;


void main()
{
	
	vec3 newPosition = position + speed * age;
	
	
	
  gl_Position = mvp * vec4(newPosition, 1.0f);
  gl_PointSize = 3.0;
  /*vec3 vertexColor = vec3(0f,1.0f,0f);
	if(type == 0){
		vertexColor = vec3(1.0f,1-(position.z/maxZ),0f);
	}
	else if(type == 1){
		vertexColor = vec3(0.5f,0.5f,0.5f);
	}
	else if(type == 2){
		vertexColor = vec3(0f,0f,(position.z/maxZ)+0.4);
	}
	else if(type == -1){
		vertexColor = vec3(1f,0f,0f);
	}*/
  
  
  
  fColor = color;
  
}
