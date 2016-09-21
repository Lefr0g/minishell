#!/bin/bash

pid=`pidof minishell`
os=`uname -s`
while [ 1 ]
do
	clear
	if [ -z $pid ]
	then
		echo "No minishell running"
		pid=`pidof minishell`
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
