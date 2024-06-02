#!/bin/bash
if(($#!=2)); then
	echo "Numero argomenti non valido"
	exit 1 
fi
if [[ -d $1 ]] ; then
	if [[ $2 == "up" ]]; then
		find "$1" -type f -exec cat {} ';' > out.txt
		sort -i out.txt | wc -l
		
	elif [[ $2 == "down" ]]; then
		find "$1" -type f -exec cat {} ';' > out.txt
		sort -i out.txt | wc -l
		
	else
		echo 'Non si è specificato se up o down'
	fi
else
	echo 'Directory non valida'
fi


