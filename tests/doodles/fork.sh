#!/bin/bash

if [ -z "$(ls ../../libft/libft.a)" ]
then
	make -C ../../libft;
fi
clang fork.c -lft -L ../../libft -I ../../libft/includes;
