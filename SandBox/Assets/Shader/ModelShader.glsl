#type vertex
#version 330 core
layout(location=0) in vec3 a_Position;
layout(location=1) in vec2 a_Nor;
layout(location=2) in vec2 a_TexCor;

uniform mat4 u_ViewProject;
uniform mat4 u_ModelMatrix;
out vec2 v_TexCor;	
out vec3 v_Position;

void main()
{
	v_TexCor=a_TexCor;
	v_Position=a_Position;
	gl_Position=u_ViewProject*u_ModelMatrix*vec4(a_Position,1.0f);
}

#type fragment

#version 330 core
out vec4 color;				

uniform sampler2D  u_Texture;
in vec2 v_TexCor;	
in vec3 v_Position;

void main()
{
	color=texture(u_Texture,v_TexCor);
}