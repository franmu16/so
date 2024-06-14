#!/bin/bash
# Scrivere uno script bash che prende 4 argomenti in input:
# la cartella sorgente, una stringa, la prima cartella di destinazione,
# la seconda cartella di destinazione.
# Se il primo argomento non è una cartella o non esiste bisogna stampare un messaggio di
# errore e terminare lo script. Se il terzo o quarto argomento non esiste si devono creare, se
# esiste ma non è una cartella si deve terminare lo script stampando un messaggio di errore.
# Lo script deve scorrere i file contenuti nella cartella sorgente e analizzare
# il proprio contenuto (che sarà di una sola riga ad es "NUMERO 3").
# Se il numero contenuto nel file è dispari il file deve essere rinominato con tutti
# caratteri maiuscoli (fatta eccezione per l'estensione .txt), altrimenti, 
# se è pari, tutti caratteri minuscoli. Lo script deve inoltre spostare tutti i file
# che contengono la stringa passata in input nella prima cartella di destinazione,
# il resto nella seconda cartella di destinazione. Infine dovrà stampare il numero di files
# spostati nella prima destinazione e il numero di file spostati nella seconda destinazione.
#
# ESEMPIO
#
# "files il target others" dovrà dare come output
# "Spostati 2 files nella cartella target" che sono FILE1.txt e pilpo.txt
# "Spostati 2 files nella cartella others" che sono CIAO.txt e otto.txt
#
# SUGGERIMENTI
# 1 - Per poter manipolare una stringa si può usare la seguente sintassi ${string:position:length}
# stringa=cane
# echo ${stringa:2:2} -> "ne"
#
# 2 - Per ottenere la lunghezza dei una stringa ${#string}
# stringa=cane
# echo ${#stringa} -> "4"
# 3 - Si usi il comando awk '{print $i}’ che consente di stampare l’i-ma stringa di ogni riga di un file.

# --- queste istruzioni creano i file di prova  ---
mkdir files
cat > files/FiLe1.txt <<EOF
NUMERO 3
EOF

cat > files/PILpo.txt <<EOF
NUMERO 4
EOF

cat > files/cIaO.txt <<EOF
NUMERO 5
EOF

cat > files/oTTo.txt <<EOF
NUMERO 6
EOF

mkdir target
mkdir others

#------------- Inserire qui il codice dello script -------------

if (($#!=4)); then
    echo "devono essere 4 arg."
    exit 1
fi

if [[ ! -d $1 ]] || [[ ! -e $1 ]]; then
    echo "il primo arg. deve essere una dir. esistente"
    exit 1
fi

if [[ ! -e $3 ]]; then
    mkdir $3
elif [[ ! -d $3 ]]; then
    echo "il 3 arg. deve essere una dir"
    exit 1
fi

if [[ ! -e $4 ]]; then
    mkdir $3
elif [[ ! -d $4 ]]; then
    echo "il 3 arg. deve essere una dir"
    exit 1
fi

r=$(find $1 -type f)
for line in $r; do
    value=$(cat $line | awk '{print $2}')
    val=$(echo "scale 2; $value/2" | bc -l)
    length=${#$line}
    if [[ $(($value/2)) == $val ]]; then
        newname=basename -s .txt $line | tr A-Z a-z)
        mv $line "files/$newname.txt"
    else
        newname=$(echo ${$line:6:(($length-10))} | tr a-z A-Z)
        mv $line "files/$newname.txt"
    fi
done
r=$(find $1 -iname "*$2*")
ACK=0
NAK=0
for line in $r; do
    file=basename $line
    mv $line $3/file
    ((ACK++))
done
r=$(find $1 -type f)
for line in $r; do
    file=basename $line
    mv $line $4/file
    ((NAK++))
done
echo "Spostati $ACK files nella cartella $3"
echo "Spostati $NAK files nella cartella $4"

