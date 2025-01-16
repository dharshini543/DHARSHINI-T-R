
#ifndef ENUM_H
#define ENUM_H

enum ADMIN_MENU
{
    ADMIN_ADD_USER = 1,
    ADMIN_DELETE_USER,
    ADMIN_INVENTORY_MANAGEMENT,
    ADMIN_CART_MANAGEMENT,
    ADMIN_BILLING,
    ADMIN_REPORTS,
    ADMIN_LOGOUT
};

enum USER_MENU
{
    USER_VIEW_INVENTORY = 1,
    USER_CART_MANAGEMENT,
    USER_BILLING,
    USER_LOGOUT
};

enum InventoryMenuOptions
{
    Inventory_AddItem = 1,
    Inventory_DeleteItem,
    Inventory_UpdateItem,
    Inventory_DisplaySummary,
    Inventory_SortByName,
    Inventory_SortByDepartment,
    Inventory_SortByPrice,
    Inventory_SortByItemID,
    Inventory_GetItemByID,
    Inventory_DisplayDeletedItems,
    Inventory_Exit
};

enum mergeSort
{
    Sort_By_Name = 1,
    Sort_By_Department,
    Sort_By_ItemID,
    Sort_By_Price

};

enum field
{
    Name = 1,
    Brand,
    Department,
    ExpiryDate,
    Price,
    Quantity

};

enum CartMenuOptions
{
    Cart_AddItem = 1,
    Cart_DeleteItem,
    Cart_UpdateQuantity,
    Cart_DisplaySummary,
    Cart_Exit
};

enum BillingMenuOptions
{
    Calculate_FinalBill = 1,
    Billing_GenerateReceipt,
    Billing_Exit
};

enum ReportMenuOptions
{
    Generate_SalesReport = 1,
    Generate_InventoryReport,
    ViewLOWStockAlerts,
    Report_Exit
};

enum returnValue
{
    Failure = 0,
    Success
};


#endif // ENUM_H
