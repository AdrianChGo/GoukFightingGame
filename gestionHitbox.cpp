#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <math.h> 
#include "macrosYTipeDef.h"

extern luchador luchadores[NLUCHADORES];
extern double deltaTime;
extern int tipoGolpe[NLUCHADORES];
extern int bSaltarAnimacion[NLUCHADORES];
extern int punhetazoIzqFase[NLUCHADORES];
extern int punhetazoDerFase[NLUCHADORES];
extern float pzAux, szAux, syAux, sxAux;
float auxPosYContacto[NLUCHADORES];
float auxPosYGolpe[NLUCHADORES];
float esperaRecuperacion = 0;
int faseColision = 0;
hitbox boxNulo{ 0,0,0,0,0,0 };

hitbox hitBoxPosicion(luchador miLuchador, int idLuchador);
int colisionEnEje(float rangoA[2], float rangoB[2]);
int colisionCuerpos(hitbox box1, hitbox box2);

void paredInvisible(luchador *miLuchador) {
	if (miLuchador->py > LIMITEPANTALLA) {
		miLuchador->py = LIMITEPANTALLA;
	}
}

void ordenarVectorMenor(float miVector[2]) {
	float aux;
	if (miVector[0] > miVector[1]) {
		aux = miVector[1];
		miVector[1] = miVector[0];
		miVector[0] = aux;
	}
}

void ordenarVectorMayor(float miVector[2]) {
	float aux;
	if (miVector[0] < miVector[1]) {
		aux = miVector[1];
		miVector[1] = miVector[0];
		miVector[0] = aux;
	}
}

void gestionColisionMutuaGolpe() {
	//printf("Ambos luchadores se estan pegando\n");

	switch (faseColision){
	case 0:
		if (luchadores[0].py + 60 > LIMITEPANTALLA) {
			luchadores[1].py += deltaTime * VELOCIDADREPULSIONGOLPE * VELOCIDADANIMACION;
			if (luchadores[1].py > 60 + auxPosYGolpe[1]) {
				luchadores[1].py = auxPosYGolpe[1] + 60;
				faseColision = 1;
			}
		}
		else if (luchadores[1].py + 60 > LIMITEPANTALLA) {
			luchadores[0].py += deltaTime * VELOCIDADREPULSIONGOLPE * VELOCIDADANIMACION;
			if (luchadores[0].py > 60 + auxPosYGolpe[0]) {
				luchadores[0].py = auxPosYGolpe[0] + 60;
				faseColision = 1;
			}
		}
		else if (luchadores[0].py < 40 + auxPosYGolpe[0]) {
			luchadores[0].py += deltaTime * VELOCIDADREPULSIONGOLPE * VELOCIDADANIMACION;
			luchadores[1].py += deltaTime * VELOCIDADREPULSIONGOLPE * VELOCIDADANIMACION;
		}
		else {
			luchadores[0].py = auxPosYGolpe[0] + 40;
			luchadores[1].py = auxPosYGolpe[1] + 40;
			faseColision = 1;
		}
		break;
	case 1:
		if (esperaRecuperacion < 1) {
			esperaRecuperacion += deltaTime;

		}
		else {
			//printf("Ya estoy listo\n");
			luchadores[0].colisionadoGolpe = 0;
			luchadores[1].colisionadoGolpe = 0;
			esperaRecuperacion = 0;
			faseColision = 0;
		}
		break;
	}
	

}

void gestionColisionIndividualGolpe(luchador* miLuchador, int idLuchador) {
	//printf("Esta habiendo colision de golpes. El que recibe es: %d\n", idLuchador);
	
	switch (faseColision) {

	case 0:
		if (miLuchador->py + 80 > LIMITEPANTALLA) {
			faseColision = 1;
		}
		else if (miLuchador->py < 80 + auxPosYGolpe[idLuchador]) {
			miLuchador->py += deltaTime * VELOCIDADREPULSIONGOLPE * VELOCIDADANIMACION;

		}
		else {
			faseColision = 1;
			miLuchador->py = auxPosYGolpe[idLuchador] + 80;
		}
		break;
	case 1:
		if (esperaRecuperacion < 1) {
			esperaRecuperacion += deltaTime;

		}
		else {
			//printf("Ya estoy listo\n");
			miLuchador->colisionadoGolpe = 0;
			esperaRecuperacion = 0;
			faseColision = 0;
		}
		break;
	}


}

void gestionColisionCuerpos() {
	hitbox box1, box2;
	box1 = hitBoxPosicion(luchadores[0], 0);
	box2 = hitBoxPosicion(luchadores[1], 1);
	//printf("Esta habiendo colision de cuerpos\n");
	if (!colisionCuerpos(box1, box2)) {
		luchadores[0].colisionadoCuerpo = 0;
		luchadores[1].colisionadoCuerpo = 0;
		luchadores[0].py = auxPosYContacto[0] + 30;
		luchadores[1].py = auxPosYContacto[1] + 30;
	}
	else if (luchadores[0].py + luchadores[1].py < 60) {
		luchadores[0].py += deltaTime * VELOCIDADREPULSION * VELOCIDADANIMACION;
		luchadores[1].py += deltaTime * VELOCIDADREPULSION * VELOCIDADANIMACION;
	}
	else {
		luchadores[0].colisionadoCuerpo = 0;
		luchadores[1].colisionadoCuerpo = 0;
		luchadores[0].py = auxPosYContacto[0] + 30;
		luchadores[1].py = auxPosYContacto[1] + 30;

	}
	
}




void imprimirHitbox(hitbox box) {
	printf("HitboxX: %4f <---> %4f\n", box.rangoX[0], box.rangoX[1]);
	printf("HitboxY: %4f <---> %4f\n", box.rangoY[0], box.rangoY[1]);
	printf("HitboxZ: %4f <---> %4f\n", box.rangoZ[0], box.rangoZ[1]);

}


int colisionEnEje(float rangoA[2], float rangoB[2]) {
	if (rangoB[0] >= rangoA[0] && rangoB[0] <= rangoA[1]) {
		return 1;
	}
	else if (rangoB[1] >= rangoA[0] && rangoB[1] <= rangoA[1]) {
		return 1;
	}
	else if (rangoA[0] >= rangoB[0] && rangoA[0] <= rangoB[1]) {
		return 1;
	}
	else if (rangoA[1] >= rangoB[0] && rangoA[1] <= rangoB[1]) {
		return 1;
	}
	else {
		return 0;
	}
}

int colisionCuerpos(hitbox box1, hitbox box2) {
	if (colisionEnEje(box1.rangoX, box2.rangoX) && colisionEnEje(box1.rangoY, box2.rangoY) && colisionEnEje(box1.rangoZ, box2.rangoZ)) {
		auxPosYContacto[0] = luchadores[0].py;
		auxPosYGolpe[0] = luchadores[0].py;
		auxPosYContacto[1] = luchadores[1].py;
		auxPosYGolpe[1] = luchadores[1].py;
		return 1;
	}
	return 0;
}




hitbox hitBoxPosicion(luchador miLuchador, int idLuchador) { //Siempre la posicion inicial está el numero menor
	hitbox boxCuerpo;


	if (miLuchador.orientacion == 1) {
		boxCuerpo.rangoX[0] = miLuchador.px - sxAux / 2;
		boxCuerpo.rangoX[1] = miLuchador.px + sxAux / 2;
		ordenarVectorMenor(boxCuerpo.rangoX);

		boxCuerpo.rangoY[0] = miLuchador.py - syAux *1.5;
		boxCuerpo.rangoY[1] = miLuchador.py + syAux *1.5;
		ordenarVectorMenor(boxCuerpo.rangoY);
	}
	else if (miLuchador.orientacion == -1) {
		boxCuerpo.rangoX[0] = -miLuchador.px + sxAux / 2;
		boxCuerpo.rangoX[1] = -miLuchador.px - sxAux / 2;
		ordenarVectorMenor(boxCuerpo.rangoX);

		boxCuerpo.rangoY[0] = -miLuchador.py + syAux*1.5;
		boxCuerpo.rangoY[1] = -miLuchador.py - syAux *1.5;
		ordenarVectorMenor(boxCuerpo.rangoY);
	}
	boxCuerpo.rangoZ[0] = miLuchador.pz - 9;
	boxCuerpo.rangoZ[1] = miLuchador.pz + 253;
	ordenarVectorMenor(boxCuerpo.rangoZ);
	return boxCuerpo;
}


//px = luch.px -40
//px = luch.px

//px = luch.px el derecho
//px = luch.px + 200 el derecho

//el derecho
//py = luch.py
//py = luch.py +- 100 * sin(Angulo que sea) en la fase adecuada

//el izquierdo
//py = luch.py
//py = luch.py seguramente lo mismo

//luch.pz + 156
//luch.pz + 174

hitbox hitBoxPunhetazoIzq(luchador miLuchador, int idLuchador) {
	hitbox box;
	switch (punhetazoIzqFase[idLuchador]) {
	case 4:
		if (miLuchador.orientacion == 1) {
			box.rangoX[0] = miLuchador.px - 40;
			box.rangoX[1] = miLuchador.px;
			ordenarVectorMenor(box.rangoX);

			box.rangoY[0] = miLuchador.py;
			box.rangoY[1] = miLuchador.py + 100 * sin(miLuchador.cuerpoLuch.hombroIzq.anguloRotacionZ);
			ordenarVectorMenor(box.rangoY);
		}
		else if (miLuchador.orientacion == -1) {
			box.rangoX[0] = (miLuchador.px - 40)* (-1);
			box.rangoX[1] = miLuchador.px* (-1);
			ordenarVectorMenor(box.rangoX);

			box.rangoY[0] = miLuchador.py * (-1);
			box.rangoY[1] = (miLuchador.py + 100 * sin(miLuchador.cuerpoLuch.hombroIzq.anguloRotacionZ)) * (-1);

			ordenarVectorMenor(box.rangoY);
		}

		box.rangoZ[0] = miLuchador.pz + 156;
		box.rangoZ[1] = miLuchador.pz + 174;

		ordenarVectorMenor(box.rangoZ);
		return box;
		break;
	default:
		return boxNulo;
		break;
	}
}

hitbox hitBoxPunhetazoDer(luchador miLuchador, int idLuchador) {
	hitbox box;
	switch (punhetazoDerFase[idLuchador]) {
	case 3:
		if (miLuchador.orientacion == 1) {
			box.rangoX[0] = miLuchador.px +200;
			box.rangoX[1] = miLuchador.px;
			ordenarVectorMenor(box.rangoX);

			box.rangoY[0] = miLuchador.py;
			box.rangoY[1] = miLuchador.py - 80 * sin(miLuchador.cuerpoLuch.hombroDer.anguloRotacionZ);
			ordenarVectorMenor(box.rangoY);
		}
		else if (miLuchador.orientacion == -1) {
			box.rangoX[0] = (miLuchador.px +200) * (-1);
			box.rangoX[1] = miLuchador.px * (-1);
			ordenarVectorMenor(box.rangoX);

			box.rangoY[0] = miLuchador.py * (-1);
			box.rangoY[1] = (miLuchador.py - 80 * sin(miLuchador.cuerpoLuch.hombroDer.anguloRotacionZ)) * (-1);

			ordenarVectorMenor(box.rangoY);
		}

		box.rangoZ[0] = miLuchador.pz + 156;
		box.rangoZ[1] = miLuchador.pz + 174;

		ordenarVectorMenor(box.rangoZ);
		return box;
		break;
	default:
		return boxNulo;
		break;
	}
}

hitbox hitBoxPatadaIzq(luchador miLuchador, int idLuchador) {
	hitbox box;
	//TODO

	if (miLuchador.orientacion == 1) {
		box.rangoX[0] = miLuchador.px + miLuchador.cuerpoLuch.caderaIzq.px - miLuchador.cuerpoLuch.piernaInfIzq.sx;
		box.rangoX[1] = miLuchador.px + miLuchador.cuerpoLuch.caderaIzq.px + miLuchador.cuerpoLuch.piernaInfIzq.sx;
		ordenarVectorMenor(box.rangoX);

		box.rangoY[0] = (miLuchador.py + syAux / 2);
		box.rangoY[1] = miLuchador.py + 100 * sin(miLuchador.cuerpoLuch.caderaIzq.anguloRotacionX);
		ordenarVectorMenor(box.rangoY);
	}
	else if (miLuchador.orientacion == -1) {
		box.rangoX[0] = miLuchador.px + miLuchador.cuerpoLuch.caderaIzq.px - miLuchador.cuerpoLuch.piernaInfIzq.sx * (-1);
		box.rangoX[1] = miLuchador.px + miLuchador.cuerpoLuch.caderaIzq.px + miLuchador.cuerpoLuch.piernaInfIzq.sx * (-1);
		ordenarVectorMenor(box.rangoX);

		box.rangoY[0] = (miLuchador.py + syAux /2) * (-1);
		box.rangoY[1] = (miLuchador.py + 100 * sin(miLuchador.cuerpoLuch.caderaIzq.anguloRotacionX))*(-1);

		ordenarVectorMenor(box.rangoY);
	}

	box.rangoZ[0] = miLuchador.pz +90 - 100 * cos(miLuchador.cuerpoLuch.caderaIzq.anguloRotacionX);
	box.rangoZ[1] = miLuchador.pz +90;

	
	ordenarVectorMenor(box.rangoZ);

	return box;
}

hitbox hitBoxPatadaDer(luchador miLuchador, int idLuchador) {
	hitbox box;
	//TODO

	if (miLuchador.orientacion == 1) {
		box.rangoX[0] = miLuchador.px + miLuchador.cuerpoLuch.caderaDer.px - miLuchador.cuerpoLuch.piernaInfDer.sx;
		box.rangoX[1] = miLuchador.px + miLuchador.cuerpoLuch.caderaDer.px + miLuchador.cuerpoLuch.piernaInfDer.sx;
		ordenarVectorMenor(box.rangoX);
		
		//box.rangoY[0] = miLuchador.py - miLuchador.cuerpoLuch.tronco.sy + miLuchador.cuerpoLuch.pierna * cos(miLuchador.cuerpoLuch.caderaDer.anguloRotacionX); //El numero por el que se multiplica el coseno se corresponde con el tamaño de la pierna calculado experimentalmente
		box.rangoY[0] = (miLuchador.py + syAux / 2);
		box.rangoY[1] = miLuchador.py + 100*sin(miLuchador.cuerpoLuch.caderaDer.anguloRotacionX);

		ordenarVectorMenor(box.rangoY);

	}
	else if (miLuchador.orientacion == -1) { 
		box.rangoX[0] = (miLuchador.px + miLuchador.cuerpoLuch.caderaDer.px - miLuchador.cuerpoLuch.piernaInfDer.sx) * (-1);
		box.rangoX[1] = (miLuchador.px + miLuchador.cuerpoLuch.caderaDer.px + miLuchador.cuerpoLuch.piernaInfDer.sx) * (-1);
		ordenarVectorMenor(box.rangoX);
	
		box.rangoY[0] = (miLuchador.py + syAux /2) *(-1);
		box.rangoY[1] = (miLuchador.py + 100 * sin(miLuchador.cuerpoLuch.caderaDer.anguloRotacionX)) * (-1);

		ordenarVectorMenor(box.rangoY);
	
	}

	box.rangoZ[0] = miLuchador.pz + 90 - 100 * cos(miLuchador.cuerpoLuch.caderaIzq.anguloRotacionX);
	box.rangoZ[1] = miLuchador.pz + 90;
	ordenarVectorMenor(box.rangoZ);
	//La pierna va de -10 a 90, por lo que tiene un valor de 100 



	return box;
}

hitbox hitBoxGolpe(luchador miLuchador, int idLuchador) {
	if (miLuchador.golpeando) {
		hitbox box;
		switch (tipoGolpe[idLuchador]) {
		case 1: //Puñetazo izquierdo
			box = hitBoxPunhetazoIzq(miLuchador, idLuchador);
			break;
		case 2: //Puñetazo izquierdo
			box = hitBoxPunhetazoDer(miLuchador, idLuchador);
			break;
		case 3: //Puñetazo izquierdo
			box = hitBoxPatadaIzq(miLuchador, idLuchador);
			break;
		case 4: //Puñetazo izquierdo
			box = hitBoxPatadaDer(miLuchador, idLuchador);
			break;
		default:
			box = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
		}
		return box;
	}
}