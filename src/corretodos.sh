#!/bin/bash

binari=('QS_Paralel' 'Validation_For' 'Validation_ForNoWait' 'Validation_Sections');
for name in ${array[@]}; do
	echo "${binari[i]}"
	i="0"
	while [ $i -lt 10 ]
	do
		time=$(srun -p gat time ./${binari[i]} 300000000 32 2>&1 | grep "elapsed" | cut -d ' ' -f3 | cut -c 3-7)
		echo "$time"
		echo "$time " >> results.txt	
		i=$[$i+1]
	done
done

