#type vertex
#version 330 core
layout(location=0) in vec3 a_Position;
layout(location=1) in vec3 a_Nor;
layout(location=2) in vec2 a_TexCor;

uniform mat4 u_ProjectMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ModelMatrix;

smooth out vec2 v_TexCor;	
smooth out vec3 v_Position;
smooth out vec3 v_Nor;

void main()
{
	 mat3 normalMatrix = mat3(transpose(inverse(u_ModelMatrix)));
    v_Nor = normalize(normalMatrix * a_Nor);  // 提前归一化

	v_TexCor=a_TexCor;
	v_Position=vec3(u_ModelMatrix*vec4(a_Position,1.0f));

	gl_Position=u_ProjectMatrix*u_ViewMatrix*u_ModelMatrix*vec4(a_Position,1.0f);
}

#type fragment

#version 330 core
out vec4 color;				

uniform sampler2D  u_Texture;

uniform vec3 u_light_pos;
uniform vec3 u_light_ka;
uniform vec3 u_light_kd;
uniform vec3 u_light_ks;
uniform vec3 u_light_Instensity;
uniform vec3 u_light_amb_instensity;
uniform vec3 u_viewPos; //摄像机位置

smooth  in vec2 v_TexCor;	
smooth  in vec3 v_Position;
smooth  in vec3 v_Nor;


void main()
{
	vec4 tex_color=texture(u_Texture,v_TexCor);

	vec3 nor = normalize(v_Nor);

	vec3 light_kd =u_light_kd;
	vec3 light_ks =u_light_ks;

	light_ks=light_kd=vec3(tex_color);

	

	vec3 amb_color= u_light_ka*u_light_amb_instensity;

	vec3 light_vector=(u_light_pos-v_Position);
	float r=length(light_vector);
	float r_square=pow(r,2);
	vec3 light_dir=normalize(light_vector);

	float cos_angle=dot(nor,light_dir);
	vec3 diffuse_color=light_kd*u_light_Instensity/r_square*max(0,cos_angle);

	vec3 view_dir=normalize(u_viewPos-v_Position);
	vec3 nor_dir=normalize(light_dir+view_dir);
	float cos_spe=dot(nor_dir,nor);
	vec3 specular_color=light_ks*u_light_Instensity/r_square*max(0,cos_spe);

	vec3 res_color=amb_color+diffuse_color+specular_color;
	//res_color=diffuse_color;
	//res_color=specular_color;

	color=vec4(res_color,1.0f);
	//color=tex_color;


}