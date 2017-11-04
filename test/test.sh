#!/bin/bash
# A shell script for testing all these codes by
# running programs in test directory.

./test-colorprintf
read -p 'Type 1 if you saw a red string on yellow and a green string on black. Type 0 otherwise.'
if [ "$REPLY" == "0" ];
then	
	printf '\033[31;1mError in colorprintf\033[0m\n'
	exit 1
fi

