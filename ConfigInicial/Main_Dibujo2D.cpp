//PrevioModificado2.							Andros Calles  
//10 / 02 / 2026								320004647
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 800;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);
	//Variable de tipo shader, el sahder y la ruta de los mismos)
    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	//Definicion de los vertices que ocupamos, que son los que dibujan
	//las posiciones que tienen las cordenadas x,y,z dejamos en 0 la Z
	// A lado ponemos el color que queremos en formato RGB
	// El resultado de estos vertices nos permite crear al cubo de Geometry Dash
	
	//Previo2.							Andros Calles  
	//10 / 02 / 2026								320004647


	float vertices[] = {
		0.5f,  0.5f, 0.0f,	0.984f,0.949f,0.2117f,		// punta arriba derecha T1
		0.5f, -0.5f, 0.0f,	0.988f, 0.596f, 0.1764f,	// abajo derecha T1
		-0.5f, -0.5f, 0.0f,	0.988f, 0.596f, 0.1764f,	// abajo punta izquierda T1
		-0.5f,  0.5f, 0.0f,	0.984f,0.949f,0.2117f,		// 2punta arriba izquierda T2
		-0.5f, -0.5f, 0.0f,	0.988f, 0.596f, 0.1764f,	//2punta izquierda abajo T2
		0.5f,  0.5f, 0.0f,	0.984f,0.949f,0.2117f,		// top left T2
		0.200f,0.175f,0.0f,	0.3176f,0.7529f,0.9098f,	// Ojo Derecho
		-0.200f,0.175f,0.0f,	0.3176f,0.7529f,0.9098f,	// Ojo Izquierdo
		0.200f,-0.250f,0.0f,	0.3176f,0.7529f,0.9098f,	// Boca 
		0.050f,-0.250f,0.0f,	0.3176f,0.7529f,0.9098f,	// Boca 
		-0.050f,-0.250f,0.0f,	0.3176f,0.7529f,0.9098f,	// Boca 
		-0.200f,-0.250f,0.0f,	0.3176f,0.7529f,0.9098f,	// Boca 
		0.5f,  0.5f, 0.0f,	0.6392f,0.6235f,0.1333f,	// Outline claro
		0.5f, -0.5f, 0.0f,	0.529f,0.4549f,0.0745f,		// Outline oscuro
		-0.5f, -0.5f, 0.0f,	0.529f,0.4549f,0.0745f,		// Outline oscuro
		-0.5f,  0.5f, 0.0f,	0.6392f,0.6235f,0.1333f,	//Outline Claro
		-0.325f,0.3f,0.0f,	0.0f,0.0f,0.0f,	//Ojo Izquierda TopIzq
		-0.325f,0.05f,0.0f,	0.0f,0.0f,0.0f,	//Ojo Izquierda BotDer
		-0.075f,0.05f,0.0f,	0.0f,0.0f,0.0f,	//Ojo Izquierda BotIzq
		-0.075f,0.3f,0.0f,	0.0f,0.0f,0.0f,	//Ojo Izquierda TopDer
		0.325f,0.3f,0.0f,	0.0f,0.0f,0.0f,	//Ojo  Derecha TopIzq
		0.325f,0.05f,0.0f,	0.0f,0.0f,0.0f,	//Ojo Derecha BotDer
		0.075f,0.05f,0.0f,	0.0f,0.0f,0.0f,	//Ojo Derecha BotIzq
		0.075f,0.3f,0.0f,	0.0f,0.0f,0.0f,	//Ojo  Derecha TopDer
		-0.325f,-0.125f,0.0f,	0.0f,0.0f,0.0f,	//Boca Izquierda TopIzq
		-0.325f,-0.375f,0.0f,	0.0f,0.0f,0.0f,	//Boca Izquierda BotIzq
		0.325f,-0.375f,0.0f,	0.0f,0.0f,0.0f,	//Boca Derecha BotDer
		0.325f,-0.125f,0.0f,	0.0f,0.0f,0.0f,	//Boca Derecha TopDer

	};
	// Inidces de los vertices para dibujar los vertices con diferentes funciones.
	unsigned int indices[] = {  // note that we start from 0!
		3,2,1,// second Triangle
		0,1,3,
		
	};

	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);
  
        //Cuadrado Amarillo
        glDrawArrays(GL_TRIANGLES,0,3);
		glDrawArrays(GL_TRIANGLES, 3, 5);
  //      //glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0);

        //Ojos y Boca
        glPointSize(100);
        glDrawArrays(GL_POINTS,6,6);
        //Contorno del Cubo
		glLineWidth(50);
		glDrawArrays(GL_LINE_LOOP,12,4);
		//Contorno de los ojos y cara
        glDrawArrays(GL_LINE_LOOP,16,4);
		glDrawArrays(GL_LINE_LOOP, 20, 4);
		glDrawArrays(GL_LINE_LOOP, 24, 4);

        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}