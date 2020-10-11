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


#define dirBaseTablaPatrones 	0x0000
#define dirBaseTablaNombres		0x1800
#define dirBaseTablaColor 		0x2000
#define TAM_TablaPatrones 		6144
#define TAM_TablaColor			6144
#define TAM_TablaNombres		768
#define Cabecera_Fichero		8
unsigned char tablaPatrones[TAM_TablaPatrones];
unsigned char tablaColor[TAM_TablaColor];
unsigned char tablaNombres[TAM_TablaNombres];
unsigned char tablaNombres2D[31][23];

void leerTablaNombres2Dimensiones(void);
void cambiarTablaNombres2DYtablaNombres(void);

void inicializar_player(struct TPlayer*);
void actualizar_personaje(struct TPlayer*);
void procesar_entrada(struct TPlayer*);
void loadSC2 (char *filename);
void mostrarSC2 (void);
void leerTablaNombres2Dimensiones(void);
//void cambiarTablaNombres2DYtablaNombres(void);
//px=100; py=192-32; pv=5; pm=0;
struct TPlayer player ={100,160,16,16,8,100,6,0,0};

void main(void){
  
  SpriteReset();
  //SetColors(1, 1, 1);	
  Screen(2);
  PutText(0,10,"leyendo..",0);
  //Carga y visualización de la pantalla de carga
	loadSC2("tiles.sc2");
  Cls();
  //leerTablaNombres2Dimensiones();
  mostrarSC2();
  PutText(0,10,"Screen 2",0);
  Sprite16();
  inicializar_player(&player);


  //Bucle render
  while(true){
    Halt();
    procesar_entrada(&player);
    actualizar_personaje(&player);
    cambiarTablaNombres2DYtablaNombres();
  }
  Exit(0);
}
 
void inicializar_player(struct TPlayer *player){
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




void leerTablaNombres2Dimensiones(void){
  unsigned int fila=0;
  unsigned int columna=0;
  char valor[4];
  //valor=Itoa(tablaNombres[0],valor,10);
  for (int i=0 ; i<TAM_TablaNombres;i++){
    //PutText((columna*32),(fila*8),Itoa(tablaNombres[i],valor,10) ,0);
    tablaNombres2D[columna][fila]=tablaNombres[i];
    columna++;
    if(i % 31==0){
      columna=0;
      fila++;
    }
  }
}

void cambiarTablaNombres2DYtablaNombres(void){
  char valor[4];
  unsigned i=0;
  for(int fila=0; fila < 24; fila++){
    //PutText(0,fila*8,Itoa(fila,valor,10),0);
    for (int columna=0;columna<32; columna++){
        //PutText((columna*32),(fila*8),Itoa(tablaNombres2D[columna][fila],valor,10) ,0);
        tablaNombres2D[columna][fila]=tablaNombres2D[columna+1][fila];
        if (columna=31) {
          tablaNombres2D[columna][fila]=tablaNombres2D[1][fila];
        }
        tablaNombres[i]=tablaNombres2D[columna][fila];
        i++;
    }
  }
  CopyRamToVram (&tablaNombres[0], dirBaseTablaNombres, TAM_TablaNombres);
}