#!/bin/bash
./cw_test.sh --test cor_files/jinx.cor cor_files/dubo.cor cor_files/big_feet.cor cor_files/overwatch.cor
read -p "PRESS ENTER TO CONTINUE"
./cw_test.sh --dump 1 cor_files/jinx.cor cor_files/dubo.cor cor_files/big_feet.cor cor_files/overwatch.cor
read -p "PRESS ENTER TO CONTINUE"

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

./cw_test.sh --test cor_files/ex.cor cor_files/turtle.cor cor_files/helltrain.cor cor_files/fluttershy.cor
read -p "PRESS ENTER TO CONTINUE"
./cw_test.sh --dump 17030 cor_files/ex.cor cor_files/turtle.cor cor_files/helltrain.cor cor_files/fluttershy.cor
read -p "PRESS ENTER TO CONTINUE"

./cw_test.sh --test cor_files/turtle.cor cor_files/helltrain.cor cor_files/fluttershy.cor
read -p "PRESS ENTER TO CONTINUE"
./cw_test.sh --dump 10000 cor_files/turtle.cor cor_files/helltrain.cor cor_files/fluttershy.cor
read -p "PRESS ENTER TO CONTINUE"

./cw_test.sh --test cor_files/turtle.cor cor_files/fluttershy.cor
read -p "PRESS ENTER TO CONTINUE"
./cw_test.sh --dump 12000 cor_files/turtle.cor cor_files/fluttershy.cor
read -p "PRESS ENTER TO CONTINUE"