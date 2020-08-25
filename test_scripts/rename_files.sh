#!/bin/bash

FOLDER=$1

FILES=$FOLDER/*
TEST_NBR=1

for f in $FILES
do
	mv $f $FOLDER/test$TEST_NBR.cor
	TEST_NBR=$(( TEST_NBR + 1 ))
done