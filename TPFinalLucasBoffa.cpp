#include <iostream>
#include <conio2.h>
#include <cstdlib>
#include <ctime>
using namespace std;


//-----------------------------------------------------------------------------------
//                                                                    PANTALLA


class Pantalla {
protected:
	//bordes del recuadro
	int x1 = 5, y1 = 5, x2 = 35, y2 = 18;
	string mensajes[10] = {
		"NICE SHOOT",
		"GOOD ONE",
		"GREAT SHOOT!",
		"NICE HIT!",
		"FANTASTIC AIM!",
		"DIRECT HIT!",
		"WELL DONE!",
		"BOOOM!",
		"NICE ONE",
		"AGREEESIVE!"	
			
	};
	
	
public:
	Pantalla();
	virtual void start();
	void dibujarBordes();
	void verDatos();
	void mostrarMensaje();
	int getx2();
};

Pantalla::Pantalla (){
	
}

void Pantalla :: start(){
	
	textcolor(BLUE);
	cout<<"Teclas Movimiento: ASDW"<<endl;
	cout<<" Disparar: SAPACEBAR"<<endl;
	cout<<" Debes disparar a las X, cuidado con los asteroides!"<<endl;
	
	
}

void Pantalla::dibujarBordes(){
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




void Pantalla::mostrarMensaje(){
	int numero=rand()%9;
	gotoxy(x1+3,y2+3);
	cout << "                             "; 
	gotoxy(x1+3,y2+3);
	textcolor(RED);
	cout<<mensajes[numero];
	
	
}

int Pantalla::getx2(){
	return x2;
}

//-------------------------------------------------------------------
//                                                          JUGADOR

class Jugador : public Pantalla{
protected:
	int x, y;
	bool disparando = false;
public:
	
	Jugador();
	void start();
	void mover();
	int getX() { return x; }
	int getY() { return y; }
	
	void dibujar();
	void borrar();
	void setDisparo(bool valor);
	bool getDisparando();
	void disparar();
	void nacer();
	
};

Jugador::Jugador(){
	
	//posición inicial del jugador
	x = (x1 + x2) / 2;  // Posición inicial del carácter en el centro horizontalmente
	y = (y1 + y2) / 2;  // Posición inicial del carácter en el centro verticalmente
	
	
}

void Jugador::nacer(){
	x = (x1 + x2) / 2; 
	y = (y1 + y2) / 2;
	start();
	
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
	
	if (kbhit()) {  // Detecta si una tecla es presionada
		int tecla = getch();  // Captura la tecla presionada
		
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
		} else if(tecla==32){
			disparar();
		}
		
		// Dibujar el carácter en la nueva posición
		
		dibujar();
	}
	
}

void Jugador::setDisparo(bool valor){
	disparando = valor;
}

bool Jugador::getDisparando(){
	return disparando;
}

void Jugador::disparar(){
	setDisparo(true);
}
//-------------------------------------------------------------------
//                                                          ENEMIGO

class Enemigo : public Pantalla{
protected:
	clock_t tempo;
	clock_t paso;
	int x, y;
	int velocidad;
	char caracter;
	int color;
	bool isAlien=true;
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
	bool getAlien();
	void setAlien(bool valor);
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

bool Enemigo::getAlien(){
	return isAlien;
}

void Enemigo::setAlien(bool valor){
	isAlien=valor;
}


//----------------------------------------------------------------------------------------
//                                                                   ALIEN

class Alien : public Enemigo {
private:
	char caracter='X';
	
public:
	int velocidad;
	int sentido=1;
	Alien(int vel, int col);
	void mover();
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
	void nacer();
	
};

Meteorito::Meteorito(int vel, int col):Enemigo(vel, col) {
	setAlien(false);
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

//------------------------------------------------------------------------------------
//                                                               JUEGO
class Juego{
	Pantalla* P1;
	Jugador* J1;
	Alien* A1;
	Alien* A2;
	Alien* A3;
	Meteorito* M1;
	int vidas=5;
	int puntos=0;
	
	
public:
	Juego();
	void Loop();
	bool hayColision(Jugador* player, Enemigo* enemy);
	void actualizar();
	void iniciar();
	void verDatos();
	void reiniciar();
};

Juego::Juego() {
	P1 = new Pantalla();
	J1 = new Jugador();
	A1 = new Alien(15, 2);
	A2 = new Alien(19, 3);
	A3 = new Alien(22, 4);
	M1 = new Meteorito(10, 15); 
}

void Juego :: Loop(){
	clrscr();  // Limpia la pantalla al inicio
	P1->start();
	while (vidas>0) {
		verDatos();
		textcolor(WHITE);
		P1->dibujarBordes();
		A1->start();
		A2->start();
		A3->start();
		J1->start();
		J1->mover();
		M1->start();
		actualizar();
		
	}
}

bool Juego::hayColision(Jugador* player, Enemigo* enemy) {
	if(enemy->getAlien()){
		//el contacto con el alien es proximo en coordenadas x
		return (abs(player->getX() - enemy->getX()) <= 1) && (player->getY() == enemy->getY());
	}else{
		//el contacto con meteorito es proximo en x o en y
		return (abs(player->getX() - enemy->getX()) <= 1 && abs(player->getY() - enemy->getY()) <= 1);
	}
	
}   

void Juego::verDatos() {
	textcolor(BLUE);
	int margen = P1->getx2()+5;
	
	gotoxy(margen+5, 8);
	cout << "                        ";  // Limpia la línea completa
	gotoxy(margen, 8);
	cout << "Puntos: " << puntos;
	
	gotoxy(margen, 10);
	cout << "                        ";  // Limpia la línea completa
	gotoxy(margen, 10);
	cout << "Vidas: ";
	
	// Dibujar los asteriscos según el número de vidas
	for (int i = 0; i < vidas; i++) {
		cout << "* ";
	}
	cout<<"("<<vidas<<")";
}

void Juego::actualizar(){
	
	
	if(hayColision(J1, M1)){
		M1->borrar();
		J1->borrar();
		M1->nacer();
		vidas--;
		J1->nacer();
		for(int i=0;i<25;i++){
			textcolor(BLUE);
			P1->dibujarBordes();
			textcolor(YELLOW);
			P1->dibujarBordes();
		}
	}
	else if(J1->getDisparando()){
		if(hayColision(J1, A1)){
			A1->nacer();
			puntos+=10;
			P1->mostrarMensaje();
		}else if(hayColision(J1, A2)){
			A2->nacer();
			puntos+=15;
			P1->mostrarMensaje();
		}else if(hayColision(J1, A3)){
			A3->nacer();
			puntos+=20;
			P1->mostrarMensaje();
		}
		J1->setDisparo(false);	
	}
	
}

void Juego::reiniciar(){
	vidas=5;
	puntos=0;
}

void Juego::iniciar(){
	clrscr();
	gotoxy(9,9);
	textcolor(YELLOW);
	cout<<"BIENVENIDO A SHOOTER ESPACIAL!!";
	gotoxy(9,10);
	cout<<"Dispara a los aliens que cruzan";
	gotoxy(9,11);
	cout<<"la pantalla horizontalmente,";
	gotoxy(9,12);
	cout<<"los más veloces dan más puntos,";
	gotoxy(9,13);
	cout<<"pero cuidado con los meteoritos ";
	gotoxy(9,14);
	cout<<"que caen desde el cielo..."<<endl;
	gotoxy(9,15);
	
	gotoxy(9,18);
	cout<<"PRESIONA TECLA 'J' PARA COMENZAR, O 'P' PARA SALIR";
	int jugar;
	do{
		if(kbhit()){
			jugar=getch();
			
			if(jugar == 'J' || jugar == 'j'){
				do{
					reiniciar();
					Loop();
					clrscr();
					textcolor(YELLOW);
					gotoxy(8,9);
					cout<<"GAME OVER";
					gotoxy(9,9);
					cout<<"PERDISTE TODAS TUS VIDAS!!";
					gotoxy(9,10);
					textcolor(YELLOW);
					cout<<"presiona 'J' para volver a intentar o 'P' para salir ";
					jugar=getch();
				}while(jugar=='J'||jugar=='j');
			}
			if(jugar=='P' || jugar=='p')
			   break;
		}	
	} while(jugar!='P' || jugar!='p');
	
	
}

//----------------------------------------------------------------------------
//                                                                MAIN

int main(int argc, char *argv[]) {
	srand(time(NULL));
	
	Juego game;
	game.iniciar();
	
	return 0;
}
