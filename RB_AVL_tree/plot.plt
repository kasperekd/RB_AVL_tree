#!/usr/bin/gnuplot
set termoption enhanced
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1
set border lw 2
set grid
set key top left
set xlabel "Number of elements in the array"
set ylabel "Execution time, s" rotate by 90
set xtics 50000
set mxtics 
set format x "%6.0f"
set format y "%.8f"
plot "lookup.txt" using 1:2 title "rbtree_lookup" with linespoints ls 1
