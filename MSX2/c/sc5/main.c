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
void deVramAVram(void);

void inicializar_player(struct TPlayer*);
void actualizar_personaje(struct TPlayer*);
void procesar_entrada(struct TPlayer*);



const struct TPlayer player ={100,160,16,16,8,100,6,0,0};
FCB TFile; 
unsigned char buffer_pantalla[30720];
char file_name_pantalla_1[]="CITY.SC5";
int contador=256;        

void main(void){
  
  SpriteReset();
  //SetColors(1, 1, 1);	
  Screen(0);
  printf("MSX Police");
  Screen(5);
  SetBorderColor(13);
  //SetDisplayPage (2);             // Page 2
  //SetActivePage(2);
  //Cls();
	//SetActivePage(0);
  //FT_LoadSc5Image("CITY.SC5",512,LDbuffer);       // On charge l'umage
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
    deVramAVram();
    procesar_entrada(&player);
    actualizar_personaje(&player);
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


void deRamAVramPage1(void){
    //Pasamos del a RAM (con un buffer) a la VRAM
    //HMMC(&buffer_pantalla[0], posicion x,posición y,longitux de la zona a copiar,la altura de la zona a copiar ); 
    HMMC(&buffer_pantalla[0], 0,213,256,212 ); 
}
void deRamAVramPage0(void){
    HMMC(&buffer_pantalla[0], 0,0,256,212 ); 
}
void deVramAVram(void){
  contador-=1;
  //if(contador=0) contador=256;
  //HMMM(posicion x,posicion y,destina x,destino y,anchura copia,altura copia);
  HMMM(0,290,contador,76,250,70);
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