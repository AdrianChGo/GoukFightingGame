#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <math.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "macrosYTipeDef.h"


//-------------------------------
extern int fasesCaminar[NLUCHADORES];
extern int bCaminarAnimacion[NLUCHADORES];
extern int bRetrocederAnimacion[NLUCHADORES];
extern int bGolpearAnimacion[NLUCHADORES];
extern double deltaTime;
extern int bPosInc[NLUCHADORES];
extern int bPosIncRetroceder[NLUCHADORES];
extern int punhetazoIzqFase[NLUCHADORES];
extern int punhetazoDerFase[NLUCHADORES];
extern int patadaIzqFase[NLUCHADORES];
extern int patadaDerFase[NLUCHADORES];
extern int tipoGolpe[NLUCHADORES];
extern int fasesRetroceder[NLUCHADORES];
extern int estadoRetroceder[NLUCHADORES];


extern int casiIgual(float valor1, float valor2, float precision);
extern void hitBoxPosicion(luchador* miLuchador, int idLuchador);

void caminarFase1(luchador* miLuchador, parteCuerpo* caderaPrincipal, parteCuerpo* caderaSecundaria, parteCuerpo* pFlexionPrincipal, parteCuerpo* pFlexionSecundario, int idLuchador, int direccion, int pFuncion) {
	miLuchador->recibeOrdenes = FALSE;
	if (caderaPrincipal->anguloRotacionX*direccion > -ANGULOFLEXION * GradosToRadianes * direccion) {
		miLuchador->py -= CAMINARESCALAR * deltaTime * VELOCIDADCAMINAR * VELOCIDADANIMACION * direccion;
		caderaPrincipal->anguloRotacionX -= GradosToRadianes * deltaTime * VELOCIDADANIMACION * VELOCIDADCAMINAR * direccion;
		pFlexionPrincipal->anguloRotacionX += (GradosToRadianes / 2) * deltaTime * VELOCIDADANIMACION * VELOCIDADCAMINAR * direccion;
	}
	else if (caderaSecundaria->anguloRotacionX * direccion < ANGULOINFLEXION * GradosToRadianes * direccion) {
		miLuchador->py -= CAMINARESCALAR * deltaTime * VELOCIDADCAMINAR * VELOCIDADANIMACION;
		caderaSecundaria->anguloRotacionX += GradosToRadianes * deltaTime * VELOCIDADANIMACION * VELOCIDADCAMINAR * direccion;
		pFlexionSecundario->anguloRotacionX += GradosToRadianes * deltaTime * VELOCIDADANIMACION * VELOCIDADCAMINAR * direccion;
	}
	else {
		caderaPrincipal->anguloRotacionX = -ANGULOFLEXION * GradosToRadianes * direccion;
		caderaSecundaria->anguloRotacionX = ANGULOINFLEXION * GradosToRadianes * direccion;
		pFlexionPrincipal->anguloRotacionX = ANGULOFLEXION / 2 * GradosToRadianes * direccion;
		pFlexionSecundario->anguloRotacionX = ANGULOINFLEXION / 2 * GradosToRadianes * direccion;
		fasesCaminar[idLuchador] = pFuncion;
	}
}

void caminarFase2(luchador* miLuchador, parteCuerpo* caderaPrincipal, parteCuerpo* caderaSecundaria, parteCuerpo* pFlexionPrincipal, parteCuerpo* pFlexionSecundario, int idLuchador, int direccion, int pFuncion) {
	if (caderaPrincipal->anguloRotacionX*direccion < 0) {
		caderaPrincipal->anguloRotacionX += GradosToRadianes * deltaTime * VELOCIDADANIMACION * VELOCIDADCAMINAR;
		pFlexionPrincipal->anguloRotacionX -= (GradosToRadianes / 2) * deltaTime * VELOCIDADANIMACION * VELOCIDADCAMINAR * direccion;
		miLuchador->py -= CAMINARESCALAR * deltaTime * VELOCIDADANIMACION * VELOCIDADCAMINAR * direccion;
	}
	else if (caderaSecundaria->anguloRotacionX * direccion > 0) {

		caderaSecundaria->anguloRotacionX -= GradosToRadianes * deltaTime * VELOCIDADANIMACION * VELOCIDADCAMINAR * direccion;
		pFlexionSecundario->anguloRotacionX -= GradosToRadianes * deltaTime * VELOCIDADANIMACION * VELOCIDADCAMINAR * direccion;
		miLuchador->py -= CAMINARESCALAR * deltaTime * VELOCIDADCAMINAR * VELOCIDADANIMACION;

	}
	else {

		caderaPrincipal->anguloRotacionX = 0;
		caderaSecundaria->anguloRotacionX = 0;
		pFlexionPrincipal->anguloRotacionX = 0;
		pFlexionSecundario->anguloRotacionX = 0;

		bPosInc[idLuchador] = 1;
		//bCaminarAnimacion[idLuchador] = 0;
		fasesCaminar[idLuchador] = pFuncion;
		miLuchador->recibeOrdenes = TRUE;
	}
}


void caminar(luchador* miLuchador, int idLuchador) {
	switch (fasesCaminar[idLuchador]) {
	case 1:
		caminarFase1(miLuchador, &miLuchador->cuerpoLuch.caderaIzq, &miLuchador->cuerpoLuch.caderaDer, &miLuchador->cuerpoLuch.pFlexPiernaInIzq, &miLuchador->cuerpoLuch.pFlexPiernaInDer, idLuchador, 1, 2);
		break;
	case 2:
		caminarFase2(miLuchador, &miLuchador->cuerpoLuch.caderaIzq, &miLuchador->cuerpoLuch.caderaDer, &miLuchador->cuerpoLuch.pFlexPiernaInIzq, &miLuchador->cuerpoLuch.pFlexPiernaInDer, idLuchador, 1, 3);
		break;
	case 3:
		caminarFase1(miLuchador, &miLuchador->cuerpoLuch.caderaDer, &miLuchador->cuerpoLuch.caderaIzq, &miLuchador->cuerpoLuch.pFlexPiernaInDer, &miLuchador->cuerpoLuch.pFlexPiernaInIzq, idLuchador, 1, 4);
		break;
	case 4:
		caminarFase2(miLuchador, &miLuchador->cuerpoLuch.caderaDer, &miLuchador->cuerpoLuch.caderaIzq, &miLuchador->cuerpoLuch.pFlexPiernaInDer, &miLuchador->cuerpoLuch.pFlexPiernaInIzq, idLuchador, 1, 1);
		break;
	default:
		caminarFase1(miLuchador, &miLuchador->cuerpoLuch.caderaIzq, &miLuchador->cuerpoLuch.caderaDer, &miLuchador->cuerpoLuch.pFlexPiernaInIzq, &miLuchador->cuerpoLuch.pFlexPiernaInDer, idLuchador, 1, 2);
		break;
	}
}


void retrocederFase1(luchador* miLuchador, parteCuerpo* caderaPrincipal, parteCuerpo* pFlexionPrincipal, int idLuchador, int siguienteFase, int posInc) {
	miLuchador->recibeOrdenes = FALSE;
	switch (estadoRetroceder[idLuchador]) {
	case 0: //p.f.x = 100 p.c.x = -50
		if (caderaPrincipal->anguloRotacionX > -50 * GradosToRadianes) {
			//miLuchador->py -= CAMINARESCALAR * deltaTime * VELOCIDADANIMACION ;
			caderaPrincipal->anguloRotacionX -= GradosToRadianes * deltaTime * VELOCIDADANIMACION * VELOCIDADRETROCEDER;
			pFlexionPrincipal->anguloRotacionX += (GradosToRadianes * 2) * deltaTime * VELOCIDADANIMACION * VELOCIDADRETROCEDER;
			miLuchador->py += CAMINARESCALAR * deltaTime * VELOCIDADANIMACION ;
		}
		else if (casiIgual(pFlexionPrincipal->anguloRotacionX, -50 * GradosToRadianes, 0.1)) {
			caderaPrincipal->anguloRotacionX = -50 * GradosToRadianes;
			pFlexionPrincipal->anguloRotacionX = 100 * GradosToRadianes;
			estadoRetroceder[idLuchador] = 1;
		}
		else {
			caderaPrincipal->anguloRotacionX = -50 * GradosToRadianes;
			pFlexionPrincipal->anguloRotacionX = 100 * GradosToRadianes;
			estadoRetroceder[idLuchador] = 1;
		}
		break;
	case 1: //Pasar todo a 0
		if (caderaPrincipal->anguloRotacionX < 0) {
			//miLuchador->py -= CAMINARESCALAR * deltaTime * VELOCIDADANIMACION ;
			caderaPrincipal->anguloRotacionX += GradosToRadianes * deltaTime * VELOCIDADANIMACION * VELOCIDADRETROCEDER;
			pFlexionPrincipal->anguloRotacionX -= (GradosToRadianes * 2) * deltaTime * VELOCIDADANIMACION * VELOCIDADRETROCEDER;
		}
		else if (casiIgual(pFlexionPrincipal->anguloRotacionX, 0, 0.1)) {
			pFlexionPrincipal->anguloRotacionX = 0;
			caderaPrincipal->anguloRotacionX = 0;
			estadoRetroceder[idLuchador] = 0;
			fasesRetroceder[idLuchador] = siguienteFase;
			if (posInc == 1) {
				bPosIncRetroceder[idLuchador] = posInc;
			}
			miLuchador->recibeOrdenes = TRUE;
		}
		else {
			pFlexionPrincipal->anguloRotacionX = 0;
			caderaPrincipal->anguloRotacionX = 0;
			estadoRetroceder[idLuchador] = 0;
			fasesRetroceder[idLuchador] = siguienteFase;
			if (posInc == 1) {
				bPosIncRetroceder[idLuchador] = posInc;
			}
			miLuchador->recibeOrdenes = TRUE;
			
		}
		break;
	}
}


void retroceder(luchador* miLuchador, int idLuchador) {
	switch (fasesRetroceder[idLuchador]) {
	case 1:
		retrocederFase1(miLuchador, &miLuchador->cuerpoLuch.caderaIzq,&miLuchador->cuerpoLuch.pFlexPiernaInIzq, idLuchador, 2, 0);
		break;
	case 2:
		retrocederFase1(miLuchador, &miLuchador->cuerpoLuch.caderaDer, &miLuchador->cuerpoLuch.pFlexPiernaInDer, idLuchador, 1, 1);
		break;
	default:
		retrocederFase1(miLuchador, &miLuchador->cuerpoLuch.caderaIzq, &miLuchador->cuerpoLuch.pFlexPiernaInIzq, idLuchador, 2, 0);
		break;
	}
}

void anhularCaminar(luchador* miLuchador, int idLuchador) {
	miLuchador->cuerpoLuch.caderaDer.anguloRotacionX = 0;
	miLuchador->cuerpoLuch.caderaIzq.anguloRotacionX = 0;
	miLuchador->cuerpoLuch.pFlexPiernaInDer.anguloRotacionX = 0;
	miLuchador->cuerpoLuch.pFlexPiernaInIzq.anguloRotacionX = 0;
	bPosInc[idLuchador] = 1;
	bPosIncRetroceder[idLuchador] = 1;
	bCaminarAnimacion[idLuchador] = 0;
	bRetrocederAnimacion[idLuchador] = 0;

}

void punhetazoIzquierdo(luchador* miLuchador, int idLuchador) {
	miLuchador->recibeOrdenes = FALSE;
	/*miLuchador->cuerpoLuch.hombroIzq.anguloRotacionY = 80 * GradosToRadianes;
	miLuchador->cuerpoLuch.hombroDer.anguloRotacionY = -80 * GradosToRadianes;*/
	switch (punhetazoIzqFase[idLuchador]) {
	case 1:
		miLuchador->golpeando = 1;
		punhetazoIzqFase[idLuchador] = 2;
		break;
	case 2:
		if (miLuchador->cuerpoLuch.hombroIzq.anguloRotacionY > 0) {
			miLuchador->cuerpoLuch.hombroIzq.anguloRotacionY -= 4*GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
			//printf("El if1\n");
		}
		else if (miLuchador->cuerpoLuch.hombroIzq.anguloRotacionY != 0) {
			miLuchador->cuerpoLuch.hombroIzq.anguloRotacionY = 0;
			//printf("El if2\n");
			punhetazoIzqFase[idLuchador] = 3;
		}
		else {
			//printf("El if3\n");
		}
		break;
	case 3: //Hombro izquierdo con 90 grados en Y y -90 Grados en X
		//printf("Hola timmy\n");
		//printf("Fase 3\n");

		if (miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionZ > -FLEXIONPUNHODERY * GradosToRadianes) {
			miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionZ -= 4*GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
			//printf("El if1\n");
		}
		else if (miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionZ != -FLEXIONPUNHODERY * GradosToRadianes) {
			miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionZ = -FLEXIONPUNHODERY * GradosToRadianes;
			punhetazoIzqFase[idLuchador] = 4;
		}
		break;

	case 4: //Hombro izquierdo con 90 grados en Y y -90 Grados en X, Valor antebrazo Z = -90
		//printf("Hola timmy\n");
		//printf("Fase 4\n");

		if (miLuchador->cuerpoLuch.hombroIzq.anguloRotacionZ > -110 * GradosToRadianes) {
			miLuchador->cuerpoLuch.hombroIzq.anguloRotacionZ -= 3*GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
		}
		else if (casiIgual(miLuchador->cuerpoLuch.hombroIzq.anguloRotacionZ, -110*GradosToRadianes, 0.1)) {
			miLuchador->cuerpoLuch.hombroIzq.anguloRotacionZ = -110 * GradosToRadianes;
		}
		else {
			miLuchador->cuerpoLuch.hombroIzq.anguloRotacionZ = -110 * GradosToRadianes;
		}

		if (miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionZ < -20 * GradosToRadianes) {
			miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionZ += 2* GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
			//printf("El if1\n");
		}
		else if (miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionZ != -20 * GradosToRadianes) {
			miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionZ = -20 * GradosToRadianes;
			punhetazoIzqFase[idLuchador] = 5;
		}
		else {
			miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionZ = -20* GradosToRadianes;
			miLuchador->cuerpoLuch.hombroIzq.anguloRotacionZ = -FLEXIONPUNHODERX * GradosToRadianes;
			punhetazoIzqFase[idLuchador] = 5;
		}
		//if (miLuchador->cuerpoLuch.hombroDer.anguloRotacionX > -FLEXIONPUNHODERX * GradosToRadianes) {
		//	miLuchador->cuerpoLuch.hombroDer.anguloRotacionX -= GOLPEARESCALAR * deltaTime * VELOCIDADANIMACION;
		//}
		//else if (miLuchador->cuerpoLuch.hombroDer.anguloRotacionX != -FLEXIONPUNHODERX * GradosToRadianes) {
		//	miLuchador->cuerpoLuch.hombroDer.anguloRotacionX = -FLEXIONPUNHODERX * GradosToRadianes;
		//}
		//if (miLuchador->cuerpoLuch.hombroDer.anguloRotacionY == -FLEXIONPUNHODERY * GradosToRadianes && miLuchador->cuerpoLuch.hombroDer.anguloRotacionX == -FLEXIONPUNHODERX * GradosToRadianes) {
		//	punhetazoIzqFase[idLuchador] = 2;
		//}
		break;
	case 5: //Esta fase sirve exclusivamente para finalizado el golpe, se quede un tiempo en la misma posicion
		//miLuchador->cuerpoLuch.hombroIzq.anguloRotacionZ = -110 * GradosToRadianes;
		
		punhetazoIzqFase[idLuchador] = 6;
		break;
	//Angulo rotacion P.Z = -110, el de S.Z es -20
	case 6:  //Angulo rotacion P.Z = 0 S.Z = 0
		//printf("Fase 6\n");

		//printf("Estoy en 5\n");
		//printf("anguloRotacionX: %f\n ", miLuchador->cuerpoLuch.hombroIzq.anguloRotacionX);
		if (miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionZ < 0) {
			miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionZ += 2 * GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
			//printf("El if1\n");
		}
		else if (casiIgual(miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionZ, -20 * GradosToRadianes, 0.1)) {
			miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionZ = 0;
		}
		else {
			miLuchador->cuerpoLuch.pFlexAntebrazoIzq.anguloRotacionZ = 0;
		}

		if (miLuchador->cuerpoLuch.hombroIzq.anguloRotacionX < 90 * GradosToRadianes) {
			miLuchador->cuerpoLuch.hombroIzq.anguloRotacionX += 4*GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
			//printf("if1\n");
			//printf("anguloRotacionX: %f\n ", miLuchador->cuerpoLuch.hombroIzq.anguloRotacionX);
		}
		else if (!casiIgual(miLuchador->cuerpoLuch.hombroIzq.anguloRotacionX, 90 * GradosToRadianes, 0.1)) {
			//printf("Esto pasa antes\n");
			//printf("anguloRotacionX: %f\n ", miLuchador->cuerpoLuch.hombroIzq.anguloRotacionX);
			miLuchador->cuerpoLuch.hombroIzq.anguloRotacionX = 90 * GradosToRadianes;
			//printf("if2\n");
			//printf("anguloRotacionX: %f\n ", miLuchador->cuerpoLuch.hombroIzq.anguloRotacionX);
			punhetazoIzqFase[idLuchador] = 7;

		}
		else {
			miLuchador->cuerpoLuch.hombroIzq.anguloRotacionX = 90 * GradosToRadianes;
			punhetazoIzqFase[idLuchador] = 7;
		}
		
		break;
	case 7:
		//printf("Fase 7\n");

		miLuchador->cuerpoLuch.hombroIzq.anguloRotacionZ = 0;
		miLuchador->cuerpoLuch.hombroIzq.anguloRotacionX = 0;
		miLuchador->cuerpoLuch.hombroIzq.anguloRotacionY = 90*GradosToRadianes;
		punhetazoIzqFase[idLuchador] = 8;
	case 8: //Objetivo: Con rotacion y a 90 grados, bajarlo a 80
		//printf("Estoy en 7\n");
		//printf("Fase 8\n");

		if (miLuchador->cuerpoLuch.hombroIzq.anguloRotacionY > 80 * GradosToRadianes) {
			miLuchador->cuerpoLuch.hombroIzq.anguloRotacionY -= 4 * GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
			//printf("En el principio\n");
		}
		else if (casiIgual(miLuchador->cuerpoLuch.hombroIzq.anguloRotacionY, 80 * GradosToRadianes, 0.1)) {
			miLuchador->cuerpoLuch.hombroIzq.anguloRotacionY = 80 * GradosToRadianes;
			bGolpearAnimacion[idLuchador] = 0;
			punhetazoIzqFase[idLuchador] = 0;
			tipoGolpe[idLuchador] = 0;
			miLuchador->golpeando = 0;
			miLuchador->recibeOrdenes = TRUE;
			//printf("En el final\n");
		}
		else {
			miLuchador->cuerpoLuch.hombroIzq.anguloRotacionY = 80 * GradosToRadianes;
			bGolpearAnimacion[idLuchador] = 0;
			punhetazoIzqFase[idLuchador] = 0;
			tipoGolpe[idLuchador] = 0;
			miLuchador->golpeando = 0;
			miLuchador->recibeOrdenes = TRUE;
		}
		break;
	default:
		miLuchador->golpeando = 1;
		punhetazoIzqFase[idLuchador] = 2;
		tipoGolpe[idLuchador] = 1;
		break;
	}
		
	//printf("AnguloRotacionY:\t%f\nAnguloRotacionX:\t%f\n", miLuchador->cuerpoLuch.hombroIzq.anguloRotacionY, miLuchador->cuerpoLuch.hombroIzq.anguloRotacionX);
	//else {
	//	caderaPrincipal->anguloRotacionX = -ANGULOFLEXION * GradosToRadianes * direccion;
	//	caderaSecundaria->anguloRotacionX = ANGULOINFLEXION * GradosToRadianes * direccion;
	//	pFlexionPrincipal->anguloRotacionX = ANGULOFLEXION / 2 * GradosToRadianes * direccion;
	//	pFlexionSecundario->anguloRotacionX = ANGULOINFLEXION / 2 * GradosToRadianes * direccion;
	//	fasesCaminar[idLuchador] = pFuncion;
	//}
}

void punhetazoDerecho(luchador* miLuchador, int idLuchador) {

	switch (punhetazoDerFase[idLuchador]) {
	case 1:
		miLuchador->recibeOrdenes = FALSE;
		miLuchador->golpeando = 1;
		punhetazoDerFase[idLuchador] = 2;
		break;
		//P.R.Y = -80 * GradosToRadianes;

	case 2:
		//printf("Fase 2\n");
		if (miLuchador->cuerpoLuch.hombroDer.anguloRotacionY < 0) {
			miLuchador->cuerpoLuch.hombroDer.anguloRotacionY += 4 * GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
		}
		else if (casiIgual(miLuchador->cuerpoLuch.hombroDer.anguloRotacionY, 0, 0.1)) {
			miLuchador->cuerpoLuch.hombroDer.anguloRotacionY = 0;
			punhetazoDerFase[idLuchador] = 3;
		}
		else {
			miLuchador->cuerpoLuch.hombroDer.anguloRotacionY = 0;
			punhetazoDerFase[idLuchador] = 3;

		}
		break;
		//Todo a 0
	case 3: //P.R.Z = 120 * GradosToRadianes
		//printf("Fase 3\n");

		if (miLuchador->cuerpoLuch.hombroDer.anguloRotacionZ  < 120 * GradosToRadianes) {
			miLuchador->cuerpoLuch.hombroDer.anguloRotacionZ += 4 * GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
		}
		else if (casiIgual(miLuchador->cuerpoLuch.hombroDer.anguloRotacionZ, 120*GradosToRadianes, 0.1)) {
			miLuchador->cuerpoLuch.hombroDer.anguloRotacionZ = 120* GradosToRadianes;
			punhetazoDerFase[idLuchador] = 4;
		}
		else {
			miLuchador->cuerpoLuch.hombroDer.anguloRotacionZ = 120 * GradosToRadianes;
			punhetazoDerFase[idLuchador] = 4;
		}
		break;
		//P.Z = 120
	case 4: //P.Z = 120 PX = 90
		//printf("Fase 4\n");
		if (miLuchador->cuerpoLuch.hombroDer.anguloRotacionZ > 90 * GradosToRadianes) {
			miLuchador->cuerpoLuch.hombroDer.anguloRotacionZ -= 4 * GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
		}
		else{
			miLuchador->cuerpoLuch.hombroDer.anguloRotacionZ = 90 * GradosToRadianes;
		}
		if (miLuchador->cuerpoLuch.hombroDer.anguloRotacionX < FLEXIONPUNHODERX * GradosToRadianes) {
			miLuchador->cuerpoLuch.hombroDer.anguloRotacionX += 4*GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
		}
		else if (casiIgual(miLuchador->cuerpoLuch.hombroDer.anguloRotacionX, 90 * GradosToRadianes, 0.1)) {
			miLuchador->cuerpoLuch.hombroDer.anguloRotacionX = FLEXIONPUNHODERY * GradosToRadianes;
			punhetazoDerFase[idLuchador] = 5;
		}
		else {
			miLuchador->cuerpoLuch.hombroDer.anguloRotacionX = FLEXIONPUNHODERY * GradosToRadianes;
			punhetazoDerFase[idLuchador] = 5;
		}
		break;
	//P.Z = 90 PX = 90
	case 5: //P.Y = -90 PX = 0 PZ = 0
		//printf("Fase 5\n");

		miLuchador->cuerpoLuch.hombroDer.anguloRotacionX = 0;
		miLuchador->cuerpoLuch.hombroDer.anguloRotacionZ = 0;

		miLuchador->cuerpoLuch.hombroDer.anguloRotacionY = -90 * GradosToRadianes;
		punhetazoDerFase[idLuchador] = 6;
		break;
	//P.Y = -90
	case 6: //P.Y = -80
		//printf("Estoy aqui\n");
		//printf("Fase 6\n");

		if (miLuchador->cuerpoLuch.hombroDer.anguloRotacionY < -80 * GradosToRadianes) {
			//printf("RotY %f\n", miLuchador->cuerpoLuch.hombroDer.anguloRotacionY/GradosToRadianes);
			miLuchador->cuerpoLuch.hombroDer.anguloRotacionY += 2 * GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
		}
		else if (casiIgual(miLuchador->cuerpoLuch.hombroDer.anguloRotacionY, -80 * GradosToRadianes, 0.1)) {
			//printf("Casi igual\tRotY %f\n", miLuchador->cuerpoLuch.hombroDer.anguloRotacionY / GradosToRadianes);
			miLuchador->cuerpoLuch.hombroDer.anguloRotacionY = -80 * GradosToRadianes;
			punhetazoDerFase[idLuchador] = 0;
			bGolpearAnimacion[idLuchador] = 0;
			tipoGolpe[idLuchador] = 0;
			miLuchador->golpeando = 0;
			miLuchador->recibeOrdenes = TRUE;
		}
		else {
			miLuchador->cuerpoLuch.hombroDer.anguloRotacionY = -80 * GradosToRadianes;
			punhetazoDerFase[idLuchador] = 0;
			bGolpearAnimacion[idLuchador] = 0;
			tipoGolpe[idLuchador] = 0;
			miLuchador->golpeando = 0;
			miLuchador->recibeOrdenes = TRUE;
		}

		break;
	default:
		miLuchador->recibeOrdenes = FALSE;
		miLuchador->golpeando = 1;
		punhetazoDerFase[idLuchador] = 2;
		tipoGolpe[idLuchador] = 2;
		break;
	

	}
}

void patadaIzquierda(luchador* miLuchador, int idLuchador) {

	switch (patadaIzqFase[idLuchador]) {
	case 1:
		miLuchador->golpeando = 1;
		patadaIzqFase[idLuchador] = 2;
		miLuchador->bloquearCaminar = 1;
		miLuchador->recibeOrdenes = FALSE;
		break;
		//Nada inicial

	case 2: //P.X.-160
		if (miLuchador->cuerpoLuch.caderaIzq.anguloRotacionX > -160 * GradosToRadianes) {
			miLuchador->cuerpoLuch.caderaIzq.anguloRotacionX -= GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
		}
		else if (casiIgual(miLuchador->cuerpoLuch.caderaIzq.anguloRotacionX, 160 *GradosToRadianes, 0.1)) {
			miLuchador->cuerpoLuch.caderaIzq.anguloRotacionX = -160 * GradosToRadianes;
			patadaIzqFase[idLuchador] = 3;
		}
		else {
			miLuchador->cuerpoLuch.caderaIzq.anguloRotacionX = -160 * GradosToRadianes;
			patadaIzqFase[idLuchador] = 3;

		}
		break;
		
	//P.R.Y = -160 * GradosToRadianes
	case 3: //P.R.Y = 0
		if (miLuchador->cuerpoLuch.caderaIzq.anguloRotacionX < 0) {
			miLuchador->cuerpoLuch.caderaIzq.anguloRotacionX += 3*GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
		}
		else if (casiIgual(miLuchador->cuerpoLuch.caderaIzq.anguloRotacionX, 0, 0.1)) {
			miLuchador->cuerpoLuch.caderaIzq.anguloRotacionX = 0;
			patadaIzqFase[idLuchador] = 0;
			bGolpearAnimacion[idLuchador] = 0;
			tipoGolpe[idLuchador] = 0;
			miLuchador->golpeando = 0;
			miLuchador->bloquearCaminar = 0;
			miLuchador->recibeOrdenes = TRUE;

		}
		else {
			miLuchador->cuerpoLuch.caderaIzq.anguloRotacionX = 0;
			patadaIzqFase[idLuchador] = 0;
			bGolpearAnimacion[idLuchador] = 0;
			tipoGolpe[idLuchador] = 0;
			miLuchador->golpeando = 0;
			miLuchador->bloquearCaminar = 0;
			miLuchador->recibeOrdenes = TRUE;

		}

		break;
	default:
		miLuchador->golpeando = 1;
		patadaIzqFase[idLuchador] = 2;
		miLuchador->bloquearCaminar = 1;
		miLuchador->recibeOrdenes = FALSE;
		tipoGolpe[idLuchador] = 3;
		break;
	}
}

void patadaDerecha(luchador* miLuchador, int idLuchador) {

	switch (patadaDerFase[idLuchador]) {
	case 1:
		miLuchador->golpeando = 1;
		patadaDerFase[idLuchador] = 2;
		miLuchador->bloquearCaminar = 1;
		miLuchador->recibeOrdenes = FALSE;
		break;
		//Nada inicial

	case 2: //P.X.90
		if (miLuchador->cuerpoLuch.caderaDer.anguloRotacionX > -90 * GradosToRadianes) {
			miLuchador->cuerpoLuch.caderaDer.anguloRotacionX -= GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
		}
		else if (casiIgual(miLuchador->cuerpoLuch.caderaDer.anguloRotacionX, -90 * GradosToRadianes, 0.1)) {
			miLuchador->cuerpoLuch.caderaDer.anguloRotacionX = -90 * GradosToRadianes;
			patadaDerFase[idLuchador] = 3;
		}
		else {
			miLuchador->cuerpoLuch.caderaDer.anguloRotacionX = -90 * GradosToRadianes;
			patadaDerFase[idLuchador] = 3;

		}
		break;

		//P.R.Y = 90 * GradosToRadianes
	case 3: //P.R.Y = 0
		if (miLuchador->cuerpoLuch.caderaDer.anguloRotacionX < 0) {
			miLuchador->cuerpoLuch.caderaDer.anguloRotacionX += 3 * GOLPEARESCALAR * GradosToRadianes * deltaTime * VELOCIDADANIMACION;
		}
		else if (casiIgual(miLuchador->cuerpoLuch.caderaDer.anguloRotacionX, 0, 0.1)) {
			miLuchador->cuerpoLuch.caderaDer.anguloRotacionX = 0;
			patadaDerFase[idLuchador] = 0;
			bGolpearAnimacion[idLuchador] = 0;
			tipoGolpe[idLuchador] = 0;
			miLuchador->golpeando = 0;
			miLuchador->bloquearCaminar = 0;
			miLuchador->recibeOrdenes = TRUE;

		}
		else {
			miLuchador->cuerpoLuch.caderaDer.anguloRotacionX = 0;
			patadaDerFase[idLuchador] = 0;
			bGolpearAnimacion[idLuchador] = 0;
			tipoGolpe[idLuchador] = 0;
			miLuchador->golpeando = 0;
			miLuchador->bloquearCaminar = 0;
			miLuchador->recibeOrdenes = TRUE;

		}
		break;

	default:
		miLuchador->golpeando = 1;
		patadaDerFase[idLuchador] = 2;
		miLuchador->bloquearCaminar = 1;
		miLuchador->recibeOrdenes = FALSE;
		tipoGolpe[idLuchador] = 4;
		break;
	}
}


void brazoEstandar(luchador* miLuchador, int idLuchador) {
	miLuchador->cuerpoLuch.hombroIzq.anguloRotacionY = 80 * GradosToRadianes;
	miLuchador->cuerpoLuch.hombroDer.anguloRotacionY = -80 * GradosToRadianes;
}