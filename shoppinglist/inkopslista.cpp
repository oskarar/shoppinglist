#include "stdafx.h"
#include "inkopslista.h"

void AddItemToList(shopingList *pToList, int *amount) {
	shoping *TempMemory = (shoping*)realloc(pToList->Item, ((*amount) + 1) * sizeof(shoping));
	if (TempMemory != NULL) {
		pToList->Item = TempMemory;
		clearReadBuffert();
		do {
			printf("Write a product name: ");
			gets_s(pToList->Item[*amount].ItemName, TOP);
		} while (pToList->Item[*amount].ItemName[0] == '\0');
		do {
			printf("\nProduct unit:");
			gets_s(pToList->Item[*amount].ItemWeight, TOP);
		} while (pToList->Item[*amount].ItemWeight[0] == '\0');
		printf("\nProduct amount:");
		scanf_s("%f", &pToList->Item[*amount].ItemAmount);
		clearReadBuffert();
		while ((pToList->Item[*amount].ItemAmount) <= 0) {
			printf("\nplease write a positive number:");
			scanf_s("%f", &pToList->Item[*amount].ItemAmount);
			clearReadBuffert();
		}
		printf("\nProduct cost in KR:");     // Redovisnings uppgiften för block 2. Lägger till en kostnad på varorna.
		scanf_s("%f", &pToList->Item[*amount].ItemWorth);
		clearReadBuffert();
		while ((pToList->Item[*amount].ItemWorth) <= 0) {
			printf("\nplease write a positive number:");
			scanf_s("%f", &pToList->Item[*amount].ItemWorth);
			clearReadBuffert();
		}
		*amount = *amount + 1;
	}
	else
		printf("Error in AddItemToList funktion");
}
int PrintList(shopingList *pToList, int *amount) {
	int WhatItem = 0, i = 1;
	if (pToList->AmountOfItems == 0) {
		printf("\nYour list is currently empty\n\n");
		return 0;// använder värdet i andra funktioner för att kolla om listan är tom eller inte 
	}
	printf("       Name\t\tamount\t\ttype\t\tCost\n\n");
	for (WhatItem = 0; WhatItem < *amount; WhatItem++) {

		printf("Item %d:%-10s\t%-10.1f\t%-10s\t%-10.1fKR\n\n", i++, (pToList)->Item[WhatItem].ItemName, (pToList)->Item[WhatItem].ItemAmount, (pToList)->Item[WhatItem].ItemWeight, (pToList)->Item[WhatItem].ItemWorth);

	}
	return 1;
}
void clearReadBuffert()
{
	while (getchar() != '\n');
}
void ChangeAmountOfItem(shopingList *pToList, int *amount) {
	int ItemChange = 0;
	if (PrintList(pToList, amount) == 0) {
		printf("Please write something in you list first\n");
		return;
	}// felhantering
	printf("\nWrite the number of the product you want to change:");
	scanf_s("%d", &ItemChange);
	clearReadBuffert();
	ItemChange = InputErrorCheck(ItemChange, *amount);
	float *AmountChange = &pToList->Item[--ItemChange].ItemAmount; // skapar en pekare som pekar på varan om ska ändras
	printf("The item you will change is:%s\n", pToList->Item[ItemChange].ItemName);
	printf("\nHow much do you want to buy:");
	scanf_s("%f", AmountChange);// updaterar värdet som pekaren pekar på 
	clearReadBuffert();
	//felhantering
	return;
}
void RemoveItemFromList(shopingList *pToList, int *amount) {
	int removeItem = 0, numberOfItems = pToList->AmountOfItems;
	if (PrintList(pToList, amount) == 0) {
		printf("\nReturning to main menu\n");
		return;
	}// kollar om det finns något i listan

	printf("Write the number of the product you want to remove:");
	scanf_s("%d", &removeItem);
	removeItem = InputErrorCheck(removeItem, *amount); // felhantering

	if (removeItem >= 0) {
		removeItem -= 1; // så man hamnar på rätt plats i indexen

		if (removeItem != (numberOfItems - 1)) {// if satsen kollar om man vill ta bort någon annan vara än den sista

			strcpy_s(pToList->Item[removeItem].ItemName, pToList->Item[numberOfItems - 1].ItemName);
			strcpy_s(pToList->Item[removeItem].ItemWeight, pToList->Item[numberOfItems - 1].ItemWeight);
			pToList->Item[removeItem].ItemAmount = pToList->Item[numberOfItems - 1].ItemAmount;
			pToList->AmountOfItems--;
			numberOfItems--;
			shoping *tempPekare = (shoping*)realloc(pToList->Item, numberOfItems * sizeof(shoping));

			if (tempPekare != NULL) {// realocerar minnet så man tar bort den sista eftersom listan minskar med en
				pToList->Item = tempPekare;
			}	//felhantering
			else {
				printf("error in RemoveItem funktion");
				return;
			}
		}
		else {// denna funktion går man in i om det är den sista varan som man vill ta bort.

			numberOfItems--;
			pToList->AmountOfItems--;
			if (numberOfItems == 0) {
				pToList = (shopingList*)calloc(1, sizeof(shopingList));
				shoping *tempPekare = (shoping*)realloc(pToList->Item, 1 * sizeof(shoping));
				if (tempPekare == NULL) {
					printf("error in RemoveItem funktion");
				}
			}
			else {
				shoping *tempPekare = (shoping*)realloc(pToList->Item, numberOfItems * sizeof(shoping));
				if (tempPekare != NULL) {
					pToList->Item = tempPekare;
				}
			}
		}
	}
}
void SaveCurrentList(shopingList *pToList, int *amount) {
	if (*amount == 0) {
		printf("There is nothing to save. Exiting to main menu\n\n");
		return;
	} // felhantering om det inte finns något att spara

	char FileName[TOP] = {}; // tar in ett namn på filen som användaren bestämer
	FILE *FilePointerSave;
	int Products = *amount;
	if (pToList == NULL) {
		printf("error in SaveCurrentList funktion");
		return;
	}
	printf("Please name the file you will save to:");
	scanf_s("%s", &FileName, TOP, stdin);
	clearReadBuffert();

	FilePointerSave = fopen(FileName, "wb");
	if (FilePointerSave == NULL) {
		printf("error in SaveCurrentList funktion.");
		return;
	}
	fwrite(&Products, sizeof(int), 1, FilePointerSave); // skriver in hur många saker som ska sparas
	fwrite(pToList->Item, sizeof(shoping), Products, FilePointerSave); // sparar alla saker i listan

	fclose(FilePointerSave);

}
void LoadListFromFile(shopingList *pToList, int *amount) {
	char choice = {};
	if (*amount > 0) {
		if (CheckInputLoadList(choice) == 1) {
			SaveCurrentList(pToList, amount);
		}
	}
	FILE *FilePointerLoad = NULL;
	int Products;
	char FileName[TOP] = {};
	printf("\nPlease write the name of the file you want to load: ");
	scanf_s("%s", &FileName, TOP, stdin);
	FilePointerLoad = fopen(FileName, "rb");
	if (FilePointerLoad == NULL) {
		printf("ERROR. Could not find that file.\nReturning to main menu\n");
		return;
	}
	printf("Loading file...\n\n");
	fread(&Products, sizeof(int), 1, FilePointerLoad); // läser in hur många saker som finns i listan

	*amount = Products; // säter amount till så många saker som finns i listan
	shoping *TempMemory = (shoping*)realloc(pToList->Item, sizeof(shoping)*Products);
	if (TempMemory == NULL) {
		printf("Error in Loadfile funktion");
		return;
	}
	else {
		pToList->Item = TempMemory;
		fread(pToList->Item, sizeof(shoping), Products, FilePointerLoad);// läser in listan
	}
	fclose(FilePointerLoad);
}
int CheckInputLoadList(int Input) {
	printf("Do you wish to save your current file first. 1=YES  0=NO.\n");
	scanf_s("%d", &Input);
	clearReadBuffert();
	while (Input != 1 && Input != 0) {
		printf("that was not an option please write 1/0\n");
		scanf_s("%d", &Input);
		clearReadBuffert();
	}
	if (Input == 1) {
		printf("Saving you list");
		return 1;
	}
	else if (Input == 0) {
		return 0;
	}
	return 0;
}
void SaveEndOfProgram(shopingList *pToList, int *amount) {
	int Choice ;
	if (*amount > 0) {
		printf("Do you wish to save you current list before exiting?\n1=YES 0=NO\n");
		scanf_s("%d", &Choice);
		clearReadBuffert();
		while (Choice > 1 || Choice<0) {

			Choice = InputErrorCheck(Choice, *amount);
		}
	}
	if (Choice == 1) {
		SaveCurrentList(pToList, amount);
		printf("\n\nSaving complete. Exiting program...\n\n");
		return;
	}
	else {

		printf("\n\nexiting your program...\n\n");
		return;
	}


}
float InputErrorCheck(float Input, int Index) {

	while (Input <= 0 || isdigit(Input) || Input > Index) {
		printf("Your input was not correct.\nTry again:");
		scanf_s("%f", &Input);
		clearReadBuffert();
	}

	return Input;
}