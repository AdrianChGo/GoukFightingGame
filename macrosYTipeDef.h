//--------------------------------------------------------

#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <math.h> 

//Para las transformaciones
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Cuerpo del luchador
typedef struct {
	float px, py, pz; //
	float angulo_trans;
	float angulo_trans_2;
	float sx, sy, sz;
	unsigned int listarender; //De momento dos tipos, cubo o esfera
	GLuint textura;
	float color1, color2, color3;

	//Las siguientes dos funcionalidades solo son usadas por los objetos auxiliares ejes de giro
	float anguloRotacionX, anguloRotacionY, anguloRotacionZ;
} parteCuerpo;

typedef struct {
	parteCuerpo piernaInfDer;
	parteCuerpo piernaInfIzq;
	parteCuerpo piernaSupDer; 
	parteCuerpo piernaSupIzq;
	parteCuerpo rodillaDer;
	parteCuerpo rodillaIzq;
	parteCuerpo pieIzq;
	parteCuerpo pieDer;
	parteCuerpo pFlexPiernaInDer;
	parteCuerpo pFlexPiernaInIzq;
	parteCuerpo caderaDer;
	parteCuerpo caderaIzq;
	parteCuerpo tronco;
	parteCuerpo hombroDer;
	parteCuerpo hombroIzq;
	parteCuerpo brazoDer;
	parteCuerpo brazoIzq;
	parteCuerpo codoDer;
	parteCuerpo codoIzq;
	parteCuerpo antebrazoDer;
	parteCuerpo antebrazoIzq;
	parteCuerpo pFlexAntebrazoDer;
	parteCuerpo pFlexAntebrazoIzq;
	parteCuerpo manoDer;
	parteCuerpo manoIzq;
	parteCuerpo cuello;
	parteCuerpo cabeza;
	parteCuerpo pelo;
} cuerpo;

typedef struct {
	float px, py, pz;
	bool recibeOrdenes;
	float velocidad;
	unsigned int enAire;
	unsigned int golpeando;
	unsigned int bloquearCaminar;
	int orientacion;
	unsigned int colisionadoCuerpo;
	unsigned int colisionadoGolpe;
	float vidaActual;
	cuerpo cuerpoLuch;
} luchador;

typedef struct {
	float rangoX[2];
	float rangoY[2];
	float rangoZ[2];
} hitbox;

#define NLUCHADORES 2
#define VELOCIDADANIMACION 500 //VALOR NORMAL DE 500
#define GradosToRadianes 0.0175


//Parametros caminar
#define VELOCIDADCAMINAR 2
#define CAMINARESCALAR 0.4 //VALOR NORMAL DE 0.6
#define VELOCIDADRETROCEDER 1 //VALOR NORMAL DE 1
#define ANGULOFLEXION 60
#define ANGULOINFLEXION ANGULOFLEXION*0.6

//Parametros golpear
//PunhoIzquierdo
#define GOLPEARESCALAR 0.5 //Default 3

//PunhoDerecho
#define FLEXIONPUNHODERY 90
#define FLEXIONPUNHODERX 90

//Patadas
#define PATEARESCALAR 3 

//Colisiones
#define VELOCIDADREPULSION 10
#define VELOCIDADREPULSIONGOLPE 5

//Controles camara

#define INCREMENTO 0.01
#define DISTANCIA 1
#define PI 3.1416
#define VALORCAMARAESTANDAR 300

//Hitboxes
#define LIMITEPANTALLA 462