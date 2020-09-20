#!/bin/bash

DIR=$(dirname "$0")

if [ "$DIR" == "" ];
then
	DIR="./"
fi

# ---- Editable area ----

# EXE = path to our asm executable
# ORIG_EXE = path to the comparison executable
# Paths need to be relative to test_scripts folder

EXE=../asm
ORIG_EXE=../resources/asm

LINECHECKER="./linechecker.sh 1 0"

# Time in seconds added to each test for readability. Set to 0 for fast output
INTERVAL=1

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
		DESTDIR=$DIR/logs/asm_test_folder
		echo -e "${YELLOW}The following files will be PERMANENTLY deleted:${NOCOL}"
		echo "   $DESTDIR/*"
		echo -ne "${RED}"
		read -p "DO NOT PRESS Y IF logs/asm_test_folder IS NOT SHOWN! ARE YOU SURE? [y/n] " -n 1 -r
		echo
		if [[ ! $REPLY =~ ^[Yy]$ ]]
		then
			exit 1
		fi
		echo -e "${NOCOL}"
		if [[ -d "$DIR/logs/asm_test_folder" ]];
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
		echo -e "| ${YELLOW}USAGE ${RED}(NOTE: RUN INSIDE test_scripts folder)${NOCOL}                                       |"
		echo -e "|                                                                                       |"
		echo -e "| ${BLUE}./asm_test_folder.sh --test [folder name without trailing '/'] ${NOCOL}                       |"
		echo -e "|      -> compare our asm output to original asm output                                 |" 
		echo -e "|                                                                                       |"                                           
		echo -e "| ${BLUE}./asm_test_folder.sh --clean ${NOCOL}                                                         |"
		echo -e "|      -> Cleans logs/asm_test_folder. ${RED}!!CHECK THAT PROMT SHOWS RIGHT FOLDER BEFORE SELECTING Y!!${NOCOL} |"
		echo -e "|                                                                                       |"
		echo -e "| Your asm needs to be compiled before you run tests.                                   |"
		echo -e "| Check that file path variables (${GREEN}EXE${NOCOL} and ${GREEN}ORIG_EXE${NOCOL}) are correctly set.                  |"
		echo -e "| (relative path from test_scripts folder)                                           |"
		echo -e "|                                                                                       |"
		echo -e "| ${YELLOW}Notes:${NOCOL}                                                                                |"
		echo -e "| Alter INTERVAL in the script file to change test speed (bigger value = slower test)   |"
		echo -e "|                                                                                       |"
		echo -e "+---------------------------------------------------------------------------------------|"
		exit 1
	fi
else
	if [[ ! -d "$DIR/logs/asm_test_folder" ]];
	then
		mkdir logs/asm_test_folder
	fi
	DESTDIR=$DIR/logs/asm_test_folder/
	if [ "$OPTION" == "--test" ] && test -d "$FOLDER";
	then
	{
		echo -e "${YELLOW}The following files will be PERMANENTLY deleted:${NOCOL}"
		echo "   $FOLDER/*.cor"
		echo "   $DESTDIR*"
		echo -ne "${RED}"
		read -p "DO NOT PRESS Y IF logs/asm_test_folder IS NOT SHOWN! [y/n] " -n 1 -r
		echo
		if [[ ! $REPLY =~ ^[Yy]$ ]]
		then
			exit 1
		fi
		echo -e "${NOCOL}"
		rm $FOLDER/*.cor
		FILES=$FOLDER/*
		rm -rf $DESTDIR/*
		rm -rf $DESTDIR/.output
		rm -rf $DESTDIR/.summary
		if [ -d "$DESTDIR/our_cor_files" ];
		then
			rm $DESTDIR/our_cor_files/*.cor
		else
			mkdir $DESTDIR/our_cor_files
		fi
		if [ -d "$DESTDIR/orig_cor_files" ];
		then
			rm $DESTDIR/orig_cor_files/*.cor
		else
			mkdir $DESTDIR/orig_cor_files
		fi
		echo "" | tee -a $DESTDIR/.output
		echo -e "${BLUE}==========================================================================================${NOCOL}" | tee -a $DESTDIR/.output
		for f in $FILES
		do
			rm $DESTDIR/orig_output 2> /dev/null
			rm $DESTDIR/our_output 2> /dev/null
			ORIG_ABORT=0
			OUR_ABORT=0
			echo -n "$TEST_NBR " > $DESTDIR/orig_output
			$ORIG_EXE $f >> $DESTDIR/orig_output 2>&1
			wait
			if [ $? -gt 1 ];
			then
				echo "abort" >> $DESTDIR/orig_output
				ORIG_ABORT=1
			fi
			cp $FOLDER/*.cor $DESTDIR/orig.cor.temp 2> /dev/null
			mv $FOLDER/*.cor $DESTDIR/orig_cor_files/. 2> /dev/null
			wait
			echo "Orig" >> $DESTDIR/log_exe_output
			cat $DESTDIR/orig_output >> $DESTDIR/log_exe_output

			echo -n "$TEST_NBR " > $DESTDIR/our_output
			$EXE $f >> $DESTDIR/our_output 2>&1
			wait
			if [ $? -gt 1 ];
			then
				echo "abort" >> $DESTDIR/orig_output
				OUR_ABORT=1
			fi
			cp $FOLDER/*.cor $DESTDIR/our.cor.temp 2> /dev/null
			mv $FOLDER/*.cor $DESTDIR/our_cor_files/. 2> /dev/null
			wait
			echo "Our" >> $DESTDIR/log_exe_output
			cat $DESTDIR/our_output >> $DESTDIR/log_exe_output
			echo "---" >> $DESTDIR/log_exe_output


			echo -e "$TEST_NBR - $f" | tee -a $DESTDIR/.output
			echo ""
			diff $DESTDIR/our_output $DESTDIR/orig_output > /dev/null
			if [ $? -eq 0 ];
			then
				echo -e "${GREEN}Program output messages are equal${NOCOL}"
				echo -ne "- " >> $DESTDIR/.summary
			else
				echo -e "${YELLOW}Differences in output messages - comparing contents${NOCOL}"
				echo -ne "${YELLOW}D ${NOCOL}" >> $DESTDIR/.summary
				$LINECHECKER $DESTDIR/our_output $DESTDIR/orig_output | tee -a $DESTDIR/.output
			fi

			echo "Comparing cor files" 

			if test -f "$DESTDIR/our.cor.temp";
			then
				if test -f "$DESTDIR/orig.cor.temp";
				then
					diff $DESTDIR/our.cor.temp $DESTDIR/orig.cor.temp > /dev/null
					if [ $? -eq 0 ];
					then
						echo -ne "${TEST_NBR} $f " >> $DESTDIR/.summary
						echo -ne "${GREEN}OK${NOCOL}" | tee -a $DESTDIR/.summary
						PASS=$(( PASS + 1 ))
					else
						echo -ne "${TEST_NBR} $f " >> $DESTDIR/.summary
						echo -ne "${RED}FAIL - Different outputs in cor files${NOCOL}" | tee -a $DESTDIR/.summary
						FAIL=$(( FAIL + 1 ))
					fi
				else
					echo -ne "${TEST_NBR} $f " >> $DESTDIR/.summary
					echo -ne "${BLUE}Ours made a .cor file, original didn't${NOCOL}" | tee -a $DESTDIR/.summary
					MISSING_ORIG=$(( MISSING_ORIG + 1 ))
				fi
			else
				if test -f "$DESTDIR/orig.cor.temp";
				then
					echo -ne "${TEST_NBR} $f " >> $DESTDIR/.summary
					echo -ne "${RED}Missing .cor file${NOCOL}" | tee -a $DESTDIR/.summary
					MISSING_OUR=$(( MISSING_OUR + 1 ))
				else
					echo -ne "${TEST_NBR} $f " >> $DESTDIR/.summary
					echo -ne "${GREEN}OK${NOCOL} (Both files missing)" | tee -a $DESTDIR/.summary
					PASS=$(( PASS + 1 ))
				fi
			fi
			if [ $OUR_ABORT -eq 1 ];
			then
				echo -ne "${RED} OURS ABORTED${NOCOL}" | tee -a $DESTDIR/.summary
			fi
			if [ $ORIG_ABORT -eq 1 ];
			then
				echo -ne "${YELLOW} ORIGINAL ABORTED${NOCOL}" | tee -a $DESTDIR/.summary
			fi
			echo "" | tee -a $DESTDIR/.summary
			rm $DESTDIR/our.cor.temp 2> /dev/null
			rm $DESTDIR/orig.cor.temp 2> /dev/null
				TEST_NBR=$(( TEST_NBR + 1 ))
			echo ""
			echo -e "${BLUE}==========================================================================================${NOCOL}" | tee -a $DESTDIR/.output
			sleep $INTERVAL
			done
			rm $DESTDIR/log 2> /dev/null
			echo "" | tee $DESTDIR/log
			echo "SUMMARY" | tee -a $DESTDIR/log
			echo -e "$PASS OK" | tee -a $DESTDIR/log
			echo -e "$MISSING_ORIG Original asm didn't make .cor file, ours did" | tee -a $DESTDIR/log
			echo -e "$MISSING_OUR Our asm didn't make .cor file, original did" | tee -a $DESTDIR/log
			echo -e "$FAIL Errors" | tee -a $DESTDIR/log
			echo -e "" | tee -a $DESTDIR/log
			echo -e "D before test number means there were stdout/error differences - check log" | tee -a $DESTDIR/log
			echo -e "" | tee -a $DESTDIR/log
			cat $DESTDIR/.summary
			sed $'s,\x1b\\[[0-9;]*[a-zA-Z],,g' $DESTDIR/.summary >> $DESTDIR/log
			echo -e "" | tee -a $DESTDIR/log
			echo "STDOUT/ERROR DIFFERENCES" >> $DESTDIR/log
			echo "Saving test output to $DESTDIR/log"
			echo ".cor files can be found in $DESTDIR our_cor_files and orig_cor_files"
			sed $'s,\x1b\\[[0-9;]*[a-zA-Z],,g' $DESTDIR/.output >> $DESTDIR/log
			rm  $DESTDIR/.output
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
		echo -e "| ${YELLOW}USAGE ${RED}(NOTE: RUN INSIDE test_scripts folder)${NOCOL}                                       |"
		echo -e "|                                                                                       |"
		echo -e "| ${BLUE}./asm_test_folder.sh --test [folder name without trailing '/'] ${NOCOL}                       |"
		echo -e "|      -> compare our asm output to original asm output                                 |" 
		echo -e "|                                                                                       |"                                           
		echo -e "| ${BLUE}./asm_test_folder.sh --clean ${NOCOL}                                                         |"
		echo -e "|      -> Cleans logs/asm_test_folder. ${RED}!!CHECK THAT PROMT SHOWS RIGHT FOLDER BEFORE SELECTING Y!!${NOCOL} |"
		echo -e "|                                                                                       |"
		echo -e "| Your asm needs to be compiled before you run tests.                                   |"
		echo -e "| Check that file path variables (${GREEN}EXE${NOCOL} and ${GREEN}ORIG_EXE${NOCOL}) are correctly set.                  |"
		echo -e "| (relative path from test_scripts folder)                                           |"
		echo -e "|                                                                                       |"
		echo -e "| ${YELLOW}Notes:${NOCOL}                                                                                |"
		echo -e "| Set INTERVAL to 0 in the script file if you want a faster test.                       |"
		echo -e "|                                                                                       |"
		echo -e "+---------------------------------------------------------------------------------------|"
		exit 1
	fi
fi