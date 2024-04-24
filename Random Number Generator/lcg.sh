#! /bin/bash

#PROJECT 4 - RANDOM NUMBERS

#GROUP A
#CEO - NADEEN
#PM - ALFIE
#DEV0 - BEN
#DEV1 - TYLER
#TEST - CHRISTINE


#Get first 8 digits of current nanoseconds
NANO=$(date +%8N)
#Convert form octal to decimal
NANO_DEC=$((10#$NANO))
#echo nanoseconds: "$NANO_DEC"

#Get first 2 digits of nanoseconds
FIRST="${NANO_DEC:0:2}"
#Convert form octal to decimal
FIRST_DEC=$((10#$FIRST))
#echo first digits: "$FIRST_DEC"

#Get next 2 digits of nanoseconds
SECOND="${NANO_DEC:2:2}"
#Convert form octal to decimal
SECOND_DEC=$((10#$SECOND))
#echo second digits: "$SECOND_DEC"
        
#Get next 2 digits of nanoseconds
THIRD="${NANO_DEC:4:2}"
#Convert form octal to decimal
THIRD_DEC=$((10#$THIRD))
#echo third digits: "$THIRD_DEC"

#Get next 2 digits of nanoseconds
FOURTH="${NANO_DEC:6:2}"
#Convert form octal to decimal
FOURTH_DEC=$((10#$FOURTH))
#echo fourth digits: "$FOURTH_DEC"


#Generate SEED variable
SEED=$(($SECOND_DEC + $THIRD_DEC + $FOURTH_DEC))
#echo SEED: "$SEED"

#Generate A variable
A=$(($FIRST_DEC + $THIRD_DEC + $FOURTH_DEC))
#echo A: "$A"

#Generate C variable
C=$(($FIRST_DEC + $SECOND_DEC + $FOURTH_DEC))
#echo C: "$C"

#Generate M variable
M=$(($FIRST_DEC + $SECOND_DEC + $THIRD_DEC))
#echo M: "$M"


#for loop to evaluate LCG 6 times
for i in {1..6}; do
	SEED=$((($A * $SEED + $C) % $M))        
	echo "$SEED"
done

