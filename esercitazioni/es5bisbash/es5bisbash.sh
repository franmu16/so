#!/bin/bash
if(($#!=2)); then
	echo "Too few arguments"
	exit 1
fi
n=1; 
while read row; do
	echo "$n. $row" 
	n=$((n+1))
done <$1 >>$2
exit 0
