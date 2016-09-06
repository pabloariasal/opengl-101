#version 330

in layout(location=0) vec3 position;

void main()
{
   gl_Position.xyz = position;
   gl_Position.w = 1.0;
}

