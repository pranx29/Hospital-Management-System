#include "../include/inventory.h"

// Function to read inventory items from file to array
int readInventoryFromFile(InventoryItem inventory[])
{
    FILE *file = fopen(INVENTORY_FILE_PATH, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int itemCount = 0;
    while (fscanf(file, "%d,%[^,],%u,%[^,],%[^,],%d,%d,%[^\n]\n",
                  &inventory[itemCount].itemId, inventory[itemCount].itemName,
                  &inventory[itemCount].category, inventory[itemCount].description,
                  inventory[itemCount].manufacturer, &inventory[itemCount].quantity,
                  &inventory[itemCount].reorderLevel, inventory[itemCount].expiryDate) == 8)
    {
        itemCount++;
        if (itemCount >= MAX_ITEMS)
        {
            printf("Maximum item limit reached. Increase MAX_ITEMS if needed.\n");
            break;
        }
    }

    fclose(file);
    return itemCount;
}

// Function to save inventory items from array to file
int saveInventoryToFile(InventoryItem inventory[], int itemCount)
{
    FILE *file = fopen(INVENTORY_FILE_PATH, "w");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    for (int i = 0; i < itemCount; i++)
    {
        fprintf(file, "%d,%s,%d,%s,%s,%d,%d,%s\n",
                inventory[i].itemId, inventory[i].itemName, inventory[i].category,
                inventory[i].description, inventory[i].manufacturer,
                inventory[i].quantity, inventory[i].reorderLevel, inventory[i].expiryDate);
    }

    fclose(file);
    return 1;
}

// Function to search for an item by ID
InventoryItem *searchItemById(int itemId)
{
    static InventoryItem inventory[MAX_ITEMS]; // Static array to hold inventory data
    int itemCount = readInventoryFromFile(inventory);

    for (int i = 0; i < itemCount; i++)
    {
        if (inventory[i].itemId == itemId)
        {
            return &inventory[i];
        }
    }
    return NULL; // Return NULL if item with given ID is not found
}

// Function to get valid category from user input
enum ItemCategory getCategory()
{
    int category;
    printf("Enter Category (0 for Medication, 1 for Medical Supplies, 2 for Medical Equipment): ");
    scanf("%d", &category);

    while (category < 0 || category > 2)
    {
        printf("Invalid category. Please enter a valid category: ");
        scanf("%d", &category);
    }

    return (enum ItemCategory)category;
}
// Function to get new item data from user input
void getItemData(InventoryItem *item)
{
    strcpy(item->itemName, getText("Item Name", MAX_NAME_LENGTH));
    item->category = getCategory();
    strcpy(item->description, getText("Description", MAX_DESCRIPTION_LENGTH));
    strcpy(item->manufacturer, getText("Manufacturer", MAX_NAME_LENGTH));
    item->quantity = getNumber("Quantity");
    item->reorderLevel = getNumber("Reorder Level");
    strcpy(item->expiryDate, getDate("Expiry Date (YYYY-MM-DD)"));
}

// Function to add a new item
int addItem(InventoryItem *newItem)
{
    InventoryItem inventory[MAX_ITEMS];
    int itemCount = readInventoryFromFile(inventory);

    if (itemCount >= MAX_ITEMS)
    {
        printf("Maximum item limit reached. Cannot add more items.\n");
        return 0;
    }

    newItem->itemId = itemCount + 1;
    inventory[itemCount] = *newItem;
    itemCount++;

    if (saveInventoryToFile(inventory, itemCount) == 0)
    {
        printf("Error saving item to file.\n");
        return 0;
    }
    else
    {
        return 1;
    }
}
// Function to enum to string
const char *getCategoryName(enum ItemCategory category)
{
    switch (category)
    {
    case Medication:
        return "Medication";
    case MedicalSupplies:
        return "Medical Supplies";
    case MedicalEquipment:
        return "Medical Equipment";
    default:
        return "Unknown";
    }
}

// Function to view inventory
void viewInventory()
{
    InventoryItem inventoryItems[MAX_ITEMS];
    int inventoryItemCount = readInventoryFromFile(inventoryItems);

    printf("\n---------------- Inventory ---------------\n");
    printf("Total Items: %d\n\n", inventoryItemCount);

    if (inventoryItemCount == 0)
    {
        printf("No items in inventory.\n");
        return;
    }

    printf("ID\tCategory\tDescription\tManufacturer\tQuantity\tReorder Level\tExpiry Date\n");
    for (int i = 0; i < inventoryItemCount; i++)
    {
        printf("%d\t%s\t%s\t%s\t%d\t%d\t%s\n", inventoryItems[i].itemId, getCategoryName(inventoryItems[i].category), inventoryItems[i].description, inventoryItems[i].manufacturer, inventoryItems[i].quantity, inventoryItems[i].reorderLevel, inventoryItems[i].expiryDate);
    }
}
void searchInventory()
{
    printf("\n---------------- Search Inventory ---------------\n");

    int itemId;

    char choice;
    do
    {
        printf("Enter item ID: ");
        scanf("%d", &itemId);
        InventoryItem *item = searchItemById(itemId);
        if (item == NULL)
        {
            printf("Item not found in inventory.\n");
        }
        else
        {
            printf("\n---------------- Item Details ---------------\n");
            printf("ID: %d\n", item->itemId);
            printf("Name: %s\n", item->itemName);
            printf("Category: %s\n", getCategoryName(item->category));
            printf("Description: %s\n", item->description);
            printf("Manufacturer: %s\n", item->manufacturer);
            printf("Quantity: %d\n", item->quantity);
            printf("Reorder Level: %d\n", item->reorderLevel);
            printf("Expiry Date: %s\n", item->expiryDate);
        }
        printf("Do you want to search for another item? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');
}

void updateInventory(){
    InventoryItem inventoryItems[MAX_ITEMS];
    int inventoryCount = readInventoryFromFile(inventoryItems);

    if(inventoryCount == 0){
        printf("No items in inventory.\n");
        return;
    }

    int itemId;
    itemId = getNumber("Item ID");

    InventoryItem *item = searchItemById(itemId);

    printf("Current Item Details\n");
    printf("ID\tName\tQuantity\tReorder Level\tExpiry Date\n");
    printf("%d\t%s\t%d\t\t%d\t%s\n", item->itemId, item->itemName, item->quantity, item->reorderLevel, item->expiryDate);

    printf("Update item:\n");
    for (int i = 0; i < inventoryCount; i++){
        if(inventoryItems[i].itemId == itemId){
            inventoryItems[i].quantity = getNumber("Quantity");
            strcpy(inventoryItems[i].expiryDate, getDate("Expiry Date (YYYY-MM-DD)"));
        }
    }

    if(saveInventoryToFile(inventoryItems, inventoryCount) == 0){
        printf("Error saving item to file.\n");
    }
    else{
        printf("Item updated successfully.\n");
    }
}