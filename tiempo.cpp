#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <math.h> 





extern double lastTime;
extern double currentTime;
extern double deltaTime;
extern int nbFrames;



void tiempo() {
	static float unSegundo = 0;
	currentTime = glfwGetTime();
	nbFrames++;
	deltaTime = currentTime - lastTime;
	unSegundo = unSegundo + deltaTime;
	if (unSegundo >= 1.0) {
		//printf("%f frame/s\n", double(nbFrames));
		nbFrames = 0;
		unSegundo = 0;
	}
	lastTime = currentTime;
}
