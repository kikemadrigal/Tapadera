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
// Para el memset
#include <string.h>
#include "player.h"
#include "tiles.h"



void inicializar_player(struct TPlayer*);
void actualizar_personaje(struct TPlayer*);
void procesar_entrada(struct TPlayer*);

int FT_LoadSc5Image(char *file_name, unsigned int start_Y, char *buffer);
void FT_SetName( FCB *p_fcb, const char *p_name );

const struct TPlayer player ={100,160,16,16,8,100,6,0,0};
// Inicializando la estructura del sistema de archivos que está en fusion-c/header/msx_fusion.h
static FCB file;            
// Creación de un búfer de 2560 bytes (20 líneas en Sc5)               
unsigned char LDbuffer[2560];               

void main(void){
  
  SpriteReset();
  //SetColors(1, 1, 1);	
  Screen(0);
  printf("MSX Police");
  Screen(5);
  SetDisplayPage (2);             // Page 2
  SetActivePage(2);
  Cls();
	SetActivePage(0);
  FT_LoadSc5Image("CITY.SC5",512,LDbuffer);       // On charge l'umage


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


/*void leerTablaNombres2Dimensiones(void){
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
}*/
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
 


int FT_LoadSc5Image(char *file_name, unsigned int start_Y, char *buffer)        // Charge les données d'un fichiers
    {

        int rd=2560;
        FT_SetName( &file, file_name );
        if(fcb_open( &file ) != FCB_SUCCESS) 
        {
              //FT_errorHandler(1, file_name);
              return (0);
        }

        fcb_read( &file, buffer, 7 );  // Skip 7 first bytes of the file  
        while (rd!=0)
        {
             rd = fcb_read( &file, buffer, 2560 );  // Read 20 lines of image data (128bytes per line in screen5)
             HMMC(buffer, 0,start_Y,256,20 ); // Move the buffer to VRAM. 
             start_Y=start_Y+20;
         }

return(1);
}