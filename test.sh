#!/bin/sh

# make
# ./corewar resources/champs/examples/test.cor
# make fclean

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'


COREWAR="./corewar"
N_FLAG="-n"
PLAYERS=(
"resources/champs/ex.cor"
"resources/champs/examples/test.cor"
"resources/champs/examples/turtle.cor")
declare -i I=0

#TESTING VALID PLAYERS
# Only testing if it is able to read the players without errors.
# Output is stores in VAR Variable. If there was an error or it timeouts VAR is empty

echo "PARSE VALID PLAYERS"
echo "-------------------"
for t in ${!PLAYERS[@]}; do
	temp=${PLAYERS[$t]}
	timeout() {
		time=$1
		expect -c "set echo \"-noecho\"; set timeout $time; spawn $COREWAR $temp ; expect timeout { exit 1 } eof { exit 0 }" > /dev/null
		if [ $? = 1 ] ; then
			printf "⌛"
			continue
		elif [ $? = 139 ] ; then
			printf "💥"
			continue
		fi
	}
	timeout 1s
	VAR=$($COREWAR $temp | grep Player)
	if [ "$VAR" ]; then
		printf "✅"
	else
		printf "❌"
	fi
done

#TESTING INVALID PLAYERS
# Players must display error for some reason.
# Output from error is ridirected to stdout with 2>&1 and stored in VAR
# IF VAR IS NOT EMPTY THERE WAS AN ERROR AND THE TEST PASSES.

PLAYERS=("resources/champs/error/42.cor"
"resources/champs/error/barriere.cor"
"this_file_does_not_exist"
)
echo "\n\n"
echo "PARSE INVALID PLAYERS"
echo "----------------------"

for t in ${!PLAYERS[@]}; do
	temp=${PLAYERS[$t]}
	timeout() {
		time=$1
		expect -c "set echo \"-noecho\"; set timeout $time; spawn $COREWAR $temp ; expect timeout { exit 1 } eof { exit 0 }" > /dev/null
		if [ $? = 1 ] ; then
			printf "⌛"
			continue
		elif [ $? = 139 ]; then
			printf "💥"
			continue
		fi
	}
	timeout 1s
	VAR=$($COREWAR $temp 2>&1)
	if [ "$VAR" ]; then
		printf "✅"
	else
		printf "❌"
	fi
done

#TESTING VALID -N INPUTS
# REQUIRES: At least two chapmions and at least one -n flag
# EXPECTED: Add to the expected variable what should be the output

PLAYERS=("-n 2 resources/champs/examples/test.cor resources/champs/ex.cor"
"-n 1 resources/champs/ex.cor"
"resources/champs/ex.cor -n 2 resources/champs/examples/turtle.cor"
"resources/champs/examples/test.cor -n 1 resources/champs/ex.cor"
"resources/champs/ex.cor -n 1 resources/champs/examples/turtle.cor -n 2 resources/champs/examples/test.cor"
"-n 2 resources/champs/ex.cor -n 1 resources/champs/examples/turtle.cor -n 3 resources/champs/ex.cor -n 4 resources/champs/examples/turtle.cor")
EXPEXTED=("Player 1, Weighing in at 23 BYTES, \"zork\": (\"just a basic living prog\")"
"Player 1, Weighing in at 23 BYTES, \"zork\": (\"just a basic living prog\")"
"Player 1, Weighing in at 23 BYTES, \"zork\": (\"just a basic living prog\")"
"Player 1, Weighing in at 23 BYTES, \"zork\": (\"just a basic living prog\")"
"Player 3, Weighing in at 23 BYTES, \"zork\": (\"just a basic living prog\")"
"Player 2, Weighing in at 23 BYTES, \"zork\": (\"just a basic living prog\")"
)
echo "\n\n"
echo "-N FLAG VALID TEST"
echo "----------------------"

for t in ${!PLAYERS[@]}; do
	temp=${PLAYERS[$t]}
	exp=${EXPEXTED[$t]}
	timeout() {
		time=$1
		expect -c "set echo \"-noecho\"; set timeout $time; spawn $COREWAR $temp ; expect timeout { exit 1 } eof { exit 0 }" > /dev/null
		if [ $? = 1 ] ; then
			printf "⌛"
			continue
		elif [ $? = 139 ]; then
			printf "💥"
			continue
		fi
	}
	timeout 1s
	VAR=$($COREWAR $temp | grep -w "$exp")
	if [ "$VAR" ]; then
		printf "✅"
	else
		printf "❌"
	fi
done

#TESTING Invalid -N INPUTS
# REQUIRES: At least one chapmions and at least one -n flag
#

PLAYERS=("-n 1 resources/champs/examples/test.cor -n 1 resources/champs/ex.cor"
"-n 2 resources/champs/ex.cor"
"-n 2 resources/champs/ex.cor -n 1 resources/champs/examples/turtle.cor -n 3 resources/champs/ex.cor -n 3 resources/champs/examples/turtle.cor"
"resources/champs/examples/test.cor -n 0 resources/champs/ex.cor"
"resources/champs/ex.cor -n 1 resources/champs/examples/turtle.cor -n 2 resources/champs/examples/test.cor -n 3" )
echo "\n\n"
echo "-N FLAG ERROR TEST"
echo "----------------------"

for t in ${!PLAYERS[@]}; do
	temp=${PLAYERS[$t]}
	exp=${EXPEXTED[$t]}
	timeout() {
		time=$1
		expect -c "set echo \"-noecho\"; set timeout $time; spawn $COREWAR $temp ; expect timeout { exit 1 } eof { exit 0 }" > /dev/null
		if [ $? = 1 ] ; then
			printf "⌛"
			continue
		elif [ $? = 139 ]; then
			printf "💥"
			continue
		fi
	}
	timeout 1s
	VAR=$($COREWAR $temp | grep -w ERROR)
	if [ "$VAR" ]; then
		printf "✅"
	else
		printf "❌"
	fi
done


#TESTING VALID -N INPUTS
# REQUIRES: At least two chapmions and at least one -n flag
# EXPECTED: Add to the expected variable what should be the output

PLAYERS=("-dump 1000 -n 1 resources/champs/ex.cor"
)
EXPEXTED=("Player 1, Weighing in at 23 BYTES, \"zork\": (\"just a basic living prog\")"
)
LINES=(130)
echo "\n\n"
echo "-N FLAG VALID TEST"
echo "----------------------"

for t in ${!PLAYERS[@]}; do
	temp=${PLAYERS[$t]}
	exp=${EXPEXTED[$t]}
	timeout() {
		time=$1
		expect -c "set echo \"-noecho\"; set timeout $time; spawn $COREWAR $temp ; expect timeout { exit 1 } eof { exit 0 }" > /dev/null
		if [ $? = 1 ] ; then
			printf "⌛"
			continue
		elif [ $? = 139 ]; then
			printf "💥"
			continue
		fi
	}
	timeout 1s
	VAR=$($COREWAR $temp | grep -w "$exp")
	if [ "$VAR" ]; then
		printf "✅"
	else
		printf "❌"
	fi
done
