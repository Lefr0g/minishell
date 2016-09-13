#!/bin/bash

if [ -z "$(ls ../../libft/libft.a)" ]
then
	make -C ../../libft;
fi
clang ft_strsplit_tests.c -lft -L ../../libft -I ../../libft/includes;
