//Practica 7					Calles Cedeño Andros Gael
//22 / 03 / 2026								320004647
#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"
#include "Camera.h"


// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

// Light attributes
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

							// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	//Practica 7						Calles Cedeño Andros Gael
	//21 / 03 / 2026								320004647
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Texturizado_ Calles Cedeño Andros Gael", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);


	// Build and compile our shader program
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		//Practica 7						Calles Cedeño Andros Gael
		//22 / 03 / 2026								320004647
		// Posicion            // Colores            // Coordenadas de la Textura (U,V)
//Dado Caras
// Frente (Cara Delante Dado)
		-0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    0.7500f, 0.3333f, // esq inf izq (izq abajo)
		 0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.3333f, // esq inf derecha (derecha abajo)
		 0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    1.0f, 0.6666f, // esq sup derecha (derecha arriba)
		-0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    0.7500f, 0.6666f, // esq sup izq (iz arriba)

		// Atras (Cara Atrás Dado)
		-0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.25f, 0.3333f,	// esq inf izq (izq abajo)
		 0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.5f, 0.3333f,	// esq inf derecha (derecha abajo)
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.5f, 0.6666f,	// esq sup derecha (derecha arriba)
		-0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.25f, 0.6666f,	// esq sup izq (iz arriba)

		// Derecha (Cara Der Dado)
		 0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    0.5f, 0.6666f,	// esq inf izq (izq abajo)
		 0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.75f, 0.6666f,	// esq inf derecha (derecha abajo)
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.75f, 1.0f,		// esq sup derecha (derecha arriba)
		 0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    0.5f, 1.0f,		// esq sup izq (iz arriba)

		// Izquierda (Cara Izq Dado)
		-0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    0.5f, 0.3333f, // esq sup izq (iz arriba)
		-0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.75f, 0.3333f, // esq sup derecha (derecha arriba)
		-0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.75f, 0.0000f, // esq inf derecha (derecha abajo)
		-0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    0.5f, 0.0000f, // esq inf izq (izq abajo)

		// Abajo (Cara Abajo Dado)
		-0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.0000f, 0.3333f, // esq inf izq (izq abajo)
		 0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.25f, 0.3333f, // esq inf derecha (derecha abajo)
		 0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    0.25f, 0.6666f, // esq sup derecha (derecha arriba)
		-0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    0.0000f, 0.6666f, // esq sup izq (iz arriba)

		// Arriba (Cara Arriba Dado)
		-0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.5f, 0.3333f, // esq inf izq (izq abajo)
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 1.0f,    0.75f, 0.3333f, // esq inf derecha (derecha abajo)
		 0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    0.75f, 0.6666f, // esq sup derecha (derecha arriba)
		-0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 1.0f,    0.5f, 0.6666f, // esq sup izq (iz arriba)
	};

	GLuint indices[] = {
		0, 1, 2,     2, 3, 0,   // Frente
		4, 5, 6,     6, 7, 4,   // Atrás
		8, 9, 10,    10, 11, 8, // Derecha
		12, 13, 14,  14, 15, 12, // Izquierda
		16, 17, 18,  18, 19, 16, // Abajo
		20, 21, 22,  22, 23, 20  // Arriba
	};

	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Load textures
	//Generamos un identificador para las texturas
	GLuint texture1;
	glGenTextures(1, &texture1);
	//Para enlazar el identificador con una textura 2D
	glBindTexture(GL_TEXTURE_2D,texture1);
	//Guardamos en enteros el tamaño de la textura y cuantos canales tiene
	int textureWidth, textureHeight,nrChannels;
	//Nos ayuda a voltear la imagen debido a que la libreria pone la coordenada 0,0 en la esquina superior izq y la nececistamos en la esquina inf izq
	stbi_set_flip_vertically_on_load(true);
	unsigned char *image;
	//Configuramos como se usa la textura (Que es un elemento 2D, LA FORMA EN LA QUE SE CARGA, LA FORMA EN LA QUE SE USA CUANDO SE SOBREPASEN LAS COORDS)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Diffuse map
	//La ruta de donde se encuentra la textura (ubicacion,tamaño,tamaño,numero de canales a utilizar)
	//Practica 7						Calles Cedeño Andros Gael
	//22 / 03 / 2026								320004647
	image = stbi_load("images/Dado.png", &textureWidth, &textureHeight, &nrChannels,0);
	//Lo enlzamos con el tipo de textura y el identificador
	glBindTexture(GL_TEXTURE_2D, texture1);
	//Usamos la informacion de arriba para ahora si convertirlo en una textura 2D (info,indicamos que es textura,modelo de color, parametros ancho,altura,
	// que tipo va a ser)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	//Ayuda a optimizar ya que al alejar nos muestra una imagen mas optimizada
	glGenerateMipmap(GL_TEXTURE_2D);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);

	

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Activamos el shader
		lampShader.Use();
		//// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 model(1);
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lampShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lampShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lampShader.Program, "projection");
		//Practica 7						Calles Cedeño Andros Gael
		//22 / 03 / 2026								320004647
		// Bind diffuse map
		//Activamos el uso de la textura de indice 0
		glActiveTexture(GL_TEXTURE0);
		//Asociamos el indentificador con el tipo de textura
		glBindTexture(GL_TEXTURE_2D, texture1);

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(VAO);
		//Dibujamos nuestros elementos 
		glDrawElements(GL_TRIANGLES, 36 , GL_UNSIGNED_INT, 0);


		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}