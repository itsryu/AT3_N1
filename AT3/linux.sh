#!/bin/bash

gcc ./functions/functions.c ./functions/menu.c ./main.c -o main

if [ $? -eq 0 ]; then
    clear
    ./main
else
    clear
    echo "Erro ao compilar o programa. Tente compilar utilizando o seguinte comando:"
    echo "gcc ./functions/functions.c ./functions/menu.c ./main.c -o main"
fi

read -p "Pressione qualquer tecla para continuar..."