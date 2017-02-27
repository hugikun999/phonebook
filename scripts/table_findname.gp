reset
set xlabel "table_size"
set ylabel "time(s)"
set terminal png font " Times_New_Roman,12 "
set output "table_size.png"
set title "Compare for table size"
set key left 

plot [10:1000][:0.0001]\
"hash.txt" using 1:3 with lines title "findname()"
