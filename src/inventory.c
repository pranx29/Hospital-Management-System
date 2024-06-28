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
    strcpy(item->expiryDate, getDate());
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
