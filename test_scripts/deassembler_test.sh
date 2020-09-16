#!/bin/bash

DIR=$(dirname "$0")

if [ "$DIR" == "" ];
then
	DIR="."
fi

DEASM="$DIR/../asm -z"
ASM="$DIR/../asm"

OPTION=$1

DEST=$DIR/logs/deassembler_test/
FOLDER=$DIR/cor_files
FILES=$FOLDER/*

RED='\033[0;31m'
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
BLUE='\033[0;36m'
NOCOL='\033[0m'

echo -e "${YELLOW}The following files will be PERMANENTLY deleted:${NOCOL}"
echo "   $DEST*.s"
echo "   $DEST*.cor"
echo "   $DEST/s_files/*.s"
echo "   $DEST/cor_files/*.cor"
echo -ne "${RED}"
read -p "DO NOT PRESS Y IF logs/deassembler_test IS NOT SHOWN! [y/n] " -n 1 -r
echo
if [[ ! $REPLY =~ ^[Yy]$ ]]
then
	exit 1
fi
echo -ne "${NOCOL}"
rm -rf $DEST*.s
rm -rf $DEST*.cor
rm -rf $DEST/s_files/*.s
rm -rf $DEST/cor_files/*.cor
wait
if [ "$OPTION" == "--clean" ];
then
	exit 0
fi
for f in $FILES
do
	echo -e "${BLUE}Testing $f:${NOCOL}"
	echo ""
	echo -ne "${BLUE}deasm output: ${NOCOL}"
	$DEASM -d $DEST $f
	wait
	echo -ne "${BLUE}  asm output: ${NOCOL}"
	$ASM $DEST/*.s
	wait
	diff $f $DEST/*.cor > /dev/null 2>&1
	if [ $? -eq 0 ];
	then
		echo -e "${GREEN}Equal cor files${NOCOL}"
	else
		echo -e "${RED}Differences in cor files or missing cor file${NOCOL}"
	fi
	wait
	mv $DEST/*.s $DEST/s_files/ > /dev/null 2>&1
	mv $DEST/*.cor $DEST/cor_files/ > /dev/null 2>&1
	wait
	echo "............................................................."
done
