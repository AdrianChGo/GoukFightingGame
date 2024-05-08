#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <MMsystem.h>
#include <time.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

void musicaFondo() {

	//PlaySound(TEXT("sonidos/thisMachine.wav"), NULL, SND_ASYNC | SND_LOOP);
	PlaySound(TEXT("sonidos/colision1.wav"), NULL, SND_ASYNC);

}

void musicaColision() {
	
	int eleccion= 1+(rand()%5);
	
	switch (eleccion) {
		case 1:
			PlaySound(TEXT("sonidos/colision1.wav"), NULL, SND_ASYNC);
			break;
		case 2:
			PlaySound(TEXT("sonidos/colision2.wav"), NULL, SND_ASYNC);
			break;
		case 3:
			PlaySound(TEXT("sonidos/colision3.wav"), NULL, SND_ASYNC);
			break;
		case 4: 
			PlaySound(TEXT("sonidos/colision4.wav"), NULL, SND_ASYNC);
			break;
		case 5:
			PlaySound(TEXT("sonidos/colision5.wav"), NULL, SND_ASYNC);
			break;
		case 6:
			PlaySound(TEXT("sonidos/colision6.wav"), NULL, SND_ASYNC);
			break;
	}


}

void musicaEntrada() {

	int eleccion = 1 + (rand() % 5);
	switch (eleccion) {
	case 1:
		PlaySound(TEXT("sonidos/entrada1.wav"), NULL, SND_ASYNC);
		break;
	case 2:
		PlaySound(TEXT("sonidos/entrada2.wav"), NULL, SND_ASYNC);
		break;
	case 3:
		PlaySound(TEXT("sonidos/entrada3.wav"), NULL, SND_ASYNC);
		break;
	}
}

void musicaVictoria() {
	int eleccion = 1 + (rand() % 5);
	switch (eleccion) {
	case 1:
		PlaySound(TEXT("sonidos/victoria1.wav"), NULL, SND_ASYNC);
		break;
	case 2:
		PlaySound(TEXT("sonidos/victoria2.wav"), NULL, SND_ASYNC);
		break;
	case 3:
		PlaySound(TEXT("sonidos/victoria3.wav"), NULL, SND_ASYNC);
		break;
	case 4:
		PlaySound(TEXT("sonidos/victoria4.wav"), NULL, SND_ASYNC);
		break;
	case 5:
		PlaySound(TEXT("sonidos/victoria5.wav"), NULL, SND_ASYNC);
		break;
	case 6:
		PlaySound(TEXT("sonidos/victoria6.wav"), NULL, SND_ASYNC);
		break;
	case 7:
		PlaySound(TEXT("sonidos/victoria7.wav"), NULL, SND_ASYNC);
		break;
	}
}