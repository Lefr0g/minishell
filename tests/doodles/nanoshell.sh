#!/bin/bash

if [ -z "$(ls ../../libft/libft.a)" ]
then
	make -C ../../libft;
fi
clang nanoshell.c -lft -L ../../libft -I ../../libft/includes;
