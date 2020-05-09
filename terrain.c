/** @file Demonstrates 3D shapes of the earth.
 *
 * @author Soheil Sepahyar
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "libkuhl.h"

static GLuint program = 0; /**< id value for the GLSL program */
static kuhl_geometry triangle;
static kuhl_geometry quad;

float my_view_mat[9];


static GLuint program_cloud = 1; // Duck GLSL Program

float initCamPos[3]  = {0,0,100}; // location of camera
float initCamLook[3] = {0,0,0}; // a point the camera is facing at
float initCamUp[3]   = {0,1,0}; // a vector indicating which direction is up


/* Called by GLFW whenever a key is pressed. */
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/* If the library handles this keypress, return */
	if (kuhl_keyboard_handler(window, key, scancode, action, mods))
		return;

	/* custom key handling code here */
}

/** Draws the 3D scene. */
void display()
{
	/* Render the scene once for each viewport. Frequently one
	 * viewport will fill the entire screen. However, this loop will
	 * run twice for HMDs (once for the left eye and once for the
	 * right). */
	viewmat_begin_frame();
	for(int viewportID=0; viewportID<viewmat_num_viewports(); viewportID++)
	{
		viewmat_begin_eye(viewportID);

		/* Where is the viewport that we are drawing onto and what is its size? */
		int viewport[4]; // x,y of lower left corner, width, height
		viewmat_get_viewport(viewport, viewportID);
		/* Tell OpenGL the area of the window that we will be drawing in. */
		glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

		/* Clear the current viewport. Without glScissor(), glClear()
		 * clears the entire screen. We could call glClear() before
		 * this viewport loop---but in order for all variations of
		 * this code to work (Oculus support, etc), we can only draw
		 * after viewmat_begin_eye(). */
		glScissor(viewport[0], viewport[1], viewport[2], viewport[3]);
		glEnable(GL_SCISSOR_TEST);
		glClearColor(.2,.2,.2,0); // set clear color to grey
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glDisable(GL_SCISSOR_TEST);
		glEnable(GL_DEPTH_TEST); // turn on depth testing
		kuhl_errorcheck();

		glEnable(GL_BLEND); // enable use of the alpha value
		// tell OpenGL how to use the alpha value:
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);



		/* Get the view matrix and the projection matrix */
		float viewMat[16], perspective[16];
		viewmat_get(viewMat, perspective, viewportID);
		
		
		//float XH = cos(glfwGetTime()) * 1000;
		//float YK = sin(glfwGetTime())* 1000;
		///pow(XH,2) + pow(YK,2) = pow(1000,2);  we know this


		mat4f_lookat_new( viewMat,  cos(glfwGetTime()) * 1000 + 7000 , 200 + sin(glfwGetTime()) * 120 , -1* sin(glfwGetTime())* 1000 - 6000,    500 ,0, -500 + glfwGetTime() * 10  ,   0,1,0);

		

		/* Calculate an angle to rotate the object. glfwGetTime() gets
		 * the time in seconds since GLFW was initialized. Rotates 45 degrees every second. */
		float angle = fmod(glfwGetTime()*45, 360);

		/* Make sure all computers/processes use the same angle */
		dgr_setget("angle", &angle, sizeof(GLfloat));

		/* Create a 4x4 rotation matrix based on the angle we computed. */
		float rotateMat[16];
		mat4f_rotateAxis_new(rotateMat, 0, 1 ,0 ,0);

		/* Create a scale matrix. */
		float scaleMat[16];
		mat4f_scale_new(scaleMat, 10, 1, -8);

		/* Combine the scale and rotation matrices into a single model matrix.
		   modelMat = scaleMat * rotateMat
		*/
		float modelMat[16];
		mat4f_mult_mat4f_new(modelMat, scaleMat, rotateMat);

		/* Construct a modelview matrix: modelview = viewMat * modelMat */
		float modelview[16];
		mat4f_mult_mat4f_new(modelview, viewMat, modelMat);

		/* Tell OpenGL which GLSL program the subsequent
		 * glUniformMatrix4fv() calls are for. */
		kuhl_errorcheck();
		glUseProgram(program);
		kuhl_errorcheck();
		
		/* Send the perspective projection matrix to the vertex program. */
		glUniformMatrix4fv(kuhl_get_uniform("Projection"),
		                   1, // number of 4x4 float matrices
		                   0, // transpose
		                   perspective); // value
		/* Send the modelview matrix to the vertex program. */
		glUniformMatrix4fv(kuhl_get_uniform("ModelView"),
		                   1, // number of 4x4 float matrices
		                   0, // transpose
		                   modelview); // value
		
		/* Generate an appropriate normal matrix based on the model view matrix:
		  normalMat = transpose(inverse(modelview))
		*/
		float normalMat[9];
		mat3f_from_mat4f(normalMat, modelview);
		mat3f_invert(normalMat);
		mat3f_transpose(normalMat);
		glUniformMatrix3fv(kuhl_get_uniform("NormalMat"),
		                   1, // number of 3x3 float matrices
		                   0, // transpose
		                   normalMat); // value

		kuhl_errorcheck();
		/* Draw the geometry using the matrices that we sent to the
		 * vertex programs immediately above */
		kuhl_geometry_draw(&triangle);
		//kuhl_geometry_draw(&quad);



		/////////////////////////////////////////////////////////////////////////////////////////////////


		float  perspectiveC[16];

		viewmat_get(viewMat, perspectiveC, viewportID);

		
		mat4f_lookat_new( viewMat,  cos(glfwGetTime()) * 1000 + 7000 , 300 + sin(glfwGetTime()) * 120 , -1* sin(glfwGetTime())* 1000 - 6000,    1000 ,0, -1000 ,   0,1,0);


		/* Calculate an angle to rotate the object. glfwGetTime() gets
		 * the time in seconds since GLFW was initialized. Rotates 45 degrees every second. */
		//float angle = fmod(0, 360);
		float angle2 = 90;

		/* Make sure all computers/processes use the same angle */
		dgr_setget("angle", &angle2, sizeof(GLfloat));

		/* Create a 4x4 rotation matrix based on the angle we computed. */
		float rotateMatC[16];
		mat4f_rotateAxis_new(rotateMatC, angle2, 1,0,0);

		/* Create a scale matrix. */
		float scaleMatC[16];
		mat4f_scale_new(scaleMatC, 12000 , 1, 8000);

		float translate_matC[16];
		mat4f_translate_new(translate_matC, 0.5 , -0.5, -300);

		//float translate_matC2[16];
		//mat4f_translate_new(translate_matC2, 0, 0, -200);

		/* Combine the scale and rotation matrices into a single model matrix.
		   modelMat = scaleMat * rotateMat
		*/
		float modelMatC[16];
		mat4f_mult_mat4f_new(modelMatC, scaleMatC, rotateMatC);

		//float modelMatnC[16];
		mat4f_mult_mat4f_new(modelMatC, modelMatC, translate_matC);

		/* Construct a modelview matrix: modelview = viewMat * modelMat */


		float scaleMatCf[16];
		mat4f_scale_new(scaleMatCf, 3/2 , 1, 1);
		mat4f_mult_mat4f_new(modelMatC, scaleMatCf, modelMatC);

		float modelviewC[16];
		mat4f_mult_mat4f_new(modelviewC, viewMat, modelMatC);

		/* Tell OpenGL which GLSL program the subsequent
		 * glUniformMatrix4fv() calls are for. */
		
		kuhl_errorcheck();
		glUseProgram(program_cloud);
		kuhl_errorcheck();
		
		/* Send the perspective projection matrix to the vertex program. */
		glUniformMatrix4fv(kuhl_get_uniform("Projection"),
		                   1, // number of 4x4 float matrices
		                   0, // transpose
		                   perspectiveC); // value
		/* Send the modelview matrix to the vertex program. */
		glUniformMatrix4fv(kuhl_get_uniform("ModelView"),
		                   1, // number of 4x4 float matrices
		                   0, // transpose
		                   modelviewC); // value
		

		kuhl_errorcheck();
		/* Draw the geometry using the matrices that we sent to the
		 * vertex programs immediately above */
	
		kuhl_errorcheck();	
		kuhl_geometry_draw(&quad);



		//glUseProgram(0); // stop using a GLSL program.
		viewmat_end_eye(viewportID);
	} // finish viewport loop
	viewmat_end_frame();

	/* Check for errors. If there are errors, consider adding more
	 * calls to kuhl_errorcheck() in your code. */
	kuhl_errorcheck();

}

void init_geometryTriangle(kuhl_geometry *geom, GLuint prog)
{


	kuhl_geometry_new(geom, prog, 6000000, // num vertices
	                  GL_TRIANGLES); // primitive type

	GLfloat * vertices = (GLfloat*) malloc((6 * 3 * 1000000) * sizeof(GLfloat));   // We should use dynamic array in order to use for nested loops for our purpose
	int my_counter = 0;

	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			vertices[my_counter++] = j;
			vertices[my_counter++] = 0;
			vertices[my_counter++] = i;

			vertices[my_counter++] = j+1;
			vertices[my_counter++] = 0;
			vertices[my_counter++] = i;

			vertices[my_counter++] = j+1;
			vertices[my_counter++] = 0;
			vertices[my_counter++] = i+1;

///////////////////////////////////////////////////////////////

			vertices[my_counter++] = j;
			vertices[my_counter++] = 0;
			vertices[my_counter++] = i;

			vertices[my_counter++] = j;
			vertices[my_counter++] = 0;
			vertices[my_counter++] = i+1;

			vertices[my_counter++] = j+1;
			vertices[my_counter++] = 0;
			vertices[my_counter++] = i+1;

		}
		
	}


		 kuhl_geometry_attrib(geom, vertices, // data
		   3, // number of components (x,y,z)
		   "in_Position", // GLSL variable
		   KG_WARN); // warn if attribute is missing in GLSL program?	

	



GLfloat * normalData = (GLfloat*) malloc((6 * 3 * 1000000) * sizeof(GLfloat));   // We should use dynamic array in order to use for nested loops for our purpose
int my_counter_normals = 0;



	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			normalData[my_counter_normals++] = 0;
			normalData[my_counter_normals++] = 1;
			normalData[my_counter_normals++] = 0;

			normalData[my_counter_normals++] = 0;
			normalData[my_counter_normals++] = 1;
			normalData[my_counter_normals++] = 0;

			normalData[my_counter_normals++] = 0;
			normalData[my_counter_normals++] = 1;
			normalData[my_counter_normals++] = 0;

			normalData[my_counter_normals++] = 0;
			normalData[my_counter_normals++] = 1;
			normalData[my_counter_normals++] = 0;

			normalData[my_counter_normals++] = 0;
			normalData[my_counter_normals++] = 1;
			normalData[my_counter_normals++] = 0;

			normalData[my_counter_normals++] = 0;
			normalData[my_counter_normals++] = 1;
			normalData[my_counter_normals++] = 0;

		}
		
	}


	kuhl_geometry_attrib(geom, normalData, 3, "in_Normal", KG_WARN);



	GLfloat * textures = (GLfloat*) malloc((6 * 2 * 1000000) * sizeof(GLfloat));   // We should use dynamic array in order to use for nested loops for our purpose
	int my_counter_tex = 0;


	/* Load the texture. It will be bound to texId */	

	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			textures[my_counter_tex++] = j;
			textures[my_counter_tex++] = i;

			textures[my_counter_tex++] = j+1;
			textures[my_counter_tex++] = i;

			textures[my_counter_tex++] = j+1;
			textures[my_counter_tex++] = i+1;

			textures[my_counter_tex++] = j;
			textures[my_counter_tex++] = i;

			textures[my_counter_tex++] = j;
			textures[my_counter_tex++] = i+1;

			textures[my_counter_tex++] = j+1;
			textures[my_counter_tex++] = i+1;


		}
		
	}


	kuhl_geometry_attrib(geom, textures, 2, "in_TexCoord", KG_WARN);
	// The 2 parameter above means each texture coordinate is a 2D coordinate.

	/* Load the texture. It will be bound to texId */	
	GLuint texId = 0;
	float aspectRatio = kuhl_read_texture_file("../my/resized_bump.png", &texId);
	msg(MSG_DEBUG, "Aspect ratio of image is %f\n", aspectRatio); // write message to log.txt
	
	/* Tell this piece of geometry to use the texture we just loaded. */
	kuhl_geometry_texture(geom, texId, "tex", KG_WARN);

	kuhl_errorcheck();

////////////////////////////////////////////////////////////////////////////////////////////////// Second Texture

	GLfloat * textures2 = (GLfloat*) malloc((6 * 2 * 1000000) * sizeof(GLfloat));   // We should use dynamic array in order to use for nested loops for our purpose
	int my_counter_tex2 = 0;


	/* Load the texture. It will be bound to texId */	

	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j < 1000; j++)
		{
			textures2[my_counter_tex2++] = j;
			textures2[my_counter_tex2++] = i;

			textures2[my_counter_tex2++] = j+1;
			textures2[my_counter_tex2++] = i;

			textures2[my_counter_tex2++] = j+1;
			textures2[my_counter_tex2++] = i+1;

			textures2[my_counter_tex2++] = j;
			textures2[my_counter_tex2++] = i;

			textures2[my_counter_tex2++] = j;
			textures2[my_counter_tex2++] = i+1;

			textures2[my_counter_tex2++] = j+1;
			textures2[my_counter_tex2++] = i+1;


		}
		
	}


	kuhl_geometry_attrib(geom, textures2, 2, "in_TexCoord2", KG_WARN);
	// The 2 parameter above means each texture coordinate is a 2D coordinate.

	/* Load the texture. It will be bound to texId */	
	GLuint texId2 = 0;
	float aspectRatio2 = kuhl_read_texture_file("../my/resized_earth.png", &texId2);
	msg(MSG_DEBUG, "Aspect ratio of image is %f\n", aspectRatio2); // write message to log.txt
	
	/* Tell this piece of geometry to use the texture we just loaded. */
	kuhl_geometry_texture(geom, texId2, "tex2", KG_WARN);

	kuhl_errorcheck();

}

 /* This illustrates how to draw a quad by drawing two triangles and reusing vertices. */
void init_geometryQuad(kuhl_geometry *geom, GLuint prog)
{
	kuhl_geometry_new(geom, prog,
	                  4, // number of vertices
	                  GL_TRIANGLES); // type of thing to draw

	GLfloat texcoordData[] = {0, 0,
							  1, 0,
						      1, 1,
	                          0, 1};
		  

	GLfloat vertexPositions[] = {-0.5, -0.5, 0,
	                             0.5, -0.5, 0,
	                             0.5, 0.5, 0,
	                             -0.5, 0.5, 0 };							 
	kuhl_geometry_attrib(geom, vertexPositions,
	                     3, // number of components x,y,z
	                     "in_Position", // GLSL variable
	                     KG_WARN); // warn if attribute is missing in GLSL program?

	/* The normals for each vertex */
	GLfloat normalData[] = {0, 1, 0,
	                        0, 1, 0,
	                        0, 1, 0,
	                        0, 1, 0};
	kuhl_geometry_attrib(geom, normalData, 3, "in_Normal", KG_WARN);
	
	/* A list of triangles that we want to draw. "0" refers to the
	 * first vertex in our list of vertices. Every three numbers forms
	 * a single triangle. */
	GLuint indexData[] = { 0, 1, 2,  
	                       0, 2, 3 };

	kuhl_geometry_indices(geom, indexData, 6);

	kuhl_geometry_attrib(geom, texcoordData, 2, "in_TexCoord", KG_WARN);
	// The 2 parameter above means each texture coordinate is a 2D coordinate.

	/* Load the texture. It will be bound to texId */	
	GLuint texId3 = 0;
	float aspectRatio3 = kuhl_read_texture_file("../my/cloud.png", &texId3);
	msg(MSG_DEBUG, "Aspect ratio of image is %f\n", aspectRatio3); // write message to log.txt
	
	/* Tell this piece of geometry to use the texture we just loaded. */
	kuhl_geometry_texture(geom, texId3, "tex", KG_WARN);

	kuhl_errorcheck();
}


 


int main(int argc, char** argv)
{
	/* Initialize GLFW and GLEW */
	kuhl_ogl_init(&argc, argv, 512, 512, 32, 4);

	/* Specify function to call when keys are pressed. */
	glfwSetKeyCallback(kuhl_get_window(), keyboard);
	// glfwSetFramebufferSizeCallback(window, reshape);

	/* Compile and link a GLSL program composed of a vertex shader and
	 * a fragment shader. */
	program = kuhl_create_program("terrain.vert", "terrain.frag");

	/* Use the GLSL program so subsequent calls to glUniform*() send the variable to
	   the correct program. */
	glUseProgram(program);
	kuhl_errorcheck();

	init_geometryTriangle(&triangle, program);


	kuhl_errorcheck();


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////


		/* Compile and link a GLSL program composed of a vertex shader and
	 * a fragment shader. */

	program_cloud = kuhl_create_program("cloud.vert", "cloud.frag");
	glUseProgram(program_cloud);
	kuhl_errorcheck();
	/* Set the uniform variable in the shader that is named "red" to the value 1. */
	//glUniform1i(kuhl_get_uniform("red"), 1);

	init_geometryQuad(&quad, program_cloud);
	
	

	dgr_init();     /* Initialize DGR based on environment variables. */


	//float initCamPos[3]  = {700,800,-500}; // location of camera
	//float initCamLook[3] = {40000,20000,-50000}; // a point the camera is facing at
	//float initCamUp[3]   = {0,1,0}; // a vector indicating which direction is up

	viewmat_init(initCamPos, initCamLook, initCamUp);
	
	
	while(!glfwWindowShouldClose(kuhl_get_window()))
	{
		display();
		kuhl_errorcheck();

		/* process events (keyboard, mouse, etc) */
		glfwPollEvents();
	}

	exit(EXIT_SUCCESS);
}
