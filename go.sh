#!/bin/bash

if (( $# > 1 )); then
	declare ARG=("$2 $3 $4 $5 $6 $7 $8")
else
	ARG="5 410 200 200"
fi

make
case $1 in
        "philo_one")
		./philo_one/philo_one $ARG
                ;;
        "philo_two")
		./philo_two/philo_two $ARG
                ;;
        "philo_three")
		./philo_three/philo_three $ARG
                ;;
        *)
                echo $ARG
                ;;
esac

make clean
