#! /bin/bash
# Progettare uno script che prende un parametro che indica il nome di una
# directory e sia in grado di esaminare tutti gli elementi della directory, 
# senza entrare nelle eventuali sotto-directory;
# lo script, per ciascun elemento trovato nella directory, deve
# scrivere in un file denominato "summary.out" (nella directory corrente), 
# un "sommario" dell'elemento secondo le sueguenti modalità:
# 1) se l'elemento è un file, lo script deve riportare nel sommario il nome del
# file e i suoi primi 10 caratteri.
# 2) se l'elemento è una sottodirectory, lo script deve riportare nel sommario
# il nome della sottodirectory e il numero di file
# in essa contenuti.
# Si controlli che il parametro passato sulla linea di comando sia uno e che
# sia il nome di una directory.
#
# SUGGERIMENTO
# - Per stampare la prima riga di un file, si può usare il comando
#          head -n 1 NOMEFILE
# - Per ottenere il numero di elementi di una directory si può usare
#   il comando ls (che scrive in output i contenuti di una directory)
#   in combinazione con il comando wc -l (che scrive in output il numero
#   di linee del suo input).

# Esempio: eseguendo il comando:
#     ./summary.sh myfiles 
# verrà creato un file summary.out con il seguente contenuto:
#   FILE myfiles/file1.txt: la vispa
#   FILE myfiles/file2.txt: sotto la panca
#   FILE myfiles/input.dat: riga uno
#   SOTTODIRECTORY myfiles/myfiles2: 1
#

# Le seguenti istruzioni creano i file e le sottodirectory per il test
mkdir myfiles
mkdir myfiles/myfiles2
cat > myfiles/input.dat << EOF
riga uno
riga due
riga tre
EOF

cat > myfiles/file1.txt << EOF
la vispa
Teresa
avea tra l'erbetta
EOF

cat > myfiles/file2.txt << EOF
sotto la panca
la capra campa
sopra la panca
la capra crepa
EOF

cat > myfiles/myfiles2/file3.txt << EOF
altro file
EOF


if (($#!=1)); then
    echo "Bisogna inserire una directory";
    exit 1;
elif [[ ! -d $1 ]]; then
    echo "Il parametro da passare deve essere una directory";
    exit 2;
fi
for line in $1/*; do
    if [[ -f $line ]]; then
        echo "$line: $(head -c 10 $line)" >> summary.out
    elif [[ -d $line ]]; then
        echo "$line, #file: $(ls $line | wc -l)" >> summary.out
    fi
done 







