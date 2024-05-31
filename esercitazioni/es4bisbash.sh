#!/bin/bash
secret=traiano
conta=0
while [[ $password != $secret ]] && [[ $conta<3 ]]; do
	read -p "Enter password" -s password
	echo $'\n'
	echo "Accesso negato"
	conta=$((conta+1))
done
if((conta>=3)); then
	echo "Tentativi terminati"
else
	echo "Accesso consentito"
fi
