#ifndef Header1_h
#define Header1_h
#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable : 4996) // så att jag kan använda fopen utan errors
#define TOP 20
#define MAX 7
typedef struct {
	char ItemName[TOP] = {};
	char ItemWeight[TOP] = {};
	float ItemAmount = 0;
	float ItemWorth = 0;
} shoping;
typedef struct {
	shoping *Item;
	int AmountOfItems = 0;
}shopingList;
void RemoveItemFromList(shopingList *pToList, int *amount);
void ChangeAmountOfItem(shopingList *pToList, int *amount);
void clearReadBuffert();
void AddItemToList(shopingList *pToList, int *amount);
int PrintList(shopingList *pToList, int *amount);
void SaveCurrentList(shopingList *pToList, int *amount);
void LoadListFromFile(shopingList *pToList, int *amount);
float InputErrorCheck(float Input, int Index);
int CheckInputLoadList(int Input);
void SaveEndOfProgram(shopingList *pToList, int *amount);

#endif