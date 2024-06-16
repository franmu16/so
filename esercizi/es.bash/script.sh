#!/bin/bash
# Scrivere un programma che data una cartella ed un file come argomenti, copi tutto il contenuto dei file della cartella all'interno del file passato come
# secondo argomento. Successivamente l'utente inserisce da tastiera un nome di un file e se questo coincide con il nome del file passato come parametro
# elimina quest'ultimo stampando il contenuto a video, altrimenti crea un file con il nome inserito da input copiando all'interno il contenuto del file
# passato come secondo parametro.
if (($#!=2)); then
	echo "Devono essere 2 parametri"
	exit 1
fi
if [[ ! -d $1 ]]; then
	echo "Il 1o parametro deve essere una directory"
	exit 1
elif [[ ! -f $2 ]]; then
	echo "Il 2o parametro deve essere un file"
	exit 1
fi
for file in "$1/*"; do
	cat $file >> $2
done
echo "Inserire nome file in cui esportare il contenuto del file $2 (inserendo $2 si vedrà a video il suo contenuto e verrà eliminato il file)"
read name
if [[ $name == $2 ]]; then
	cat $2
	rm $2
else
	touch $name
	cat $2 > $name
fi
