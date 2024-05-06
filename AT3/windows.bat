@echo off

gcc ./functions/functions.c ./functions/menu.c ./main.c -o main.exe

if %errorlevel% equ 0 (
	cls
	main.exe
) else (
	cls
	echo Erro ao compilar o programa, tente compilar utilizando este comando: gcc ./functions/functions.c ./functions/menu.c ./main.c -o main.exe
)

pause