#!/bin/bash

DIR=$(dirname "$0")

if [ "$DIR" == "" ];
then
	DIR="./"
fi

# ---- Editable area ----

# EXE = path to our corewar executable
# ORIG_EXE = path to the comparison executable
# Paths need to be relative to assembler_tests folder

EXE=../corewar
ORIG_EXE=../resources/corewar

LINECHECKER=./linechecker.sh

# Time in seconds added to each test for readability. Set to 0 for fast output
INTERVAL=0

# ---- Do not edit after this point unless you know what you're doing! ----

OPTION=$1
FOLDER=$DIR/$2
TEST_NBR=1

PASS=0
WARNING=0
MISSING_OUR=0
MISSING_ORIG=0
FAIL=0

RED='\033[0;31m'
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
BLUE='\033[0;36m'
NOCOL='\033[0m'

if [ $# -lt 2 ];
then
	if [ "$OPTION" == "--clean" ];
	then
	{
		DESTDIR=$DIR/logs/cw_test_folder
		echo -e "${YELLOW}The following files will be PERMANENTLY deleted:${NOCOL}"
		echo "   $DESTDIR/*"
		echo -ne "${RED}"
		read -p "DO NOT PRESS Y IF logs/cw_test_folder IS NOT SHOWN! ARE YOU SURE? [y/n] " -n 1 -r
		echo
		if [[ ! $REPLY =~ ^[Yy]$ ]]
		then
			exit 1
		fi
		echo -e "${NOCOL}"
		if [[ -d "$DIR/logs/cw_test_folder" ]];
		then
			rm -rf $DESTDIR/*
			rm -rf $DESTDIR/.output
			rm -rf $DESTDIR/.summary
		fi
	}
	else
		echo "";
		echo -e ${RED}INVALID OPTION OR FOLDER NAME $FOLDER ${NOCOL}
		echo "";
		echo -e "+---------------------------------------------------------------------------------------+"
		echo -e "|                                                                                       |"
		echo -e "| ${YELLOW}USAGE ${RED}(NOTE: RUN INSIDE assembler_tests folder)${NOCOL}                                       |"
		echo -e "|                                                                                       |"
		echo -e "| ${BLUE}./cw_test_folder.sh --test [folder name without trailing '/'] ${NOCOL}                       |"
		echo -e "|      -> compare our corewar output to original corewar output                                 |" 
		echo -e "|                                                                                       |"                                           
		echo -e "| ${BLUE}./cw_test_folder.sh --clean ${NOCOL}                                                         |"
		echo -e "|      -> Cleans logs/cw_test_folder. ${RED}!!CHECK THAT PROMT SHOWS RIGHT FOLDER BEFORE SELECTING Y!!${NOCOL} |"
		echo -e "|                                                                                       |"
		echo -e "| Your corewar needs to be compiled before you run tests.                                   |"
		echo -e "| Check that file path variables (${GREEN}EXE${NOCOL} and ${GREEN}ORIG_EXE${NOCOL}) are correctly set.                  |"
		echo -e "| (relative path from assembler_tests folder)                                           |"
		echo -e "|                                                                                       |"
		echo -e "| ${YELLOW}Notes:${NOCOL}                                                                                |"
		echo -e "| Alter INTERVAL in the script file to change test speed (bigger value = slower test)   |"
		echo -e "|                                                                                       |"
		echo -e "+---------------------------------------------------------------------------------------|"
		exit 1
	fi
else
	if [[ ! -d "$DIR/logs/cw_test_folder" ]];
	then
		mkdir logs/cw_test_folder
	fi
	DESTDIR=$DIR/logs/cw_test_folder/
	if [ "$OPTION" == "--test" ] && test -d "$FOLDER";
	then
	{
		echo -e "${YELLOW}The following files will be PERMANENTLY deleted:${NOCOL}"
		echo "   $DESTDIR*"
		echo -ne "${RED}"
		read -p "DO NOT PRESS Y IF logs/cw_test_folder IS NOT SHOWN! [y/n] " -n 1 -r
		echo
		if [[ ! $REPLY =~ ^[Yy]$ ]]
		then
			exit 1
		fi
		echo -e "${NOCOL}"
		FILES=$FOLDER/*
		rm -rf $DESTDIR/*
		rm -rf $DESTDIR/.output
		rm -rf $DESTDIR/.summary
		echo "" | tee $DESTDIR/.output
		echo -e "${BLUE}==========================================================================================${NOCOL}" | tee -a $DESTDIR/.output
		for f in $FILES
		do
			rm $DESTDIR/orig_output 2> /dev/null
			rm $DESTDIR/our_output 2> /dev/null

			$ORIG_EXE $f >> $DESTDIR/orig_output 2>&1
			echo "Orig $TEST_NBR" >> $DESTDIR/log_exe_output
			cat $DESTDIR/orig_output >> $DESTDIR/log_exe_output

			$EXE $f >> $DESTDIR/our_output 2>&1
			echo "Our $TEST_NBR" >> $DESTDIR/log_exe_output
			cat $DESTDIR/our_output >> $DESTDIR/log_exe_output
			echo "---" >> $DESTDIR/log_exe_output

			echo -e "$TEST_NBR - $f" | tee -a $DESTDIR/.output
			echo ""
			diff $DESTDIR/our_output $DESTDIR/orig_output > /dev/null
			if [ $? -eq 0 ];
			then
				echo -e "${GREEN}Program output messages are equal${NOCOL}"
				echo -e "  $TEST_NBR - $f" >> $DESTDIR/.summary
			else
				echo -e "${YELLOW}Differences${NOCOL}"  | tee -a $DESTDIR/.output
				echo ""
				echo -e "${YELLOW}D ${NOCOL}$TEST_NBR - $f" >> $DESTDIR/.summary
				echo -ne ${BLUE}
				echo "OURS" | tee -a $DESTDIR/.output
				echo -ne ${NOCOL}
				cat $DESTDIR/our_output | tee -a $DESTDIR/.output
				echo "" | tee -a $DESTDIR/.output
				echo -ne ${BLUE}
				echo "ORIG" | tee -a $DESTDIR/.output
				echo -ne ${NOCOL}
				cat $DESTDIR/orig_output | tee -a $DESTDIR/.output
			fi

			TEST_NBR=$(( TEST_NBR + 1 ))
			echo ""
			echo -e "${BLUE}==========================================================================================${NOCOL}" | tee -a $DESTDIR/.output
			sleep $INTERVAL
			done
			rm $DESTDIR/log 2> /dev/null
			echo "" | tee $DESTDIR/log
			echo "SUMMARY" | tee -a $DESTDIR/log
			echo -e "" | tee -a $DESTDIR/log
			echo -e "D before test number means there were stdout/error differences - check log" | tee -a $DESTDIR/log
			echo -e "" | tee -a $DESTDIR/log
			cat $DESTDIR/.summary
			sed $'s,\x1b\\[[0-9;]*[a-zA-Z],,g' $DESTDIR/.summary >> $DESTDIR/log
			echo -e "" | tee -a $DESTDIR/log
			echo "STDOUT/ERROR DIFFERENCES" >> $DESTDIR/log
			echo "Saving test output to $DESTDIR/log"
			sed $'s,\x1b\\[[0-9;]*[a-zA-Z],,g' $DESTDIR/.output >> $DESTDIR/log
			rm  $DESTDIR/.summary
			rm  $DESTDIR/our_output
			rm  $DESTDIR/orig_output
	}
	else
		echo "";
		echo -e ${RED}INVALID OPTION OR FOLDER NAME $FOLDER ${NOCOL}
		echo "";
		echo -e "+---------------------------------------------------------------------------------------+"
		echo -e "|                                                                                       |"
		echo -e "| ${YELLOW}USAGE ${RED}(NOTE: RUN INSIDE assembler_tests folder)${NOCOL}                                       |"
		echo -e "|                                                                                       |"
		echo -e "| ${BLUE}./cw_test_folder.sh --test [folder name without trailing '/'] ${NOCOL}                       |"
		echo -e "|      -> compare our asm output to original asm output                                 |" 
		echo -e "|                                                                                       |"                                           
		echo -e "| ${BLUE}./cw_test_folder.sh --clean ${NOCOL}                                                         |"
		echo -e "|      -> Cleans logs/cw_test_folder. ${RED}!!CHECK THAT PROMT SHOWS RIGHT FOLDER BEFORE SELECTING Y!!${NOCOL} |"
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