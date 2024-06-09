#!/bin/bash
touch mylog
c=100
while (($c>=0)); do
	r=$(find . -name "mylog.$c*")
	if [[ -n "$r" ]]; then
		t=$c
		t=$((t+1))
		mv "mylog.$c*" "mylog.$t*"
		if ((t==1)); then
			gzip "mylog.$t"
		fi
	fi
	c=$((c-1))
done
mv "mylog" "mylog.0"
exit 0
