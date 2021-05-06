// shoppinglist.cpp : Defines the entry point for the console application.
//
//Oskar Berglund, obd16004, DVA117, block 2 Shoppinglista

#include "stdafx.h"
#include "inkopslista.h"


int main()
{
	int choice = 0;
	int *amount;

	shopingList *pToList;
	pToList = (shopingList*)calloc(1, sizeof(shopingList));
	amount = &pToList->AmountOfItems;
	pToList->Item = (shoping*)calloc(1, sizeof(shoping));

	do {

		printf("\nEnter 1 To add an item to the list.\nEnter 2 To read the current list.\nEnter 3 to remove an item from the list.\nEnter 4 to change amount of an item.\nEnter 5 to save list to file.\nEnter 6 to load list.\nEnter 7 to exit.\n");
		printf("\nMake your choice:");
		scanf_s("%d", &choice);
		while (isalpha(choice) != 0) {
			printf("Please enter a number:");
			scanf_s("%d", &choice);
		}
		switch (choice) {
		case 1: AddItemToList(pToList, amount);
			break;
		case 2:PrintList(pToList, amount);
			break;
		case 3: RemoveItemFromList(pToList, amount); break;
		case 4: ChangeAmountOfItem(pToList, amount); break;
		case 5: SaveCurrentList(pToList, amount); break;
		case 6: LoadListFromFile(pToList, amount); break;
		case 7: SaveEndOfProgram(pToList, amount); break;
		default:printf("There is only %d options\n\n", MAX);  break;
		}

	} while (choice != MAX);
	free(pToList);
	printf("Good bye\n");
	return 0;
}