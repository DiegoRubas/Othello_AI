#!/bin/bash
make
./projet 8 c 1 1 & ./projet 8 c 1 2 & ./projet 8 c 1 3 & ./projet 8 c 2 2 & ./projet 8 c 2 3
./projet 8 c 3 3 & ./projet 8 c 1 4 & ./projet 8 c 2 4 & ./projet 8 c 3 4

./projet 8 c 4 4 & ./projet 8 c 1 5 &  ./projet 8 c 2 5 &  ./projet 8 c 3 5 &  ./projet 8 c 4 5 &  ./projet 8 c 5 5 


./projet 8 c 1 6 & ./projet 8 c 2 6 & ./projet 8 c 3 6
./projet 8 c 4 6 & ./projet 8 c 5 6 & ./projet 8 c 6 6