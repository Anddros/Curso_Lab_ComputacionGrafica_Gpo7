
//Previo 8 							Calles Cedeño Andros Gael
//24 / 03 / 2026									320004647

// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
// Properties
const GLuint WIDTH = 900, HEIGHT = 700;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;


// Light attributes
glm::vec3 lightPos(0.5f, 0.5f, 2.5f);
glm::vec3 lightPos2(-0.0f, 30.0f, -50.0f);
// Ajusta el angulo en el que se encontrara ya sea el sol/luna 
float orbitAngle = 0.0f;
// Ajusta la velocidad del ciclo
float orbitSpeed = 0.25f;
// Qué tan lejos giran del centro
float orbitRadius =50.0f; 
float movelightPos = 0.0f;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;
bool activanim = false;

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
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Materiales e Iluminacion_ Calles Cedeño Andros Gael", nullptr, nullptr);

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
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

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

    // Setup and compile our shaders
    Shader shader("Shader/modelLoading.vs", "Shader/modelLoading.frag");
    Shader lampshader("Shader/lamp.vs", "Shader/lamp.frag");
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");



    // Load models
    Model cocina_perro((char*)"Models/CocinaPerro.obj");
    Model solModel((char*)"Models/Sol.obj");
    Model lunaModel((char*)"Models/Luna.obj");
    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 200.0f);

    float vertices[] = {
        //Coordenadas de los vertices(x,y,z) Direccion del Vectro Normal
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load textures

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

    image = stbi_load("Models/Texture_albedo.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
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
        // Incrementar el ángulo basado en el tiempo
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // Luz 1 (Sol): Órbita en el plano YZ (Frente a Atrás)
        lightPos.x = 0.0f; // Centrado respecto al modelo
        lightPos.y = sin(orbitAngle) * orbitRadius; // Altura
        lightPos.z = cos(orbitAngle) * orbitRadius; // Profundidad

        // Luz 2 (Luna): 180 grados desfasada
        lightPos2.x = 0.0f;
        lightPos2.y = sin(orbitAngle + glm::radians(180.0f)) * orbitRadius;
        lightPos2.z = cos(orbitAngle + glm::radians(180.0f)) * orbitRadius;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        lightingShader.Use();
        GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position");
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(lightPosLoc, lightPos.x + movelightPos, lightPos.y + movelightPos, lightPos.z + movelightPos);
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        //Practica 8 							Calles Cedeño Andros Gael
        //29 / 03 / 2026									320004647
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        
        //Luz Sol

        // Set Light Properties
        float IntensidadSol = (lightPos.y > 0) ? 1.0f : 0.0f;
        //Para nuestra luz ambiental 
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.16f * IntensidadSol, 0.16f * IntensidadSol, 0.0f * IntensidadSol);
        // Para nuestra luz difusa 
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 0.6f * IntensidadSol, 0.6f * IntensidadSol, 0.0f * IntensidadSol);
        //Para nuestra luz especular 
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 0.75f * IntensidadSol, 0.75f * IntensidadSol, 0.5f * IntensidadSol);
        //Para calcular la posicion de la luz cuando se mueva el sol
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.position"), lightPos.x, lightPos.y, lightPos.z);


        //Practica 8 							Calles Cedeño Andros Gael
        //29 / 03 / 2026									320004647

        // Set material properties
        //Para nuestra luz ambiental
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 1.0f, 1.0f, 1.0f);
        //Para nuestra luz difusa
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);
        //Para nuestra luz especular
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 1.0f, 1.0f, 1.0f);
        //El brillo de nuestro objeto
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 1.0f);


        //Luz Luna
     
        // Set lights properties
        float IntensidadLuna = (lightPos2.y > 0) ? 1.0f : 0.0f;
        //Para nuestra luz ambiental 
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.ambient"), 0.05f * IntensidadLuna, 0.05f * IntensidadLuna, 0.0f * IntensidadLuna);
        // Para nuestra luz difusa 
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.diffuse"), 0.2f * IntensidadLuna, 0.4f * IntensidadLuna, 0.8f * IntensidadLuna);
        //Para nuestra luz especular
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.specular"), 0.4f * IntensidadLuna, 0.6f * IntensidadLuna, 1.0f * IntensidadLuna);
        //Para calcular la posicion de la luz cuando se mueva la luna
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.position"), lightPos2.x, lightPos2.y, lightPos2.z);
        
        //Practica 8 							Calles Cedeño Andros Gael
        //29 / 03 / 2026									320004647

        // Set material properties 
        //Para nuestra luz ambiental
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material2.ambient"), 0.1, 0.1, 0.1f);
        //Para nuestra luz difusa
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material2.diffuse"), 1.0f, 1.0f, 1.0f);
        //Para nuestra luz especular
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material2.specular"), 0.2f, 0.2f, 0.2f);
        //Agreamos uno para el brillo de un solo 1 elemento
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material2.shininess"), 10.0f);



        //Practica 8 							Calles Cedeño Andros Gael
        //29 / 03 / 2026									320004647
  
        // Draw the loaded model
        glm::mat4 model(1);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 10.0f));
        model = glm::scale(model, glm::vec3(0.125f, 0.125f, 0.125f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        cocina_perro.Draw(lightingShader);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        

        glBindVertexArray(0);

        // Activamos el shader de las lámparas
        lampshader.Use();

        // Pasamos las matrices de Proyección y Vista al Shader de la lámpara
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        //Dibujo del Sol
        if (IntensidadSol > 0) {
            glm::mat4 modeloSol = glm::mat4(1.0f); // Resetear matriz
            modeloSol = glm::translate(modeloSol, lightPos); // Mover a la posición de órbita
            modeloSol = glm::scale(modeloSol, glm::vec3(4.0f, 4.0f, 4.0f)); 

            glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modeloSol));
            solModel.Draw(lampshader); 
        }

        //Dibujo de la Luna
        if (IntensidadLuna > 0) {
            glm::mat4 modeloLuna = glm::mat4(1.0f); // Resetear matriz
            modeloLuna = glm::translate(modeloLuna, lightPos2);// Mover a la posición de órbita
            modeloLuna = glm::scale(modeloLuna, glm::vec3(4.0f, 4.0f, 4.0f));

            glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modeloLuna));
            lunaModel.Draw(lampshader); 
        }
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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
    if (keys[GLFW_KEY_O])
    {
        orbitAngle += orbitSpeed * deltaTime; // Gira en un sentido
    }
    if (keys[GLFW_KEY_L])
    {
        orbitAngle -= orbitSpeed * deltaTime; // Gira en sentido contrario
    }

    if (activanim)
    {
        if (rot > -90.0f)
            rot -= 0.1f;
    }

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
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

    if (keys[GLFW_KEY_O])
    {
       
        movelightPos += 0.1f;
    }

    if (keys[GLFW_KEY_L])
    {
        
        movelightPos -= 0.1f;
    }


}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
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


