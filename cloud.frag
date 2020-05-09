#version 150 // GLSL 150 = OpenGL 3.2

out vec4 fragColor;
in vec2 out_TexCoord;

uniform sampler2D tex;

void main() 
{
	
//	if(true)
//	{
		fragColor = texture(tex, out_TexCoord);
//	}
//
//	else
//	{
//		fragColor = vec4(out_TexCoord,0,1);
//	}

	//fragColor = texture(tex, out_TexCoord);

	//if()
	//{

		//fragColor.xyz = vec3(1,1,1);
		//fragColor.a = 1;
	//}

//	else if(fragColor.r >= 0.5 && fragColor.g >= 0.5 && fragColor.b >= 0.5)
//	{
//		fragColor = texture(tex, out_TexCoord);
//		fragColor.a = 0.5;
//	}

//	else
//	{
//		fragColor = texture(tex, out_TexCoord);
//		fragColor.a = 0;
//	}

}
