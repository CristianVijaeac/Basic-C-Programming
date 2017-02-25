#! /bin/bash

if [[ -z $first_time ]]; then
	clear
	first_time=1
	echo -e  "Write:
		a - check point a
		b - check point b
		ab - check point a and b
		c - check point c
		bc - check point b and c
		abc - check all the points\n\t"
	read OPTION
	export OPTION
	export first_time
	procpid=$BASHPID
	(sleep 10; pkill -f "tema1" & pkill -P $procpid)&	
	bash checker.sh
	exit
fi


make

mkdir output


for i in $(seq 1 10); do
	./tema1 < "input/input"$i &> "output/output"$i".out"
done


POINT=3
BEST=30

case "$OPTION" in

	a) REF="ref/ref_a/ref"
		;;
	b) REF="ref/ref_b/ref"
		;;
	c) REF="ref/ref_c/ref"
		;;
	ab) REF="ref/ref_ab/ref"
		POINT=6
		BEST=60
		;;
	bc) REF="ref/ref_bc/ref"
		POINT=6
		BEST=60
		;;
	abc) REF="ref/ref_abc/ref"
	    POINT=9
		BEST=90
		;;
	*) echo -e "Nu exista aceasta optiune\n0 puncte"
	   exit
		;;
esac


TOTAL=0
for i in $(seq 1 10); do
	line=1
	test=1
	while read -u5 -r ref && read -u6 -r out; do
		if [ "$out" != "$ref" ]; then
			test=0
			echo "La testul $i, linia $line este o greseala"
			echo "Referinta: $ref"
			echo -e "Output: $out\n"
			break
		fi
	done 5<$REF$i 6<"output/output"$i".out"
	if [ $test -eq 1 ]; then
		echo "Test$i.....................OK"
		TOTAL=$(($TOTAL + POINT))
	fi
done
	if [ "$TOTAL" -eq $BEST ]; then
		echo "Felicitari! Ai punctajul maxim ($BEST) pentru optiunea aleasa! ^_^"
	else
		echo "Mai poti incerca. Ai acumulat $TOTAL puncte pentru optiunea aleasa! :)"
	fi


rm -rf output
make clean
