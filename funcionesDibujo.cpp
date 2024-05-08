#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <math.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "macrosYTipeDef.h"

extern int mostrarOrbitas, eleccionCamara;

extern unsigned int transformLoc;
extern unsigned int colorLoc, colorLocMarcadorVida;
extern GLuint shaderProgram, shaderProgramMarcadorVida, texturaFondo, texturaSuelo;
extern unsigned int VAOEsfera, VAOCubo, VAOCuboBueno, VAOCuadrado, VAOCuadradoVida, VAOEjeX, VAOEjeY, VAOEjeZ;
extern int chunksTamanho;

extern void setLuces();
extern luchador luchadores[NLUCHADORES];
extern parteCuerpo cuerNull;

void dibujarCubo(unsigned int VAODeCubo) {
	glBindVertexArray(VAODeCubo);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void dibujarCuadrado(unsigned int VAODeCuadrado) {
	glBindVertexArray(VAODeCuadrado);
	glDrawArrays(GL_TRIANGLES, 0, 12);
}

void dibujarEjes(unsigned int VAOEjeX, unsigned int VAOEjeY, unsigned int VAOEjeZ) {
	glUseProgram(shaderProgram);
	glUniform3f(colorLoc, 1.0f, 0.0f, 0.0f);
	glBindVertexArray(VAOEjeX);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);

	glUniform3f(colorLoc, 0.0f, 1.0f, 0.0f);
	glBindVertexArray(VAOEjeY);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);

	glUniform3f(colorLoc, 0.0f, 0.0f, 1.0f);
	glBindVertexArray(VAOEjeZ);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}

void dibujarEsfera(unsigned int VAODeEsfera) {
	glBindVertexArray(VAODeEsfera);
	glDrawArrays(GL_TRIANGLES, 0, 1080);
}


void dibujarMarcadorVida(luchador miLuchador, int idLuchador) {
	glUseProgram(shaderProgramMarcadorVida);
	//setLuces();
		
	float i, j;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glm::mat4 transformAux;
	transformAux = glm::mat4();

	if (idLuchador == 0) {

		for (int i = 0; i < 16; i++) {
			if (miLuchador.vidaActual >= 255 - i * 4) {
				glUniform3f(colorLocMarcadorVida, 0.0f, .0f, 1.0f);
			}
			else if (miLuchador.vidaActual >= 191 - i * 4) {
				glUniform3f(colorLocMarcadorVida, 0.0f, 1.0f, 0.0f);
			}
			else if (miLuchador.vidaActual >= 127 - i * 4) {
				glUniform3f(colorLocMarcadorVida, 1.0f, 1.0f, 0.0f);
			}
			else if (miLuchador.vidaActual >= 63 - i * 4) {
				glUniform3f(colorLocMarcadorVida, 1.0f, 0.0f, 0.0f);
			}
			else {
				glUniform3f(colorLocMarcadorVida, 0.0f, 0.0f, 0.0f);
			}
			if (miLuchador.vidaActual <= 0) {
				glUniform3f(colorLocMarcadorVida, 0.0f, 0.0f, 0.0f);
			}
			transformAux = glm::mat4();
			//transformAux = glm::translate(transformAux, glm::vec3(1000, 1100- 56.25*i, 1200));
			if (eleccionCamara == 5) {
				transformAux = glm::translate(transformAux, glm::vec3(100, 100 + 20 * i, 550));
				transformAux = glm::rotate(transformAux, (float)(-90 * GradosToRadianes), glm::vec3(0.0f, 0.0f, 1.0f));
				transformAux = glm::scale(transformAux, glm::vec3(21, 1, 40));
			}
			else {
				transformAux = glm::translate(transformAux, glm::vec3((100 + 20 * i) * luchadores[0].orientacion, (-600 + luchadores[0].py) * luchadores[0].orientacion, 550));
				transformAux = glm::rotate(transformAux, (float)(-90 * GradosToRadianes), glm::vec3(0.0f, 1.0f, .0f));
				transformAux = glm::scale(transformAux, glm::vec3(50, 1, 20));

			}

			//transformAux = glm::translate(transformAux, glm::vec3(0, 0, i * 56.25));
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformAux));
			dibujarCuadrado(VAOCuadradoVida);
		}
	}
	else if (idLuchador == 1) {


		for (int i = 0; i < 16; i++) {
			if (miLuchador.vidaActual >= 255 - i * 4) {
				glUniform3f(colorLocMarcadorVida, 0.0f, .0f, 1.0f);
			}
			else if (miLuchador.vidaActual >= 191 - i * 4) {
				glUniform3f(colorLocMarcadorVida, 0.0f, 1.0f, 0.0f);
			}
			else if (miLuchador.vidaActual >= 127 - i * 4) {
				glUniform3f(colorLocMarcadorVida, 1.0f, 1.0f, 0.0f);
			}
			else if (miLuchador.vidaActual >= 63 - i * 4) {
				glUniform3f(colorLocMarcadorVida, 1.0f, 0.0f, 0.0f);
			}
			else {
				glUniform3f(colorLocMarcadorVida, 0.0f, 0.0f, 0.0f);
			}
			if (miLuchador.vidaActual <= 0) {
				glUniform3f(colorLocMarcadorVida, 0.0f, 0.0f, 0.0f);
			}
			transformAux = glm::mat4();
			if (eleccionCamara == 5) {
				transformAux = glm::translate(transformAux, glm::vec3(100, -100 - 20 * i, 550));
				transformAux = glm::rotate(transformAux, (float)(-90 * GradosToRadianes), glm::vec3(0.0f, 0.0f, 1.0f));
				transformAux = glm::scale(transformAux, glm::vec3(21, 1, 40));
			}
			else {
				transformAux = glm::translate(transformAux, glm::vec3((100 + 20 * i) * luchadores[1].orientacion, (-600 + luchadores[0].py) * luchadores[0].orientacion, 550));
				transformAux = glm::rotate(transformAux, (float)(-90 * GradosToRadianes), glm::vec3(0.0f, 1.0f, .0f));
				transformAux = glm::scale(transformAux, glm::vec3(50, 1, 20));


			}

			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformAux));
			dibujarCuadrado(VAOCuadradoVida);
		}
	}
}

void dibujarMisEjes(glm::mat4 transform) {
	glUseProgram(shaderProgram);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//El suelo

	transform = glm::mat4();
	transform = glm::scale(transform, glm::vec3(10000, 10000, 10000));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	dibujarEjes(VAOEjeX, VAOEjeY, VAOEjeZ);

}

void dibujarSkyBox() {
	glUseProgram(shaderProgram);
	setLuces();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCullFace(GL_FRONT);
	//El suelo
	glm::mat4 transformAux;

	transformAux = glm::mat4();
	if (eleccionCamara == 1 && luchadores[0].orientacion == -1) {
		transformAux = glm::rotate(transformAux, (float)(-40), glm::vec3(1.0f, .0f, .0f));

	}
	else {
		transformAux = glm::rotate(transformAux, (float)(40), glm::vec3(1.0f, .0f, .0f));

	}
	transformAux = glm::scale(transformAux, glm::vec3(6000, 6000, 6000));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformAux));
	//Texturas
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturaFondo);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	//----------------------------------

	dibujarEsfera(VAOEsfera);

	glCullFace(GL_BACK);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void dibujarSuelo(float color[], glm::mat4 transform) { //En el futuro se pasará una textura en lugar de un color 
	glUseProgram(shaderProgram);
	setLuces();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f);
	float i, j;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//El suelo
	glm::mat4 transformAux;
	//Texturas
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturaSuelo);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	//----------------------------------
	for (i = -1000; i <= 1000; i += chunksTamanho)
		for (j = -1000; j <= 1000; j += chunksTamanho) {
			transformAux = glm::mat4();
			transformAux = glm::translate(transform, glm::vec3(i, j, -9));
			transformAux = glm::scale(transformAux, glm::vec3(chunksTamanho, chunksTamanho, 1));

			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformAux));
			dibujarCuadrado(VAOCuadrado);
		}
	glBindTexture(GL_TEXTURE_2D, 0);

}

glm::mat4 dibujarParteCuerpo(parteCuerpo compLuch, parteCuerpo parteFlexion1, glm::mat4 transform) {
	glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f);
	if (parteFlexion1.px != 0 || parteFlexion1.py != 0 || parteFlexion1.pz != 0) {
		//Hacer el rotate
		transform = glm::translate(transform, glm::vec3(parteFlexion1.px, parteFlexion1.py, parteFlexion1.pz));

		if (parteFlexion1.anguloRotacionX != 0 || parteFlexion1.anguloRotacionY != 0 || parteFlexion1.anguloRotacionZ != 0) {
			transform = glm::rotate(transform, (float)(parteFlexion1.anguloRotacionX), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, (float)(parteFlexion1.anguloRotacionY), glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, (float)(parteFlexion1.anguloRotacionZ), glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
	glm::mat4 transformDevolver = transform;
	transform = glm::translate(transform, glm::vec3(compLuch.px, compLuch.py, compLuch.pz));
	if (compLuch.anguloRotacionX != 0) {
		transform = glm::rotate(transform, (float)(compLuch.anguloRotacionX), glm::vec3(1.0f, 0.0f, 0.0f));
	}


	transform = glm::scale(transform, glm::vec3(compLuch.sx, compLuch.sy, compLuch.sz));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	//Texturas
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, compLuch.textura);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	//----------------------------------


	if (compLuch.listarender == VAOCubo || compLuch.listarender == VAOCuboBueno)
		dibujarCubo(compLuch.listarender);
	else if (compLuch.listarender == VAOEsfera)
		dibujarEsfera(compLuch.listarender);


	glBindTexture(GL_TEXTURE_2D, 0);


	return transformDevolver;
}

void dibujarPersona(luchador miLuchador, int idLuchador, glm::mat4 transform) {
	glUseProgram(shaderProgram);
	setLuces();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Tren inferior
	transform = glm::translate(transform, glm::vec3(miLuchador.px, miLuchador.py, miLuchador.pz));

	glm::mat4 transformPiernaIzq, transformPiernaDer;

	//Piernas rectangulares
	transformPiernaIzq = dibujarParteCuerpo(miLuchador.cuerpoLuch.piernaSupIzq, miLuchador.cuerpoLuch.caderaIzq, transform);
	transformPiernaDer = dibujarParteCuerpo(miLuchador.cuerpoLuch.piernaSupDer, miLuchador.cuerpoLuch.caderaDer, transform);
	dibujarParteCuerpo(miLuchador.cuerpoLuch.piernaInfIzq, miLuchador.cuerpoLuch.pFlexPiernaInIzq, transformPiernaIzq);
	dibujarParteCuerpo(miLuchador.cuerpoLuch.piernaInfDer, miLuchador.cuerpoLuch.pFlexPiernaInDer, transformPiernaDer);
	//dibujarParteCuerpoNivel2(piernaInfDer, pFlexPiernaInDer, caderaDer, transform);
	//dibujarParteCuerpoNivel2(piernaInfIzq, pFlexPiernaInIzq, caderaIzq, transform);

	//Articulaciones
	dibujarParteCuerpo(miLuchador.cuerpoLuch.pieIzq, miLuchador.cuerpoLuch.pFlexPiernaInIzq, transformPiernaIzq);
	dibujarParteCuerpo(miLuchador.cuerpoLuch.pieDer, miLuchador.cuerpoLuch.pFlexPiernaInDer, transformPiernaDer);
	dibujarParteCuerpo(miLuchador.cuerpoLuch.rodillaIzq, cuerNull, transformPiernaIzq);
	dibujarParteCuerpo(miLuchador.cuerpoLuch.rodillaDer, cuerNull, transformPiernaDer);


	//Tren superior

	glm::mat4 transformBrazoIzq, transformBrazoDer;
	dibujarParteCuerpo(miLuchador.cuerpoLuch.tronco, cuerNull, transform);
	if (idLuchador == 0) {
		dibujarParteCuerpo(miLuchador.cuerpoLuch.hombroIzq, cuerNull, transform);
		dibujarParteCuerpo(miLuchador.cuerpoLuch.hombroDer, cuerNull, transform);
	}

	transformBrazoIzq = dibujarParteCuerpo(miLuchador.cuerpoLuch.brazoIzq, miLuchador.cuerpoLuch.hombroIzq, transform);
	transformBrazoDer = dibujarParteCuerpo(miLuchador.cuerpoLuch.brazoDer, miLuchador.cuerpoLuch.hombroDer, transform);
	dibujarParteCuerpo(miLuchador.cuerpoLuch.codoIzq, cuerNull, transformBrazoIzq);
	dibujarParteCuerpo(miLuchador.cuerpoLuch.codoDer, cuerNull, transformBrazoDer);

	glm::mat4 transformAntebrazoIzq, transformAntebrazoDer;
	transformAntebrazoIzq = dibujarParteCuerpo(miLuchador.cuerpoLuch.antebrazoIzq, miLuchador.cuerpoLuch.pFlexAntebrazoIzq, transformBrazoIzq);
	transformAntebrazoDer = dibujarParteCuerpo(miLuchador.cuerpoLuch.antebrazoDer, miLuchador.cuerpoLuch.pFlexAntebrazoDer, transformBrazoDer);
	//dibujarParteCuerpo(antebrazoIzq, pFlexAntebrazoIzq, hombroIzq, transform);
	//dibujarParteCuerpo(antebrazoDer, pFlexAntebrazoDer, hombroDer, transform);
	dibujarParteCuerpo(miLuchador.cuerpoLuch.manoIzq, cuerNull, transformAntebrazoIzq);
	dibujarParteCuerpo(miLuchador.cuerpoLuch.manoDer, cuerNull, transformAntebrazoDer);

	dibujarParteCuerpo(miLuchador.cuerpoLuch.cuello, cuerNull, transform);
	dibujarParteCuerpo(miLuchador.cuerpoLuch.cabeza, cuerNull, transform);

	dibujarParteCuerpo(miLuchador.cuerpoLuch.pelo, cuerNull, transform);



}