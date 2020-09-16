#!/bin/bash

RED='\033[0;31m'
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
BLUE='\033[0;36m'
NOCOL='\033[0m'

#You can add your own tests after check_for_errors() and run_test()

check_for_errors()
{
	if [ $? -eq 1 ];
	then
		echo -ne "${YELLOW}"
		read -p "OUTPUT DIFFERENCES - CHECK DIFFERENCES AND PRESS ENTER TO CONTINUE"
		wait
		echo -ne "${NOCOL}"
	fi
}

run_test()
{
	echo -e "${BLUE}TESTING WITH FILES $2${NOCOL}\n"
	sleep 0.5
	./cw_test.sh --test $2
	check_for_errors
	echo  -e "${BLUE}TESTING DUMP VALUE $1 WITH FILES $2${NOCOL}\n"
	sleep 0.5
	./cw_test.sh --dump $1 $2
	check_for_errors
}

#	Add more tests below these comment lines!
#	Syntax: run_test <cycle nbr for dump> <"cor_file1.cor cor_file2.cor cor_file3.cor cor-file4.cor">
#	Does not currently support other flags than -d.
#	Note: Run test always runs the test script twice, once without dump to see the winner
#	And once to see what happens inside the vm.
#	If you want to only run --dump or --test, do not use this function

run_test 150000 "cor_files/terminator.cor cor_files/helltrain.cor"
run_test 150000 "cor_files/terminator.cor"
run_test 1000 "cor_files/Wall.cor cor_files/Eraser.cor cor_files/mortel.cor cor_files/NoIdea.cor"
run_test 1000 "cor_files/Rainbow_dash.cor cor_files/_.cor"
run_test 17030 "cor_files/ex.cor cor_files/turtle.cor cor_files/helltrain.cor cor_files/fluttershy.cor"
run_test 10000 "cor_files/turtle.cor cor_files/helltrain.cor cor_files/fluttershy.cor"
run_test 12000 "cor_files/turtle.cor cor_files/fluttershy.cor"
run_test 0 "cor_files/jinx.cor cor_files/big_feet.cor cor_files/overwatch.cor cor_files/wave.cor"
run_test 1 "cor_files/jinx.cor cor_files/dubo.cor cor_files/big_feet.cor cor_files/overwatch.cor"
run_test -1 "cor_files/jinx.cor cor_files/dubo.cor cor_files/big_feet.cor cor_files/overwatch.cor"
run_test 9000 "cor_files/terminator.cor cor_files/Hidden.cor cor_files/Kittystrophic.cor cor_files/Stargate0_1.cor"
run_test 15000 "cor_files/terminator.cor"
