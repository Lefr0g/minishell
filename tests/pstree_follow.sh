#!/bin/bash

pid=`pidof minishell`
while [ 1 ]
do
	clear
	if [ -z $pid ]
	then
		echo "No minishell running"
		pid=`pidof minishell`
	else
		output=`pstree -cpg $pid`
		if [ -z $output ]
		then
			pid=""
		fi
		echo "$output"
		echo -e "\nprocess(pid,gpid)"
	fi
	sleep 1
done
