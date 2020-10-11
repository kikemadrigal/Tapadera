//
// Fusion-C
// My First Program in C
//

#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/newTypes.h"
#include "fusion-c/header/vdp_sprites.h"
#include "fusion-c/header/vdp_graph2.h"
#include "fusion-c/header/psg.h"
#include "fusion-c/header/io.h"
#include <stdio.h>
#include "player.h"
#include "tiles.h"

#define dirBaseTablaPatrones 	0x0000
#define dirBaseTablaNombres		0x1800
#define dirBaseTablaColor 		0x2000
#define TAM_TablaPatrones 		6144
#define TAM_TablaColor			6144
#define TAM_TablaNombres		768
#define Cabecera_Fichero		8
/*unsigned char tablaPatrones[TAM_TablaPatrones];
unsigned char tablaColor[TAM_TablaColor];
unsigned char tablaNombres[TAM_TablaNombres];*/
unsigned char tablaNombres2D[31][23];

void crearSC2 (char *filename);
void inicializar_player(struct TPlayer*);
void actualizar_personaje(struct TPlayer*);
void procesar_entrada(struct TPlayer*);
void loadSC2 (char *filename);
void mostrarSC2 (void);
void moverPantalla(void);

const struct TPlayer player ={100,160,16,16,8,100,6,0,0};
unsigned int fila=0;
unsigned int columna=0;
unsigned int contador=0;
void main(void){
  
  SpriteReset();
  //SetColors(1, 1, 1);	
  Screen(2);
  PutText(0,10,"leyendo..",0);
  //crearSC2("tiles.sc2");
  //Carga de la pantalla en el array
	loadSC2("tiles.sc2");
  mostrarSC2();

	
  //PutText(0,10,"Screen 2",0);
  Sprite16();
  inicializar_player(&player);


  //Bucle render
  while(true){
    /**/
    __asm 
    halt
    __endasm;

    procesar_entrada(&player);
    actualizar_personaje(&player);
    moverPantalla();
  }

}
 
void inicializar_player(struct TPlayer *player ){
    // px= player posición eje x, py= player posición eje y
    // pv player velocidad, pm= player movimiento (se obtiene del teclado)
    //px=100; py=192-32; pv=5; pm=0;
    // lo metemos en la tabla de dEfinición de patrones
    // el 1 argumento es la posición en la poisión en la tabla de definición de sprites (sprite pattern)
    // el 2 argumentos son los datos del sprite
    // el 3 argumento es el numero del línea del patron

    SetSpritePattern( 0, coche_derecha, 32);
    SetSpritePattern( 4, coche_izquierda, 32);

    // Mostramos nuestro esprite
    // 1. el plano o su definición en la tabla de atributos, ahí s e alamcenará la posición x e y
    // 2 la definición en sprite pattern qu eva de 4 en 4 bytes
    // 3 posición eje x, 4 posición eje y, 5 color
    //Ponemos el player
    PutSprite( 0, player->plano, player->x, player->y, player->color );
    
}
void actualizar_personaje(struct TPlayer *player){

    PutSprite( 0, player->plano, player->x,player->y, player->color );
}



//Sistema de input
void procesar_entrada(struct TPlayer *player){
  //Screen(0);
	// 0 son cursores teclado
  // 0=inactive  1=up 2=up & right 3=right 4=down & right 5=down 6=down & left 7=left 8=up & left 
	int8 pm = JoystickRead(0);
    switch (pm)
    {
      case 1:
          player->y-=player->v;
          break;
      case 3:
          player->x+=player->v;
          player->plano=0;

          break;
      case 5:
          player->y+=player->v;
          break;
      case 7:
          player->x-=player->v;
          player->plano=1;
          break;
      default:
          break;
    }
}


void crearSC2 (char *filename) {
	int file;

	printf("\n\rCreando fichero %s.\n\r", filename);
	Create (filename);
	file=Open(filename, O_WRONLY);
	Write(file, tablaPatrones, TAM_TablaPatrones);
	Write(file, tablaNombres, TAM_TablaNombres);
	Write(file, tablaColor, TAM_TablaColor);
	Close(file);
}

void loadSC2 (char *filename) {
	int file;	// Set a file handler variable
  //Open: Abre un archive y devuelve un entero con valor del manejador del archivo o -1 si da error
	file=Open(filename, O_RDONLY);
	// Read lee nbytes (TAM_TablaPatrones) desde el archivo definido por el entero FileHandler (file) al *buffer tablaPatrones
	Read(file, tablaPatrones, TAM_TablaPatrones);
	// Leyendo la tabla de nombres
	Read(file, tablaNombres, TAM_TablaNombres);
	// Leyendo la tabla de colores
	Read(file, tablaColor, TAM_TablaColor);
	Close(file);
}

void mostrarSC2 (void) {
	HideDisplay();
	// Tablas patrones, nombre (mapa) y color
	CopyRamToVram (&tablaPatrones[0], dirBaseTablaPatrones, TAM_TablaPatrones);
	CopyRamToVram (&tablaNombres[0], dirBaseTablaNombres, TAM_TablaNombres);
	CopyRamToVram (&tablaColor[0], dirBaseTablaColor, TAM_TablaColor);	
	ShowDisplay();
}

void moverPantalla(void){
  contador+=20;
  //if (contador>255) contador=0; 
  SetScrollH(contador);
}

