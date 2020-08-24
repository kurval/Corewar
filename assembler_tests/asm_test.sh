#!/bin/bash

DIR=$(dirname "$0")

if [ "$DIR" == "" ];
then
	DIR="."
fi
echo $DIR;

# ---- Editable area ----

# EXE = path to our asm executable
# ORIG_EXE = path to school-given asm
# Paths need to be relative to assembler_tests folder
# DO NOT REMOVE DIR OR THE SCRIPT WILL ONLY WORK INSIDE ASM FOLDER (unless dirname does not work for you)

EXE=$DIR/../sources/assembler/asm
ORIG_EXE=$DIR/../resources/asm

LINECHECKER=$DIR/./linechecker

# TEST_COUNT represents the number of tests in tests/ folder.
TEST_COUNT=81

# ---- Do not edit after this point unless you know what you're doing! ----

OPTION=$1
TEST_NBR=1

RED='\033[0;31m'
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
BLUE='\033[0;36m'
NOCOL='\033[0m'

if [ $# -ne 1 ];
then
	echo -e "+---------------------------------------------------------------------------------------+"
	echo -e "|                                                                                       |"
	echo -e "| ${YELLOW}USAGE ${RED}(NOTE: RUN INSIDE assembler_tests folder)${NOCOL}                                       |"
	echo -e "|                                                                                       |"
	echo -e "| ${BLUE}./asm_test.sh --compare${NOCOL}                                                               |"
	echo -e "|      -> compare our asm output to original asm output                                 |" 
	echo -e "|                                                                                       |"                                           
	echo -e "| ${BLUE}./asm_test.sh --create ${NOCOL}                                                               |"
	echo -e "|      -> ${RED}DO NOT USE ON WINDOWS${NOCOL} - create reference output                               |"
	echo -e "|         files with the original asm                                                   |"
	echo -e "|                                                                                       |"
	echo -e "| Your asm needs to be compiled before you run tests.                                   |"
	echo -e "| Check that file path variables (${GREEN}EXE${NOCOL} and ${GREEN}ORIG_EXE${NOCOL}) are correctly set.                  |"
	echo -e "| (relative path from assembler_tests folder)                                           |"
	echo -e "|                                                                                       |"
	echo -e "| ${YELLOW}How to add more tests:${NOCOL}                                                                |"
	echo -e "| If file name doesn't matter, you can add a file with a new number in ${GREEN}tests${NOCOL} folder.    |"
	echo -e "| Remember to change ${GREEN}TEST_COUNT${NOCOL} variable to reflect the number of files in the folder.  |"
	echo -e "| After adding new files, run ${BLUE}./asm_test.sh --create${NOCOL} to create new reference files.     |"
	echo -e "| NOTE THAT --create ONLY WORKS IF YOU CAN RUN THE ORIGINAL ASSEMBLER!                  |"
	echo -e "|                                                                                       |"
	echo -e "+---------------------------------------------------------------------------------------|"
	exit 1
else
	if [[ ! -d "$DIR/logs_asm_test" ]];
	then
		mkdir logs_asm_test
	fi
	if [ "$OPTION" == "--create" ];
	then
	{
		echo "Creating new reference files..." 
		echo "Don't panic in case of segfaults, original asm is not very good."
		echo "Segfaults can be ignored."
		if [ -d "$DIR/logs_asm_test/orig_cor_files" ];
		then
			rm $DIR/logs_asm_test/orig_cor_files/*.cor
		else
			mkdir $DIR/logs_asm_test/orig_cor_files
		fi
		rm $DIR/logs_asm_test/orig_output
		while [ $TEST_NBR -le $TEST_COUNT ]
		do
			echo -n "$TEST_NBR " >> $DIR/logs_asm_test/orig_output
			$ORIG_EXE $DIR/tests/test$TEST_NBR.s >> $DIR/logs_asm_test/orig_output 2>&1
			if [ $? -gt 2 ];
			then
				echo "abort" >> $DIR/logs_asm_test/orig_output
			fi
			mv $DIR/tests/test$TEST_NBR.cor $DIR/logs_asm_test/orig_cor_files/orig$TEST_NBR.cor 2> /dev/null
			TEST_NBR=$(( TEST_NBR + 1 ))
		done
		echo -e ${GREEN}All done!${NOCOL}
	}
	elif [ "$OPTION" == "--compare" ];
	then
	{
		if [ -d "$DIR/logs_asm_test/our_cor_files" ];
		then
			rm $DIR/logs_asm_test/our_cor_files/*.cor
		else
			mkdir $DIR/logs_asm_test/our_cor_files
		fi
		rm $DIR/logs_asm_test/our_output
		while [ $TEST_NBR -le $TEST_COUNT ]
		do
			echo -ne "Creating .cor files... ${TEST_NBR}/${TEST_COUNT}\r"
			echo -n "$TEST_NBR " >> $DIR/logs_asm_test/our_output
			$EXE $DIR/tests/test$TEST_NBR.s >> $DIR/logs_asm_test/our_output 2>&1
			if [ $? -gt 1 ];
			then
				echo "abort" >> $DIR/logs_asm_test/our_output
			fi
			mv $DIR/tests/test$TEST_NBR.cor $DIR/logs_asm_test/our_cor_files/our$TEST_NBR.cor 2> /dev/null
			TEST_NBR=$(( TEST_NBR + 1 ))
		done
		echo -ne '\n'


		echo "Comparing program output messages"
		diff $DIR/logs_asm_test/our_output $DIR/logs_asm_test/orig_output > /dev/null
		if [ $? -eq 0 ];
		then
    		echo -e "${GREEN}Program output messages are equal${NOCOL}"
		else
			echo -e "${YELLOW}Differences in output messages - comparing contents${NOCOL}"
			$LINECHECKER $DIR/logs_asm_test/our_output $DIR/logs_asm_test/orig_output
		fi


		echo "Comparing .cor file contents"
		TEST_NBR=1;
		while [ $TEST_NBR -le $TEST_COUNT ]
		do
			if [ $TEST_NBR -lt 10 ];
			then
				echo -n " "
			fi
			if test -f "$DIR/logs_asm_test/our_cor_files/our${TEST_NBR}.cor";
			then
				if test -f "$DIR/logs_asm_test/orig_cor_files/orig${TEST_NBR}.cor";
				then
					diff $DIR/logs_asm_test/our_cor_files/our$TEST_NBR.cor $DIR/logs_asm_test/orig_cor_files/orig${TEST_NBR}.cor > /dev/null
					if [ $? -eq 0 ];
					then
						echo -e "${TEST_NBR} ${GREEN}OK${NOCOL}"
					else
						echo -e "${TEST_NBR} ${RED}FAIL - Different outputs in cor files${NOCOL}"
					fi
				else
					echo -e "${TEST_NBR} ${YELLOW}Ours made a .cor file, original didn't${NOCOL}"
				fi
			else
				if test -f "$DIR/logs_asm_test/orig_cor_files/orig${TEST_NBR}.cor";
				then
					echo -e "${RED}FAIL - Missing .cor file${NOCOL}"
				else
					echo -e "${TEST_NBR} ${GREEN}OK${NOCOL} (Both files missing)"
				fi
			fi
			TEST_NBR=$(( TEST_NBR + 1 ))
		done
		echo ""
		echo ".cor files can be found in $DIR/logs_asm_test/our_cor_files and $DIR/logs_asm_test/orig_cor_files."
		echo "In case of line number errors compare files $DIR/logs_asm_test/our_output and $DIR/logs_asm_test/orig_output"
	}
	else
		echo "";
		echo -e ${RED}INVALID OPTION${NOCOL}
		echo "";
		echo -e "+---------------------------------------------------------------------------------------+"
		echo -e "|                                                                                       |"
		echo -e "| ${YELLOW}USAGE ${RED}(NOTE: RUN INSIDE assembler_tests folder)${NOCOL}                                       |"
		echo -e "|                                                                                       |"
		echo -e "| ${BLUE}./asm_test.sh --compare${NOCOL}                                                               |"
		echo -e "|      -> compare our asm output to original asm output                                 |" 
		echo -e "|                                                                                       |"                                           
		echo -e "| ${BLUE}./asm_test.sh --create ${NOCOL}                                                               |"
		echo -e "|      -> ${RED}DO NOT USE ON WINDOWS${NOCOL} - create reference output                               |"
		echo -e "|         files with the original asm                                                   |"
		echo -e "|                                                                                       |"
		echo -e "| Your asm needs to be compiled before you run tests.                                   |"
		echo -e "| Check that file path variables (${GREEN}EXE${NOCOL} and ${GREEN}ORIG_EXE${NOCOL}) are correctly set.                  |"
		echo -e "| (relative path from assembler_tests folder)                                           |"
		echo -e "|                                                                                       |"
		echo -e "| ${YELLOW}How to add more tests:${NOCOL}                                                                |"
		echo -e "| If file name doesn't matter, you can add a file with a new number in ${GREEN}tests${NOCOL} folder.    |"
		echo -e "| Remember to change ${GREEN}TEST_COUNT${NOCOL} variable to reflect the number of files in the folder.  |"
		echo -e "| After adding new files, run ${BLUE}./asm_test.sh --create${NOCOL} to create new reference files.     |"
		echo -e "| NOTE THAT --create ONLY WORKS IF YOU CAN RUN THE ORIGINAL ASSEMBLER!                  |"
		echo -e "|                                                                                       |"
		echo -e "+---------------------------------------------------------------------------------------|"
		exit 1
	fi
fi