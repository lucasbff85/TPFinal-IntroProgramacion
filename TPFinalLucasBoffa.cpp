#include <iostream>
#include <conio2.h>
#include <cstdlib>
#include <ctime>
using namespace std;

//----------------------------------------------------------------------------------
//                                                                    JUEGO

class Juego{
	
};


//-----------------------------------------------------------------------------------
//                                                                    CAJA


class Caja : public Juego {
protected:
	//bordes del recuadro
	int x1 = 5, y1 = 5, x2 = 50, y2 = 25;
	
public:
	Caja();
	void aparecer();
			
};

Caja::Caja (){
	
}

void Caja :: aparecer(){
	
	textcolor(BLUE);
	cout<<"Teclas Movimiento: ASDW"<<endl;
	cout<<" Disparar: SAPACEBAR"<<endl;
	cout<<" Debes disparar a las X, cuidado con los asteroides!"<<endl;
	
	textcolor(WHITE);
	
	
	//Dibujar líneas horizontales
	for (int i = x1; i <= x2; i++){
		gotoxy(i,y1);
		cout<<"#"; //Linea superior
		gotoxy(i,y2);
		cout<<"#"; //Linea inferior
	}
	
	//Dibujar líneas verticales
	for (int i = y1; i <= y2; i++){
		gotoxy(x1,i);
		cout<<"#"; //Línea izquierda
		gotoxy(x2,i);
		cout<<"#";  //Línea derecha
	}
	
	// Dibujar esquinas
	gotoxy(x1, y1);
	cout << "#";  // Esquina superior izquierda
	gotoxy(x2, y1);
	cout << "#";  // Esquina superior derecha
	gotoxy(x1, y2);
	cout << "#";  // Esquina inferior izquierda
	gotoxy(x2, y2);
	cout << "#";  // Esquina inferior derecha
}

//-------------------------------------------------------------------
//                                                          PERSONAJE

class Personaje{
private:
		int x, y;
public:
	Personaje();
	virtual void nacer();
	virtual void mover();
	virtual void dibujar();
	void borrar();
	int getX() { return x; }
	int getY() { return y; }
	void eliminado();
	
};

//-------------------------------------------------------------------
//                                                          JUGADOR

class Jugador : public Caja{
private:
	int vidas = 5;
	int x, y;
	
public:
	
	Jugador();
	void aparecer();
	void mover();
	int getX() { return x; }
	int getY() { return y; }
	int getVidas() { return vidas; }
	void perderVida() { vidas--; }
	void dibujar();
	void borrar();
	
			
};

Jugador::Jugador(){
	
	//posición inicial del jugador
	x = (x1 + x2) / 2;  // Posición inicial del carácter en el centro horizontalmente
	y = (y1 + y2) / 2;  // Posición inicial del carácter en el centro verticalmente
	
	
}

void Jugador :: aparecer(){
	// Dibujar el carácter en la posición inicial
	gotoxy(x, y);
	//cout << "[ ]";
	
	
}

void Jugador :: dibujar(){
	gotoxy(x-1,y);
	cout << "[";
	gotoxy(x+1,y);
	cout<<"]";
	gotoxy(x,y);
	cout<<" ";
	gotoxy(x,y);
}

void Jugador :: borrar(){
	gotoxy(x-1,y);
	cout << " ";
	gotoxy(x+1,y);
	cout<<" ";
	gotoxy(x,y);
	cout<<" ";
}

void Jugador::mover(){

	if(getVidas()>0) {
		if (kbhit()) {  // Detecta si una tecla es presionada
			int tecla = getch();  // Captura la tecla presionada
			
			// Borrar el carácter actual
			//gotoxy(x, y);
			//cout << " ";
			//cout<<"  ";
			
			borrar();
			
			// Mover el caracter según la tecla presionada
			if ((tecla == 'a' || tecla == 'A') && x > x1 + 2) {  // Mover izquierda
				x--;
			} else if ((tecla == 'd' || tecla == 'D') && x < x2 - 2) {  // Mover derecha
				x++;
			} else if ((tecla == 'w' || tecla == 'W') && y > y1 + 1) {  // Mover arriba
				y--;
			} else if ((tecla == 's' || tecla == 'S') && y < y2 - 1) {  // Mover abajo
				y++;
			}
			
			// Dibujar el carácter en la nueva posición
			
			dibujar();
		}
	}
}

//----------------------------------------------------------------------------------------
//                                                                   ENEMIGO

class Enemigo : public Caja {
private:
	clock_t tempo;
	clock_t paso;
	int x, y;
	
	
public:
	int velocidad;
	int color;
	int sentido;
	Enemigo(int velocidad);
	void mover();
	int getX() { return x; }
	int getY() { return y; }
	void borrar();
	void start();
	void renacer();
	void dibujar();
	
};

Enemigo::Enemigo(int velocidad) {
	sentido=1;
	paso=CLOCKS_PER_SEC/velocidad;
	tempo=clock();
	color=(rand()%15+1);
	renacer();
	dibujar();
}

void Enemigo::dibujar(){
	gotoxy(x,y);
	cout<<"X";
}

void Enemigo::renacer(){
	if(sentido<0){
		x= x2 - 1;
		y=rand()%(y2-y1-1)+(y1+1);
	}else{
		x= x1 + 1;
		y=rand()%(y2-y1-1)+(y1+1);
	}
	 
	
	
}

void Enemigo::start(){
	if (tempo + paso < clock()) {
		borrar();
		mover();
		tempo = clock();
	}	
}


void Enemigo::borrar(){
	gotoxy(x,y);
	cout<<' ';
}

void Enemigo::mover(){
	if(sentido<0 && x<=x1+1){
		sentido=1;
		renacer();
		dibujar();
		
	}
	else if(sentido>0 && x>=x2-1){
		sentido=(-1);
		renacer();
		dibujar();
	}
	else{
		x+=sentido;
		gotoxy(x,y);
		textcolor(color);
		cout << "X";
		gotoxy(x,y);
	}
		
	
	
}


//----------------------------------------------------------------------------
//                                                                METEORITO

class Meteorito : public Caja {
private:
	clock_t tempo;
	clock_t paso;
	int x, y;
	
	
public:
	int velocidad;
	int color;
	Meteorito(int velocidad);
	void mover();
	int getX() { return x; }
	int getY() { return y; }
	void borrar();
	void start();
	void renacer();
	void dibujar();
	
};

Meteorito::Meteorito(int velocidad) {
	paso=CLOCKS_PER_SEC/velocidad;
	tempo=clock();
	color=WHITE;
	renacer();
	dibujar();
}

void Meteorito::dibujar(){
	gotoxy(x,y);
	cout<<"0";
}

void Meteorito::renacer(){
	y= y1 + 1;
	x=rand()%(x2-x1-1)+(x1+1); 
	
	
}

void Meteorito::start(){
	if (tempo + paso < clock()) {
		borrar();
		mover();
		tempo = clock();
	}	
}


void Meteorito::borrar(){
	gotoxy(x,y);
	cout<<' ';
}

void Meteorito::mover(){
	if(y>=y2-1){
		renacer();
		dibujar();
		
	}
	else{
		y++;
		gotoxy(x,y);
		textcolor(color);
		cout << "0";
		gotoxy(x,y);
	}
	
	
	
}


//----------------------------------------------------------------------------

//                                                                MAIN

int main(int argc, char *argv[]) {
	srand(time(NULL));
	
	
	
	Caja Caja1;
	Caja1.aparecer();
	
	Enemigo E1(15);
	Enemigo E2(22);
	Enemigo E3(19);
	Meteorito M1(10);
	
	Jugador J1;
	J1.aparecer();
	
	while(true){
		J1.mover();
		E1.start();
		E2.start();
		E3.start();
		M1.start();
	}
	
	return 0;
}

