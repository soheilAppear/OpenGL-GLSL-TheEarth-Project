#version 150 // GLSL 150 = OpenGL 3.2

out vec4 fragColor;
in vec2 out_TexCoord;
uniform sampler2D tex;


out vec4 fragColor2;
in vec2 out_TexCoord2;
uniform sampler2D tex2;


in vec3 out_Normal;    // Fragment position normal vector
out vec4 normal_color;

vec3 camPos = vec3(2,2,2);   // I'm not sure about this at all!



in vec4 light_position_in_camera; // position of the light in camera coordinates




float diffuseScalar(vec3 normal, vec3 lightDir, bool frontBackSame)
{
	/* Basic equation for diffuse shading */

	float diffuse = dot(normalize(lightDir), normalize(normal.xyz));


	if(frontBackSame)
		diffuse = abs(diffuse);
	else
		diffuse = clamp(diffuse, 0, 1);

	diffuse = diffuse/2 + .5;

	return diffuse;
}


void main() 
{
		//vec3 normalized_normal_vector = (normalize(out_Normal));


		fragColor = texture(tex, out_TexCoord);
		fragColor = texture(tex2, out_TexCoord2);
		normal_color.xyz = out_Normal;
		normal_color.a = 1;

	


}
