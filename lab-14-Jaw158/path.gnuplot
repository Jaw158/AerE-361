set title "Potential Earth to Moon Trajectory"
set term dumb
set xrange [-400000:50000]
set yrange [-50000:50000]
set object 1 circle at 4671.46,0 size 6371
set object 2 circle at -379729.54,0 size 1737
plot 'path.txt' using 1:2 with lines
