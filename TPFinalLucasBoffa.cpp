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
	virtual void start();
			
};

Caja::Caja (){
	
}

void Caja :: start(){
	
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
//                                                          JUGADOR

class Jugador : public Caja{
private:
	int vidas = 5;
	int x, y;
	
public:
	
	Jugador();
	void start();
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

void Jugador :: start(){
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
//-------------------------------------------------------------------
//                                                          ENEMIGO

class Enemigo : public Caja{
protected:
	clock_t tempo;
	clock_t paso;
	int x, y;
	int velocidad;
	char caracter;
	int color;
public:
	
	Enemigo(int vel, int col);
	Enemigo (int vel);
	virtual ~Enemigo() = default;  // Agregar destructor virtual
	virtual void nacer();
	virtual void mover();
	virtual void dibujar(char caracter);
	void start();
	void borrar();
	int getX() { return x; }
	int getY() { return y; }
	
};

Enemigo :: Enemigo(int vel, int col){
	velocidad=vel;
	color=col;
	paso=CLOCKS_PER_SEC/velocidad;
	tempo=clock();
	color=col;
	nacer();
	dibujar(caracter);
}

Enemigo :: Enemigo(int vel){
	velocidad=vel;
}

void Enemigo::dibujar(char caracter){
	gotoxy(x,y);
	cout<<caracter;
}

void Enemigo::borrar(){
	gotoxy(x,y);
	cout<<' ';
}

void Enemigo::start(){
	if (tempo + paso < clock()) {
		borrar();
		mover();
		tempo = clock();
	}	
}

void Enemigo::mover(){
	
}
void Enemigo::nacer(){
	
}


//----------------------------------------------------------------------------------------
//                                                                   ALIEN

class Alien : public Enemigo {
private:
//	clock_t tempo;
//	clock_t paso;
	//int x, y;
	char caracter='X';
	
public:
	int velocidad;
	int sentido=1;
	Alien(int vel, int col);
	void mover();
	int getX() { return x; }
	int getY() { return y; }
	void nacer();
	
};

Alien::Alien(int vel, int col) : Enemigo(vel, col) {
	nacer();
}


void Alien::nacer(){
	if(sentido<0){
		x= x2 - 1;
		y=rand()%(y2-y1-1)+(y1+1);
	}else{
		x= x1 + 1;
		y=rand()%(y2-y1-1)+(y1+1);
	}	 	
	
}


void Alien::mover(){
	if(sentido<0 && x<=x1+1){
		sentido=1;
		nacer();
		Enemigo::dibujar(caracter);
		
	}
	else if(sentido>0 && x>=x2-1){
		sentido=(-1);
		nacer();
		Enemigo::dibujar(caracter);
	}
	else{
		x+=sentido;
		gotoxy(x,y);
		textcolor(color);
		Enemigo::dibujar(caracter);
		gotoxy(x,y);
	}			
	
}


//----------------------------------------------------------------------------
//                                                                METEORITO

class Meteorito : public Enemigo {
private:
	char caracter='0';
	
	
public:
	int vel;
	Meteorito(int velocidad, int color);
	void mover();
	int getX() { return x; }
	int getY() { return y; }
	void nacer();
	
};

Meteorito::Meteorito(int vel, int col):Enemigo(vel, col) {
	nacer();
}


void Meteorito::nacer(){
	y= y1 + 1;
	x=rand()%(x2-x1-1)+(x1+1); 
	
	
}


void Meteorito::mover(){
	if(y>=y2-1){
		nacer();
		Enemigo::dibujar(caracter);
		
	}
	else{
		y++;
		gotoxy(x,y);
		textcolor(color);
		Enemigo::dibujar(caracter);
		gotoxy(x,y);
	}		
	
}


//----------------------------------------------------------------------------
//                                                                MAIN

int main(int argc, char *argv[]) {
	srand(time(NULL));
	
	
	
	Caja Caja1;
	Caja1.start();
	
	Alien E1(15, 2);
	Alien E2(22, 3);
	Alien E3(19, 4);
	Meteorito M1(10, 15);
	
	Jugador J1;
	J1.start();
	
	while(true){
		J1.mover();
		E1.start();
		E2.start();
		E3.start();
		M1.start();
	}
	
	return 0;
}

