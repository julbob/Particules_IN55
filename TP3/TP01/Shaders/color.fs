#version 140

uniform sampler2D texId;

in vec3 fColor;

out vec4 fragColor;


void main()
{
  fragColor = vec4( fColor, 0.1f );
  
   //fragColor =  texture2D( texId, vec2(10,10) );
}
