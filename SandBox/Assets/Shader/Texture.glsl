#type vertex
#version 330 core
layout(location=0) in vec3 a_Position;
layout(location=1) in vec2 a_TexCor;

uniform mat4 u_ViewProject;				
out vec2 v_TexCor;	

void main()
{
	v_TexCor=a_TexCor;
	gl_Position=u_ViewProject*vec4(a_Position,1.0f);
}


#type fragment

#version 330 core
out vec4 color;				

uniform sampler2D  u_Texture;
in vec2 v_TexCor;	
void main()
{
	color=texture(u_Texture,v_TexCor);
}