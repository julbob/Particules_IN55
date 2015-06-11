#version 140

uniform vec3 myColor;

in vec3 fColor;

out vec4 fragColor;


void main()
{
  fragColor = vec4( fColor, 0.1f );
}
