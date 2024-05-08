#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <math.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "macrosYTipeDef.h"

extern unsigned int viewLoc;
extern unsigned int viewLocMarcadorVida;
extern unsigned int projectionLoc;
extern unsigned int projectionLocMarcadorVida;
extern double ancho;
extern double alto;
extern double xCamara, yCamara, zCamara, dirCamaraY;
extern double dirX, dirY, dirZ;

extern GLuint shaderProgram, shaderProgramMarcadorVida;

extern luchador luchadores[NLUCHADORES];
extern float camaraPosicion[3];

void myCamara(int eleccionCamara) {
	glViewport(0, 0, ancho, alto);
	//Planeta
	//View matrix
	glm::mat4 view;
	switch (eleccionCamara) {
		case 1: //Vista desde arriba
			view = glm::mat4();
			//view = glm::lookAt(glm::vec3(xCamara, yCamara, zCamara), glm::vec3(dirX*1000, dirY*1000, dirZ*1000), glm::vec3(0.0f, 1.0f, .0f));
			view = glm::lookAt(glm::vec3(0, luchadores[0].py * luchadores[0].orientacion, 170 + luchadores[0].pz), glm::vec3(0.0f, -1000.0f * luchadores[0].orientacion, 170), glm::vec3(0.0f, 0.0f, 1.0f));
			camaraPosicion[0] = 0; camaraPosicion[1] = luchadores[0].py * luchadores[0].orientacion; camaraPosicion[2] = 170;
			break;
		case 2: //Vista en primera persona
			view = glm::mat4();
			//view = glm::lookAt(glm::vec3(xCamara, yCamara, zCamara), glm::vec3(-xCamara, -yCamara, -zCamara), glm::vec3(0.0f, 1.0f, .0f));
			view = glm::lookAt(glm::vec3(0, luchadores[1].py * luchadores[1].orientacion, 170 + luchadores[1].pz), glm::vec3(0.0f, -1000.0f * luchadores[1].orientacion, 170), glm::vec3(0.0f, 0.0f, 1.0f));

			break;
		case 3: //Vista en tercera persona
			view = glm::mat4();
			view = glm::lookAt(glm::vec3(xCamara, yCamara, zCamara), glm::vec3(0.0f, .0f, 0.0f), glm::vec3(0.0f, 1.0f, .0f));
			break;
		case 4: //Vista en tercera persona
			view = glm::mat4();
			view = glm::lookAt(glm::vec3(xCamara, yCamara, zCamara), glm::vec3(0.0f, .0f, 0.0f), glm::vec3(0.0f, 1.0f, .0f));
			break;
		case 5: //Vista en tercera persona
			view = glm::mat4();
			view = glm::lookAt(glm::vec3(xCamara, yCamara, zCamara), glm::vec3(1000.0f, dirCamaraY, 250.0f), glm::vec3(0.0f, .0f, 1.0f));
			camaraPosicion[0] = xCamara; camaraPosicion[1] = yCamara; camaraPosicion[2] = zCamara;
			break;
		case 6: //Vista en tercera persona
			view = glm::mat4();
			view = glm::lookAt(glm::vec3(xCamara, yCamara, zCamara), glm::vec3(0.0f, .0f, 0.0f), glm::vec3(0.0f, .0f, 1.0f));
			break;
	}
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUseProgram(shaderProgramMarcadorVida);
	glUniformMatrix4fv(viewLocMarcadorVida, 1, GL_FALSE, glm::value_ptr(view));
	//Proyection matriz
	glm::mat4 projection, projectionMarcadorVida;
	projection = glm::mat4();
	projection = glm::perspective(glm::radians(80.0f), (float)ancho / (float)alto, 10.0f, 10000.0f);


	
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUseProgram(shaderProgramMarcadorVida);
	glUniformMatrix4fv(projectionLocMarcadorVida, 1, GL_FALSE, glm::value_ptr(projection));

	////Ejes
	////View matrix
	//view = glm::mat4();
	//view = glm::lookAt(glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, .0f, 0.0f), glm::vec3(0.0f, .0f, 1.0f));
	//glUniformMatrix4fv(viewLocEjes, 1, GL_FALSE, glm::value_ptr(view));

	////Proyection matriz
	//projection = glm::mat4();
	//projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
	//glUniformMatrix4fv(projectionLocEjes, 1, GL_FALSE, glm::value_ptr(projection));


}
