#!/bin/bash
if(($#!=1));then
	echo "Bisogna inserire un utente"
	exit 1
else
	risultato=$(who|grep $1|wc -l)
	echo "Il numero di utenti $1 e':  $risultato"
	exit 0
fi
