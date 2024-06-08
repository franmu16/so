#!/bin/bash
if (($#!=1)); then
	echo "Bisogna specificare la stringa";
	exit 1;
fi
echo "$(find . -name "*$1*" -type f)"
echo "$(find . -name "*$1*" -type f| wc -l)"
exit 0
