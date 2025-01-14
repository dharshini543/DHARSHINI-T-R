# Grocery Management System

The Grocery Management System is a C-based application designed to help manage a grocery store efficiently. This program allows users to manage inventory, handle customer carts, generate bills, and produce detailed reports for sales and stock analysis.  


## Features

 ### 1. User Management
- User login with credentials for secure access.
- Administrator role to manage other users.
- Ability to add, delete user details.
- Role-based access control.
- Initialization of the first admin user if no users exist.

 ### 2. Inventory Management
- Add, delete, and update items in the inventory.
- Display inventory summary.
- Sort inventory by:
  - Name
  - Department
  - Price
- Retrieve inventory details by item ID.

### 3. Cart Management
- Add items from inventory to the cart.
- Update quantities of items in the cart.
- Remove items from the cart.
- Display cart summary.

 ### 4. Billing
- Calculate the final bill based on cart items.
- Apply discounts and generate a detailed receipt.

### 5. Reporting
- Generate sales reports for transactions.
- Generate inventory reports to review stock levels.
- View low-stock alerts for inventory restocking.

---

## File Structure
- **`main.c`**: Entry point of the application.
- **`billing.h`/`billing.c`**: Handles billing and receipt generation.
- **`cart.h`/`cart.c`**: Manages customer cart operations.
- **`enum.h`**: Contains enumerations for menu options and constants.
- **`inventory.h`/`inventory.c`**: Manages inventory operations.
- **`inventory_FO.h`/`inventory_FO.c`**: Handles file operations related to inventory.
- **`report.h`/`report.c`**: Generates sales and inventory reports.
- **`sales_report_FO.h`/`sales_report_FO.c`**: Handles file operations for sales reporting.
- **`sorting.h`/`sorting.c`**: Provides sorting algorithms for inventory.
- **`start.h`/`start.c`**: Contains the main program logic for initialization and user interaction.
- **`user.h`/`user.c`**: Handles user login and authentication.

## How to Run the Project

### Prerequisites
- Install a C compiler (e.g., GCC).
- Install **Qt Creator** (available at [Qt Official Site](https://www.qt.io)).
- Ensure **CMake** (version 3.16 or higher) is installed.
- Clone this repository or download the source code.

## Steps to Build and Run

#### Using Qt Creator
1. Open **Qt Creator** and select **Open Project**.
2. Navigate to the project directory and open the `CMakeLists.txt` file.
3. Configure the project by choosing a suitable build kit (e.g., Desktop GCC).
4. Click on the **Build Project** button (hammer icon) to compile the application.
5. After a successful build, click on the **Run** button (green play icon) to execute the program.

### Project Developed by
[https://github.com/dharshini543](https://github.com/dharshini543)
