#! /bin/bash
# Si scriva uno script che legga da un file con nome in.txt tutte le linee di testo e per ogni linea
# determini il numero della linea letta e stampi su un file con nome out.txt il numero di linea e la linea letta
mkdir myfiles
mkdir myfiles/myfiles2

cat > myfiles/file2.txt << EOF
sotto la panca
la capra campa
sopra la panca
la capra crepa
EOF


if (($#!=1)); then
    echo "Deve essere 1 parametro"
    exit 1
fi
touch out.txt
conta=1
while read row; do
    echo "$conta $row" >> out.txt
    ((++conta))
done < $1
#cat -n $1 > out.txt
exit 0
