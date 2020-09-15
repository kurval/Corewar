#!/bin/bash

DIR=$(dirname "$0")

if [ "$DIR" == "" ];
then
	DIR="."
fi

EXE=$DIR/../corewar
ORIG_EXE=$DIR/../resources/corewar

RED='\033[0;31m'
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
BLUE='\033[0;36m'
NOCOL='\033[0m'

OPTION=$1

if [ $# -lt 1 ];
then
	echo "Usage: ./cw_test.sh --test [file1.cor] [file2.cor] ..."
	echo "Usage: ./cw_test.sh --dump [cycle number] [file1.cor] [file2.cor] ..."
	exit 1
fi
if [ "$OPTION" == "--dump" ];
then
	if [ $# -lt 3 ];
	then
		echo "Usage: ./cw_test.sh --dump [cycle number] [file1.cor] [file2.cor] ..."
		exit 1
	fi
	echo "" > corewar_our_output
	echo "" > corewar_orig_output
	wait
	$EXE -d $2 $3 $4 $5 $6 > corewar_our_output 2>&1
	$ORIG_EXE -d $2 $3 $4 $5 $6 > corewar_orig_output 2>&1
	wait
elif [ "$OPTION" == "--test" ];
then
	if [ $# -lt 2 ];
	then
		echo "Usage: ./cw_test.sh --dump [cycle number] [file1.cor] [file2.cor] ..."
		exit 1
	fi
	echo "" > corewar_our_output
	echo "" > corewar_orig_output
	wait
	$EXE $2 $3 $4 $5 > corewar_our_output 2>&1
	$ORIG_EXE $2 $3 $4 $5 > corewar_orig_output 2>&1
	wait
else
	echo "Usage: ./cw_test.sh --test [file1.cor] [file2.cor] ..."
	echo "Usage: ./cw_test.sh --dump [cycle number] [file1.cor] [file2.cor] ..."
fi
diff corewar_orig_output corewar_our_output > /dev/null
if [ $? -eq 0 ];
then
	echo -e "${GREEN}Program output messages are equal${NOCOL}"
else
	INPUT_OURS="$DIR/corewar_our_output"
	INPUT_ORIG="$DIR/corewar_orig_output"
	while true
	do
		read -r OUR_LINE <&8 || break
		read -r ORIG_LINE <&9 || break
		DIFF=$(diff <(echo "$OUR_LINE") <(echo "$ORIG_LINE"))
		if [ "$DIFF" != "" ] 
		then
			echo -ne "${RED}"
		fi
		echo "OURS > $OUR_LINE"
		echo -ne "${NOCOL}"
		echo "ORIG > $ORIG_LINE"
		echo ""
	done 8<$INPUT_OURS 9<$INPUT_ORIG
	exec 8>&-
	exec 9>&- 
	rm corewar_orig_output
	rm corewar_our_output
fi