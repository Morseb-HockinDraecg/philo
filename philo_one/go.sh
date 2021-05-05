if [ $# != 0 ]; then
	ARG=$@; make ; ./philo_one $ARG; make clean
else
	ARG="2 610 300 300"; make ; ./philo_one $ARG; make clean
fi
