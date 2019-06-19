set title "Earth to Moon Trajectory"
set xlabel "S1 (km)"
set ylabel "S2 (km)"
set term png size 4500,1000
set xrange [-400000:50000]
set yrange [-50000:50000]
set output "trajectory.png"
set object 1 circle at 4671.46,0 size 6371 fc rgb "purples"
set object 2 circle at -379729.54,0 size 1737 fc rgb "green"
plot 'path.txt' using 1:2 with lines


