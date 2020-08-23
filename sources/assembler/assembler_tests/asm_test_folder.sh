#!/bin/bash

# ---- Editable area ----

# EXE = path to our asm executable
# ORIG_EXE = path to the comparison executable
# Paths need to be relative to assembler_tests folder

EXE=../asm
ORIG_EXE=../../../resources/asm

LINECHECKER=./linechecker

# Time in seconds added to each test for readability. Set to 0 for fast output
INTERVAL=1
# ---- Do not edit after this point unless you know what you're doing! ----

OPTION=$1
FOLDER=$2
TEST_NBR=1

RED='\033[0;31m'
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
BLUE='\033[0;36m'
NOCOL='\033[0m'

if [ $# -lt 2 ];
then
	echo -e "+---------------------------------------------------------------------------------------+"
	echo -e "|                                                                                       |"
	echo -e "| ${YELLOW}USAGE ${RED}(NOTE: RUN INSIDE assembler_tests folder)${NOCOL}                                       |"
	echo -e "|                                                                                       |"
	echo -e "| ${BLUE}./asm_test_folder.sh --test [folder name without trailing '/'] ${NOCOL}                       |"
	echo -e "|      -> compare our asm output to original asm output                                 |" 
	echo -e "|                                                                                       |"                                           
	echo -e "| ${BLUE}./asm_test_folder.sh --clean [folder name without trailing '/'] ${NOCOL}                      |"
	echo -e "|      -> Cleans .cor files, test files and folders in the given folder                 |"
	echo -e "|                                                                                       |"
	echo -e "| Your asm needs to be compiled before you run tests.                                   |"
	echo -e "| Check that file path variables (${GREEN}EXE${NOCOL} and ${GREEN}ORIG_EXE${NOCOL}) are correctly set.                  |"
	echo -e "| (relative path from assembler_tests folder)                                           |"
	echo -e "|                                                                                       |"
	echo -e "| ${YELLOW}Notes:${NOCOL}                                                                                |"
	echo -e "| Set INTERVAL to 0 in the script file if you want a faster test.                       |"
	echo -e "|                                                                                       |"
	echo -e "+---------------------------------------------------------------------------------------|"
	exit 1
else
if [ "$OPTION" == "--test" ] && test -d "$FOLDER";
then
{
	echo -e "${YELLOW}The following files will be deleted:${NOCOL}"
	echo "  $FOLDER/*.cor"
	echo "	.output"
	echo "  $FOLDER/our_output"
	echo "  $FOLDER/orig_output"
	echo "  $FOLDER/our_cor_files/*"
	echo "  $FOLDER/orig_cor_files/*"
	echo -ne "${RED}"
	read -p "ARE YOU SURE? [y/n] " -n 1 -r
	echo
	if [[ ! $REPLY =~ ^[Yy]$ ]]
	then
		exit 1
	fi
	echo -e "${NOCOL}"
	FILES=$FOLDER/*
	rm $FOLDER/*.cor
	rm -f .output
	if [ -d "$FOLDER/our_cor_files" ];
	then
		rm $FOLDER/our_cor_files/*.cor
	else
		mkdir $FOLDER/our_cor_files
	fi
	if [ -d "$FOLDER/orig_cor_files" ];
	then
		rm $FOLDER/orig_cor_files/*.cor
	else
		mkdir $FOLDER/orig_cor_files
	fi
	for f in $FILES
	do
		rm $FOLDER/orig_output
		rm $FOLDER/our_output


		echo -n "$TEST_NBR " > $FOLDER/orig_output
		$ORIG_EXE $f >> $FOLDER/orig_output 2>&1
		if [ $? -gt 1 ];
		then
			echo "abort" >> $FOLDER/orig_output
		fi
		cp $FOLDER/*.cor $FOLDER/orig.cor.temp 2> /dev/null
		mv $FOLDER/*.cor $FOLDER/orig_cor_files/. 2> /dev/null


		echo -n "$TEST_NBR " > $FOLDER/our_output
		$EXE $f >> $FOLDER/our_output 2>&1
		if [ $? -gt 1 ];
		then
			echo "abort" >> $FOLDER/orig_output
		fi
		cp $FOLDER/*.cor $FOLDER/our.cor.temp 2> /dev/null
		mv $FOLDER/*.cor $FOLDER/our_cor_files/. 2> /dev/null


		echo -e "$TEST_NBR - $f" | tee -a .output
		diff $FOLDER/our_output $FOLDER/orig_output > /dev/null
		if [ $? -eq 0 ];
		then
			echo -e "${GREEN}Program output messages are equal${NOCOL}" | tee -a .output
		else
			echo -e "${YELLOW}Differences in output messages - comparing contents${NOCOL}" | tee -a .output
			$LINECHECKER $FOLDER/our_output $FOLDER/orig_output | tee -a .output
		fi

		echo "Comparing cor files" | tee -a .output

		if test -f "$FOLDER/our.cor.temp";
		then
			if test -f "$FOLDER/orig.cor.temp";
			then
				diff $FOLDER/our.cor.temp $FOLDER/orig.cor.temp > /dev/null
				if [ $? -eq 0 ];
				then
					echo -e "${TEST_NBR} ${GREEN}OK${NOCOL}" | tee -a .output
				else
					echo -e "${TEST_NBR} ${RED}FAIL - Different outputs in cor files${NOCOL}" | tee -a .output
				fi
			else
				echo -e "${TEST_NBR} ${YELLOW}Ours made a .cor file, original didn't${NOCOL}" | tee -a .output
			fi
		else
			if test -f "$FOLDER/orig.cor.temp";
			then
				echo -e "${RED}Missing .cor file${NOCOL}" | tee -a .output
			else
				echo -e "${TEST_NBR} ${GREEN}OK${NOCOL} (Both files missing)" | tee -a .output
			fi
		fi

		rm $FOLDER/our.cor.temp 2> /dev/null
		rm $FOLDER/orig.cor.temp 2> /dev/null
			TEST_NBR=$(( TEST_NBR + 1 ))
		echo -e "${BLUE}==========================================================================================${NOCOL}" | tee -a .output
		sleep $INTERVAL
		done
		sed $'s,\x1b\\[[0-9;]*[a-zA-Z],,g' .output > log
		rm .output
}
elif [ "$OPTION" == "--clean" ] && test -d "$FOLDER";
then
	echo -e "${YELLOW}The following files will be deleted:${NOCOL}"
	echo "  $FOLDER/*.cor"
	echo "  $FOLDER/our_output"
	echo "  $FOLDER/orig_output"
	echo "  $FOLDER/our_cor_files/* (inc. folder itself)"
	echo "  $FOLDER/orig_cor_files/* (inc. folder itself)"
	echo -ne "${RED}"
	read -p "ARE YOU SURE? [y/n] " -n 1 -r
	echo	
	if [[ ! $REPLY =~ ^[Yy]$ ]]
	then
		exit 1
	fi
	FILES=$FOLDER/*
	rm $FOLDER/*.cor
	rm $FOLDER/our_output
	rm $FOLDER/orig_output
	rm -rf $FOLDER/our_cor_files
	rm -rf $FOLDER/orig_cor_files
else
	echo "";
	echo -e ${RED}INVALID OPTION OR FOLDER NAME${NOCOL}
	echo "";
	echo -e "+---------------------------------------------------------------------------------------+"
	echo -e "|                                                                                       |"
	echo -e "| ${YELLOW}USAGE ${RED}(NOTE: RUN INSIDE assembler_tests folder)${NOCOL}                                       |"
	echo -e "|                                                                                       |"
	echo -e "| ${BLUE}./asm_test_folder.sh --test [folder name without trailing '/'] ${NOCOL}                       |"
	echo -e "|      -> compare our asm output to original asm output                                 |" 
	echo -e "|                                                                                       |"                                           
	echo -e "| ${BLUE}./asm_test_folder.sh --clean [folder name without trailing '/'] ${NOCOL}                      |"
	echo -e "|      -> Cleans .cor files, test files and folders in the given folder                 |"
	echo -e "|                                                                                       |"
	echo -e "| Your asm needs to be compiled before you run tests.                                   |"
	echo -e "| Check that file path variables (${GREEN}EXE${NOCOL} and ${GREEN}ORIG_EXE${NOCOL}) are correctly set.                  |"
	echo -e "| (relative path from assembler_tests folder)                                           |"
	echo -e "|                                                                                       |"
	echo -e "| ${YELLOW}Notes:${NOCOL}                                                                                |"
	echo -e "| Set INTERVAL to 0 in the script file if you want a faster test.                       |"
	echo -e "|                                                                                       |"
	echo -e "+---------------------------------------------------------------------------------------|"
	exit 1
fi
fi