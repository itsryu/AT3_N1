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
	char status[11];
	Guest guest[4];
	int guestSize;
} Room;

static void configEnviroment();
static void clearScreen();
static void readFile(FILE* file, Room* room, int* num);
static void saveFile(FILE* file, Room* room);
static void showRooms(Room* room, int num);