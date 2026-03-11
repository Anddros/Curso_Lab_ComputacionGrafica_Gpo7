//Previo 5						Calles Cedeño Andros Gael
//03 / 03 / 2026								320004647
#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

//For model
float	parteSup = 0.0f,
parteMid = 0.0f,
parteBaj= 0.0f,
dedo1=0,
dedo2=0,
dedo3 = 0;



int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado jerarquico_ Calles Cedeño Andros Gael", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	// use with Orthographic Projection




	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f,  0.5f, 0.5f,
		0.5f,  0.5f, 0.5f,
		-0.5f,  0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		-0.5f, -0.5f,-0.5f,
		 0.5f, -0.5f,-0.5f,
		 0.5f,  0.5f,-0.5f,
		 0.5f,  0.5f,-0.5f,
		-0.5f,  0.5f,-0.5f,
		-0.5f, -0.5f,-0.5f,

		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp



		//View set up 
		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));


		glBindVertexArray(VAO);
		//Practica 5						Calles Cedeño Andros Gael
		// 08 / 03 / 2026								320004647
		
		//Garra Parte Superior
		model = glm::rotate(model, glm::radians(parteSup), glm::vec3(0.0f, 0.0f, 1.0f)); //parteSup
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 3.0f, 1.0f));
		color = glm::vec3(0.8470f, 0.4823f, 0.1294f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//A
		
		//Garra Parte Media
		model = glm::translate(modelTemp, glm::vec3(0.0f, -2.5f, 0.0f));
		model = glm::rotate(model, glm::radians(parteMid), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTemp = model;
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		color = glm::vec3(0.8784f, 0.6117f, 0.1686f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//B

		////Garra parte baja
		model = glm::translate(modelTemp, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::rotate(model, glm::radians(parteBaj), glm::vec3(1.0f, 0.0f, 0.0f));
		modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.0f, 0.25f, 0.0f));
		model = glm::scale(model, glm::vec3(2.75f, 1.0f, 2.75f));
		color = glm::vec3(0.9098f, 0.6980f, 0.2117f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//C

		//Practica 5						Calles Cedeño Andros Gael
		// 08 / 03 / 2026								320004647
 
		// DEDO 1 
		glm::mat4 baseDedo1 = glm::rotate(modelTemp2, glm::radians(315.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		baseDedo1 = glm::translate(baseDedo1, glm::vec3(1.25f, -0.5f, 0.0f));

		// Falange A
		model = glm::rotate(baseDedo1, glm::radians(dedo1), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 modelTempD1 = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 1.0f, 0.65f));
		color = glm::vec3(0.3568f, 0.4509f, 0.6588f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Falange B
		model = glm::translate(modelTempD1, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 modelTempD1_B = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.65f, 1.0f, 0.55f));
		color = glm::vec3(0.4f, 0.4823f, 0.6901f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Falange C (Punta )
		model = glm::translate(modelTempD1_B, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.55f, 1.0f, 0.45f));
		color = glm::vec3(0.8313f, 0.2941f, 0.1725f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);



		//Practica 5						Calles Cedeño Andros Gael
		// 08 / 03 / 2026								320004647

		//DEDO 2
		glm::mat4 baseDedo2 = glm::rotate(modelTemp2, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		baseDedo2 = glm::translate(baseDedo2, glm::vec3(1.25f, -0.5f, 0.0f));
		// Falange A
		model = glm::rotate(baseDedo2, glm::radians(dedo1), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 modelTempD2 = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 1.0f, 0.65f));
		color = glm::vec3(0.3568f, 0.4509f, 0.6588f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Falange B
		model = glm::translate(modelTempD2, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 modelTempD2_B = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.65f, 1.0f, 0.55f));
		color = glm::vec3(0.4f, 0.4823f, 0.6901f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// Falange C (Punta)
		model = glm::translate(modelTempD2_B, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.55f, 1.0f, 0.45f));
		color = glm::vec3(0.8313f, 0.2941f, 0.1725f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Practica 5						Calles Cedeño Andros Gael
		// 08 / 03 / 2026								320004647

		//DEDO 3
		glm::mat4 baseDedo3 = glm::rotate(modelTemp2, glm::radians(155.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		baseDedo3 = glm::translate(baseDedo3, glm::vec3(1.25f, -0.5f, 0.0f));
		// Falange A
		model = glm::rotate(baseDedo3, glm::radians(dedo1), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 modelTempD3 = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 1.0f, 0.65f));
		color = glm::vec3(0.3568f, 0.4509f, 0.6588f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Falange B
		model = glm::translate(modelTempD3, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 modelTempD3_B = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.65f, 1.0f, 0.55f));
		color = glm::vec3(0.4f, 0.4823f, 0.6901f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// Falange C (Punta)
		model = glm::translate(modelTempD3_B, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.55f, 1.0f, 0.45f));
		color = glm::vec3(0.8313f, 0.2941f, 0.1725f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Practica 5						Calles Cedeño Andros Gael
		// 08 / 03 / 2026								320004647

		// DEDO 4 
		glm::mat4 baseDedo4 = glm::rotate(modelTemp2, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		baseDedo4 = glm::translate(baseDedo4, glm::vec3(1.25f, -0.5f, 0.0f));
		// Falange A
		model = glm::rotate(baseDedo4, glm::radians(dedo1), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 modelTempD4 = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 1.0f, 0.65f));
		color = glm::vec3(0.3568f, 0.4509f, 0.6588f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// Falange B
		model = glm::translate(modelTempD4, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 modelTempD4_B = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.65f, 1.0f, 0.55f));
		color = glm::vec3(0.4f, 0.4823f, 0.6901f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// Falange C (Punta)
		model = glm::translate(modelTempD4_B, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.55f, 1.0f, 0.45f));
		color = glm::vec3(0.8313f, 0.2941f, 0.1725f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Practica 5						Calles Cedeño Andros Gael
		// 08 / 03 / 2026								320004647

		//DEDO 5
		glm::mat4 baseDedo5 = glm::rotate(modelTemp2, glm::radians(25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		baseDedo5 = glm::translate(baseDedo5, glm::vec3(1.25f, -0.5f, 0.0f));
		// Falange A
		model = glm::rotate(baseDedo5, glm::radians(dedo1), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 modelTempD5 = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 1.0f, 0.65f));
		color = glm::vec3(0.3568f, 0.4509f, 0.6588f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// Falange B
		model = glm::translate(modelTempD5, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 modelTempD5_B = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.65f, 1.0f, 0.55f));
		color = glm::vec3(0.4f, 0.4823f, 0.6901f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// Falange C (Punta)
		model = glm::translate(modelTempD5_B, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.55f, 1.0f, 0.45f));
		color = glm::vec3(0.8313f, 0.2941f, 0.1725f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	
		glBindVertexArray(0);

		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.08f;
	 if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
		 movY += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.18f;
	 
	 //Controles Parte Superior Garra
	 if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		 parteSup += 0.18f;;
		 if (parteSup > 5.0f) parteSup = 5.0f; // Límite de apertura
	 }
	 if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		 parteSup -= 0.18f;
		 if (parteSup < -5.0f) parteSup = -5.0f; // Límite de cierre
	 }

	 //Controles Parte Media Garra
	 if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
		 parteMid += 0.18f;;
		 if (parteMid > 15.0f) parteMid = 15.0f; // Límite de apertura
	 }
	 if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		 parteMid -= 0.18f;
		 if (parteMid < -15.0f) parteMid = -15.0f; // Límite de cierre
	 }

	 //Controles Parte Baja Garra
	 if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		 parteBaj -= 0.18f;
		 if (parteBaj < -15.0f) parteBaj = -15.0f; // Límite de cierre
	 }

	 if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		 parteBaj += 0.18f;;
		 if (parteBaj > 15.0f) parteBaj = 15.0f; // Límite de apertura
	 }

	 //Controles Falange 1
	 if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		 dedo1 += 0.18f;
		 if (dedo1 > 45.0f) dedo1 = 45.0f; // Límite de apertura
	 }
	 if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		 dedo1 -= 0.18f;
		 if (dedo1 < -7.0f) dedo1 = -7.0f; // Límite de cierre
	 }
	 //Controles Falange 2
	 if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		 dedo2 += 0.18f;
		 if (dedo2 > 45.0f) dedo2 = 45.0f;// Límite de apertura
	 }
	 if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		 dedo2 -= 0.18f;
		 if (dedo2 < -10.0f) dedo2 = -10.0f;// Límite de cierre
	 }
	 //Controles Falange 3
	 if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		 dedo3 += 0.18f;
		 if (dedo3 > 60.0f) dedo3 = 60.0f;// Límite de apertura
	 }
	 if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		 dedo3 -= 0.18f;
		 if (dedo3 < -10.0f) dedo3 = -10.0f;// Límite de cierre
	 }
 }


