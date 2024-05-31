#!/bin/bash
echo -n "Inserire stringa: "
read s1
risultato=$(who | grep $s1 | wc -l)
echo "Utenti con nome $s1: $risultato"
exit 0
