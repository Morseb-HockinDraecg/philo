if [ $# != 0 ]; then
	ARG=$@; make ; ./philo_one $ARG; make clean
else
	ARG="3 1000 300 300 3"; make ; ./philo_one $ARG; make clean
fi
