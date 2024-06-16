# Scrivere uno script che prenda 2 parametri in ingresso e verifichi che siano
# due cartelle. Lo script deve verificare che nella seconda cartella passata in
# input ci siano 3 cartelle: anno1, anno2, anno3; altrimentri crea quelle che mancano.
# Lo script deve esaminare i file presenti nella prima cartella passata in input esami
# creare un file di log nella cartella specificata come secondo parametro. Il file di
# log deve essere strutturato nel seguente modo (valido anche come esempio di output):
#
# -- INIZIO FILE log --
# Esami a 6 CFU: f2 csd
# Esami a 9 CFU: et asd am1
# Media ponderata: 27.846
# Media aritmetica: 28
# -- FINE FILE log --
#
# Lo script deve inoltre spostare ciascun file, in base all'anno indicato, nella cartella
# corrispondente (anno1,anno2 o anno3) stampando i vari spostamenti.
# 
# SUGGERIMENTI:
# 1 - Per poter manipolare una stringa si può usare la seguente sintassi ${string:position:length}
# stringa=cane
# echo ${stringa:2:2} -> "ne"
#
# 2 - Per ottenere la lunghezza dei una stringa ${#string}
# stringa=cane
# echo ${#stringa} -> "4"
#
# 3 - Per poter ottenere la posizione di un carattere in una certa stringa usare `expr index "$stringa" <carattere>`
# stringa=cane
# echo `expr index "$stringa" n` -> "3"
# USARE L'ACCENTO GRAVE `
#
# 4 - Si usi il comando awk '{print $i}’ che consente di stampare l’i-ma stringa di ogni riga di un file.
#
# -- creazione file -- #
#!/bin/bash
mkdir esami

cat > esami/et.txt << EOF
ANNO 2
VOTO 27
CFU 9
EOF

cat > esami/f2.txt << EOF
ANNO 1
VOTO 28
CFU 6
EOF

cat > esami/asd.txt << EOF
ANNO 2
VOTO 25
CFU 9
EOF

cat > esami/am1.txt << EOF
ANNO 1
VOTO 30
CFU 9
EOF

cat > esami/csd.txt << EOF
ANNO 2
VOTO 30
CFU 6
EOF

mkdir dest
mkdir dest/anno2

# -- Inserisci qui il codice -- #
if [[ $# != 2 ]] || [[ ! -d $1 ]] || [[ ! -d $2 ]];then
    echo "SYNTAX: $0 <directory> <directory>"
    exit 1
fi

if [[ -z $(find $2 -maxdepth 1 -type d -name "anno1") ]]; then
    mkdir $2/anno1
fi

if [[ -z $(find $2 -maxdepth 1 -type d -name "anno2") ]]; then
    mkdir $2/anno2
fi

if [[ -z $(find $2 -maxdepth 1 -type d -name "anno3") ]]; then
    mkdir $2/anno3
fi
r=$(find $1 -type f)
somma=0
psomma=0
conta=0
scfu=0
Scfu=""
Ncfu=""
touch "$2/log.txt"
for row in $r; do
#while read row; do
    voto=$(cat $row | grep -i "voto" | awk '{print $2}')
    cfu=$(cat $row | grep "CFU" | awk '{print $2}')
    anno=$(cat $row | grep "ANNO" | awk '{print $2}')
    nome=$(basename $row .txt)
    somma=$(($somma+$voto))
    psomma=$(($psomma+(($voto*$cfu))))
    scfu=$(($scfu+$cfu))
    ((conta++))
    if [[ $cfu == "6" ]]; then
        Scfu=$(echo "$Scfu $nome")
    fi
    if [[ $cfu == "9" ]]; then
        Ncfu=$(echo "$Ncfu $nome")
    fi
    mv $row "$2/anno$anno/$nome.txt"
    echo "Spostato $nome.txt in anno$anno"
done
media=$(echo "scale 3; $somma/$conta" | bc -l);
mediap=$(echo "scale 3; $psomma/$scfu" | bc -l);
echo "Esami a 6 CFU: $Scfu" >> "$2/log.txt"
echo "Esami a 9 CFU: $Ncfu" >> "$2/log.txt"
echo "Media aritmetica: $media" >> "$2/log.txt"
echo "Media ponderata: $mediap" >> "$2/log.txt"
exit 0



