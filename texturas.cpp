/*Autor: Adrián Chaves Gómez*/

#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <math.h> 

#include <iostream>
#include "macrosYTipeDef.h"
// Es necesario para que el stb_image funcione
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h> //STB son unas librerías de cabecera


extern luchador luchadores[NLUCHADORES];

GLuint Carga_Texturas(const char* nombre) {
	// load and create a texture 
	// -------------------------
	GLuint textura;
	glGenTextures(1, &textura);
	glBindTexture(GL_TEXTURE_2D, textura); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load(nombre, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (nrChannels == 3) {
			//if (!strcmp(nombre, "texturas/vegetaPiernaSuperiorDer.png")) {
			//	printf("PNG FALSO\n");
			//}
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else if (nrChannels == 4) {
			//if (!strcmp(nombre, "texturas/vegetaPiernaSuperiorDer.png")) {
			//	printf("PNG de verdad\n");
			//}
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		}
		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data); //con mimap 

	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	return textura;

}

void procesarTexturasJ1() {
	//TrenInferior
	luchadores[0].cuerpoLuch.piernaInfDer.textura = Carga_Texturas("texturas/gokuPierna.jpg");
	luchadores[0].cuerpoLuch.piernaInfIzq.textura = Carga_Texturas("texturas/gokuPierna.jpg");
	luchadores[0].cuerpoLuch.piernaInfDer.anguloRotacionX = 90 * GradosToRadianes;
	luchadores[0].cuerpoLuch.piernaInfIzq.anguloRotacionX = 90 * GradosToRadianes;

	luchadores[0].cuerpoLuch.piernaSupDer.textura = Carga_Texturas("texturas/gokuPierna.jpg");
	luchadores[0].cuerpoLuch.piernaSupIzq.textura = Carga_Texturas("texturas/gokuPierna.jpg");
	luchadores[0].cuerpoLuch.piernaSupDer.anguloRotacionX = 90 * GradosToRadianes;
	luchadores[0].cuerpoLuch.piernaSupIzq.anguloRotacionX = 90 * GradosToRadianes;

	luchadores[0].cuerpoLuch.rodillaDer.textura = Carga_Texturas("texturas/gokuPierna.jpg");
	luchadores[0].cuerpoLuch.rodillaIzq.textura = Carga_Texturas("texturas/gokuPierna.jpg");
	luchadores[0].cuerpoLuch.pieIzq.textura = Carga_Texturas("texturas/botas.jpg");
	luchadores[0].cuerpoLuch.pieDer.textura = Carga_Texturas("texturas/botas.jpg");


	//TrenSuperior

	luchadores[0].cuerpoLuch.tronco.textura = Carga_Texturas("texturas/gokuTorso.png");
	luchadores[0].cuerpoLuch.tronco.anguloRotacionX = 90 * GradosToRadianes;
	luchadores[0].cuerpoLuch.hombroDer.textura = Carga_Texturas("texturas/prueba.jpg");
	luchadores[0].cuerpoLuch.hombroIzq.textura = Carga_Texturas("texturas/prueba.jpg");
	luchadores[0].cuerpoLuch.brazoDer.textura = Carga_Texturas("texturas/prueba.jpg");
	luchadores[0].cuerpoLuch.brazoIzq.textura = Carga_Texturas("texturas/prueba.jpg");

	luchadores[0].cuerpoLuch.codoDer.textura = Carga_Texturas("texturas/prueba.jpg");
	luchadores[0].cuerpoLuch.codoIzq.textura = Carga_Texturas("texturas/prueba.jpg");

	luchadores[0].cuerpoLuch.antebrazoDer.textura = Carga_Texturas("texturas/prueba.jpg");
	luchadores[0].cuerpoLuch.antebrazoIzq.textura = Carga_Texturas("texturas/prueba.jpg");


	luchadores[0].cuerpoLuch.manoDer.textura = Carga_Texturas("texturas/munhequera.jpg");
	luchadores[0].cuerpoLuch.manoIzq.textura = Carga_Texturas("texturas/munhequera.jpg");

	luchadores[0].cuerpoLuch.cuello.textura = Carga_Texturas("texturas/cuello.jpg");
	luchadores[0].cuerpoLuch.cabeza.textura = Carga_Texturas("texturas/vegetaFace2.jpg");


	luchadores[0].cuerpoLuch.cabeza.anguloRotacionX = 90 * GradosToRadianes;


	luchadores[0].cuerpoLuch.pelo.textura = Carga_Texturas("texturas/pelo2.jpg");


}

void procesarTexturasJ2() {
	//TrenInferior
	luchadores[1].cuerpoLuch.piernaInfDer.textura = Carga_Texturas("texturas/vegetaPiernaInferiorDer.png");
	luchadores[1].cuerpoLuch.piernaInfIzq.textura = Carga_Texturas("texturas/vegetaPiernaInferiorIzq.png");
	luchadores[1].cuerpoLuch.piernaInfDer.anguloRotacionX = 90 * GradosToRadianes;
	luchadores[1].cuerpoLuch.piernaInfIzq.anguloRotacionX = 90 * GradosToRadianes;

	luchadores[1].cuerpoLuch.piernaSupDer.textura = Carga_Texturas("texturas/vegetaPiernaSuperiorDer.png");
	luchadores[1].cuerpoLuch.piernaSupIzq.textura = Carga_Texturas("texturas/vegetaPiernaSuperiorIzq.png");
	luchadores[1].cuerpoLuch.piernaSupDer.anguloRotacionX = 90 * GradosToRadianes;
	luchadores[1].cuerpoLuch.piernaSupIzq.anguloRotacionX = 90 * GradosToRadianes;

	luchadores[1].cuerpoLuch.rodillaDer.textura = Carga_Texturas("texturas/vegetaRodilla.jpg");
	luchadores[1].cuerpoLuch.rodillaIzq.textura = Carga_Texturas("texturas/vegetaRodilla.jpg");
	luchadores[1].cuerpoLuch.pieIzq.textura = Carga_Texturas("texturas/botas.jpg");
	luchadores[1].cuerpoLuch.pieDer.textura = Carga_Texturas("texturas/botas.jpg");


	//TrenSuperior

	luchadores[1].cuerpoLuch.tronco.textura = Carga_Texturas("texturas/vegetaTraje.jpg");
	luchadores[1].cuerpoLuch.tronco.anguloRotacionX = 90 * GradosToRadianes;

	luchadores[1].cuerpoLuch.hombroDer.textura = Carga_Texturas("texturas/brazoVegeta.jpg");
	luchadores[1].cuerpoLuch.hombroIzq.textura = Carga_Texturas("texturas/brazoVegeta.jpg");
	luchadores[1].cuerpoLuch.brazoDer.textura = Carga_Texturas("texturas/brazoVegeta.jpg");
	luchadores[1].cuerpoLuch.brazoIzq.textura = Carga_Texturas("texturas/brazoVegeta.jpg");

	luchadores[1].cuerpoLuch.codoDer.textura = Carga_Texturas("texturas/brazoVegeta.jpg");
	luchadores[1].cuerpoLuch.codoIzq.textura = Carga_Texturas("texturas/brazoVegeta.jpg");

	luchadores[1].cuerpoLuch.antebrazoDer.textura = Carga_Texturas("texturas/guantesVegeta.jpg");
	luchadores[1].cuerpoLuch.antebrazoIzq.textura = Carga_Texturas("texturas/guantesVegeta.jpg");


	luchadores[1].cuerpoLuch.manoDer.textura = Carga_Texturas("texturas/guantesVegeta.jpg");
	luchadores[1].cuerpoLuch.manoIzq.textura = Carga_Texturas("texturas/guantesVegeta.jpg");

	luchadores[1].cuerpoLuch.cuello.textura = Carga_Texturas("texturas/cuello.jpg");
	luchadores[1].cuerpoLuch.cabeza.textura = Carga_Texturas("texturas/vegetaFace.png");

	luchadores[1].cuerpoLuch.cabeza.anguloRotacionX = 90 * GradosToRadianes;


	luchadores[1].cuerpoLuch.pelo.textura = Carga_Texturas("texturas/pelo.jpg");


}

