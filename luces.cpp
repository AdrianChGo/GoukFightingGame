/*Autor: Adrián Chaves Gómez*/

#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <math.h> 

//Controles iluminación
extern float colorIluminacion[3];

//--------------------------------------------------------
extern GLuint shaderProgram;

//color luz
extern unsigned int lightLoc, lightPosLoc, viewPosLoc;
extern float camaraPosicion[3];
//posición de la fuente 


void setLuces() {
	glUseProgram(shaderProgram);
	glUniform3f(lightLoc, colorIluminacion[0], colorIluminacion[1], colorIluminacion[2]);
	glUniform3f(lightPosLoc, 0.0f, .0f, 500.0f);
	glUniform3f(viewPosLoc, camaraPosicion[0], camaraPosicion[1], camaraPosicion[2]);
}