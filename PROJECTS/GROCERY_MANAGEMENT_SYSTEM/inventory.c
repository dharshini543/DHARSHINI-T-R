#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inventory.h"
#include "enum.h"
#include "inventory_FO.h"
#include <ctype.h>
#include <stdbool.h>


int isDigits(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
            return 0;
    }
    return 1;
}

int validateDate(const char *date)
{
    if (strlen(date) != 10)
        return 0;

    if (date[4] != '-' || date[7] != '-')
        return 0;

    char year[5], month[3], day[3];
    strncpy(year, date, 4);
    year[4] = '\0';
    strncpy(month, date + 5, 2);
    month[2] = '\0';
    strncpy(day, date + 8, 2);
    day[2] = '\0';

    if (!isDigits(year) || !isDigits(month) || !isDigits(day))
        return 0;

    int y = atoi(year), m = atoi(month), d = atoi(day);

    if (m < 1 || m > 12 || d < 1 || d > 31)
        return 0;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2)
    {
        int isLeap = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
        if (d > (isLeap ? 29 : 28))
            return 0;
    }
    else if (d > daysInMonth[m - 1])
        return 0;

    return 1;
}


int addItemToInventory(Inventory *inventory)
{
    int choice = 1;
    InventoryItem *temp = inventory->head;

    while(choice)
    {
        InventoryItem *newitem = (InventoryItem*)malloc(sizeof(InventoryItem));
        if (!newitem)
        {
            printf("Memory allocation failed.\n");
            return Failure;
        }
        else
        {
            newitem->itemID = inventory->itemCount+1;

            printf("Item name: ");
            while (true)
            {
                scanf(" %[^\n]", newitem->name);
                if (strlen(newitem->name) > 0 && strlen(newitem->name) < 50)
                    break;
                printf("Invalid name. Please enter a non-empty name (max 50 characters): ");
            }

            printf("Item Brand: ");
            while (true)
            {
                scanf(" %[^\n]", newitem->brand);
                if (strlen(newitem->brand) > 0 && strlen(newitem->brand) < 50)
                    break;
                printf("Invalid brand. Please enter a non-empty brand (max 50 characters): ");
            }

            printf("Item Department: ");
            while (true)
            {
                scanf(" %[^\n]", newitem->department);
                if (strlen(newitem->department) > 0 && strlen(newitem->department) < 50)
                    break;
                printf("Invalid department. Please enter a non-empty department (max 50 characters): ");
            }

            printf("Item Expiry Date (YYYY-MM-DD): ");
            while (true)
            {
                scanf("%s", newitem->expiryDate);
                if (validateDate(newitem->expiryDate))
                    break;
                printf("Invalid date format. Please enter a valid date (YYYY-MM-DD): ");
            }

            printf("Item price: ");
            while (true)
            {
                if (scanf("%f", &newitem->price) == 1 && newitem->price > 0)
                {
                    break;
                }
                else
                {
                    printf("Invalid price. Please enter a positive number: ");
                    while (getchar() != '\n');
                }
            }

            printf("Item Quantity: ");
            while (true)
            {
                if (scanf("%f", &newitem->quantity) == 1 && newitem->quantity > 0)
                {
                    break;
                }
                else
                {
                    printf("Invalid quantity. Please enter a positive number: ");
                    while (getchar() != '\n');
                }
            }

            newitem->next = 0;

            if(inventory->head == 0 || strcmp(newitem->name,inventory->head->name) < 0)
            {
                newitem->next = inventory->head;
                inventory->head = newitem;
            }
            else
            {
                InventoryItem *temp = inventory->head;

                while(temp->next != 0 && strcmp(temp->next->name ,newitem->name) < 0)
                {
                    temp = temp->next;
                }
                newitem->next = temp->next;
                temp->next = newitem;
            }
            inventory->itemCount++;
            printf("Item Added\n");
            addInventoryItemToFile(inventory, *newitem);
        }
        printf("Want to continue...press 1\n");
        scanf("%d",&choice);
    }

    return Success;
}


int deleteItemFromInventory(Inventory *inventory, int itemID)
{

    InventoryItem *current = inventory->head;
    InventoryItem *prev = NULL;

    if (!current)
    {
        printf("Inventory is Empty\n");
        return Failure;
    }
    else if(inventory->head->itemID == itemID)
    {
        InventoryItem *temp = inventory->head->next;
        printf("%d\t%s\t\t%s\t\t%.2f\t\t%f\t\t%s\t\t%s\n", inventory->head->itemID, inventory->head->name, inventory->head->brand, inventory->head->price, inventory->head->quantity, inventory->head->department, inventory->head->expiryDate);
        free(inventory->head);
        inventory->head = temp;
        deleteInventoryItem(inventory, itemID);

        return Success;
    }
    else
    {
        while(current != 0 && current->itemID != itemID)
        {
            prev = current;
            current = current->next;
        }
        if(current == 0)
        {
            printf("Item with ID %d not exists\n",itemID);
            return Failure;
        }
        else
        {
            prev->next = current->next;
            printf("%d\t%s\t\t%s\t\t%.2f\t\t%f\t\t%s\t\t%s\n", current->itemID, current->name, current->brand, current->price, current->quantity, current->department, current->expiryDate);
            free(current);
            deleteInventoryItem(inventory, itemID);
            return Success;
        }
    }
}


int updateItemDetails(Inventory *inventory, int itemID)
{
    int field;
    char newName[50];
    char newBrand[50];
    char newDepartment[30];
    char newExpiryDate[30];
    float newPrice;
    float newQuantity;

    InventoryItem *temp = inventory->head;
    if (!temp)
    {
        printf("No Item in inventory. Please add.\n");
        return Failure;
    }
    else
    {
        while (temp != NULL && temp->itemID != itemID)
        {
            temp = temp->next;
        }
        if (temp == NULL)
        {
            printf("Item not found with the given item Id.\n");
            return Failure ;
        }
        else
        {
            printf("Enter new details for the item\n");
            printf("Enter\n1.Update Name\n2.Update Brand\n3.Update Department\n4.Update Expiry Date\n5.Update Price\n6.Update Quantity\n\n");
            scanf("%d", &field);

            switch (field)
            {
            case Name:
                printf("Item name: ");
                while (1)
                {
                    scanf(" %[^\n]", newName);
                    if (strlen(newName) > 0 && strlen(newName) < 50)
                        break;
                    printf("Invalid name. Please enter a non-empty name (max 50 characters): ");
                }
                strcpy(temp->name,newName);
                updateInventoryItemField(inventory, itemID, Name, newName, temp);
                break;
            case Brand:
                printf("Item Brand: ");
                while (1)
                {
                    scanf(" %[^\n]", newBrand);
                    if (strlen(newBrand) > 0 && strlen(newBrand) < 50)
                        break;
                    printf("Invalid brand. Please enter a non-empty brand (max 50 characters): ");
                }
                strcpy(temp->brand,newBrand);
                updateInventoryItemField(inventory, itemID, Brand, newBrand, temp);
                break;
            case Department:
                printf("Item Department: ");
                while (1)
                {
                    scanf(" %[^\n]", newDepartment);
                    if (strlen(newDepartment) > 0 && strlen(newDepartment) < 50)
                        break;
                    printf("Invalid department. Please enter a non-empty department (max 50 characters): ");
                }
                strcpy(temp->department,newDepartment);
                updateInventoryItemField(inventory, itemID, Department, newDepartment, temp);
                break;
            case ExpiryDate:
                printf("Item Expiry Date (YYYY-MM-DD): ");
                while (1)
                {
                    scanf("%s", newExpiryDate);
                    if (validateDate(newExpiryDate))
                        break;
                    printf("Invalid date format. Please enter a valid date (YYYY-MM-DD): ");
                }

                strcpy(temp->expiryDate,newExpiryDate);
                updateInventoryItemField(inventory, itemID, ExpiryDate, newExpiryDate, temp);
                break;
            case Price:
                printf("Item price: ");
                while (1)
                {
                    if (scanf("%f", &newPrice) == 1 && newPrice > 0)
                        break;
                    else
                    {
                        printf("Invalid price. Please enter a positive number: ");
                        while (getchar() != '\n');
                    }
                }
                temp->price = newPrice;
                updateInventoryItemField(inventory, itemID, Price, &newPrice, temp);
                break;
            case Quantity:
                printf("Item Quantity: ");
                while (1)
                {
                    if (scanf("%f", &newQuantity) == 1 && newQuantity > 0)
                        break;
                    else
                    {
                        printf("Invalid quantity. Please enter a positive number: ");
                        while (getchar() != '\n');
                    }
                }

                temp->quantity = newQuantity;
                updateInventoryItemField(inventory, itemID, Quantity, &newQuantity, temp);
                break;

            default:
                printf("Enter a valid option\n");
                return Failure;
            }

            return Success;
        }
    }
}


void displayInventorySummary(const Inventory *inventory)
{
    if(inventory->head == 0)
    {
        printf("Inventory is empty\n");
    }
    else
    {
        InventoryItem* temp = inventory->head;
        printf("Inventory Summary:\n");
        printf("------------------------------------------------------------------------------------------------------------------\n");
        printf("ID\tName\t\t\tBrand\t\t\tDepartment\t\tExpiry Date\tPrice\tQuantity\n");
        printf("------------------------------------------------------------------------------------------------------------------\n");
        while(temp != 0)
        {
            if(temp->itemID > 0)
            {
                printf("%d\t%-20s\t%-20s\t%-20s\t%-15s\t%.2f\t%.2f\n",
                       temp->itemID,
                       temp->name,
                       temp->brand,
                       temp->department,
                       temp->expiryDate,
                       temp->price,
                       temp->quantity);
            }
            temp = temp->next;
        }
    }
}


void displayDeletedItems(const Inventory *inventory)
{
    int deletedItemCount = 0;
    InventoryItem *temp = inventory->head;

    while (temp != NULL)
    {
        if (temp->itemID < 0)
        {
            if(deletedItemCount == 0)
            {
                printf("Displaying deleted items:\n");
                printf("ItemNo\tName\t\tBrand\t\tDepartment\t\tExpiryDate\n");
            }
            printf("%d\t%s\t\t%s\t\t%s\t\t%s\n",++deletedItemCount, temp->name,temp->brand,temp->department,temp->expiryDate);
        }
        temp = temp->next;
    }

    if (deletedItemCount == 0)
    {
        printf("No deleted items to display.\n");
    }
    else
    {
        printf("Total deleted items: %d\n", deletedItemCount);
    }
}


int getInventoryItemByID(Inventory*inventory, int itemID)
{
    InventoryItem *temp = inventory->head;
    if(!temp)
    {
        printf("No Item in inventory. Please add.\n");
        return Failure ;
    }
    else
    {
        while(temp != 0 && temp->itemID != itemID)
        {
            temp = temp->next;
        }
        if(temp == 0)
        {
            printf("Item not found with the given item Id.\n");
            return Failure;
        }
        else
        {
            printf("%d\t%s\t\t%s\t\t%.2f\t\t%.2f\t\t%s\t\t%s\n", temp->itemID, temp->name, temp->brand, temp->price, temp->quantity, temp->department, temp->expiryDate);

            return Success;
        }
    }
}
