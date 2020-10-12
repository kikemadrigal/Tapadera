//
// Fusion-C
// My First Program in C
//

#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/newTypes.h"
#include "fusion-c/header/vdp_sprites.h"
#include "fusion-c/header/vdp_graph2.h"

#include <stdio.h>
// Para el memset
#include <string.h>
#include "player.h"



void leerArchivoPantalla1();
void leerArchivo(char *archivo);
void FT_SetName( FCB *p_fcb, const char *p_name );
void leerArchivo(char *archivo);
void deRamAVramPage0(void);
void deRamAVramPage1(void);
void deVramAVramEdificios(void);
void deVramAVramTodaLaPantalla(void);

void inicializar_player(struct TPlayer*);
void actualizar_personaje(struct TPlayer*);
void procesar_entrada();




FCB TFile; 
unsigned char buffer_pantalla[30720];
char file_name_pantalla_1[]="CITY.SC5";
int contador1=0;
int contador2=256;        

void main(void){
  
  SpriteReset();
  
  Screen(5);
  SetBorderColor(13);

  leerArchivoPantalla1();
  deRamAVramPage0();
  deRamAVramPage1();

  Sprite16();
 
  inicializar_player(&player);


  //Bucle render
  while(true){
    /**/
    __asm 
    halt
    __endasm;
    deVramAVramEdificios();
    //deVramAVramTodaLaPantalla();
    procesar_entrada();
    actualizar_personaje(&player);
  }

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

    //Le ponemos el color al sprite
    //SC5SpriteColors( 0, color_coche_derecha );	
    //SC5SpriteColors( 0, color_coche_izquierda );	
    // Mostramos nuestro esprite
    // 1. el plano o su definición en la tabla de atributos, ahí s e alamcenará la posición x e y
    // 2 la definición en sprite pattern qu eva de 4 en 4 bytes
    // 3 posición eje x, 4 posición eje y, 5 color
    //Ponemos el player
    PutSprite( 0, player->plano, player->x, player->y, 6 );
    
}
void actualizar_personaje(struct TPlayer *player){

    PutSprite( 0, player->plano, player->x,player->y, player->color );
}



//Sistema de input
void procesar_entrada(){
  //Screen(0);
	// 0 son cursores teclado
  // 0=inactive  1=up 2=up & right 3=right 4=down & right 5=down 6=down & left 7=left 8=up & left 
	int8 pm = JoystickRead(0);
    switch (pm)
    {
      case 1:
          player.y-=player.v;
          break;
      case 3:
          player.x+=player.v;
          player.plano=0;

          break;
      case 5:
          player.y+=player.v;
          break;
      case 7:
          player.x-=player.v;
          player.plano=1;
          break;
      default:
          break;
    }
}


/**********************************************************
* *******************MAPA**********************************
**********************************************************/

void leerArchivoPantalla1(){
    //Cargamos el archivo en la estructura
    FT_SetName( &TFile, &file_name_pantalla_1[0] );
    fcb_open( &TFile );
    //Sino omitimos los 7 primeros bytes (los que defininen la estructura del binario) aparecen  unas marcas arriba a la derecha
    fcb_read( &TFile, &buffer_pantalla[0], 7 ); 
    //Cargamos el archivo definido en la estructura y lo ponemos en la RAM (buffer)
    fcb_read( &TFile, &buffer_pantalla[0], 30720 );  
    fcb_close( &TFile );
}

void leerArchivo(char *archivo){
    FT_SetName( &TFile, archivo );
    fcb_open( &TFile );
    fcb_read( &TFile, &buffer_pantalla[0], 7 );  // Skip 7 first bytes of the file  
    fcb_read( &TFile, &buffer_pantalla[0], 30720 );  // Read 20 lines of image data (128bytes per line in screen5)
    fcb_close( &TFile );
}
void deRamAVramPage0(void){
  //Pasamos del a RAM (con un buffer) a la VRAM
  //HMMC(&buffer_pantalla[0], posicion x,posición y,longitux de la zona a copiar,la altura de la zona a copiar ); 
  HMMC(&buffer_pantalla[0], 0,0,256,212 ); 
}
void deRamAVramPage1(void){
  HMMC(&buffer_pantalla[0], 0,256,256,212 ); 
}

void deVramAVramEdificios(void){
  contador1+=1;
  contador2-=1;
  //if(contador=0) contador=256;
  //HMMM(posicion x,posicion y (si es mayor que 256 es la page 1),destina x,destino y,anchura copia,altura copia);
  HMMM(contador1,336,0,80,256,70);
  HMMM(0,336,contador2,80,256,70);
  if (contador1>255) contador1=0;
  if (contador2<0) contador2=256;
}
void deVramAVramTodaLaPantalla(void){
  contador1+=1;
  contador2-=1;
  //if(contador=0) contador=256;
  //HMMM(posicion x,posicion y (si es mayor que 256 es la page 1),destina x,destino y,anchura copia,altura copia);
  HMMM(contador1,256,0,0,256,212);
  HMMM(0,256,contador2,0,256,212);
  if (contador1>255) contador1=0;
  if (contador2<0) contador2=256;
}
/*
void modificarBufferParaEfectoScroll(void){
  for(int i=0; i<30720;i++){
    if(i>10240 && i <20480){
      buffer_pantalla[i]=buffer_pantalla[i+1];
    }
  }
  HMMC(&buffer_pantalla[0], 0,0,0,0);
}
*/






void FT_SetName( FCB *p_fcb, const char *p_name )  // Routine servant à vérifier le format du nom de fichier
{
  char i, j;
  memset( p_fcb, 0, sizeof(FCB) );
  for( i = 0; i < 11; i++ ) {
    p_fcb->name[i] = ' ';
  }
  for( i = 0; (i < 8) && (p_name[i] != 0) && (p_name[i] != '.'); i++ ) {
    p_fcb->name[i] =  p_name[i];
  }
  if( p_name[i] == '.' ) {
    i++;
    for( j = 0; (j < 3) && (p_name[i + j] != 0) && (p_name[i + j] != '.'); j++ ) {
      p_fcb->ext[j] =  p_name[i + j] ;
    }
  }
}