#!/bin/bash

../asm -d . ../resources/champs/examples/zork.s
echo

../corewar $1 zork.cor
echo
../corewar zork.cor $1
echo

../corewar $1 zork.cor zork.cor
echo
../corewar zork.cor $1 zork.cor
echo
../corewar zork.cor zork.cor $1
echo

../corewar $1 zork.cor zork.cor zork.cor
echo
../corewar zork.cor $1 zork.cor zork.cor
echo
../corewar zork.cor zork.cor $1 zork.cor
echo
../corewar zork.cor zork.cor zork.cor $1

rm -f zork.cor
