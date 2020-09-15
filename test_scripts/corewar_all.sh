#!/bin/bash
./cw_test.sh --test cor_files/Wall.cor cor_files/Eraser.cor cor_files/mortel.cor cor_files/NoIdea.cor
read -p "PRESS ENTER TO CONTINUE"
./cw_test.sh --dump 1000 cor_files/Wall.cor cor_files/Eraser.cor cor_files/mortel.cor cor_files/NoIdea.cor
read -p "PRESS ENTER TO CONTINUE"

./cw_test.sh --test cor_files/Wall.cor cor_files/Eraser.cor cor_files/mortel.cor cor_files/NoIdea.cor
read -p "PRESS ENTER TO CONTINUE"
./cw_test.sh --dump 1000 cor_files/Wall.cor cor_files/Eraser.cor cor_files/mortel.cor cor_files/NoIdea.cor
read -p "PRESS ENTER TO CONTINUE"

./cw_test.sh --test cor_files/Rainbow_dash.cor cor_files/_.cor
read -p "PRESS ENTER TO CONTINUE"
./cw_test.sh --dump 1000 cor_files/Rainbow_dash.cor cor_files/_.cor
read -p "PRESS ENTER TO CONTINUE"