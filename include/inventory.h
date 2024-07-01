#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define MAX_DESCRIPTION_LENGTH 200


enum ItemCategory {
    Medication,
    MedicalSupplies,
    MedicalEquipment
} ;

#define MAX_ITEMS 100  
#define INVENTORY_FILE_PATH "data/inventories.csv"  

typedef struct {
    int itemId;
    char itemName[MAX_NAME_LENGTH];
    enum ItemCategory category;
    char description[MAX_DESCRIPTION_LENGTH];
    char manufacturer[MAX_NAME_LENGTH];
    int quantity;
    int reorderLevel;
    char expiryDate[MAX_DATE_LENGTH];  
} InventoryItem;

// Function prototypes
int readInventoryFromFile(InventoryItem inventory[]);
int saveInventoryToFile(InventoryItem inventory[], int itemCount);
InventoryItem *searchItemById(int itemId);
void getItemData(InventoryItem *item);
int addItem(InventoryItem *newItem);
const char *getCategoryName(enum ItemCategory category);
void viewInventory();
void searchInventory();
void updateInventory();
#endif /* INVENTORY_H */
