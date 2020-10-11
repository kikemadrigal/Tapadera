10 rem Program: Tapadera
20 rem Autor: MSX Murcia 2020
30 rem Platform: MSX1, MSX2
40 rem language: MSX Basic



100 defint a-z: defusr1=&H41:defusr2=&H44:color 1,15,15
1 'Inicializar mapa, son 32 columnas y 24 filas'
140 gosub 20000
1 'Llamamos a la rutina guardar información en array'
150 'gosub 20200
1 'Llamamos a copiar la page 1 en la page 0'
160 gosub 20400
1 'Inicializamos el personaje'
170 gosub 10000
1 'inicilizamos los eneminos con el manager'
180 gosub 12000
1 'Creamos el 1 enemigo, la ev y la el es para que se mueva hacia arriba o hacia abajo'
190 gosub 12400:ex(1)=8*12:ey(1)=8*20:ev(1)=8:es(1)=4:ep(1)=4
200 'gosub 12400:ex(2)=8*18:ey(2)=8*16:ev(2)=8:es(2)=5:ep(2)=5
210 'gosub 12400:ex(3)=8*14:ey(3)=8*15:ev(3)=8:es(3)=3
1 'con el 0 le decimos que es la barra espaciadora y no los botones de los joystick'
220 strig(0) on

1 'Mostramos el HUD'
240 'gosub 9000



1 ' ----------------------'
1 '      MAIN LOOP
1 ' ----------------------'


1 'Movemos la pantalla'
500 gosub 21000
1 'Capturamos las teclas'
520 gosub 6200
1 'Comprobamos las colisiones'
530 gosub 8000
1 'Actaulizamos el render'
540 gosub 7000
1 'Mostrar infomacion'
550 'gosub 9000
560 goto 500








1 ' ----------------------'
1 '     INPUT SYSTEM'
1 ' ----------------------'
    1'1 Arriba, 2 arriba derecha, 3 derecha, 4 abajo derecha, 5 abajo, 6 abajo izquierda, 7 izquierda, 8 izquierda arriba
    6000 j=stick(0)
    6010 px=x:py=y
    6020 if j=3 then  x=x+pv:ps=0
    6030 if j=7 then  x=x-pv:ps=2
    6040 if j=1 then  y=y-pv
    6050 if j=5 then  y=y+pv
6100 return

1 '2 Sistema de input'
    6200 px=x:py=y 
    6210 on stick(0) gosub 6230,6200,6240,6200,6250,6200,6260
6220 return
1 '1'
6230 y=y-pv:return
1 '3'
6240  x=x+pv:ps=0:return
1 '5'
6250  y=y+pv:return
1 '7'
6260 x=x-pv:ps=2:return

1 ' ----------------------'
1 '     RENDER SYSTEM'
1 ' ----------------------'
    1 'Pintamos de nuevo el player con la posición, el color y el plano(dibujitos de izquierda, derecha..)'
    7000 gosub 10500
    1 'Dibujamos los enenmigos'
    7010 gosub 12600
7110 return



1 ' ----------------------'
1 '     COLLISION SYSTEM'
1 ' ----------------------'

    1 'Colision del playaer con la pantalla'
    8000 if y<192-(8*8) then y=py
    8070 if y>192-(8*3) then y=py
    8080 if x<0 then x=px
    8090 if x>256-16 then x=px
8100 return




1 ' ----------------------'
1 '     HUD'
1 ' ----------------------'
    9000 'preset (0,192-8):print #1,"Tapadera game, fre "fre(0)
    9010 preset (0,192-8):print #1,"mc:"mc", me: "me
9090 return





1 ' ----------------------'
1 '         PLAYER
1 ' ----------------------'
1 'inicialice player'
    10000 x=8*2:px=x:y=8*19:py=y: pw=16: ph=16: pd=3: pu=0: pv=8: pe=100: pc=0
    1 'variables para manejar los sprites, 
    1 'ps=payer sprite, lo cremaos con el spritedevtools 
    1 'pp=player plano; para cambiarlo en el plano osprite paraq ue de la sención de movimento
    10010 ps=0: pp=0
    10020 'put sprite 1,(-10,-10),6,0
10030 return

1 'Update player'
    10500 put sprite pp,(x,y),6,ps
    10510 put sprite pp+1,(x,y),4,ps+1
10520 return


1 ' ----------------------'
1 '         Enemies
1 ' ----------------------'
1 'Definiendo la extructura de los enemigos'
1 'em=numero maximo de enemigos'
1 'et=turno de enemigo'
1 'en=numero de enemigo'
1 'Componente de posicion'
    1 'ex=coordenada x, ey=coordenada y', ep=coordenada previa x, ei=coordenada previa y
1 'Componente de fisica'
    1 'ev=velocidad enemigo eje x, el=velocidad eje y'
1 'Componente de render'
    1 'ew=ancho enemigo, eh= alto enemigo, es=enemigo sprite'
1 'Componente RPG'
    1 'ee=enemigo energia '

1 'Definiendo el espacio para los arrays con los valores de los enemigos'
    1 'creamos el espacio en la memoria para 3 enemigos'
    1 'Con em le decimos el espacio con en el enemigo actual que será actualizado o dibujado'
    1 'Para saber lo que es cada variable ir a la inicialización del enemigo'   
    1 'em=enemigos maximos'
    12000 em=5
    1 'Component position'
    12010 DIM ex(em),ey(em)
    1 'Compenent phisics'
    12020 DIM ev(em),el(em)
    1 'Component render'
    12030 DIM ew(em),eh(em),es(em),ep(em)
    1 'Component RPG'
    12040 DIM ee(em)
12050 return

1 'Init'
1 'con en=1 (enemigo número)le decimos que queremos trabajar con el enemigo 1
1 'Pero vamos a rellenar la entidad 0 para que despues podamos copiar sus valores en la 1 y las demás que creemos'
1 'Después de estudiar la subrrutina 6000 y 6100 mira la línea 140'
    12200 en=1
    12210 ex(0)=0:ey(0)=0
    12220 ev(0)=0:el(0)=0
    12230 ew(0)=16:eh(0)=16:es(0)=0:ep(0)=0
    12240 ee(0)=100
12250 return

1 ' Crear enemigo'
    1 'Como el espacio en la memoria lo creamos en el loader, ahora rellenamos, 
    1 'el dibujado lo hacemos en el render '
    1 'Aqui le asignamos el sprite que será el definido en el lodaer '
    1 'En lugar de ponerles valores le copiamos los valores de la entidad creada en el init'
    1 'la siguiente vez que llamemos a crear enemigo se creará en la siguiente posición del array'
    12400 ex(en)=ex(0):ey(en)=ey(0)
    12410 ev(en)=ev(0):el(en)=el(0)
    12420 ew(en)=ew(0):eh(en)=eh(0):es(en)=es(0):ep(en)=ep(0)
    12430 ee(en)=ee(0)
    1 'Al sumarle un enemigo cuando volvamos a llamar a esta subrrutina
    1 'Creará el enemigo en la siguiente posición, pero antes fíjate en las dimensiones 
    1 'Que le reservaste en el loader.bas'
    12440 en=en+1
12450 return

1 'update enemies
    1 'dibujamos los enemigos, sin el for ser ve más claro'
    12600 for i=1 to en-1
        1 'Esto es para animar los muñegotes'
        12610 es(i)=es(i)+1:ex(i)=ex(i)-1
        12620 if es(i)>4 and i=1 then es(i)=4
        12630 'if es(i)>1 and i=2 then es(i)=4
        12640 'if es(i)>2 and i=3 then es(i)=6
        12650 'if es(i)>2 and i=4 then es(i)=6
        1 'Nuestros enemigos son el sprite 2 en adelante'
        12660 PUT SPRITE ep(i),(ex(i),ey(i)),1,es(i)
    12670 next i
12680 return


1 ' ----------------------'
1 '         MAP'
1 ' ----------------------'
    20000 dim m(32,24): md=6144:mc=256:me=0
20010 return

1 'Guardamos la información de la tabla de mapa en un array
    20200 'for f=0 to 25
        20230 'for c=0 to 31
            20240 'print #1,vpeek (md);
            20250 'm(c,f)=vpeek(md):md=md+1
        20260 'next c
    20270 'next f
20280 return

1 'Rutina copiar mapa de la page 1 a la 0'
    20400 copy (0,0)-(255,212),1 to (0,0),0
20490 return

1 'Register 20h / 32: Source X Low byte (0-FF)
1 'Register 21h: Source X High byte (0-1)
1 'Register 22h: Source Y Low byte (0-FF)
1 'Register 23h: Source Y High byte (0-3)
1 'Register 24h: Destination X Low byte (0-FF)
1 'Register 25h: Destination X High byte (0-1)
1 'Register 26h: Destination Y Low byte (0-FF)
1 'Register 27h: Destination Y High byte (0-3)
1 'Register 28h: Number of X dots low byte (0-FF)
1 'Register 29h: Number of X dots high byte (0-3)
1 'Register 2Ah: Number of Y dots low byte (0-FF)
1 'Register 2Bh / 43: Number of Y dots high byte (0-3)




1 '32 tiles de ancho por la fila a partir de la cual quiero moverlos'
1 'Rutina dibujar array, 6144+(32*20)=6784, 6144+(32*23)=6880'
    21000 _TURBO on(mc,me)
    21010 mc=mc-1
    21020 me=me+1
    1 'Copiamos otro trozo movible de la page 1 y lo pegamos encima de la imagen de la page o par dar sensación de movimiento'
    21030 copy (me,8*9)-(8*32,8*19),1 to (0,8*9),0
    1 'Copiamos de nuevo la imagen de la page 1'
    21040 copy (0,8*9)-((8*32),(8*19)),1 to (mc,8*9),0
    21050 if mc=0 then mc=256
    21060 if me>=256 then me=0
    21070 _TURBO off
21100 return





