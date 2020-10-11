10 rem Program: Tapadera
20 rem Autor: MSX Murcia 2020
30 rem Platform: MSX1, MSX2
40 rem language: MSX Basic
100 defint a-z: defusr1=&H41:defusr2=&H44:color 1,15,15
140 gosub 20000
150 'gosub 20200
160 gosub 20400
170 gosub 10000
180 gosub 12000
190 gosub 12400:ex(1)=8*12:ey(1)=8*20:ev(1)=8:es(1)=4:ep(1)=4
200 'gosub 12400:ex(2)=8*18:ey(2)=8*16:ev(2)=8:es(2)=5:ep(2)=5
210 'gosub 12400:ex(3)=8*14:ey(3)=8*15:ev(3)=8:es(3)=3
220 strig(0) on
240 'gosub 9000
500 gosub 21000
520 gosub 6200
530 gosub 8000
540 gosub 7000
550 'gosub 9000
560 goto 500
    6000 j=stick(0)
    6010 px=x:py=y
    6020 if j=3 then  x=x+pv:ps=0
    6030 if j=7 then  x=x-pv:ps=2
    6040 if j=1 then  y=y-pv
    6050 if j=5 then  y=y+pv
6100 return
    6200 px=x:py=y 
    6210 on stick(0) gosub 6230,6200,6240,6200,6250,6200,6260
6220 return
6230 y=y-pv:return
6240  x=x+pv:ps=0:return
6250  y=y+pv:return
6260 x=x-pv:ps=2:return
    7000 gosub 10500
    7010 gosub 12600
7110 return
    8000 if y<192-(8*8) then y=py
    8070 if y>192-(8*3) then y=py
    8080 if x<0 then x=px
    8090 if x>256-16 then x=px
8100 return
    9000 'preset (0,192-8):print #1,"Tapadera game, fre "fre(0)
    9010 preset (0,192-8):print #1,"mc:"mc", me: "me
9090 return
    10000 x=8*2:px=x:y=8*19:py=y: pw=16: ph=16: pd=3: pu=0: pv=8: pe=100: pc=0
    10010 ps=0: pp=0
    10020 'put sprite 1,(-10,-10),6,0
10030 return
    10500 put sprite pp,(x,y),6,ps
    10510 put sprite pp+1,(x,y),4,ps+1
10520 return
    12000 em=5
    12010 DIM ex(em),ey(em)
    12020 DIM ev(em),el(em)
    12030 DIM ew(em),eh(em),es(em),ep(em)
    12040 DIM ee(em)
12050 return
    12200 en=1
    12210 ex(0)=0:ey(0)=0
    12220 ev(0)=0:el(0)=0
    12230 ew(0)=16:eh(0)=16:es(0)=0:ep(0)=0
    12240 ee(0)=100
12250 return
    12400 ex(en)=ex(0):ey(en)=ey(0)
    12410 ev(en)=ev(0):el(en)=el(0)
    12420 ew(en)=ew(0):eh(en)=eh(0):es(en)=es(0):ep(en)=ep(0)
    12430 ee(en)=ee(0)
    12440 en=en+1
12450 return
    12600 for i=1 to en-1
        12610 es(i)=es(i)+1:ex(i)=ex(i)-1
        12620 if es(i)>4 and i=1 then es(i)=4
        12630 'if es(i)>1 and i=2 then es(i)=4
        12640 'if es(i)>2 and i=3 then es(i)=6
        12650 'if es(i)>2 and i=4 then es(i)=6
        12660 PUT SPRITE ep(i),(ex(i),ey(i)),1,es(i)
    12670 next i
12680 return
    20000 dim m(32,24): md=6144:mc=256:me=0
20010 return
    20200 'for f=0 to 25
        20230 'for c=0 to 31
            20240 'print #1,vpeek (md);
            20250 'm(c,f)=vpeek(md):md=md+1
        20260 'next c
    20270 'next f
20280 return
    20400 copy (0,0)-(255,212),1 to (0,0),0
20490 return
    21000 _TURBO on(mc,me)
    21010 mc=mc-1
    21020 me=me-1
    21030 'copy (0,8*9)-(8*32,8*19),0 to (mc,8*9),0
    21040 copy (0,8*9)-((8*32),(8*19)),1 to (mc,8*9),0
    21050 if mc=0 then mc=256
    21060 if me>=256 then me=0
    21070 _TURBO off
21100 return
