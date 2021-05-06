if [ $# != 0 ]; then
	ARG=$@; make ; ./philo_two $ARG; make clean
else
	ARG="2 320 300 300"; make ; ./philo_two $ARG; make clean
fi
