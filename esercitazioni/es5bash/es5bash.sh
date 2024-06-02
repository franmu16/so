#!/bin/bash
cnt=1
while read row; do
echo "$cnt. $row" >> out.txt
cnt=$((cnt+1))
done < in.txt
exit 0

