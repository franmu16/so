#!/bin/bash
if (($#!=1)); then
	echo "Bisogna passare come parametro una ed una sola directory "
	exit 1
fi
# $1 ha la directory della cartella, $file = $1 + file NON FUNZIONA
for file in $(find "$1" -type f); do
	nome=$(basename "$file") 
	if [[ $nome == *[[:lower:]]* ]]; then
#newname=$(echo $file | tr A-Z a-z)   lo script funziona solo se la dir. è tutta minuscola
		newnome=$(echo $nome | tr a-z A-Z)
		mv $file "$1/$newnome"
	fi
done
exit 0
