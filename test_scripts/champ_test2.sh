#!/bin/bash

../corewar $1 $2
echo
../corewar $2 $1
echo

../corewar $1 $2 $2
echo
../corewar $2 $1 $2
echo
../corewar $2 $2 $1
echo

../corewar $1 $2 $2 $2
echo
../corewar $2 $1 $2 $2
echo
../corewar $2 $2 $1 $2
echo
../corewar $2 $2 $2 $1
