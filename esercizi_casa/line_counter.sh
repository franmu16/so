#!/bin/bash
if(($#!=2)); then
	echo "Numero argomenti non valido"
	exit 1 
fi
if [[ -d $1 ]] ; then
	if [[ $2 == "up" ]]; then
		find "$1" -type f -exec wc -l {} ';' | sort -n
		
	elif [[ $2 == "down" ]]; then
		find "$1" -type f -exec wc -l {} ';' | sort -nr
	else
		echo 'Non si è specificato se up o down'
		exit 1
	fi
else
	echo 'Directory non valida'
	exit 1
fi
exit 0
