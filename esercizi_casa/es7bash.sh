#!/bin/bash
if(($#!=1)); then
	echo "Numero argomenti errato"
	exit 1
fi
if [[ ! -e $1 ]]; then
	echo "Il file $1 non esiste!"
elif [[ -e $1 ]] && [[ -f $1 ]]; then
	echo "Il file $1 esiste!"
	if [[ -x "$1" ]]; then
		echo "Hai i permessi di esecuzione"
	else
		echo "Non hai i permessi di esecuzione"
	fi
fi
