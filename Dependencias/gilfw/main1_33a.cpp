
#include <glad.h>
#include <glfw3.h>
#include <iostream>

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// Gestion de teclado
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Version del Core de Opengl a usar
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Cersion del core the Opengl a usar
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Basico VisualstudioGlfwGlad", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Eror al crear la ventana" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	// Captura los punteros de opengl
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error con Glad" << std::endl;
		return -1;
	}
	
	// Lazo principal.
	
	while (!glfwWindowShouldClose(window))
	{
		// Entrada de teclado
		
		processInput(window);

		// Dibujo de fondo de pantalla.
		// ------
		glClearColor(1.0f, .0f, .0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}
