#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <math.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "macrosYTipeDef.h"


extern int eleccionCamara, mostrarOrbitas;
extern double xCamara, yCamara, zCamara;
extern double dirCamaraX, dirCamaraY, dirCamaraZ;
extern double gradosAumentar;



extern void caminar(luchador *miLuchador);

extern int animacionesActuales[NLUCHADORES];
extern int bCaminarAnimacion[NLUCHADORES];
extern int bRetrocederAnimacion[NLUCHADORES];
extern int bPosInc[NLUCHADORES];
extern int bPosIncRetroceder[NLUCHADORES];
extern int bSaltarAnimacion[NLUCHADORES];
extern int bGolpearAnimacion[NLUCHADORES];
extern float aceleracionGravitatoria[NLUCHADORES];
extern int tipoGolpe[NLUCHADORES];
extern int punhetazoIzqFase[NLUCHADORES];
extern int punhetazoDerFase[NLUCHADORES];
extern int patadaIzqFase[NLUCHADORES];
extern int patadaDerFase[NLUCHADORES];
extern int modoJuego;
extern int bModoSeleccionado;
extern int numeroOrdenes;
extern float esperarAtacar;

extern luchador luchadores[NLUCHADORES];

extern void anhularCaminar(luchador* miLuchador, int idLuchador);
extern void imprimirHitbox(hitbox box);
extern hitbox hitBoxPosicion(luchador miLuchador, int idLuchador);
extern hitbox hitBoxGolpe(luchador miLuchador, int idLuchador);
extern void imprimirControles(int modo);


void keyCallback(GLFWwindow* window, unsigned int key) //Funcion utilizada para ocultar las orbitas según el uso del teclado y controlar la cámara
{
	//std::cout << key << std::endl;


}

void specialKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//std::cout << key << std::endl;
	

	switch (modoJuego) {
	case 0:
		if (key == '1' && action == GLFW_RELEASE) {
			modoJuego = 1;
			bModoSeleccionado = 1;
			eleccionCamara = 5;
			xCamara = -600, yCamara = 0, zCamara = 170;
			imprimirControles(1);
			break;
		}
		if (key == '2' && action == GLFW_RELEASE) {
			modoJuego = 2;
			bModoSeleccionado = 1;
			eleccionCamara = 5;
			xCamara = -600, yCamara = 0, zCamara = 170;
			imprimirControles(2);
			break;
		}
		break;
	case 1:
		if (key == '2' && action == GLFW_RELEASE) {
			modoJuego = 3;
			numeroOrdenes = 8;
			bModoSeleccionado = 1;
			esperarAtacar = 2;
		}
		if (key == '3' && action == GLFW_RELEASE) {
			modoJuego = 3;
			numeroOrdenes = 8;
			bModoSeleccionado = 1;
			esperarAtacar = 1;
		}
		if (key == '4' && action == GLFW_RELEASE) {
			modoJuego = 3;
			numeroOrdenes = 6;
			bModoSeleccionado = 1;
		}
	case 3: //Modo 1 jugador

		
		//Camara
		if (key == '1' && action == GLFW_PRESS) { //Modo 1 Camara vista por detrás y-
			eleccionCamara = 1;

		}
		//if (key == '2' && action == GLFW_PRESS) { //Modo 2 vista por delante y+
		//	eleccionCamara = 2;
		//	xCamara = 0, yCamara = +VALORCAMARAESTANDAR, zCamara = 0;
		//}
		//if (key == '3' && action == GLFW_PRESS) { //Modo 3 Camara Vista por arriba z+
		//	eleccionCamara = 3;
		//	xCamara = 0, yCamara = 0, zCamara = VALORCAMARAESTANDAR * 3;
		//}
		//if (key == '4' && action == GLFW_PRESS) { //Modo 4 Camara Vista por abajo z-
		//	eleccionCamara = 4;
		//	xCamara = 0, yCamara = 0, zCamara = -VALORCAMARAESTANDAR * 3;
		//}
		if (key == '3' && action == GLFW_PRESS) { //Modo 5 Camara Vista perfil izquierdo x-
			eleccionCamara = 5;
			xCamara = -600, yCamara = 0, zCamara = 170;
		}
		//if (key == '6' && action == GLFW_PRESS) { //Modo 6 Camara Vista perfil derecho x+
		//	eleccionCamara = 6;
		//	xCamara = 400, yCamara = 0, zCamara = 200;
		//}
		//if (key == 93 && action == GLFW_PRESS) {
		//	zCamara += 10;
		//}
		//if (key == 61 && action == GLFW_PRESS) {
		//	zCamara -= 10;
		//}
		if ((key == 'r' || key == 'R') && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			xCamara += 10;
		}
		if ((key == 't' || key == 'T') && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			xCamara -= 10;
		}

		if ((key == 'y' || key == 'Y') && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			if (eleccionCamara == 5) {
				yCamara += 10;
				dirCamaraY += 10;
			}
		}
		if ((key == 'u' || key == 'U') && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			if (eleccionCamara == 5) {
				yCamara -= 10;
				dirCamaraY -= 10;
			}
		}

		//Controles jugador 1

		//Saltar
		if ((key == 'w' || key == 'W' || key == GLFW_KEY_UP) && action == GLFW_PRESS) {
			//Saltar
			if (!luchadores[0].enAire) {
				bSaltarAnimacion[0] = 1;
			}
			else {
				aceleracionGravitatoria[0] = -10;
				//printf("hola\n");
			}
		}
		if ((key == 'd' || key == 'D' || key == GLFW_KEY_RIGHT) && action == GLFW_PRESS) {
			if (luchadores[0].orientacion == 1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bCaminarAnimacion[0] = 1;
					bPosInc[0] = 0;
				}
			}
			if (luchadores[0].orientacion == -1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bRetrocederAnimacion[0] = 1;
					bPosIncRetroceder[0] = 0;
				}
			}
		}
		else if ((key == 'd' || key == 'D' || key == GLFW_KEY_RIGHT) && action == GLFW_RELEASE) {
			if (luchadores[0].orientacion == 1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bPosInc[0] = 0;
					bCaminarAnimacion[0] = 0;
				}
			}

			if (luchadores[0].orientacion == -1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bPosIncRetroceder[0] = 0;
					bRetrocederAnimacion[0] = 0;
				}
			}
		}

		if ((key == 'a' || key == 'A' || key == GLFW_KEY_LEFT) && action == GLFW_PRESS) {
			if (luchadores[0].orientacion == 1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bRetrocederAnimacion[0] = 1;
					bPosIncRetroceder[0] = 0;
				}
			}


			if (luchadores[0].orientacion == -1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bCaminarAnimacion[0] = 1;
					bPosInc[0] = 0;
				}
			}
		}

		else if ((key == 'a' || key == 'A' || key == GLFW_KEY_LEFT) && action == GLFW_RELEASE) {
			if (luchadores[0].orientacion == 1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bPosIncRetroceder[0] = 0;
					bRetrocederAnimacion[0] = 0;
				}
			}

			if (luchadores[0].orientacion == -1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bPosInc[0] = 0;
					bCaminarAnimacion[0] = 0;
				}
			}
		}

		if ((key == 'g' || key == 'G') && action == GLFW_PRESS) { //Puño derecho
			if (luchadores[0].golpeando == 0) {
				tipoGolpe[0] = 1;
				punhetazoIzqFase[0] = 1;
				bGolpearAnimacion[0] = 1;
			}
		}

		if ((key == 'h' || key == 'H') && action == GLFW_PRESS) { //Puño izquierdo
			if (luchadores[0].golpeando == 0) {
				tipoGolpe[0] = 2;
				punhetazoDerFase[0] = 1;
				bGolpearAnimacion[0] = 1;
			}
		}

		if ((key == 'b' || key == 'B') && action == GLFW_PRESS) { //Patada izquierda alta
			if (luchadores[0].golpeando == 0) {
				tipoGolpe[0] = 3;
				patadaIzqFase[0] = 1;
				bGolpearAnimacion[0] = 1;
				anhularCaminar(&luchadores[0], 0);
			}
		}
		if ((key == 'n' || key == 'N') && action == GLFW_PRESS) { //Patada hacia adelante
			if (luchadores[0].golpeando == 0) {
				tipoGolpe[0] = 4;
				patadaDerFase[0] = 1;
				bGolpearAnimacion[0] = 1;
				anhularCaminar(&luchadores[0], 0);
			}
		}

		break;

	case 2:

		//Camara
		if (key == '1' && action == GLFW_PRESS) { //Modo 1 Camara vista por detrás y- Nota: Comentar despues
			eleccionCamara = 1;
			xCamara = 0, yCamara = -VALORCAMARAESTANDAR, zCamara = 0;
		}
		//if (key == '2' && action == GLFW_PRESS) { //Modo 2 vista por delante y+
		//	eleccionCamara = 2;
		//	xCamara = 0, yCamara = +VALORCAMARAESTANDAR, zCamara = 0;
		//}
		//if (key == '3' && action == GLFW_PRESS) { //Modo 3 Camara Vista por arriba z+
		//	eleccionCamara = 3;
		//	xCamara = 0, yCamara = 0, zCamara = VALORCAMARAESTANDAR * 3;
		//}
		//if (key == '4' && action == GLFW_PRESS) { //Modo 4 Camara Vista por abajo z-
		//	eleccionCamara = 4;
		//	xCamara = 0, yCamara = 0, zCamara = -VALORCAMARAESTANDAR * 3;
		//}
		if (key == '3' && action == GLFW_PRESS) { //Modo 5 Camara Vista perfil izquierdo x-. Nota: Comentar despues
			eleccionCamara = 5;
			xCamara = -600, yCamara = 0, zCamara = 170;
		}

		//if (key == 61 && action == GLFW_PRESS) {
		//	zCamara -= 10;
		//}

		if ((key == 'r' || key == 'R') && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			xCamara += 10;
		}
		if ((key == 't' || key == 'T') && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			xCamara -= 10;
		}

		if ((key == 'y' || key == 'Y') && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			yCamara += 10;
			dirCamaraY += 10;
		}
		if ((key == 'u' || key == 'U') && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			yCamara -= 10;
			dirCamaraY -= 10;
		}

		//Controles jugador 1

		//Saltar
		if ((key == 'w' || key == 'W') && action == GLFW_PRESS) {
			//Saltar
			if (!luchadores[0].enAire) {
				bSaltarAnimacion[0] = 1;
			}
			else {
				aceleracionGravitatoria[0] = -10;
				//printf("hola\n");
			}
		}
		if ((key == 'd' || key == 'D') && action == GLFW_PRESS) {
			if (luchadores[0].orientacion == 1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bCaminarAnimacion[0] = 1;
					bPosInc[0] = 0;
				}
			}
			if (luchadores[0].orientacion == -1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bRetrocederAnimacion[0] = 1;
					bPosIncRetroceder[0] = 0;
				}
			}
		}
		else if ((key == 'd' || key == 'D') && action == GLFW_RELEASE) {
			if (luchadores[0].orientacion == 1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bPosInc[0] = 0;
					bCaminarAnimacion[0] = 0;
				}
			}

			if (luchadores[0].orientacion == -1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bPosIncRetroceder[0] = 0;
					bRetrocederAnimacion[0] = 0;
				}
			}
		}

		if ((key == 'a' || key == 'A') && action == GLFW_PRESS) {
			if (luchadores[0].orientacion == 1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bRetrocederAnimacion[0] = 1;
					bPosIncRetroceder[0] = 0;
				}
			}


			if (luchadores[0].orientacion == -1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bCaminarAnimacion[0] = 1;
					bPosInc[0] = 0;
				}
			}
		}

		else if ((key == 'a' || key == 'A') && action == GLFW_RELEASE) {
			if (luchadores[0].orientacion == 1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bPosIncRetroceder[0] = 0;
					bRetrocederAnimacion[0] = 0;
				}
			}

			if (luchadores[0].orientacion == -1) {
				if (luchadores[0].bloquearCaminar == 0) {
					bPosInc[0] = 0;
					bCaminarAnimacion[0] = 0;
				}
			}
		}

		if ((key == 'c' || key == 'C') && action == GLFW_PRESS) {
			if (luchadores[0].golpeando == 0) {
				tipoGolpe[0] = 1;
				punhetazoIzqFase[0] = 1;
				bGolpearAnimacion[0] = 1;
			}
		}

		if ((key == 'x' || key == 'X') && action == GLFW_PRESS) {
			if (luchadores[0].golpeando == 0) {
				tipoGolpe[0] = 2;
				punhetazoDerFase[0] = 1;
				bGolpearAnimacion[0] = 1;
			}
		}

		if ((key == 'v' || key == 'V') && action == GLFW_PRESS) { //Patada izquierda alta
			if (luchadores[0].golpeando == 0) {
				tipoGolpe[0] = 3;
				patadaIzqFase[0] = 1;
				bGolpearAnimacion[0] = 1;
				anhularCaminar(&luchadores[0], 0);
			}
		}
		if ((key == 's' || key == 'S') && action == GLFW_PRESS) { //Patada derecha hacia adelante
			if (luchadores[0].golpeando == 0) {
				tipoGolpe[0] = 4;
				patadaDerFase[0] = 1;
				bGolpearAnimacion[0] = 1;
				anhularCaminar(&luchadores[0], 0);
			}
		}


		//Controles jugador 2

			//Saltar
		if ((key == 'i' || key == 'I') && action == GLFW_PRESS) {
			//Saltar
			if (!luchadores[1].enAire) {
				bSaltarAnimacion[1] = 1;
			}
			else {
				aceleracionGravitatoria[1] = -10;
				//printf("hola\n");
			}
		}
		if ((key == 'l' || key == 'L') && action == GLFW_PRESS) {
			if (luchadores[1].orientacion == 1) {
				if (luchadores[1].bloquearCaminar == 0) {
					bCaminarAnimacion[1] = 1;
					bPosInc[1] = 0;
				}
			}
			if (luchadores[1].orientacion == -1) {
				if (luchadores[1].bloquearCaminar == 0) {
					bRetrocederAnimacion[1] = 1;
					bPosIncRetroceder[1] = 0;
				}
			}
		}
		else if ((key == 'l' || key == 'L') && action == GLFW_RELEASE) {
			if (luchadores[1].orientacion == 1) {
				if (luchadores[1].bloquearCaminar == 0) {
					bPosInc[1] = 0;
					bCaminarAnimacion[1] = 0;
				}
			}

			if (luchadores[1].orientacion == -1) {
				if (luchadores[1].bloquearCaminar == 0) {
					bPosIncRetroceder[1] = 0;
					bRetrocederAnimacion[1] = 0;
				}
			}
		}

		if ((key == 'j' || key == 'J') && action == GLFW_PRESS) {
			if (luchadores[1].orientacion == 1) {
				if (luchadores[1].bloquearCaminar == 0) {
					bRetrocederAnimacion[1] = 1;
					bPosIncRetroceder[1] = 0;
				}
			}


			if (luchadores[1].orientacion == -1) {
				if (luchadores[1].bloquearCaminar == 0) {
					bCaminarAnimacion[1] = 1;
					bPosInc[1] = 0;
				}
			}
		}

		else if ((key == 'j' || key == 'J') && action == GLFW_RELEASE) {
			if (luchadores[1].orientacion == 1) {
				if (luchadores[1].bloquearCaminar == 0) {
					bPosIncRetroceder[1] = 0;
					bRetrocederAnimacion[1] = 0;
				}
			}

			if (luchadores[1].orientacion == -1) {
				if (luchadores[1].bloquearCaminar == 0) {
					bPosInc[1] = 0;
					bCaminarAnimacion[1] = 0;
				}
			}
		}

		if ((key == 'b' || key == 'B') && action == GLFW_PRESS) {
			if (luchadores[1].golpeando == 0) {
				tipoGolpe[1] = 1;
				punhetazoIzqFase[1] = 1;
				bGolpearAnimacion[1] = 1;
			}
		}

		if ((key == 'n' || key == 'N') && action == GLFW_PRESS) {
			if (luchadores[1].golpeando == 0) {
				tipoGolpe[1] = 2;
				punhetazoDerFase[1] = 1;
				bGolpearAnimacion[1] = 1;
			}
		}

		if (key == 47 && action == GLFW_PRESS) { //Patada izquierda alta
			if (luchadores[1].golpeando == 0) {
				tipoGolpe[1] = 3;
				patadaIzqFase[1] = 1;
				bGolpearAnimacion[1] = 1;
				anhularCaminar(&luchadores[1], 1);
			}
		}
		if ((key == '.' || key == ':') && action == GLFW_PRESS) { //Patada derecha hacia adelante
			if (luchadores[1].golpeando == 0) {
				tipoGolpe[1] = 4;
				patadaDerFase[1] = 1;
				bGolpearAnimacion[1] = 1;
				anhularCaminar(&luchadores[1], 1);
			}
		}
		break;




	}





	////Impresion de datos

	//if ((key == 'r' || key == 'R') && action == GLFW_PRESS) {
	//	hitbox miHitbox, rivalHitbox;
	//	miHitbox = hitBoxPosicion(luchadores[0], 0);
	//	rivalHitbox = hitBoxPosicion(luchadores[1], 1);
	//	printf("MiHitbox:\n");
	//	imprimirHitbox(miHitbox);
	//	printf("\nRivalHitbox:\n");
	//	imprimirHitbox(rivalHitbox);
	//	printf("\nmiLuchador: %f\t%f\t%f\t%d\n", luchadores[0].px, luchadores[0].py, luchadores[0].pz, luchadores[0].orientacion);
	//	printf("Rival: %f\t%f\t%f\t%d\n", luchadores[1].px, luchadores[1].py, luchadores[1].pz, luchadores[1].orientacion);

	//}

	//if ((key == 't' || key == 'T') && action == GLFW_PRESS) {
	//	hitbox miHitbox, rivalHitbox;
	//	miHitbox = hitBoxGolpe(luchadores[0], 0);
	//	rivalHitbox = hitBoxGolpe(luchadores[1], 1);
	//	printf("MiHitbox:\n");
	//	imprimirHitbox(miHitbox);
	//	printf("\nRivalHitbox:\n");
	//	imprimirHitbox(rivalHitbox);
	//	printf("\nmiLuchador: %f\t%f\t%f\t%d\t%f\n", luchadores[0].px, luchadores[0].py, luchadores[0].pz, luchadores[0].orientacion, luchadores[0].vidaActual);
	//	printf("Rival: %f\t%f\t%f\t%d\t%f\n", luchadores[1].px, luchadores[1].py, luchadores[1].pz, luchadores[1].orientacion, luchadores[1].vidaActual);
	//}
	
	if ((key == 'q' || key == 'Q') && action == GLFW_PRESS) {
		
		
		printf("\nmiLuchador: %f\n", luchadores[0].py);
		printf("Rival: %f\n", luchadores[1].py);
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){

}