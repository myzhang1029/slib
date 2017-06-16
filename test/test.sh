#!/bin/bash
# A shell script for testing all these codes by
# running programs in test directory.
if ! [ `./test-colorprintf` == '[31m[43mred[0m[32m[40mgreen[0m' ]; then
	printf '\033[31;1mError in colorprintf\033[0m'
	exit 1
fi

