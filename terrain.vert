#version 150 // GLSL 150 = OpenGL 3.2

in vec3 in_Position;


///vec4 in_Position_main;

in vec2 in_TexCoord;

in vec2 in_TexCoord2; // for earth texture (second texture)

uniform mat4 ModelView;
uniform mat4 Projection;

out vec4 textColor;

uniform sampler2D tex;

out vec2 out_TexCoord;


out vec4 textColor2;
uniform sampler2D tex2;
out vec2 out_TexCoord2;


out vec4 textColor_right;
uniform sampler2D tex_right;
out vec2 out_TexCoord_right;

out vec4 textColor_up;
uniform sampler2D tex_up;
out vec2 out_TexCoord_up;

vec4 pos;
vec4 in_position_right;
vec4 in_position_up;

vec4 pos_for_normals;
uniform mat4 GeomTransform;
uniform mat3 NormalMat;
vec3 in_light = vec3(10, 20, 10);
in vec3 in_Normal;   // normal vector   (object coordinates)
out vec3 out_Normal;	// normal vector   (camera coordinates)
vec3 pos3vec;


void main() 
{
	
	//vec4 pos = vec4(in_Position.x , in_Position.y, in_Position.z, 1.0);


	out_TexCoord = (in_TexCoord) / 1000.0;     // for bumping pictures
	textColor = texture(tex, out_TexCoord);
	

	textColor_right = texture(tex, out_TexCoord);
	//textColor_right = vec4(out_TexCoord,0,1);
	textColor_right.x += 0.001;

 
	textColor_up = texture(tex, out_TexCoord);
	//textColor_up = vec4(out_TexCoord,0,1);
	textColor_up.y += 0.001;



	out_TexCoord2 = (in_TexCoord2) / 1000.0;    // for color pictures
	textColor2 = texture(tex2, out_TexCoord2);

	


/////////////////////////////////////////////////////////  //adjusting pixels color for main, right and up positions  // i did not use them yet. maybe I'll use them lator!


	float pixel_val_r = textColor.r;
	float pixel_val_g = textColor.g;
	float pixel_val_b = textColor.b;


	float pixel_val_r_right = textColor_right.r;
	float pixel_val_g_right = textColor_right.g;
	float pixel_val_b_right = textColor_right.b;


	float pixel_val_r_up = textColor_up.r;
	float pixel_val_g_up = textColor_up.g;
	float pixel_val_b_up = textColor_up.b;

	//pos = vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//adjusting y position for main

	if(textColor.r > 1 && textColor.g > 1 && textColor.b > 1)
	{
			pos = vec4(in_Position.x, in_Position.y + 140, in_Position.z, 1.0);
	}

	else if(textColor.r <= 1 && textColor.r > 0.9  && textColor.g <= 1 && textColor.g > 0.9 && textColor.b <= 1 && textColor.b > 0.9)
	{
			pos = vec4(in_Position.x, in_Position.y + 130, in_Position.z, 1.0);
	}

	else if(textColor.r <= 0.9 && textColor.r > 0.8  && textColor.g <= 0.9 && textColor.g > 0.8 && textColor.b <= 0.9 && textColor.b > 0.8)
	{
			pos = vec4(in_Position.x, in_Position.y + 120, in_Position.z, 1.0);

	}

	else if(textColor.r <= 0.8 && textColor.r > 0.7  && textColor.g <= 0.8 && textColor.g > 0.7 && textColor.b <= 0.8 && textColor.b > 0.7)
	{
			pos = vec4(in_Position.x, in_Position.y + 110, in_Position.z, 1.0);
	}

	else if(textColor.r <= 0.7 && textColor.r > 0.6  && textColor.g <= 0.7 && textColor.g > 0.6 && textColor.b <= 0.7 && textColor.b > 0.6)
	{
			pos = vec4(in_Position.x, in_Position.y + 100, in_Position.z, 1.0);
	}

	else if(textColor.r <= 0.6 && textColor.r > 0.5  && textColor.g <= 0.6 && textColor.g > 0.5 && textColor.b <= 0.6 && textColor.b > 0.5)
	{
			pos = vec4(in_Position.x, in_Position.y + 90, in_Position.z, 1.0);
	}

	else if(textColor.r <= 0.5 && textColor.r > 0.4  && textColor.g <= 0.5 && textColor.g > 0.4 && textColor.b <= 0.5 && textColor.b > 0.4)
	{
			pos = vec4(in_Position.x, in_Position.y + 80, in_Position.z, 1.0);
	}

	else if(textColor.r <= 0.4 && textColor.r > 0.3  && textColor.g <= 0.4 && textColor.g > 0.3 && textColor.b <= 0.4 && textColor.b > 0.3)
	{
			pos = vec4(in_Position.x, in_Position.y + 70, in_Position.z, 1.0);
	}

	else if(textColor.r <= 0.3 && textColor.r > 0.2  && textColor.g <= 0.3 && textColor.g > 0.2 && textColor.b <= 0.3 && textColor.b > 0.2)
	{
			pos = vec4(in_Position.x, in_Position.y + 60, in_Position.z, 1.0);
	}

	else if(textColor.r <= 0.2 && textColor.r > 0.1  && textColor.g <= 0.2 && textColor.g > 0.1 && textColor.b <= 0.2 && textColor.b > 0.1)
	{
			pos = vec4(in_Position.x, in_Position.y + 50, in_Position.z, 1.0);
	}


	else if(textColor.r <= 0.1 && textColor.r > 0.01  && textColor.g <= 0.1 && textColor.g > 0.01 && textColor.b <= 0.1 && textColor.b > 0.01)
	{
			pos = vec4(in_Position.x, in_Position.y + 40, in_Position.z, 1.0);
	}

	else
	{
			pos = vec4(in_Position.x, in_Position.y + 20, in_Position.z, 1.0);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
	//adjusting y position for right
	
	//in_position_right = vec4(in_Position.x + 0.000001, in_Position.y, in_Position.z,1);


	if(textColor_right.r > 1 && textColor_right.g > 1 && textColor_right.b > 1)
	{
				in_position_right = vec4(in_Position.x + 0.000001, in_Position.y + 140 , in_Position.z,1);
	}

	else if(textColor_right.r <= 1 && textColor_right.r > 0.9  && textColor_right.g <= 1 && textColor_right.g > 0.9 && textColor_right.b <= 1 && textColor_right.b > 0.9)
	{
				in_position_right = vec4(in_Position.x + 0.000001, in_Position.y + 130 , in_Position.z,1);
	}

	else if(textColor_right.r <= 0.9 && textColor_right.r > 0.8  && textColor_right.g <= 0.9 && textColor_right.g > 0.8 && textColor_right.b <= 0.9 && textColor_right.b > 0.8)
	{
				in_position_right = vec4(in_Position.x + 0.000001, in_Position.y + 120 , in_Position.z,1);

	}

	else if(textColor_right.r <= 0.8 && textColor_right.r > 0.7  && textColor_right.g <= 0.8 && textColor_right.g > 0.7 && textColor_right.b <= 0.8 && textColor_right.b > 0.7)
	{
				in_position_right = vec4(in_Position.x + 0.000001, in_Position.y + 110 , in_Position.z,1);
	}

	else if(textColor_right.r <= 0.7 && textColor_right.r > 0.6  && textColor_right.g <= 0.7 && textColor_right.g > 0.6 && textColor_right.b <= 0.7 && textColor_right.b > 0.6)
	{
				in_position_right = vec4(in_Position.x + 0.000001, in_Position.y + 100 , in_Position.z,1);
	}

	else if(textColor_right.r <= 0.6 && textColor_right.r > 0.5  && textColor_right.g <= 0.6 && textColor_right.g > 0.5 && textColor_right.b <= 0.6 && textColor_right.b > 0.5)
	{
				in_position_right = vec4(in_Position.x + 0.000001, in_Position.y + 90 , in_Position.z,1);
	}

	else if(textColor_right.r <= 0.5 && textColor_right.r > 0.4  && textColor_right.g <= 0.5 && textColor_right.g > 0.4 && textColor_right.b <= 0.5 && textColor_right.b > 0.4)
	{
				in_position_right = vec4(in_Position.x + 0.000001, in_Position.y + 80 , in_Position.z,1);
	}

	else if(textColor_right.r <= 0.4 && textColor_right.r > 0.3  && textColor_right.g <= 0.4 && textColor_right.g > 0.3 && textColor_right.b <= 0.4 && textColor_right.b > 0.3)
	{
				in_position_right = vec4(in_Position.x + 0.000001, in_Position.y + 70 , in_Position.z,1);
	}

	else if(textColor_right.r <= 0.3 && textColor_right.r > 0.2  && textColor_right.g <= 0.3 && textColor_right.g > 0.2 && textColor_right.b <= 0.3 && textColor_right.b > 0.2)
	{
				in_position_right = vec4(in_Position.x + 0.000001, in_Position.y + 60 , in_Position.z,1);
	}

	else if(textColor_right.r <= 0.2 && textColor_right.r > 0.1  && textColor_right.g <= 0.2 && textColor_right.g > 0.1 && textColor_right.b <= 0.2 && textColor_right.b > 0.1)
	{
				in_position_right = vec4(in_Position.x + 0.000001, in_Position.y + 50 , in_Position.z,1);
	}


	else if(textColor_right.r <= 0.1 && textColor_right.r > 0.01  && textColor_right.g <= 0.1 && textColor_right.g > 0.01 && textColor_right.b <= 0.1 && textColor_right.b > 0.01)
	{
				in_position_right = vec4(in_Position.x + 0.000001, in_Position.y + 40 , in_Position.z,1);
	}

	else
	{
				in_position_right = vec4(in_Position.x + 0.000001, in_Position.y + 20 , in_Position.z,1);
	}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//adjusting y position for up

	//in_position_up = vec4(in_Position.x , in_Position.y, in_Position.z + 0.000001,1);


	if(textColor_up.r > 1 && textColor_up.g > 1 && textColor_up.b > 1)
	{
				in_position_up = vec4(in_Position.x , in_Position.y + 140 , in_Position.z + 0.000001,1);
	}

	else if(textColor_up.r <= 1 && textColor_up.r > 0.9  && textColor_up.g <= 1 && textColor_up.g > 0.9 && textColor_up.b <= 1 && textColor_up.b > 0.9)
	{
				in_position_up = vec4(in_Position.x , in_Position.y + 130 , in_Position.z + 0.001,1);
	}

	else if(textColor_up.r <= 0.9 && textColor_up.r > 0.8  && textColor_up.g <= 0.9 && textColor_up.g > 0.8 && textColor_up.b <= 0.9 && textColor_up.b > 0.8)
	{
				in_position_up = vec4(in_Position.x , in_Position.y + 120 , in_Position.z  + 0.001,1);

	}

	else if(textColor_up.r <= 0.8 && textColor_up.r > 0.7  && textColor_up.g <= 0.8 && textColor_up.g > 0.7 && textColor_up.b <= 0.8 && textColor_up.b > 0.7)
	{
				in_position_up = vec4(in_Position.x , in_Position.y + 110 , in_Position.z + 0.001,1);
	}

	else if(textColor_up.r <= 0.7 && textColor_up.r > 0.6  && textColor_up.g <= 0.7 && textColor_up.g > 0.6 && textColor_up.b <= 0.7 && textColor_up.b > 0.6)
	{
				in_position_up = vec4(in_Position.x , in_Position.y + 100 , in_Position.z + 0.001,1);
	}

	else if(textColor_up.r <= 0.6 && textColor_up.r > 0.5  && textColor_up.g <= 0.6 && textColor_up.g > 0.5 && textColor_up.b <= 0.6 && textColor_up.b > 0.5)
	{
				in_position_up = vec4(in_Position.x , in_Position.y + 90 , in_Position.z + 0.001,1);
	}

	else if(textColor_up.r <= 0.5 && textColor_up.r > 0.4  && textColor_up.g <= 0.5 && textColor_up.g > 0.4 && textColor_up.b <= 0.5 && textColor_up.b > 0.4)
	{
				in_position_up = vec4(in_Position.x , in_Position.y + 80 , in_Position.z + 0.001,1);
	}

	else if(textColor_up.r <= 0.4 && textColor_up.r > 0.3  && textColor_up.g <= 0.4 && textColor_up.g > 0.3 && textColor_up.b <= 0.4 && textColor_up.b > 0.3)
	{
				in_position_up = vec4(in_Position.x , in_Position.y + 70 , in_Position.z + 0.001,1);
	}

	else if(textColor_up.r <= 0.3 && textColor_up.r > 0.2  && textColor_up.g <= 0.3 && textColor_up.g > 0.2 && textColor_up.b <= 0.3 && textColor_up.b > 0.2)
	{
				in_position_up = vec4(in_Position.x , in_Position.y + 60 , in_Position.z + 0.001,1);
	}

	else if(textColor_up.r <= 0.2 && textColor_up.r > 0.1  && textColor_up.g <= 0.2 && textColor_up.g > 0.1 && textColor_up.b <= 0.2 && textColor_up.b > 0.1)
	{
				in_position_up = vec4(in_Position.x , in_Position.y + 50 , in_Position.z + 0.001,1);
	}


	else if(textColor_up.r <= 0.1 && textColor_up.r > 0.01  && textColor_up.g <= 0.1 && textColor_up.g > 0.01 && textColor_up.b <= 0.1 && textColor_up.b > 0.01)
	{
				in_position_up = vec4(in_Position.x , in_Position.y + 40 , in_Position.z + 0.001,1);
	}

	else
	{
				in_position_up = vec4(in_Position.x , in_Position.y + 20 , in_Position.z + 0.001,1);
	}

	

	vec3 AB = vec3(in_position_right.x - in_Position.x , in_position_right.y - in_Position.y, in_position_right.z - in_Position.z);
	vec3 AC = vec3(in_position_up.x - in_Position.x , in_position_up.y - in_Position.y, in_position_up.z - in_Position.z);

	AB = -1 * normalize(AB);
	AC = -1 * normalize(AC);

	vec3 new_normal_crossed = cross(AB,AC);
	//out_Normal = new_normal_crossed;
	out_Normal = -1 * normalize(new_normal_crossed);


	gl_Position = Projection * ModelView * pos;
}