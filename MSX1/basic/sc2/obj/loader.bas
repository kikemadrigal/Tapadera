1 'Vamos a trabajar con screen 2,2 (sprites de 16x16pixeles)'
80 screen 2,2:key off:open "grp:" for output as #1

1 'Inicializacion de las dimensiones de los arrays de nuestras entidades'
110 print #1,"Reservando espacio de arrays"
120 gosub 3000
1 'Inicializamos los gráficos'
130 print #1,"Cargando graficos"
140 'gosub 4000
1 'Cargamos el xbasic'
150 print #1,"Cargando xbasic"
160 bload"xbasic.bin",r
170 print #1,"Escribiendo main.bas en RAM"
1 'cargamos la pantalla de presentación'
180 cls:BLOAD"CITY.BIN",S
190 'print #1,"Cargando sprites"
1 'Inicializamos los sprites'
200 gosub 1000
1 'Cargamos el main'
210 load "game.bas",r
220 'goto 220



1 'Rutina cargar sprites con datas basic'
    1 'En screen 2 sería base(13)=6912-&h1b00-put sprite atributo,(x,y),color,definición_sprite$ para la tabla atributos sprites (ta=Tabla Atributos)
    1 'base(14)=14336-&h3800-sprite$(entero_numero) para tabla definición sprites (td=tabla Definición)'
    1 'Leer datas 
    1000 ta=base(13): td=base(14)
    1 'Vamos a cargar 6 sprites'
    1000 for I=0 to 5:a$=""
        1010 for J=1 to 32: read b$
            1020 a$=a$+chr$(VAL(b$))
            1025 'a$=a$+chr$(a)
            1 'Otra forma sería así pero abría que eliminar el sprite$(numero_sprite)'
            1030 'vpoke td, VAL("&H"+a$)
        1050 NEXT J
        1060 SPRITE$(I)=a$
    1070 NEXT I

    1 'REM Tapadera_sprites
    1 'coche derecha 1
    1120 DATA 0,0,0,0,0,0,0,255
    1130 DATA 136,136,143,136,136,255,112,48
    1140 DATA 0,0,0,0,0,0,0,128
    1150 DATA 64,96,252,2,2,254,54,48
    1 'coche derecha 2
    1160 DATA 0,0,0,0,0,0,0,0
    1170 DATA 127,104,104,111,111,127,0,0
    1180 DATA 0,0,0,0,0,0,0,0
    1190 DATA 128,64,96,252,252,240,0,0
    1 'coche izquierda 1
    1200 DATA 0,0,0,0,0,0,0,1
    1210 DATA 2,6,63,64,64,127,108,12
    1220 DATA 0,0,0,0,0,0,0,255
    1230 DATA 17,17,241,17,17,255,14,12
    1 'coche izquierda 2
    1240 DATA 0,0,0,0,0,0,0,0
    1250 DATA 1,2,6,63,63,15,0,0
    1260 DATA 0,0,0,0,0,0,0,0
    1270 DATA 254,22,22,246,246,254,0,0
    1 'Enemigo 1'
    1280 DATA 0,0,0,0,1,1,1,31
    1290 DATA 3,3,3,3,2,2,2,6
    1300 DATA 0,0,0,0,128,128,128,248
    1310 DATA 192,192,192,192,64,64,64,96
    1 'Enemigo 1'
    1320 DATA 0,0,0,0,5,5,5,7
    1330 DATA 3,3,3,3,2,2,2,6
    1340 DATA 0,0,0,0,160,160,160,224
    1350 DATA 192,192,192,192,64,64,64,96






1 'El color al sprite se lo mondremos más adelante con put sprite (aunque tambien sepuede escribir con vpoke)'
1990 return





1 'Rutina reservar espacio para arrays'
    1 'Definiendo el espacio para los arrays con los valores de los enemigos'
    3000 em=5
    1 ' Component position'
    3010 DIM ex(em),ey(em),ep(em),ei(em)
    1 'Definiendo el espacio para la colocación de los mapas'
    1 'Será 10 filas x 10 columnas por mw=mapa word=6 mundos para completar el juego'
    3020 'mw=6
    3030 'DIM mp(10,10,mw)
3040 return



1 'Rutina cargar gráficos, los gráficos se cargarán con datas basic
    1 'Screen 2 sería base(10)=6144-&h1800 tabla mapa, base(11)=8192-&h2000 tabla color tiles, base(12)=0 definición tiles'
    1 'Definicición de tiles, cada tile se degine con 8 bytes
    1 'La tabla de definicion de tiles va desde el registro 0 al 6148
    1 '1 trozo: 0-2047 (&h7ff),2 trozo 2047(&h800)-4095(&hfff), 3 trozo 4096(&h1000)-6147(&h17ff)'
    1 'cargamos el banco 0 de definición de tiles (el de abajo)'
    4000 for i=0 to 255*8:read a$
        4010 vpoke i, val(a$)
    4020 next I
     1 'cargamos el banco 1 de definición de tiles (el de enmedio)'
    4030 for i=2048 to 2048+(255*8):read a$
        4040 vpoke i, val(a$)
    4050 next I
    1 'cargamos el banco 2 de definición de tiles (el de arriba)'
    4060 for i=4096 to 4096+(255*8):read a$
        4070 vpoke i, val(a$)
    4080 next I

    1 'Cargamos los colores del banco 0'
    4090 for i=8192 to 8192+(255*8):read a$
        4100 vpoke i, val(a$)
    4110 next I
    1 'Cargamos los colores del banco 1'
    4120 for i=10240 to 10240+(255*8):read a$
        4130 vpoke i, val(a$)
    4140 next I
    1 'Cargamos los colores del banco 2'
    4150 for i=12288 to 12288+(255*8):read a$
        4160 vpoke i, val(a$)
    4170 next I

    1 'Cargamos la tabla de nombres para decirle que tile va en que posición'
    4180 cls:for i=6144 to 6144+768:read a$
        4190 vpoke i, val(a$)
    4200 next


30000 return