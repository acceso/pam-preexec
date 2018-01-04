#!/bin/sh

# change accordingly
PASSFILE="/home/user/.otp"

nextpass=`head -1 $PASSFILE`
if [ $nextpass"" == "" ]; then
	# no more passwords available! exit
	exit
fi

sed -e '1d' $PASSFILE > ${PASSFILE}.tmp
mv ${PASSFILE}.tmp ${PASSFILE}

echo $nextpass
