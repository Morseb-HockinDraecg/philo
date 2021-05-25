all:
	$(MAKE) -C ./philo_one
	$(MAKE) -C ./philo_two
	$(MAKE) -C ./philo_three
	$(info Make philo)

clean:
	$(MAKE) clean -C ./philo_one
	$(MAKE) clean -C ./philo_two
	$(MAKE) clean -C ./philo_three
	$(info All philo clean)

fclean:
	$(MAKE) fclean -C ./philo_one
	$(MAKE) fclean -C ./philo_two
	$(MAKE) fclean -C ./philo_three
	$(info All philo fclean)

re:
	$(MAKE) re -C ./philo_one
	$(MAKE) re -C ./philo_two
	$(MAKE) re -C ./philo_three
	$(info All philo re)

.PHONY : all clean fclean re
.SILENT :