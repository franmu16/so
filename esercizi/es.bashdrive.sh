# Scrivere un programma il quale prende come parametro due file di testo ed un numero intero NUM. #Il primo file di testo contine una singola parola, mentre il

# secondo file di testo contiene un insieme di parole. Il programma prende dal primo file #(contentente una parola) il carattere in posizione NUM e cerca nel

# secondo file se esistono parole che iniziano per quel carattere. Se esistono, esse vengono #stampate su un terzo filemkdir myfiles
mkdir myfiles/myfiles2

cat > myfiles/file1.txt << EOF
onlinegdb
EOF

cat > myfiles/file2.txt << EOF
sotto la panca
la capra campa
sopra la panca
la capra crepa
EOF



# INSERIRE QUI IL CODICE

if (($#!=3)); then
    echo "Devono essere 3 parametri"
    exit 1
fi
touch out.txt
char=$(cat $1 | cut -c $3)
echo "La lettera da cercare e' $char"
for parola in $(cat $2); do
    iniziale=$(echo $parola|cut -c 1);
    if [[ $iniziale == $char ]]; then
        echo $parola >> out.txt
    fi
done
exit 0
