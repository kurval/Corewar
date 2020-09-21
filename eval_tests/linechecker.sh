INPUT_OURS=$3
INPUT_ORIG=$4
ERR_ONLY=$1
STRICTNESS=$2

RED='\033[0;31m'
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
BLUE='\033[0;36m'
NOCOL='\033[0m'

if [ $# -ne 4 ];
then
	echo "--------"
	echo "${YELLOW}Usage: ./linechecker.sh [errors_only (1 | 0)] [strictness (1 = red on diff 0 = yellow on diff)] [our_file] [orig_file]"
	echo "Compares 2 files line by line. Prints differing our file lines in color based on strictness${NOCOL}"
	echo "--------"
	exit 1;
fi
while true
do
	read -r OUR_LINE <&8 || break
	read -r ORIG_LINE <&9 || break
	DIFF=$(diff <(echo "$OUR_LINE") <(echo "$ORIG_LINE"))
	if [ "$DIFF" != "" ] 
	then
		if [ $STRICTNESS == 1 ];
		then
			echo -ne "${RED}"
		else
			echo -ne "${YELLOW}"
		fi
	fi
	if [ "$DIFF" != "" ] || [ $ERR_ONLY != 1 ];
	then
		echo "OURS > $OUR_LINE"
		echo -ne "${NOCOL}"
		echo "ORIG > $ORIG_LINE"
		echo ""
	fi
done 8<$INPUT_OURS 9<$INPUT_ORIG
exec 8>&-
exec 9>&- 
wait