//
// Created by 11534 on 2025/3/9.
//
#include "graphics.h"
#include "conio.h"
#include "Storage.h"
#include <chrono>
#include <ctime>

#ifndef MONEY_MANAGE_WINOUT_H
#define MONEY_MANAGE_WINOUT_H

void creatOutputScreen(Storage&);

int getCurrentMonth();

int getFirstDay();

void interact(Storage&);

void fillNumber(int, int, int, Storage&);

bool creatDailyScreen(Storage&);

void fillEveryDay(int ,Storage&);

void creatTitle(char);

#endif //MONEY_MANAGE_WINOUT_H
