Компиляция программы:
chmod +x compile.sh
./compile.sh
Запуск:
./a.out 2

(Вторым аргументом командной строки является количество нейронов (>0))

Визуализация результата работы (кругами обозначаются точки выборки, треугольниками - веса нейронов)
gnuplot -p plot_window.gnu 
(Запуск в окне gnuplot)

или же 
gnuplot plot_gif.gnu
(создание файла results.gif с зацикленной гиф анимацией)