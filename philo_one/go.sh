if [ $# != 0 ]; then
	ARG=$@; make ; ./philo_one $ARG; make clean
else
	ARG="10 3000 3000 3000 10"; make ; ./philo_one $ARG; make clean
fi
