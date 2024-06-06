#!/bin/bash
if (($#!=1)); then
	echo "Nella riga di comando deve andarci un parametro"
	exit 1
fi
n=0
for file in $(find . -name "*$1*"); do
	if [[ -f $file ]]; then 
		echo $file
		n=$((n+1))
	fi
done
echo "File con nome $1: $n" 
exit 0
