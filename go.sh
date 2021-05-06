#!/bin/bash

declare -a ARG=("$2 $3 $4 $5 $6 $7 $8")

case $1 in
        "philo_one")
                if (( $# > 1 )); then
					make ; ./philo_one/philo_one $ARG ; make clean
				else
					ARG="2 320 300 300"; make ; ./philo_one/philo_one $ARG; make clean
				fi
                ;;
        "philo_two")
                if (( $# > 1 )); then
					make ; ./philo_two/philo_two $ARG ; make clean
				else
					ARG="2 320 300 300"; make ; ./philo_two/philo_two $ARG; make clean
				fi
                ;;
        "philo_three")
                if (( $# > 1 )); then
					make ; ./philo_three/philo_three $ARG ; make clean
				else
					ARG="2 320 300 300"; make ; ./philo_three/philo_three $ARG; make clean
				fi
                ;;
        *)
                echo "J'te connais pas, ouste !"
                ;;
esac
