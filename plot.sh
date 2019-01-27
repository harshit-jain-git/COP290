gnuplot
set terminal png truecolor
set output "plot.png"
set grid
set style data histograms
set style fill solid 1.00 border -1
plot "performance.txt"  using 1:2:3 title "pthread" with errorbars, '' using 1:4:5 title "mkl" with errorbars, '' using 1:6:7 title "cblas" with errorbars
#plot "performance.txt"  using 1:2 title "pthread", '' using 1:4 title "mkl", '' using 1:6 title "cblas"