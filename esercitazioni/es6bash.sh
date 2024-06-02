#!/bin/bash
if(($#!=2)); then
	echo "Valori non inseriti su riga comando"
	echo "Inserire primo valore: "
	read n1
	echo "Inserire secondo valore: "
	read n2
else
	n1=$1
	n2=$2
fi
n=0
r=0;
c=0;
while ((r<n1)); do
	while ((c<n2)); do
		echo -n "$n "
		n=$((n+1))
		c=$((c+1))
	done
	r=$((r+1))
	c=0
	echo $'\n'
done
exit 0

#for r in $(seq $n1); do
#	for c in $(seq $n2); do
#	echo "$n "
#	n=$((n+1))
#	done
#done
