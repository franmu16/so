#!/bin/bash
if(($#!=1)); then
	echo "Passare un parametro";
	exit 1;
fi
cd $1
r=$(find . -name "*[[:upper:]]*" -type f)
for file in $r; do
	newname=$(echo $file | tr A-Z a-z)
	mv "$file" "$newname"
done
exit 0
