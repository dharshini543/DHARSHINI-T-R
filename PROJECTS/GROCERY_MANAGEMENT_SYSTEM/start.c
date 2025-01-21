#include <stdio.h>
#include<string.h>
#include <stdbool.h>
#include "user.h"
#include "inventory.h"
#include "cart.h"
#include "billing.h"
#include "report.h"
#include "billing.h"
#include "sales_report_FO.h"
#include "inventory_FO.h"
#include "enum.h"
#include "sorting.h"

int main_menu()
{
    Userlist userlist = {0};
    Inventory inventory = {0};
    Cart cart = {0};
    Report report = {0};
    float totalsales = 0;
    int choice = 0;
    int option = 0;
    int ID = 0;
    float quantity = 0;
    int success = 0;
    User *currentUser = NULL;
    int isTrue = 1;

    openUserFile();
    openInventoryFile();
    openSalesReportFile();

    loadUsersFromFile(&userlist);
    loadInventoryFromFile(&inventory);
    loadSalesReportFromFile(&report);

    if(userlist.userCount == 0)
    {
        addFirstAdminUser(&userlist);
    }

    printf("Welcome to the Grocery Management System!\n");
    int proceedToLogin = 1;
    while (currentUser == NULL)
    {

        printf("Press 1 to login. Any other number to Exit\n");
        scanf("%d", &proceedToLogin);

        if(proceedToLogin != 1)
        {
            break;
        }

        currentUser = loginUser(&userlist);
        if (currentUser == NULL)
        {
            printf("Login failed. Please try again.\n");
        }
        else
        {
            printf("Login successful. Welcome, %s!\n", currentUser->username);
        }

        while (currentUser != NULL)
        {
            if (currentUser->role == ROLE_ADMIN)
            {
                printf("Admin Menu:\n");
                printf("1. Add User\n");
                printf("2. Delete User\n");
                printf("3. Display Users\n");
                printf("4. Manage Inventory\n");
                printf("5. Manage Cart\n");
                printf("6. Billing\n");
                printf("7. View Reports\n");
                printf("8. Logout\n");

                printf("Enter your choice: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case  ADMIN_ADD_USER:

                    isTrue = 1;
                    char newUsername[MAX_USERNAME_LENGTH];
                    char username[MAX_USERNAME_LENGTH];
                    char newPassword[MAX_PASSWORD_LENGTH];
                    char password[MAX_PASSWORD_LENGTH];
                    int roleChoice;
                    int role;

                    while(true)
                    {

                        printf("Enter username: ");
                        if(scanf("%s", username) == 1 && strlen(username) < MAX_USERNAME_LENGTH)
                        {

                            strcpy(newUsername , username);
                            break;
                        }
                        else
                        {
                            printf("Invalid Username,Enter valid Username\n");
                        }
                    }

                    while(true)
                    {
                        printf("Enter Password: ");
                        if(scanf("%s", password) == 1 && strlen(password) < MAX_USERNAME_LENGTH)
                        {
                            strcpy(newPassword , password);
                            break;
                        }
                        else
                        {
                            printf("Invalid Password,Enter valid Password\n");
                        }
                    }
                    while(true)
                    {
                        printf("Enter role (1. Admin, 2. User): ");
                        scanf("%d", &role);

                        if(role == 1 || role == 2)
                        {
                            roleChoice = role;
                            break;
                        }
                        else
                        {
                            printf("Invalid Role,Enter 1 or 2\n");
                        }
                    }


                    addUser(&userlist, newUsername, newPassword, (roleChoice == 1) ? ROLE_ADMIN : ROLE_USER);
                    break;

                case  ADMIN_DELETE_USER:

                    char deleteUsername[MAX_USERNAME_LENGTH];
                    char userID[MAX_USERNAME_LENGTH];
                    while(true)
                    {
                        printf("Enter username to delete: ");
                        if(scanf("%s", userID) == 1 && strlen(password) < MAX_USERNAME_LENGTH)
                        {
                            strcpy(deleteUsername , userID);
                            break;
                        }
                        else
                        {
                            printf("Invalid Username,Enter valid username\n");
                        }
                    }
                    deleteUser(&userlist, deleteUsername);
                    break;

                case ADMIN_DISPLAY_USERS:
                    displayUsers(&userlist);
                    break;

                case  ADMIN_INVENTORY_MANAGEMENT:
                    isTrue = 1;
                    while(isTrue)
                    {
                        printf("Enter\n"
                               "1.Add Item to Inventory\n"
                               "2.Delete Item from Inventory\n"
                               "3.Update Inventory Item Details\n"
                               "4.Display Inventory summary\n"
                               "5.Sort Inventory By Name\n"
                               "6.Sort Inventory By Department\n"
                               "7.Sort Inventory By Price\n"
                               "8.Sort Inventory By ID\n"
                               "9.Get list by ID\n"
                               "10.Display Deleted Items\n"
                               "11.Exit Inventory\n");
                        scanf("%d", &option);

                        switch(option)
                        {
                        case Inventory_AddItem:
                            success = addItemToInventory(&inventory);
                            if(success)
                            {
                                printf("Items Added succesfully to the Inventory\n");
                            }
                            else
                            {
                                printf("Failed to add Item to the Inventory\n");
                            }
                            break;

                        case Inventory_DeleteItem:
                            if(inventory.head == NULL)
                            {
                                printf("Inventory is Empty\n");
                            }
                            else
                            {
                                printf("Enter ID to delete Item\n");
                                scanf("%d", &ID);
                                success = deleteItemFromInventory(&inventory, ID);
                                if(success)
                                {
                                    printf("Item deleted succesfully from the Inventory\n");
                                }
                                else
                                {
                                    printf("Failed to delete Item from the Inventory\n");
                                }
                            }
                            break;

                        case Inventory_UpdateItem:
                            if(inventory.head == NULL)
                            {
                                printf("Inventory is Empty\n");
                            }
                            else
                            {
                                printf("Enter ID to update Item details\n");
                                scanf("%d", &ID);
                                success = updateItemDetails(&inventory, ID);
                                if(success)
                                {
                                    printf("Item updated succesfully to the Inventory\n");
                                }
                                else
                                {
                                    printf("Failed to update Item to the Inventory\n");
                                }
                            }
                            break;

                        case Inventory_DisplaySummary:
                            if(inventory.head == NULL)
                            {
                                printf("Inventory is Empty\n");
                            }
                            else
                            {
                                displayInventorySummary(&inventory);
                            }
                            break;

                        case Inventory_SortByName:
                            if(inventory.head == NULL)
                            {
                                printf("Inventory is Empty\n");
                            }
                            else
                            {
                                success = sortInventorybyName(&inventory);
                                if(success)
                                {
                                    printf("Inventory sorted by item name.\n");
                                }
                                else
                                {
                                    printf("Failed to sort Inventory by name\n");
                                }
                            }
                            break;

                        case Inventory_SortByDepartment:
                            if(inventory.head == NULL)
                            {
                                printf("Inventory is Empty\n");
                            }
                            else
                            {
                                success = sortInventorybyDepartment(&inventory);
                                if(success)
                                {
                                    printf("Inventory sorted by item Department.\n");
                                }
                                else
                                {
                                    printf("Failed to sort Inventory by Department\n");
                                }
                            }
                            break;

                        case Inventory_SortByPrice:
                            if(inventory.head == NULL)
                            {
                                printf("Inventory is Empty\n");
                            }
                            else
                            {
                                success = sortInventorybyPrice(&inventory);
                                if(success)
                                {
                                    printf("Inventory sorted by item Price.\n");
                                }
                                else
                                {
                                    printf("Failed to sort inventory by Price.\n");
                                }
                            }
                            break;

                        case Inventory_SortByItemID:
                            if(inventory.head == NULL)
                            {
                                printf("Inventory is Empty\n");
                            }
                            else
                            {
                                success = sortInventorybyItemID(&inventory);
                                if(success)
                                {
                                    printf("Inventory sorted by item Price.\n");
                                }
                                else
                                {
                                    printf("Failed to sort inventory by Price.\n");
                                }
                            }
                            break;

                        case Inventory_GetItemByID:
                            if(inventory.head == NULL)
                            {
                                printf("Inventory is Empty\n");
                            }
                            else
                            {
                                printf("Enter ID of an item\n");
                                scanf("%d", &ID);
                                success = getInventoryItemByID(&inventory, ID);
                                if(success)
                                {
                                    printf("Got item Successfully\n");
                                }
                                else
                                {
                                    printf("Failed to get item\n");
                                }
                            }
                            break;

                        case Inventory_DisplayDeletedItems:
                            if(inventory.head == NULL)
                            {
                                printf("Inventory is Empty\n");
                            }
                            else
                            {
                                displayDeletedItems(&inventory);
                            }
                            break;

                        case Inventory_Exit:
                            isTrue = 0;
                            break;

                        default:
                            printf("Enter valid option\n");
                        }
                    }
                    break;

                case  ADMIN_CART_MANAGEMENT:
                    isTrue = 1;
                    while(isTrue)
                    {
                        printf("Enter\n"
                               "1.Add Item to Cart\n"
                               "2.Delete Item from Cart\n"
                               "3.Update Cart item quantity\n"
                               "4.Display Cart Summary\n"
                               "5.Exit Cart\n");
                        scanf("%d", &option);

                        switch(option)
                        {

                        case Cart_AddItem:
                            if(inventory.head == NULL)
                            {
                                printf("Inventory is Empty\n");
                            }
                            else
                            {
                                printf("Enter ID of Inventory Item to add\n");
                                scanf("%d", &ID);
                                printf("Enter Quantity\n");
                                scanf("%f", &quantity);
                                success = addItemToCart(&cart, &inventory, ID, quantity);
                                if(success)
                                {
                                    printf("Item Added succesfully to the cart\n");
                                }
                                else
                                {
                                    printf("Failed to add Item to the cart\n");
                                }
                            }
                            break;

                        case Cart_DeleteItem:
                            if(cart.head == NULL)
                            {
                                printf("Cart is Empty\n");
                            }
                            else
                            {
                                printf("Enter ID to remove item from cart\n");
                                scanf("%d", &ID);
                                success = removeItemFromCart(&inventory, &cart, ID);
                                if(success)
                                {
                                    printf("Item deleted succesfully from the cart\n");
                                }
                                else
                                {
                                    printf("Failed to delete Item from the cart\n");
                                }
                            }
                            break;

                        case Cart_UpdateQuantity:
                            if(cart.head == NULL)
                            {
                                printf("Cart is Empty\n");
                            }
                            else
                            {
                                printf("Enter ID to update quantity\n");
                                scanf("%d", &ID);
                                printf("Enter Quantity\n");
                                scanf("%f", &quantity);
                                success = updateCartItemQuantity(&inventory, &cart, ID, quantity);
                                if(success)
                                {
                                    printf("Item updated succesfully to the cart\n");
                                }
                                else
                                {
                                    printf("Failed to update Item to the cart\n");
                                }
                            }
                            break;

                        case Cart_DisplaySummary:
                            if(cart.head == NULL)
                            {
                                printf("Cart is Empty\n");
                            }
                            else
                            {
                                viewCartSummary(&cart);
                            }
                            break;

                        case Cart_Exit:
                            isTrue = 0;
                            break;

                        default:
                            printf("Enter valid option\n");
                        }
                    }
                    break;

                case  ADMIN_BILLING:

                    if(cart.head == 0)
                    {
                        printf("No Items in cart,Please add...\n");
                    }
                    else
                    {
                        isTrue = 1;
                        while(isTrue)
                        {
                            printf("Enter\n"
                                   "1.Provide Discount\n"
                                   "2.Generate Receipt\n"
                                   "3.Exit Billing\n");
                            scanf("%d", &option);

                            switch(option)
                            {
                                float DiscountAmount = 0;

                            case Calculate_FinalBill:
                                DiscountAmount = calculateFinalBill(&cart, &inventory, &totalsales);
                                break;

                            case Billing_GenerateReceipt:
                                generateReceipt(&cart, &inventory,DiscountAmount,&report);
                                generateSalesReport(&cart, &inventory,&report, 0);
                                cart.head = 0;
                                break;

                            case Billing_Exit:
                                isTrue = 0;
                                break;

                            default:
                                printf("Enter valid option\n");
                            }
                        }
                        break;
                    }
                    break;


                case  ADMIN_REPORTS:
                    isTrue = 1;
                    while(isTrue)
                    {
                        printf("Enter\n"
                               "1.Generate Sales Report\n"
                               "2.Generate Inventory Report\n"
                               "3.View Low Stock alerts\n"
                               "4.Exit Report\n");
                        scanf("%d", &option);

                        switch(option)
                        {
                        case Generate_SalesReport:
                            generateSalesReport(&cart, &inventory,&report,1);
                            cart.head = 0;
                            break;

                        case Generate_InventoryReport:
                            generateInventoryReport(&inventory);
                            break;

                        case ViewLOWStockAlerts:
                            if(inventory.head == NULL)
                            {
                                printf("Inventory is Empty\n");
                            }
                            else
                            {
                                viewLowStockAlerts(&inventory);
                            }
                            break;

                        case Report_Exit:
                            isTrue = 0;
                            break;

                        default:
                            printf("Enter valid option\n");
                        }
                    }
                    break;

                case  ADMIN_LOGOUT:

                    currentUser->isLoggedIn = 0;
                    currentUser = NULL;
                    printf("Admin Logging out....\n\n\n");
                    break;

                default:
                    printf("Invalid choice.\n");
                }
            }
            else if (currentUser->role == ROLE_USER)
            {
                printf("User Menu:\n");
                printf("1. View Inventory\n");
                printf("2. Manage Cart\n");
                printf("3. Billing\n");
                printf("4. Logout\n");

                printf("Enter your choice: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case  USER_VIEW_INVENTORY:

                    displayInventorySummary(&inventory);
                    break;

                case  USER_CART_MANAGEMENT:
                    isTrue = 1;
                    while(isTrue)
                    {
                        printf("Enter\n"
                               "1.Add Item to Cart\n"
                               "2.Delete Item from Cart\n"
                               "3.Update Cart item quantity\n"
                               "4.Display Cart Summary\n"
                               "5.Exit Cart\n");
                        scanf("%d", &option);

                        switch(option)
                        {

                        case Cart_AddItem:
                            if(inventory.head == NULL)
                            {
                                printf("Inventory is Empty\n");
                            }
                            else
                            {
                                printf("Enter ID of Inventory Item to add\n");
                                scanf("%d", &ID);
                                printf("Enter Quantity\n");
                                scanf("%f", &quantity);
                                success = addItemToCart(&cart, &inventory, ID, quantity);
                                if(success)
                                {
                                    printf("Item Added succesfully to the cart\n");
                                }
                                else
                                {
                                    printf("Failed to add Item to the cart\n");
                                }
                            }
                            break;

                        case Cart_DeleteItem:
                            if(cart.head == NULL)
                            {
                                printf("Cart is Empty\n");
                            }
                            else
                            {
                                printf("Enter ID to remove item from cart\n");
                                scanf("%d", &ID);
                                success = removeItemFromCart(&inventory, &cart, ID);
                                if(success)
                                {
                                    printf("Item deleted succesfully from the cart\n");
                                }
                                else
                                {
                                    printf("Failed to delete Item from the cart\n");
                                }
                            }
                            break;

                        case Cart_UpdateQuantity:
                            if(cart.head == NULL)
                            {
                                printf("Cart is Empty\n");
                            }
                            else
                            {
                                printf("Enter ID to update quantity\n");
                                scanf("%d", &ID);
                                printf("Enter Quantity\n");
                                scanf("%f", &quantity);
                                success = updateCartItemQuantity(&inventory, &cart, ID, quantity);
                                if(success)
                                {
                                    printf("Item updated succesfully to the cart\n");
                                }
                                else
                                {
                                    printf("Failed to update Item to the cart\n");
                                }
                            }
                            break;

                        case Cart_DisplaySummary:
                            if(cart.head == NULL)
                            {
                                printf("Cart is Empty\n");
                            }
                            else
                            {
                                viewCartSummary(&cart);
                            }
                            break;

                        case Cart_Exit:
                            isTrue = 0;
                            break;

                        default:
                            printf("Enter valid option\n");
                        }
                    }
                    break;

                case  USER_BILLING:

                    if(cart.head == 0)
                    {
                        printf("No Items in cart,Please add...\n");
                    }
                    else
                    {
                        isTrue = 1;
                        while(isTrue)
                        {
                            printf("Enter\n1.Provide Discount\n2.Generate Receipt\n3.Exit Billing\n");
                            scanf("%d", &option);

                            switch(option)
                            {
                                float DiscountAmount = 0;

                            case Calculate_FinalBill:
                                DiscountAmount = calculateFinalBill(&cart, &inventory, &totalsales);
                                break;

                            case Billing_GenerateReceipt:
                                generateReceipt(&cart, &inventory,DiscountAmount,&report);
                                generateSalesReport(&cart, &inventory,&report, 0);
                                cart.head = 0;
                                break;

                            case Billing_Exit:
                                isTrue = 0;
                                break;

                            default:
                                printf("Enter valid option\n");
                            }
                        }
                        break;
                    }
                    break;

                case USER_LOGOUT:

                    currentUser->isLoggedIn = 0;
                    currentUser = NULL;
                    printf("User Logging out....\n\n\n");
                    break;

                default:
                    printf("Invalid choice.\n");
                }
            }
            else
            {
                printf("Invalid User Role.\n");
                currentUser = NULL;
                break;
            }
        }
    }
    saveUsersToFile(&userlist);
    closeUserFile();
    closeSalesReportFile();
    closeInventoryFile();

    return 0;
}
