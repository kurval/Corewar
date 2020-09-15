#!/bin/bash

echo "RUNNING OUTPUT TEST 1 (BROKEN COR FILES)"
echo ""
sleep 0.5
./cw_test_folder.sh --test error_cors

read -p "TEST 1 DONE - PRESS ENTER TO CONTINUE"

echo "RUNNING OUTPUT TEST 2 (ALL RESOURCE CORS (NOT SUPER SLOW ONES))"
echo ""
sleep 0.5
./cw_test_folder.sh --test cor_files

read -p "TEST 2 DONE - PRESS ENTER TO CONTINUE"

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