#!/bin/bash
secret=savagay
#read -p "Enter password" -s password
while [[ $password != $secret ]]; do
	read -p "Enter password:" -s password
	echo $'\n'
	echo "Accesso non consentito"
done
echo $'\n'
echo "Accesso consentito"
exit 0

