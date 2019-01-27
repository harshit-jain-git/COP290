set terminal svg size 1920,1080 fname 'Verdana'
set output 'time_comparison.eps'
# set terminal png size 1920,1080
# set output 'time_comparison.png'
set logscale y
set boxwidth 1 absolute
set style data histograms
set style histogram clustered gap 5 
set style fill solid 1.0 border lt -1
set errorbars fullwidth
set style fill solid 1 border lt -1
set title "Comparison of Mean and Standard deviation of latencies of pthread, mkl and openblas methods"
set style histogram errorbars gap 5 lw 2
array A[3] = ["pthread", "mkl", "openblas"]
plot for [COL=2:6:2] 'performance.dat' using COL:COL+1:xticlabels(1) title A[COL/2]
