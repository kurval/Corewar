#!/bin/bash

OPTION=$1

RED='\033[0;31m'
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
NOCOL='\033[0m'

EXE=../asm
ORIG_EXE=../../../resources/asm

TEST_NBR=1
TEST_COUNT=65

if [ $# -ne 1 ];
then
	echo "usage: ./asm_test.sh --compare -> compare our asm output to original asm output"
	echo "usage: ./asm_test.sh --create -> DO NOT USE ON WINDOWS - create reference output files with the original asm"
	exit 1
else
	if [ "$OPTION" == "--create" ];
	then
	{
		rm orig_output
		rm orig_cor_files/*.cor
		while [ $TEST_NBR -le $TEST_COUNT ]
		do
			echo -n "$TEST_NBR " >> orig_output
			$ORIG_EXE tests/test$TEST_NBR.s >> orig_output 2>&1
			mv tests/test$TEST_NBR.cor orig_cor_files/orig$TEST_NBR.cor > /dev/null
			TEST_NBR=$(( TEST_NBR + 1 ))
		done
	}
	elif [ "$OPTION" == "--compare" ];
	then
	{
		rm our_output
		rm our_cor_files/*.cor
		while [ $TEST_NBR -le $TEST_COUNT ]
		do
			echo -ne "Creating .cor files... ${TEST_NBR}/${TEST_COUNT}\r"
			echo -n "$TEST_NBR " >> our_output
			$EXE tests/test$TEST_NBR.s >> our_output 2>&1
			mv tests/test$TEST_NBR.cor our_cor_files/our$TEST_NBR.cor 2> /dev/null
			TEST_NBR=$(( TEST_NBR + 1 ))
		done
		echo -ne '\n'


		echo "Comparing program output messages"
		diff our_output orig_output > /dev/null
		if [ $? -eq 0 ];
		then
    		echo -e "${GREEN}Program output messages are equal${NOCOL}"
		else
			echo -e "${YELLOW}Differences in output messages - comparing contents${NOCOL}"
			./linechecker our_output orig_output
		fi


		echo "Comparing .cor file contents"
		TEST_NBR=1;
		while [ $TEST_NBR -le $TEST_COUNT ]
		do
			if test -f "our_cor_files/our${TEST_NBR}.cor";
			then
				if test -f "orig_cor_files/orig${TEST_NBR}.cor";
				then
					diff our_cor_files/our$TEST_NBR.cor orig_cor_files/orig${TEST_NBR}.cor > /dev/null
					if [ $? -eq 0 ];
					then
						echo -e "${TEST_NBR} ${GREEN}OK${NOCOL}"
					else
						echo -e "${TEST_NBR} ${RED}FAIL - Different outputs in cor files${NOCOL}"
					fi
				else
					echo -e "${TEST_NBR} ${RED}FAIL - Ours made a .cor file, original didn't${NOCOL}"
				fi
			else
				if test -f "orig_cor_files/orig${TEST_NBR}.cor";
				then
					echo -e "${RED}FAIL - Missing .cor file${NOCOL}"
				else
					echo -e "${TEST_NBR} ${GREEN}OK${NOCOL}"
				fi
			fi
			TEST_NBR=$(( TEST_NBR + 1 ))
		done
	}
	else
		echo "invalid option"
	fi
fi