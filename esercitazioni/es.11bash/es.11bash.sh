#!/bin/bash
if(($#!=4)); then
	echo "Bisogna passare 4 parametri";
	exit 1;
fi
if [[ ! -d $2 ]]; then
	mkdir "$2"
fi
conta=0
s=0
for file in "$1/*"; do
	echo $(cat $file | grep "$4" | awk '{print $3}')
done > $2/$3
cat $2/$3
for result in $(cat $2/$3); do
	s=$(($s+$result))
	((conta++))
done
avg=$(echo "scale=3; $s/$conta" | bc -l) 
echo "Media = $avg"
exit 0
