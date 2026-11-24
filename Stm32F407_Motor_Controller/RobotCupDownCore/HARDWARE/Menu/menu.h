#ifndef _MENU_H
#define _MENU_H
#include "system.h"

typedef struct
{
	u8 YM;
	u8 QD;
	u8 NEXT;
	u8 FH;
	void (*HS)(void);
}Menu_table ;

void menu();
void TASK1();
void TASK2();
void TASK3();
void TASK4();
void TASK5();
void TASK6();
void TASK7();
void TASK8();
void TASK9();
void TASK10();
void TASK11();
void TASK12();

void MASK1();
void MASK2();
void MASK3();
void MASK4();
void MASK5();
void MASK6();
void MASK7();
void MASK8();
void MASK9();
void MASK10();
void MASK11();
void MASK12();

#endif