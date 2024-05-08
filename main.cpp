

#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <math.h> 

//Para las transformaciones
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "lecturaShader_0_9.h"

#include <iostream>
#include "macrosYTipeDef.h"

//Librerias para generar numeros aleatorios
#include <stdlib.h>
#include <time.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 500;
const unsigned int SCR_HEIGHT = 500;

unsigned int transformLocMarcadorVida;
unsigned int transformLoc; 
unsigned int viewLoc;
unsigned int viewLocMarcadorVida;
unsigned int projectionLoc;
unsigned int projectionLocMarcadorVida;
unsigned int colorLoc;
unsigned int colorLocMarcadorVida;
//color luz
unsigned int lightLoc;
//posición de la fuente 
unsigned int lightPosLoc;
//Luz especular
unsigned int viewPosLoc;

int modoJuego=0;
int bModoSeleccionado=0;
int numeroOrdenes;
float esperarAtacar = 0;
float esperaAcumulada = 0;

//-------------------------------------------------------

//Parametros fondo
GLuint texturaFondo;

//Parametros suelo
int chunksTamanho = 200;
float colorSuelo[3]= {1.0f, 0.0f, 0.0f};
GLuint texturaSuelo;
GLuint texturaMensaje1, texturaMensaje2, texturaMensaje3, texturaMensaje4, texturaMensaje5;

//-----------------

//Parametros modo 1 jugador
int eleccionAnteriorJugador1=30;


//--------------------------


//Controles camara

double ancho=500;
double alto=500;
int eleccionCamara = 5;
double xCamara = -600, yCamara = 0, zCamara = 170;
double dirCamaraX, dirCamaraY = 0, dirCamaraZ;




//--------------------------------------------------------

//Controles iluminación
float colorIluminacion[3] = { 1.0f,1.0f, 1.0f };
float camaraPosicion[3] = { 0.0f, 0.0f, 0.0f };

//--------------------------------------------------------


//Cuerpo del luchador


luchador luchadores[NLUCHADORES];

//Cuerpo del luchador parametros
float distanciaTiXCuerpo = 15; //Tronco inferior
float distanciaTsXCuerpo = distanciaTiXCuerpo * 1.5;
//Objetos cuerpo

parteCuerpo cuerNull = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //Función meramente auxiliar


//extern GLuint setShaders(const char *nVertx, const char *nFrag);
GLuint shaderProgram, shaderProgramMarcadorVida;


// unsigned int VBO, VAO, EBO;
unsigned int VAOEjeX, VAOEjeY, VAOEjeZ;
unsigned int VAOEsfera, VAOCubo, VAOCuboBueno, VAOCuadrado, VAOCuadradoVida;

extern void procesarEsfera();
extern void procesarEjeX(); extern void procesarEjeY(); extern void procesarEjeZ();
extern void procesarCubo();
extern void procesarCuboBueno();
extern void procesarCuadrado();
extern void procesarCuadradoVida();


//Control temporal

double lastTime = glfwGetTime();
double currentTime;
double deltaTime;
int nbFrames = 0;
extern void tiempo();
//------------------------------




extern void myCamara(int eleccionCamara);
extern void setLuces();
extern GLuint Carga_Texturas(const char* nombre);
extern void procesarTexturasJ1();
extern void procesarTexturasJ2();


//FuncionesDibujo.cpp

extern void dibujarCubo(unsigned int VAODeCubo);
extern void dibujarCuadrado(unsigned int VAODeCuadrado);
extern void dibujarEjes(unsigned int VAOEjeX, unsigned int VAOEjeY, unsigned int VAOEjeZ);
extern void dibujarEsfera(unsigned int VAODeEsfera);
//-------------------------


//Sonidos

extern void musicaVictoria();
extern void musicaEntrada();
extern void musicaColision();
//---------------------------------


//Funciones extra

int casiIgual(float valor1, float valor2, float precision) {
	if (valor1 >= valor2 - precision && valor1 <= valor2 + precision) {
		return 1;
	}
	return 0;
}



//Animaciones

double gradosAumentar = 0;
int animacionFinalFase = 1;

//Booleanos, se deben inicializar a 0
int bCaminarAnimacion[NLUCHADORES];
int bRetrocederAnimacion[NLUCHADORES];
int bPosInc[NLUCHADORES]; //Comprueba si estás en la posición de inicio del camino
int bPosIncRetroceder[NLUCHADORES]; //Comprueba lo mismo, pero con el retroceso
int bSaltarAnimacion[NLUCHADORES];
int bGolpearAnimacion[NLUCHADORES];

//-------------------------------
int tipoGolpe[NLUCHADORES];
int fasesCaminar[NLUCHADORES];
int fasesRetroceder[NLUCHADORES];
int estadoRetroceder[NLUCHADORES];
int animacionesActuales[NLUCHADORES];

//Golpear
int punhetazoIzqFase[NLUCHADORES];
int punhetazoDerFase[NLUCHADORES];
int patadaIzqFase[NLUCHADORES];
int patadaDerFase[NLUCHADORES];

float danhoTipoGolpe[4];

//--------------------------------
// 
// Posicion estandar de los brazo

extern void brazoEstandar(luchador* miLuchador, int idLuchador);

//Hitboxes
float pzAux, szAux, syAux, sxAux;
extern int faseColision;

extern void gestionColisionMutuaGolpe();
extern void gestionColisionIndividualGolpe(luchador* miLuchador, int idLuchador);
extern void gestionColisionCuerpos();

extern int colisionCuerpos(hitbox box1, hitbox box2);
extern hitbox hitBoxPosicion(luchador miLuchador, int idLuchador);
extern hitbox hitBoxGolpe(luchador miLuchador, int idLuchador);
extern void paredInvisible(luchador* miLuchador);

void cancelarAtaque(luchador* miLuchador, int idLuchador) {
	switch (tipoGolpe[idLuchador]) {
	case 1: //Punhetazo izquierdo
		miLuchador->cuerpoLuch.hombroIzq.anguloRotacionX = 0;
		miLuchador->cuerpoLuch.hombroIzq.anguloRotacionY = 0;
		miLuchador->cuerpoLuch.hombroIzq.anguloRotacionZ = 0;
		miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionX = 0;
		miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionY = 0;
		miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionZ = 0;
		brazoEstandar(miLuchador, idLuchador);
		break;
	case 2: //Punhetazo derecho
		miLuchador->cuerpoLuch.hombroDer.anguloRotacionX = 0;
		miLuchador->cuerpoLuch.hombroDer.anguloRotacionY = 0;
		miLuchador->cuerpoLuch.hombroDer.anguloRotacionZ = 0;
		miLuchador->cuerpoLuch.pFlexAntebrazoDer.anguloRotacionX = 0;
		miLuchador->cuerpoLuch.pFlexAntebrazoDer.anguloRotacionY = 0;
		miLuchador->cuerpoLuch.pFlexAntebrazoDer.anguloRotacionZ = 0;
		brazoEstandar(miLuchador, idLuchador);
		break;
	case 3: //Patada izquierda
		miLuchador->cuerpoLuch.caderaIzq.anguloRotacionX = 0;
		miLuchador->cuerpoLuch.caderaIzq.anguloRotacionY = 0;
		miLuchador->cuerpoLuch.caderaIzq.anguloRotacionZ = 0;
		break;
	case 4: //Patada derecha
		miLuchador->cuerpoLuch.caderaDer.anguloRotacionX = 0;
		miLuchador->cuerpoLuch.caderaDer.anguloRotacionY = 0;
		miLuchador->cuerpoLuch.caderaDer.anguloRotacionZ = 0;
		break;
	}
	bGolpearAnimacion[idLuchador] = 0;
	tipoGolpe[idLuchador] = 0;
	miLuchador->golpeando = 0;
	miLuchador->bloquearCaminar = 0;

}

void gestionarColisiones() {
	if (luchadores[0].colisionadoGolpe || luchadores[1].colisionadoGolpe) {
		if (faseColision == 1) { //Comprueba que no se aproveche el tiempo de inmunidad para atravesar al otro jugador
			hitbox box1Cuerpo, box2Cuerpo;
			box1Cuerpo = hitBoxPosicion(luchadores[0], 0);
			box2Cuerpo = hitBoxPosicion(luchadores[1], 1);
			if (luchadores[0].colisionadoCuerpo && luchadores[1].colisionadoCuerpo) {
				gestionColisionCuerpos();
				return;
			}
			if (colisionCuerpos(box1Cuerpo, box2Cuerpo)) {
				//printf("Oh dios mio, una colision en mi aparato\n");
				luchadores[0].colisionadoCuerpo = 1;
				luchadores[1].colisionadoCuerpo = 1;
				return;
			}
		}
		if (luchadores[0].colisionadoGolpe && luchadores[1].colisionadoGolpe) {
			gestionColisionMutuaGolpe();
			//printf("La vida del luchador 0 es: %f\tLa vida del luchador 1 es %f\n", luchadores[0].vidaActual, luchadores[1].vidaActual);
		}
		else if (luchadores[0].colisionadoGolpe) {
			gestionColisionIndividualGolpe(&luchadores[0], 0);
		}
		else if (luchadores[1].colisionadoGolpe) {
			gestionColisionIndividualGolpe(&luchadores[1], 1);
			
		}
	}

	else {
		hitbox box1Cuerpo, box1Golpe, box2Cuerpo, box2Golpe;
		box1Cuerpo = hitBoxPosicion(luchadores[0], 0);
		box2Cuerpo = hitBoxPosicion(luchadores[1], 1);
		if (luchadores[0].golpeando && luchadores[1].golpeando && luchadores[0].colisionadoGolpe == 0 && luchadores[1].colisionadoGolpe ==0) {
			box1Golpe = hitBoxGolpe(luchadores[0], 0);
			box2Golpe = hitBoxGolpe(luchadores[1], 1);
			if (colisionCuerpos(box1Golpe, box2Golpe)) {
				musicaColision();
				//printf("Ambos luchadores se han pegado entre si\n");

				luchadores[1].colisionadoGolpe= 1;
				luchadores[1].vidaActual -= danhoTipoGolpe[tipoGolpe[0]-1];
				luchadores[0].colisionadoGolpe= 1;
				luchadores[0].vidaActual -= danhoTipoGolpe[tipoGolpe[1]-1];


				//Salto
				luchadores[0].velocidad = 15;
				luchadores[0].pz += 2;
				bSaltarAnimacion[0] = 0;
				luchadores[0].enAire = 1;

				luchadores[1].velocidad = 15;
				luchadores[1].pz += 2;
				bSaltarAnimacion[1] = 0;
				luchadores[1].enAire = 1;
				
				cancelarAtaque(&luchadores[1], 1);
				cancelarAtaque(&luchadores[0], 0);
				return;
			}
		}
		if (luchadores[0].golpeando && luchadores[1].colisionadoGolpe ==0) {
			box1Golpe= hitBoxGolpe(luchadores[0], 0);
			if (colisionCuerpos(box1Golpe, box2Cuerpo)) { //El luchador 1 golpea al luchador 2
				//printf("El luchador 0 esta golpeando\n");

				musicaColision();
				//printf("El luchador 0 le ha pegado al luchador 1\n");
				luchadores[1].colisionadoGolpe=1;
				luchadores[1].vidaActual -= danhoTipoGolpe[tipoGolpe[0]-1];
				//printf("vida: %f\n", luchadores[1].vidaActual);
				//Salto
				luchadores[1].velocidad = 10;
				luchadores[1].pz += 2;
				bSaltarAnimacion[1] = 0;
				luchadores[1].enAire = 1;
				if (luchadores[1].golpeando) {
					cancelarAtaque(&luchadores[1], 1);
				}
				return;
			}
			else {
				//printf("No ha sido posible la colision\n");
			}
		}
		if (luchadores[1].golpeando && luchadores[0].colisionadoGolpe == 0) {
			box2Golpe = hitBoxGolpe(luchadores[1], 1);
			if (colisionCuerpos(box1Cuerpo, box2Golpe)) { //El luchador 2 golpea al luchador 1
				musicaColision();
				//printf("El luchador 1 le ha pegado al luchador 0\n");
				luchadores[0].colisionadoGolpe=1;
				luchadores[0].vidaActual -= danhoTipoGolpe[tipoGolpe[1]-1];
				//printf("vida: %f\n", luchadores[0].vidaActual);
				//Salto

				luchadores[0].velocidad = 10;
				luchadores[0].pz += 2;
				bSaltarAnimacion[0] = 0;
				luchadores[0].enAire = 1;
				if (luchadores[0].golpeando) {
					cancelarAtaque(&luchadores[0], 0);
				}
				return;
			}
		}

		if (luchadores[0].colisionadoCuerpo && luchadores[1].colisionadoCuerpo) {
			gestionColisionCuerpos();
			return;
		}
		if (colisionCuerpos(box1Cuerpo, box2Cuerpo)) {
			//printf("Oh dios mio, una colision en mi aparato\n");
			luchadores[0].colisionadoCuerpo = 1;
			luchadores[1].colisionadoCuerpo = 1;
			return;
		}
	}
}

//Gravedad
float aceleracionGravitatoria[NLUCHADORES];
void gravedad() {
	for (int i = 0; i < NLUCHADORES; i++) {
		if (luchadores[i].pz > 0.0f) {
			luchadores[i].velocidad += aceleracionGravitatoria[i] * 1 / 60 * deltaTime * VELOCIDADANIMACION;
			luchadores[i].pz += luchadores[i].velocidad * 1 / 60 * deltaTime * VELOCIDADANIMACION;
			//printf("Velocidad %f\tAltura %f\tAceleracion %f\n", luchadores[i].velocidad, luchadores[i].pz, aceleracionGravitatoria[i]);
		}
		else {
			luchadores[i].velocidad = 0;
			luchadores[i].pz = 0.0f;
			luchadores[i].enAire = 0;
			aceleracionGravitatoria[i] = -20.0f;
		}
	}
}


//Caminar

extern void caminarFase1(luchador* miLuchador, int idLuchador);

extern void caminarFase2(luchador* miLuchador, int idLuchador);

extern void caminar(luchador* miLuchador, int idLuchador);

extern void retroceder(luchador* miLuchador, int idLuchador);

extern void punhetazoIzquierdo(luchador* miLuchador, int idLuchador);

extern void punhetazoDerecho(luchador* miLuchador, int idLuchador);

extern void patadaIzquierda(luchador* miLuchador, int idLuchador);

extern void patadaDerecha(luchador* miLuchador, int idLuchador);

extern void anhularCaminar(luchador* miLuchador, int idLuchador);

void gestionarAnimacion(luchador* miLuchador, int idLuchador) {
	if (bCaminarAnimacion[idLuchador] || !bPosInc[idLuchador]) {
		caminar(miLuchador, idLuchador);
	}
	else if (bRetrocederAnimacion[idLuchador] || !bPosIncRetroceder[idLuchador]) {
		retroceder(miLuchador, idLuchador);
	}
	//if()
	if (bSaltarAnimacion[idLuchador] && !miLuchador->enAire) {
		miLuchador->velocidad = 110;
		miLuchador->pz += 2;
		bSaltarAnimacion[idLuchador] = 0;
		miLuchador->enAire = 1;
	}
	if (bGolpearAnimacion[idLuchador]) {
		switch (tipoGolpe[idLuchador]) {
			case 1: 
				punhetazoIzquierdo(miLuchador, idLuchador); //Puñetazo normal
				break;
			case 2:
				punhetazoDerecho(miLuchador, idLuchador); //Gancho épico
				break;
			case 3:
				patadaIzquierda(miLuchador, idLuchador); //Patada alta
				break;
			case 4:
				patadaDerecha(miLuchador, idLuchador); //Patada normal
				break;
			default:
				break;
		}
	}
}

void gestionarAccionAleatoria(luchador* miLuchador, int idLuchador) {
	int orden;
	int caminarORetroceder;
	if (esperaAcumulada < esperarAtacar) {
		esperaAcumulada += deltaTime;

	}
	else {
		if (miLuchador->recibeOrdenes == FALSE) {
			orden = eleccionAnteriorJugador1;

		}
		else { //Generar numero aleatorio del rango ??
			orden = 1 + (rand() % numeroOrdenes);
			eleccionAnteriorJugador1 = orden;
			//printf("Nueva orden generada: %d\n", orden);
			esperaAcumulada = 0;
		}

		switch (orden) {
		case 1:case 10: case 15:
			if (!miLuchador->enAire) {
				//printf("No estoy en aire\n");
				miLuchador->velocidad = 110;
				miLuchador->pz += 2;
				miLuchador->enAire = 1;
			}
			else {
				aceleracionGravitatoria[0] = -10;
			}
			break;
		case 2: case 8:
			caminar(miLuchador, idLuchador);

			break;
		case 3:
			punhetazoIzquierdo(miLuchador, idLuchador);
			break;
		case 4:
			punhetazoDerecho(miLuchador, idLuchador);
			break;
		case 5:
			patadaIzquierda(miLuchador, idLuchador);
			break;
		case 6:
			patadaDerecha(miLuchador, idLuchador);
			break;
		case 7:
			retroceder(miLuchador, idLuchador);
			break;
		case 30:
			miLuchador->recibeOrdenes == TRUE;
			//printf("Va bien\n");
			break;
		default:
			break;
		}
	}
	
}


//void pruebaRodilla() {
//	pFlexPiernaInIzq.ejeRotacion = glm::vec3(1.0f, 0.0f, 0.0f);
//	pFlexPiernaInIzq.anguloRotacion = gradosAumentar*GradosToRadianes;
//}

//------------------------------------

extern void dibujarMarcadorVida(luchador miLuchador, int idLuchador);
extern void dibujarMisEjes(glm::mat4 transform);
extern void dibujarSkyBox();
extern void dibujarSuelo(float color[], glm::mat4 transform);
extern glm::mat4 dibujarParteCuerpo(parteCuerpo compLuch, parteCuerpo parteFlexion1, glm::mat4 transform);
extern void dibujarPersona(luchador miLuchador, int idLuchador, glm::mat4 transform);

extern void keyCallback(GLFWwindow* window, unsigned int key);
extern void specialKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
extern void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void openGlInit() {
	//Habilito aqui el depth en vez de arriba para los usuarios de linux y mac mejor arriba
	//Incializaciones varias
	

	glClearDepth(1.0f); //Valor z-buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // valor limpieza buffer color
	glEnable(GL_DEPTH_TEST); // z-buffer
	glEnable(GL_CULL_FACE); //ocultacion caras back
	glCullFace(GL_BACK);
	//glEnable(GL_ALPHA);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 32);

	for (int i = 0; i < NLUCHADORES; i++) {
		//Caminar
		fasesCaminar[i] = 0;
		fasesRetroceder[i] = 0;
		estadoRetroceder[i] = 0;

		animacionesActuales[i] = 0;
		bCaminarAnimacion[i] = 0;	
		bPosInc[i] = 1;
		bPosIncRetroceder[i] = 1;
		//-----------------------
		//Golpear
		bGolpearAnimacion[i] = 1;
		tipoGolpe[i] = 0;
		punhetazoIzqFase[i] = 0;
		//Golpear punhDer
		punhetazoDerFase[i] = 0;
		patadaIzqFase[i] = 0;
		patadaDerFase[i] = 0;

		//------------------------
		
		//Saltar
		aceleracionGravitatoria[i] = -20;
		//---------------------------------

		//Hitboxes
	


		//---------------------------------
	}
	luchadores[0] = { 0,100,100,1, 0.0, 1, 0, 0,  1, 0, 0, 255.0f};
	luchadores[1] = { 0,100,100,1, 0.0, 1, 0, 0, -1, 0, 0, 255.0f };

	//Definimos el dolor de los golpes
	danhoTipoGolpe[0] = 10.0f;
	danhoTipoGolpe[1] = 10.0f;
	danhoTipoGolpe[2] = 15.0f;
	danhoTipoGolpe[3] = 15.0f;

}

int bFinalJuego = FALSE;
void dobleDerrota() {
	printf("En su extrema temeridad, ambos luchadores acabaron muertos y derrotados. Que en paz descansen\n");
	bFinalJuego = TRUE;
}

void victoria(int idLuchador) {
	if (modoJuego == 2) {
		printf("Enhorabuena jugador %d, has logrado alzarte con la victoria dignamente\n", idLuchador);
	}
	else if (modoJuego == 3) {
		if (idLuchador == 1) {
			printf("Lo sentimos heroe, tu fuerza esta vez no ha sido suficiente para eliminar al maligno\n¡Intentalo nuevamente, el reino depende de ti!\n");
		}
		else if (idLuchador == 0) {
			printf("Enhorabuena heroe, venciste al mal que se parecia muchisimo a ti y ahora puedes ir a tu planeta de fiesta o algo\n");
		}
	}
}

void comprobarGanador() {
	if (luchadores[0].vidaActual <= 0 && luchadores[1].vidaActual <= 0) {
		dobleDerrota();
		musicaVictoria();
		bFinalJuego = TRUE;
	}
	else if (luchadores[0].vidaActual <= 0) {
		victoria(1);
		musicaVictoria();
		bFinalJuego = TRUE;

	}
	else if (luchadores[1].vidaActual <= 0) {
		victoria(0);
		musicaVictoria();
		bFinalJuego = TRUE;

	}
}

void gestionarOrientacion() {
	int activar[NLUCHADORES];
	
	if (luchadores[0].orientacion == 1 && luchadores[0].py+50 < luchadores[1].py*(-1)) {
		for (int i = 0; i < NLUCHADORES; i++) {
			if (bCaminarAnimacion[i] == 1) {
				activar[i] = 1;
			}
			else if (bRetrocederAnimacion[i] == 1) {
				activar[i] = -1;
			}
			else {
				activar[i] = 0;
			}
		}

		luchadores[0].orientacion = -1;
		luchadores[1].orientacion = 1;
		luchadores[0].py = -luchadores[0].py;
		luchadores[1].py = -luchadores[1].py;
		anhularCaminar(&luchadores[0], 0);
		anhularCaminar(&luchadores[1], 1);

		//printf("Se ha producido un cambio en la parte A\n");

		for (int i = 0; i < NLUCHADORES; i++) {
			if (activar[i] == 1) {
				bRetrocederAnimacion[i] = 1;
				bPosIncRetroceder[i] = 0;
			}
			else if (activar[i] == -1) {
				bCaminarAnimacion[i] = 1;
				bPosIncRetroceder[i] = 0;
			}
		}
	}
	else if (luchadores[1].orientacion == 1 && luchadores[1].py+50 < luchadores[0].py*(-1)) {
		for (int i = 0; i < NLUCHADORES; i++) {
			if (bCaminarAnimacion[i] == 1) {
				activar[i] = 1;
			}
			else if (bRetrocederAnimacion[i] == 1) {
				activar[i] = -1;
			}
			else {
				activar[i] = 0;
			}
		}

		luchadores[0].orientacion = 1;
		luchadores[1].orientacion = -1;
		luchadores[0].py = -luchadores[0].py;
		luchadores[1].py = -luchadores[1].py;
		anhularCaminar(&luchadores[0], 0);
		anhularCaminar(&luchadores[1], 1);

		//printf("Se ha producido un cambio en la parte B\n");


		for (int i = 0; i < NLUCHADORES; i++) {
			if (activar[i] == 1) {
				bRetrocederAnimacion[i] = 1;
				bPosIncRetroceder[i] = 0;
			}
			else if (activar[i] == -1) {
				bCaminarAnimacion[i] = 1;
				bPosIncRetroceder[i] = 0;
			}
		}
	}

}

void mostrarMensaje(GLuint miTexturaMensaje) {
	glUseProgram(shaderProgram);
	setLuces();
	glm::mat4 transformAux;
	transformAux = glm::mat4();
	glUniform3f(colorLocMarcadorVida, 1.0f, 1.0f, 1.0f);


	transformAux = glm::translate(transformAux, glm::vec3(-20, 0, 170));
	transformAux = glm::rotate(transformAux, (float)(-90 * GradosToRadianes), glm::vec3(0.0f, 0.0f, 1.0f));
	transformAux = glm::scale(transformAux, glm::vec3(1000, 1, 1000));

	/*transformAux = glm::translate(transformAux, glm::vec3(100, 0, 0));
	transformAux = glm::rotate(transformAux, (float)(-90 * GradosToRadianes), glm::vec3(0.0f, 1.0f, .0f));
	transformAux = glm::scale(transformAux, glm::vec3(100, 1, 100));*/

	//transformAux = glm::translate(transformAux, glm::vec3(0, 0, i * 56.25));
		//Texturas
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, miTexturaMensaje);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	//----------------------------------

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformAux));
	dibujarCuadrado(VAOCuadradoVida);
	glBindTexture(GL_TEXTURE_2D, 0);


}

void animacionFinal() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Borro el Buffer the la ventana
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Para dibujarlos en lineas
	gravedad();


	if (luchadores[0].vidaActual <= 0) {
		luchadores[0].velocidad = 15;
		luchadores[0].pz += 2;
		bSaltarAnimacion[0] = 0;
		luchadores[0].enAire = 1;

		luchadores[0].py += deltaTime * VELOCIDADANIMACION;
	}

	if (luchadores[1].vidaActual <= 0) {
		luchadores[1].velocidad = 15;
		luchadores[1].pz += 2;
		bSaltarAnimacion[1] = 0;
		luchadores[1].enAire = 1;

		luchadores[1].py += deltaTime * VELOCIDADANIMACION;

	}

	myCamara(eleccionCamara); //Según el valor de eleección cámara, se verá de una forma u otra

	glUseProgram(shaderProgram);

	
	glm::mat4 transform; // es la matriz de transformacion	
	dibujarMarcadorVida(luchadores[0], 0);
	dibujarMarcadorVida(luchadores[1], 1);
	dibujarSkyBox();

	dibujarSuelo(colorSuelo, transform);
	if (luchadores[0].py <= 1000 && luchadores[1].py <= 1000) {
		if (luchadores[0].orientacion == -1) {
			dibujarPersona(luchadores[1], 1, transform);
			transform = glm::rotate(transform, (float)(180 * GradosToRadianes), glm::vec3(0.0f, 0.0f, 1.0f));
			dibujarPersona(luchadores[0], 0, transform);
		}
		else {
			dibujarPersona(luchadores[0], 0, transform);
			transform = glm::rotate(transform, (float)(180 * GradosToRadianes), glm::vec3(0.0f, 0.0f, 1.0f));
			dibujarPersona(luchadores[1], 1, transform);
		}
	}

	if (luchadores[0].py > 1000 || luchadores[1].py > 1000) {
		if (luchadores[0].vidaActual <= 0 && luchadores[1].vidaActual <= 0) {
			mostrarMensaje(texturaMensaje5);
		}
		else if (luchadores[0].vidaActual <= 0) {
			mostrarMensaje(texturaMensaje4);
		}
		else if (luchadores[1].vidaActual <= 0) {
			mostrarMensaje(texturaMensaje3);
		}
	}

}

void imprimirControles(int modo) {
	if (modo == 1) { //Modo un jugador
		std::cout << "/*/*/*/*/*/*/*/Controles Modo un jugador/*/*/*/*/*/*/*/" << std::endl;
		std::cout << "Teclas A, D: Izquierda y derecha" << std::endl;
		std::cout << "Alter: Flecha izquierda y derecha: izquierda y derecha" << std::endl;
		std::cout << "Tecla W: Saltar" << std::endl;
		std::cout << "Alter: Flecha hacia arriba: Saltar" << std::endl;
		std::cout << "Guantazo izquierdo y derecho: G y H" << std::endl;
		std::cout << "Patada izquierda y derecha: B y N" << std::endl;
		std::cout << "Camara en primera persona: 1" << std::endl;
		std::cout << "Camara en tercera persona: 3" << std::endl;
		std::cout << "R: Acercar camara" << std::endl;
		std::cout << "T: Alejar camara" << std::endl;
		std::cout << "Y: Mover camara a la izquierda" << std::endl;
		std::cout << "U: Mover camara a la derecha" << std::endl;



	}
	else if(modo == 2){ //Modo dos jugadores
		std::cout << "/*/*/*/*/*/*/*/Controles Modo dos jugadores/*/*/*/*/*/*/*/" << std::endl;
		std::cout << "Advertencia: Estos controles son en extremo incomodo, pero no se encontro una gestion mejor para 2 jugadores" << std::endl;

		std::cout << "-----------Jugador 1------------" << std::endl;
		std::cout << "Teclas A, D: Izquierda y derecha" << std::endl;
		std::cout << "Tecla W: Saltar" << std::endl;
		std::cout << "Guantazo izquierdo y derecho: C y X" << std::endl;
		std::cout << "Patada izquierda y derecha: V y S" << std::endl;

		std::cout << "-----------Jugador 2------------" << std::endl;
		std::cout << "Teclas J, L: Izquierda y derecha" << std::endl;
		std::cout << "Tecla I: Saltar" << std::endl;
		std::cout << "Guantazo izquierdo y derecho: B y N" << std::endl;
		std::cout << "Patada izquierda y derecha: '-' y '.'" << std::endl;

		std::cout << "R: Acercar camara" << std::endl;
		std::cout << "T: Alejar camara" << std::endl;
		std::cout << "Y: Mover camara a la izquierda" << std::endl;
		std::cout << "U: Mover camara a la derecha" << std::endl;
	}
}

void Display() {
	if (bFinalJuego == FALSE) {
		// render
	// ------
	//caminar();
	//pruebaRodilla();


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Borro el Buffer the la ventana
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Para dibujarlos en lineas

		gravedad();
		//printf("mi modo juego es: %d\nNumero ordenes: %d\n", modoJuego,numeroOrdenes);

		gestionarAnimacion(&luchadores[0], 0);
		if (modoJuego == 2) {
			gestionarAnimacion(&luchadores[1], 1);
		}


		if (modoJuego == 3) {
			gestionarAccionAleatoria(&luchadores[1], 1);
		}


		myCamara(eleccionCamara); //Según el valor de eleección cámara, se verá de una forma u otra

		glUseProgram(shaderProgram);


		glm::mat4 transform; // es la matriz de transformacion	
		dibujarMarcadorVida(luchadores[0], 0);
		dibujarMarcadorVida(luchadores[1], 1);

		//dibujarMisEjes(transform);
		//transform = glm::rotate(transform, (float)(180*GradosToRadianes), glm::vec3(0.0f, 0.0f, 1.0f));

		dibujarSkyBox();

		dibujarSuelo(colorSuelo, transform);
		if (luchadores[0].orientacion == -1) {
			dibujarPersona(luchadores[1], 1, transform);
			transform = glm::rotate(transform, (float)(180 * GradosToRadianes), glm::vec3(0.0f, 0.0f, 1.0f));
			dibujarPersona(luchadores[0], 0, transform);
		}
		else {
			dibujarPersona(luchadores[0], 0, transform);
			transform = glm::rotate(transform, (float)(180 * GradosToRadianes), glm::vec3(0.0f, 0.0f, 1.0f));
			dibujarPersona(luchadores[1], 1, transform);
		}



		gestionarColisiones();
		gestionarOrientacion();
		paredInvisible(&luchadores[0]);
		paredInvisible(&luchadores[1]);

		comprobarGanador();
		glBindVertexArray(0); // unbind 

	}
	//Poner ventana de gracias por jugar
	else {
		animacionFinal();
	}
}



void evento1(GLuint miTextura) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Borro el Buffer the la ventana
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Para dibujarlos en lineas

	gravedad();
	//printf("mi modo juego es: %d\nNumero ordenes: %d\n", modoJuego,numeroOrdenes);

	gestionarAnimacion(&luchadores[0], 0);
	if (modoJuego == 2) {
		gestionarAnimacion(&luchadores[1], 1);
	}


	if (modoJuego == 3) {
		gestionarAccionAleatoria(&luchadores[1], 1);
	}


	myCamara(eleccionCamara); //Según el valor de eleección cámara, se verá de una forma u otra

	glUseProgram(shaderProgram);


	glm::mat4 transform; // es la matriz de transformacion	
	dibujarMarcadorVida(luchadores[0], 0);
	dibujarMarcadorVida(luchadores[1], 1);

	//dibujarMisEjes(transform);
	//transform = glm::rotate(transform, (float)(180*GradosToRadianes), glm::vec3(0.0f, 0.0f, 1.0f));

	dibujarSkyBox();

	dibujarSuelo(colorSuelo, transform);


	mostrarMensaje(miTextura);





	glBindVertexArray(0); // unbind 

}


void inicializarCuerpo(int idLuchador) {
	//Los rectangulos siempre que sean articulables (extermidades) tendrán sus proporciones determinadas por su articulación. Ejemplo, la parte inferior de la pierna va determinada por las rodillas
//TrenInferior
	luchadores[idLuchador].cuerpoLuch.piernaInfDer = { 0, 0, -25, 0,0, 20, 50, 10, 0, 0, 0.0f, 1.0f, 0.0f };
	luchadores[idLuchador].cuerpoLuch.piernaInfIzq = { 0, 0, -25, 0,0, 20, 50, 10, 0, 0, 0.0f, 1.0f, 0.0f };

	luchadores[idLuchador].cuerpoLuch.piernaSupDer = { 0, 0, -25, 0,0, 25, 50, 9, 0, 0, 0.0f, 1.0f, 0.0f }; //Le pongo 9 como sy a las piernas parra evitar un solapamiento con el tronco
	luchadores[idLuchador].cuerpoLuch.piernaSupIzq = { 0, 0, -25, 0,0, 25, 50, 9, 0, 0, 0.0f, 1.0f, 0.0f };

	luchadores[idLuchador].cuerpoLuch.rodillaDer = { 0, 0, -luchadores[idLuchador].cuerpoLuch.piernaSupDer.sy, 0,0, 10, 10, 10, 0, 0, 0.0f, 0.0f, 1.0f };
	luchadores[idLuchador].cuerpoLuch.rodillaIzq = { 0, 0, -luchadores[idLuchador].cuerpoLuch.piernaSupIzq.sy, 0,0, 10, 10, 10, 0, 0, 0.0f, 0.0f, 1.0f };
	luchadores[idLuchador].cuerpoLuch.pieIzq = { 0, -5, -luchadores[idLuchador].cuerpoLuch.piernaSupIzq.sy, 0,0, 10, 20, 10, 0, 0, 1.0f, 1.0f, 1.0f };
	luchadores[idLuchador].cuerpoLuch.pieDer = { 0, -5, -luchadores[idLuchador].cuerpoLuch.piernaSupIzq.sy, 0,0, 10, 20, 10, 0, 0, 1.0f, 1.0f, 1.0f };


	//La cadera no se dibuja, solo sirve de toma de datos
	//Objetos auxiliares para la rotación
	luchadores[idLuchador].cuerpoLuch.pFlexPiernaInDer = { 0, 0, -luchadores[idLuchador].cuerpoLuch.piernaSupIzq.sy, 0,0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }; //Al ser un objeto auxiliar, nunca es dibujado (Pude haber escogido de referencia tanto la rodilla izquierda como la derecha)
	luchadores[idLuchador].cuerpoLuch.pFlexPiernaInIzq = { 0, 0, -luchadores[idLuchador].cuerpoLuch.piernaSupIzq.sy, 0,0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }; //Al ser un objeto auxiliar, nunca es dibujado (Pude haber escogido de referencia tanto la rodilla izquierda como la derecha)

	luchadores[idLuchador].cuerpoLuch.caderaDer = { -distanciaTiXCuerpo, 0, luchadores[idLuchador].cuerpoLuch.piernaInfIzq.sy + luchadores[idLuchador].cuerpoLuch.piernaSupIzq.sy, 0,0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	luchadores[idLuchador].cuerpoLuch.caderaIzq = { distanciaTiXCuerpo, 0, luchadores[idLuchador].cuerpoLuch.piernaInfDer.sy + luchadores[idLuchador].cuerpoLuch.piernaSupIzq.sy, 0,0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };



	//TrenSuperior
	pzAux = luchadores[idLuchador].cuerpoLuch.piernaSupIzq.sy + luchadores[idLuchador].cuerpoLuch.piernaInfIzq.sy + 30;
	szAux = 80;
	syAux = 20;
	sxAux = 50;
	luchadores[idLuchador].cuerpoLuch.tronco = { 0, 5, luchadores[idLuchador].cuerpoLuch.piernaSupIzq.sy + luchadores[idLuchador].cuerpoLuch.piernaInfIzq.sy + 30, 0,0, sxAux, szAux, syAux, 0, 0, 1.0f, 1.0f, 0.0f }; //25, 14, 50
	luchadores[idLuchador].cuerpoLuch.hombroDer = { -distanciaTsXCuerpo, 5, pzAux + (szAux / 2) - 5, 0,0, 10, 10, 10, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f };
	luchadores[idLuchador].cuerpoLuch.hombroIzq = { distanciaTsXCuerpo, 5, pzAux + (szAux / 2) - 5, 0,0, 10, 10, 10, 0, 0, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f };
	luchadores[idLuchador].cuerpoLuch.brazoDer = { -20, 0, 0, 0,0, 40, 10, 8, 0, 0, 0.0f,0.0f,1.0f };
	luchadores[idLuchador].cuerpoLuch.brazoIzq = { 20, 0, 0, 0,0, 40, 10, 8, 0, 0, 0.9294117647058824f,0.5686274509803921f,0.12941176470588237f };

	luchadores[idLuchador].cuerpoLuch.codoDer = { -luchadores[idLuchador].cuerpoLuch.brazoIzq.sx, 0, 0, 0,0, 8, 8, 8, 0, 0, 1.0f, 1.0f, 1.0f };
	luchadores[idLuchador].cuerpoLuch.codoIzq = { luchadores[idLuchador].cuerpoLuch.brazoDer.sx, 0, 0, 0,0, 8, 8, 8, 0, 0, 1.0f, 1.0f, 1.0f};

	luchadores[idLuchador].cuerpoLuch.antebrazoDer = { -20,0, 0, 0,0, 40, 10, 8, 0, 0, 0.0f,0.0f,1.0f };
	luchadores[idLuchador].cuerpoLuch.antebrazoIzq = { +20, 0, 0, 0,0, 40, 10, 8, 0, 0, 0.9294117647058824f,0.5686274509803921f,0.12941176470588237f };

	//Los siguientes objeto son auxiliares
	luchadores[idLuchador].cuerpoLuch.pFlexAntebrazoDer = { -luchadores[idLuchador].cuerpoLuch.brazoIzq.sx, 0, 0, 0,0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	luchadores[idLuchador].cuerpoLuch.pFlexAntebrazoIzq = { luchadores[idLuchador].cuerpoLuch.brazoDer.sx, 0, 0, 0,0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

	//-------------------------

	luchadores[idLuchador].cuerpoLuch.manoDer = { - luchadores[idLuchador].cuerpoLuch.antebrazoDer.sx, 0, 0, 0,0, 8, 8, 8, 0, 0, 1.0f, 1.0f, 1.0f };
	luchadores[idLuchador].cuerpoLuch.manoIzq = { luchadores[idLuchador].cuerpoLuch.antebrazoIzq.sx, 0, 0, 0,0, 8, 8, 8, 0, 0, 1.0f, 1.0f, 1.0f };

	luchadores[idLuchador].cuerpoLuch.cuello = { 0, 5, pzAux + szAux / 2 + 10, 0,0, 10, syAux, 20, 0, 0, 0.0f,1.0f,1.0f };
	luchadores[idLuchador].cuerpoLuch.cabeza = { 0, 2, luchadores[idLuchador].cuerpoLuch.cuello.pz + 25, 0,0, 20, 30, 20, 0, 0, 0.9882352941176471f,0.8156862745098039f,0.7058823529411765f };

	if (idLuchador == 0) {
		luchadores[idLuchador].cuerpoLuch.pelo = { 0, 0, luchadores[idLuchador].cuerpoLuch.cabeza.sz + luchadores[idLuchador].cuerpoLuch.cabeza.pz + 20, 0,0, 40, 15, 80, 0, 0, 0.0f, 1.0f, 0.5f };
	}
	else {
		luchadores[idLuchador].cuerpoLuch.pelo = { 0, 0, luchadores[idLuchador].cuerpoLuch.cabeza.sz + luchadores[idLuchador].cuerpoLuch.cabeza.pz, 0,0, 80, 15, 40, 0, 0, 0.0f, 1.0f, 0.5f };
	}

	//------------------------------

}



int main()
{
	// glfw: initialize and configure
	// ------------------------------
	srand(time(NULL));
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	//Creo la ventana
														
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Gouk Fighting Game 3.3", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Fallo Crear Ventana" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetCharCallback(window, keyCallback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, specialKeyInput);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	

	openGlInit();
	//printf("Elige tu modo de juego favorito:\n\tPulsa 1 para jugar en modo 1 jugador (En este modo podras estar en tercera persona con 3 y en primera persona con 1)\n\tPulsa 2 para jugar en modo 2 jugadores\n");
	inicializarCuerpo(0);
	inicializarCuerpo(1);
	//inicializarCuerpo(1);
	procesarTexturasJ1();
	procesarTexturasJ2();
	texturaFondo = Carga_Texturas("texturas/fondo.png");
	texturaSuelo = Carga_Texturas("texturas/suelo.png");
	texturaMensaje1 = Carga_Texturas("texturas/mensaje1.jpg");
	texturaMensaje2 = Carga_Texturas("texturas/mensaje2.jpg");
	texturaMensaje3 = Carga_Texturas("texturas/mensaje3.jpg");
	texturaMensaje4 = Carga_Texturas("texturas/mensaje4.jpg");
	texturaMensaje5 = Carga_Texturas("texturas/mensaje5.jpg");


	
	shaderProgram = setShaders("shader.vert", "shader.frag");
	shaderProgramMarcadorVida = setShaders("shaderMarcadorVida.vert", "shaderMarcadorVida.frag");
	procesarEsfera();
	procesarEjeX(); procesarEjeY(); procesarEjeZ();
	procesarCubo();
	procesarCuboBueno();
	procesarCuadrado();
	procesarCuadradoVida();
	for (int i = 0; i < NLUCHADORES; i++) {
		luchadores[i].cuerpoLuch.cabeza.listarender = luchadores[i].cuerpoLuch.manoIzq.listarender = luchadores[i].cuerpoLuch.manoDer.listarender = luchadores[i].cuerpoLuch.codoIzq.listarender = luchadores[i].cuerpoLuch.codoDer.listarender = luchadores[i].cuerpoLuch.hombroIzq.listarender = luchadores[i].cuerpoLuch.hombroDer.listarender = luchadores[i].cuerpoLuch.rodillaIzq.listarender = luchadores[i].cuerpoLuch.rodillaDer.listarender = luchadores[i].cuerpoLuch.pieIzq.listarender = luchadores[i].cuerpoLuch.pieDer.listarender = VAOEsfera;
		luchadores[i].cuerpoLuch.tronco.listarender = luchadores[i].cuerpoLuch.pelo.listarender = luchadores[i].cuerpoLuch.cuello.listarender = luchadores[i].cuerpoLuch.antebrazoIzq.listarender = luchadores[i].cuerpoLuch.antebrazoDer.listarender = luchadores[i].cuerpoLuch.brazoIzq.listarender = luchadores[i].cuerpoLuch.brazoDer.listarender =  luchadores[i].cuerpoLuch.piernaSupIzq.listarender = luchadores[i].cuerpoLuch.piernaSupDer.listarender = luchadores[i].cuerpoLuch.piernaInfIzq.listarender = luchadores[i].cuerpoLuch.piernaInfDer.listarender = VAOCubo;
		luchadores[i].cuerpoLuch.pelo.listarender = VAOCuboBueno;
	}
	
	glEnable(GL_DEPTH_TEST);


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Lazo de la ventana mientras no la cierre
	
	glUseProgram(shaderProgram); // lo muevo para aqui por no 

	colorLoc = glGetUniformLocation(shaderProgram, "objectColor");
	transformLoc = glGetUniformLocation(shaderProgram, "transform");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc= glGetUniformLocation(shaderProgram, "projection");
	//Color de la luz
	lightLoc = glGetUniformLocation(shaderProgram, "lightColor");
	//posición de la fuente de luz difusa
	lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
	//Luz especular
	viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");

	transformLocMarcadorVida = glGetUniformLocation(shaderProgramMarcadorVida, "transform");
	viewLocMarcadorVida = glGetUniformLocation(shaderProgramMarcadorVida, "view");
	projectionLocMarcadorVida = glGetUniformLocation(shaderProgramMarcadorVida, "projection");
	colorLocMarcadorVida = glGetUniformLocation(shaderProgramMarcadorVida, "color");


	brazoEstandar(&luchadores[0], 0);
	brazoEstandar(&luchadores[1], 1);
	// -----------
	while (!bModoSeleccionado && !glfwWindowShouldClose(window)) {
		processInput(window);
		evento1(texturaMensaje1);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	if (modoJuego == 1) {
		bModoSeleccionado = 0;
		//printf("Por favor, seleccione la dificultad que desea:\n\t2. Facil\n\t3. Normal\n\t4. Dificil\n");
		while (!bModoSeleccionado && !glfwWindowShouldClose(window)) {
			processInput(window);
			evento1(texturaMensaje2);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	musicaEntrada();
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);
		
		Display();
		tiempo();
		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	int key;
	key = glfwGetKey(window, GLFW_KEY_ESCAPE);
	if (key == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	ancho = width;
	alto = height;
}