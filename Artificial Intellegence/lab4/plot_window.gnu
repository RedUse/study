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
set yrange[-3:4]
set xrange[-3:3]
set xlabel 'X_1' 
set ylabel 'X_2'

set grid
set macro

set style increment user

N = system("wc -l test.dat")
neurons = 13

do for [i=0:(N-1)] {
    # номер итерации обучения
    LABEL = "i = " . i
    set obj 10 rect at -1.5,-1.5 size char strlen(LABEL), char 1 
    set obj 10 fillstyle empty border -1 front
    set label 10 at -1.5,-1.5 LABEL front center
   

    plot 'weights.dat' every :::i::i w l ls 2, 'weights.dat' every :::i::i w p ls 2#, 'coordinates.dat' u 1:2 w p ls 1
    # do for [j=0:neurons] {
    #     Px = system("head -".(neurons*i+j)." weights.dat | tail -1 | awk '{print $1}'")
    #     Py = system("head -".(neurons*i+j)." weights.dat | tail -1 | awk '{print $2}'")
    #     LABEL = "".j
    #     #set obj 5 rect at Px,Py size char strlen(LABEL), char 1 
    #     #set obj 5 fillstyle empty border -1 front
    #     set label 5 at Px,Py LABEL front center
    # }

    pause 0.01
}
pause mouse
