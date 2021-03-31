reset
set term x11
set size square

set border linewidth 1.5
set pointsize 1.7

# стиль для тестовых данных с классом 1 (класс 0 отображается дефолтным стилем)
set style line 1 lc rgb '#008712' pt 7   # circle green

# стиль для весов
set style line 2 lc rgb '#fc0362' pt 9   # triangle red

unset key

set tics scale 0.1
set xtics 1
set ytics 1
set yrange[-2:2]
set xrange[-2:2]
set xlabel 'X_1' 
set ylabel 'X_2'

set grid
set macro

set style increment user

N = system("wc -l test.dat")
N = N

do for [i=0:(N-1)] {
    # номер итерации обучения
    LABEL = "i = " . i
    set obj 10 rect at -1.5,-1.5 size char strlen(LABEL), char 1 
    set obj 10 fillstyle empty border -1 front
    set label 10 at -1.5,-1.5 LABEL front center

    set object 1 circle front at 0.0,0.0 size 1.0 fillcolor rgb "black" lw 1

    plot 'test.dat' every 1:1:0:0:i:0 u 1:2:3 w p lc var, 'weights.dat' every :::i::i w p ls 2 
    pause 0.001
}
pause mouse