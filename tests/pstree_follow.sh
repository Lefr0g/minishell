#!/bin/bash

os=`uname -s`
while [ 1 ]
do
	pid=`pidof minishell`
	clear
	if [ -z "$pid" ]
	then
		echo -n "No minishell running "
	else
		if [ $os = "Darwin" ]
		then
			output=`pstree $pid`
		else
			output=`pstree -cpg $pid`
		fi
		if [ -z "$output" ]
		then
			pid=""
		fi
		echo "$output"
		if [ $os != "Darwin" ]
		then
			echo -e "\nprocess(pid,gpid)"
		fi
	fi
	sleep 1
done
