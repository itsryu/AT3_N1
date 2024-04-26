#pragma once

#include "stdio.h"

#define FILE_PATH "guests.csv"
#define LENGTH 100
#define ROOMS 50

typedef struct {
	char name[LENGTH];
} Guest;

typedef struct {
	int number;
	Guest *guest;
	int status;
} Room;

static void configEnviroment();
static void clearScreen();
static void readFile(FILE* file);