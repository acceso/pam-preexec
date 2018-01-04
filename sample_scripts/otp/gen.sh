#!/bin/sh

if [ `which pwgen`"" == "" ]; then
	echo "pwgen needed!"
	exit
fi

for a in `seq 1 40` ; do 
	pwgen -AB1
done


