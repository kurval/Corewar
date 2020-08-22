#!/bin/sh

# make
# ./corewar resources/champs/examples/test.cor
# make fclean

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'


COREWAR="./corewar"
N_FLAG="-n"
PLAYERS=("resources/champs/jumper.cor"
"resources/champs/ex.cor"
"resources/champs/Car.cor"
"resources/champs/examples/test.cor"
"resources/champs/examples/turtle.cor")

declare -i I=0
echo "PARSE VALID PLAYERS"
echo "-------------------"
for t in ${!PLAYERS[@]}; do
	temp=${PLAYERS[$t]}
	timeout() {
		time=$1
		expect -c "set echo \"-noecho\"; set timeout $time; spawn -noecho $COREWAR $temp ; expect timeout { exit 1 } eof { exit 0 }"

		if [ $? = 1 ] ; then
			echo "Timeout after ${time} seconds"
		fi

	}
	timeout 1s $COREWAR $temp
	 if [ $? = 124 ] ; then
		echo "it timed out, do something..."
	else
		echo "didn't time out"
fi
	VAR=$($COREWAR $temp | grep Player)
	if [ "$VAR" ]; then
		printf "${GREEN}\xE2\x9C\x94${NC}"
	else
		printf "${RED}\xE2\x9D\x8C${NC}"
	fi
done

PLAYERS=("resources/champs/error/42.cor"
"resources/champs/error/barriere.cor"
"this_file_does_not_exist"
)
echo " "
echo "PARSE INVALID PLAYERS"
echo "----------------------"

for t in ${!PLAYERS[@]}; do
	temp=${PLAYERS[$t]}
	VAR=$($COREWAR $temp 2>&1)
	if [ "$VAR" ]; then
		printf "${GREEN}\xE2\x9C\x94${NC}"
	else
		printf "${RED}\xE2\x9D\x8C${NC}"
	fi
done

PLAYERS=("-n 2 resources/champs/jumper.cor resources/champs/ex.cor"
"resources/champs/ex.cor"
"resources/champs/Car.cor"
"resources/champs/examples/test.cor"
"resources/champs/examples/turtle.cor")
echo " "
echo "-N FLAG VALID TEST"
echo "----------------------"

for t in ${!PLAYERS[@]}; do
	temp=${PLAYERS[$t]}
	VAR=$($COREWAR $temp | grep -i winner)
	if [ "$VAR" ]; then
		printf "${GREEN}\xE2\x9C\x94${NC}"
	else
		printf "${RED}\xE2\x9D\x8C${NC}"
	fi
done
