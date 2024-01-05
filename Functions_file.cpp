#include "Header_file.h"
#include <iostream>
#include <fstream>
#include <sstream>

User::User(int user_id, const std::string &user_name, const std::string &password, const std::string &user_type)
    : UserID(user_id), UserName(user_name), Password(password), UserType(user_type) {}

void User::Register()
{
    // Add code for user registration
}

bool User::Login(const std::string &entered_password) const
{
    return Password == entered_password;
}

int User::GetUserID() const
{
    return UserID;
}

std::string User::GetUserName() const
{
    return UserName;
}

std::string User::GetUserPassword() const
{
    return Password;
}

std::string User::GetUserType() const
{
    return UserType;
}
void User::ViewMenu() const {
    std::cout << "Viewing menu as a generic user...\n";
    
}

// Virtual function PlaceOrder (default implementation)
void User::PlaceOrder() const {
    std::cout << "Placing an order as a generic user...\n";
    
}

// Virtual function ViewOrderHistory (default implementation)
void User::ViewOrderHistory() const {
    std::cout << "Viewing order history as a generic user...\n";
    
}

bool UserManagementSystem::RegisterUser(User &user)
{
    // Open file for writing user information
    std::ofstream userFile("users.txt", std::ios::app);

    // Check if the user already exists
    if (CheckUserExists(user))
    {
        std::cout << "User with the same ID already exists. Registration failed.\n";
        return false;
    }

    // Write user information to file
    userFile << user.GetUserID() << ' ' << user.GetUserName() << ' ' << user.GetUserPassword() << ' ' << user.GetUserType() << '\n';

    // Close file
    userFile.close();

    std::cout << "User registered successfully!\n";
    return true;
}

bool UserManagementSystem::AuthenticateUser(const std::string &user_type, int user_id, const std::string &entered_password)
{
    // Open file for reading user information
    std::ifstream userFile("users.txt");

    int id;
    std::string username, password, type;

    // Read user information from file and check for authentication
    while (userFile >> id >> username >> password >> type)
    {
        if (type == user_type && id == user_id && entered_password == password)
        {
            // Authentication successful
            userFile.close();
            return true;
        }
    }

    // Authentication failed
    userFile.close();
    return false;
}

bool UserManagementSystem::CheckUserExists(const User &user)
{
    // Add code for checking if a user exists
    // Open file for reading user information
    std::ifstream userFile("users.txt");

    int id;
    std::string username, password, type;

    // Check if the user already exists
    while (userFile >> id >> username >> password >> type)
    {
        if (id == user.GetUserID())
        {
            userFile.close();
            return true;
        }
    }

    // User doesn't exist
    userFile.close();
    return false;
}

Administrator::Administrator(int user_id, const std::string &user_name, const std::string &password)
    : User(user_id, user_name, password, "Administrator") {}

void Administrator::AdminMenu(Administrator &admin)
{
    while (true)
    {
        int adminChoice;
        std::cout << "\n\nAdministrator Options:\n[1]. View Menu\n[2]. Add Menu Item\n[3]. Remove Menu Item\n[4]. Manage Inventory\n[5]. Manage Discount/Promotion\n"
                     "[6]. View Order History\n[7]. Add Notification\n[8]. Remove Notification\n[9]. Rate Menu Item\n[10]. Display From File\n[11]. View Users From File\n"
                     "[12]. View Menu Items From File\n[13]. View Orders From File\n[14]. View Ratings From File\n[15]. View Payments From File\n[16]. Calculate Monthly Earnings\n"
                     "[17]. Logout\nEnter your choice: ";
        std::cin >> adminChoice;

        switch (adminChoice)
        {
        case 1:
            admin.ViewMenu();
            break;
        case 2:
            admin.AddMenuItem();
            break;
        case 3:
            admin.RemoveMenuItem();
            break;
        case 4:
            admin.ManageInventory();
            break;
        case 5:
            admin.ManageDiscountPromotion();
            break;
        case 6:
            admin.ViewOrderHistory();
            break;
        case 7:
            admin.AddNotification();
            break;
        case 8:
            admin.RemoveNotification();
            break;
        case 9:
            admin.RateMenuItem();
            break;
        case 10:
            admin.DisplayFromFile("user.txt");
            break;
        case 11:
            admin.ViewUsersFromFile();
            break;
        case 12:
            admin.ViewMenuItemsFromFile();
            break;
        case 13:
            admin.ViewOrdersFromFile();
            break;
        case 14:
            admin.ViewRatingsFromFile();
            break;
        case 15:
            admin.ViewPaymentsFromFile();
            break;
        case 16:
            admin.CalculateMonthlyEarnings();
            break;
        case 17:
            std::cout << "Logging out...\n";
            admin.Logout();
            return;
        default:
            std::cout << "Invalid choice\n";
            break;
        }
    }
}

void Administrator::ViewMenu() const 
{
    // Get the menu type from the administrator
    std::string menuType = GetMenuTypeFromAdmin();

    // Use the obtained menu type to open the corresponding menu file
    std::ifstream menuFile(menuType + "_menu.txt");

    if (!menuFile.is_open())
    {
        std::cerr << "Error opening menu file.\n";
        return;
    }

    std::cout << "Cafe " << menuType << " Menu:\n";

    std::string category;
    while (std::getline(menuFile, category))
    {
        std::cout << "\n" << std::string(50, '-') << "\n";
        std::cout << " " << category << "\n";
        std::cout << std::string(50, '-') << "\n";

        std::string menuItem;
        while (std::getline(menuFile, menuItem) && !menuItem.empty())
        {
            std::cout << " - " << menuItem << "\n";
        }
    }

    menuFile.close();
}

void Administrator::AddMenuItem()
{
    // Get the menu type from the administrator
    std::string menuType = GetMenuTypeFromAdmin();

    // Use the obtained menu type to open the corresponding menu file for appending
    std::ofstream menuFile(menuType + "_menu.txt", std::ios::app);

    if (!menuFile.is_open())
    {
        std::cerr << "Error opening menu file.\n";
        return;
    }

    std::string category;
    std::cout << "Enter the category of the new menu item: ";
    std::cin >> category;

    std::string itemName;
    std::cout << "Enter the name of the new menu item: ";
    std::cin.ignore(); // Clear the newline character from the buffer
    std::getline(std::cin, itemName);

    double itemPrice;
    std::cout << "Enter the price of the new menu item: $";
    std::cin >> itemPrice;

    menuFile << "\n"
        << category << "\n"
        << itemName << ": $" << itemPrice << "\n";

    std::cout << "New menu item added successfully!\n";

    menuFile.close();
}

void Administrator::RemoveMenuItem()
{
    // Get the menu type from the administrator
    std::string menuType = GetMenuTypeFromAdmin();

    // Use the obtained menu type to open the corresponding menu files for reading and writing
    std::ifstream menuFileIn(menuType + "_menu.txt");
    std::ofstream menuFileOut(menuType + "_menu_temp.txt");

    if (!menuFileIn.is_open() || !menuFileOut.is_open())
    {
        std::cerr << "Error opening menu files.\n";
        return;
    }

    std::cout << "Current Cafe " << menuType << " Menu:\n";

    int lineNumber = 1;
    std::string line;

    // Display the current menu for selection
    while (std::getline(menuFileIn, line))
    {
        std::cout << lineNumber << ". " << line << '\n';
        lineNumber++;
    }

    menuFileIn.clear();                 // Clear the end-of-file flag
    menuFileIn.seekg(0, std::ios::beg); // Move the file pointer back to the beginning

    // Ask the administrator to select an item for removal
    std::cout << "\nEnter the number of the item to remove: ";
    int itemNumber;
    std::cin >> itemNumber;

    lineNumber = 1;

    // Remove the selected item from the file
    while (std::getline(menuFileIn, line))
    {
        if (lineNumber != itemNumber)
        {
            menuFileOut << line << '\n';
        }
        lineNumber++;
    }

    std::cout << "Menu item removed successfully!\n";

    menuFileIn.close();
    menuFileOut.close();

    // Rename the temporary file to replace the original menu file
    std::remove((menuType + "_menu.txt").c_str());
    std::rename((menuType + "_menu_temp.txt").c_str(), (menuType + "_menu.txt").c_str());
}

// Function to get the menu type from the administrator
std::string Administrator::GetMenuTypeFromAdmin() const
{
    int menuTypeChoice;
    std::cout << "\nSelect Menu Type:\n[1]. Administrator Menu\n[2] Student Menu\n[3] Faculty Menu\n[4] Non-Faculty Menu\nEnter your choice: ";
    std::cin >> menuTypeChoice;

    std::string menuType;
    switch (menuTypeChoice)
    {
    case 1:
        menuType = "admin";
        break;
    case 2:
        menuType = "student";
        break;
    case 3:
        menuType = "faculty";
        break;
    case 4:
        menuType = "non_faculty";
        break;
    default:
        std::cout << "Invalid choice\n";
        exit(1);
    }

    return menuType;
}



std::string ReadInventoryData()
{
    std::ifstream inventoryFile("Inventory.txt");
    std::ostringstream inventoryData;

    if (inventoryFile.is_open())
    {
        inventoryData << inventoryFile.rdbuf();
        inventoryFile.close();
    }
    else
    {
        std::cerr << "Error: Unable to open inventory file.\n";
    }

    return inventoryData.str();
}
void displayInventory()
{
    std::ifstream inventoryFile("inventory.txt");

    if (!inventoryFile.is_open())
    {
        std::cerr << "Error opening inventory file.\n";
        return;
    }

    std::cout << "Current Inventory:\n";

    std::string line;
    while (std::getline(inventoryFile, line))
    {
        std::cout << line << '\n';
    }

    inventoryFile.close();
}
int FindItemLineNumber(const std::string &itemName)
{
    std::ifstream inventoryFile("inventory.txt");

    if (inventoryFile.is_open())
    {
        std::string line;
        int lineNumber = 0;

        while (std::getline(inventoryFile, line))
        {
            // Check if the line contains the specified item
            if (line.find(itemName) != std::string::npos)
            {
                inventoryFile.close();
                return lineNumber;
            }

            lineNumber++;
        }

        inventoryFile.close();
    }
    else
    {
        std::cerr << "Error: Unable to open inventory file.\n";
    }

    // Item not found
    return -1;
}
void WriteInventoryData(const std::string &updatedInventoryData)
{
    std::ofstream inventoryFile("inventory.txt");

    if (inventoryFile.is_open())
    {
        inventoryFile << updatedInventoryData;
        inventoryFile.close();
    }
    else
    {
        std::cerr << "Error: Unable to open inventory file for writing.\n";
    }
}
void UpdateItemQuantity()
{
    // Read current inventory data from the file
    std::string inventoryData = ReadInventoryData();

    // Display current inventory
    std::cout << "Current Inventory:\n"
              << inventoryData << "\n";

    // Update item quantity
    std::string itemName;
    std::string newQuantity;
    std::cout << "Enter the name of the item to update: ";
    std::cin >> itemName;
    std::cout << "Enter the new quantity: ";
    std::cin >> newQuantity;

    // Find the line number of the item in the inventory
    int lineNumber = FindItemLineNumber(itemName);

    if (lineNumber != -1)
    {
        // Update the quantity in the inventory data
        std::istringstream iss(inventoryData);
        std::ostringstream updatedData;
        std::string line;
        int currentLine = 0;

        while (std::getline(iss, line))
        {
            if (currentLine == lineNumber)
            {
                // Update the quantity for the specific item
                updatedData << itemName << "\t" << newQuantity << "\n";
            }
            else
            {
                updatedData << line << "\n";
            }

            currentLine++;
        }

        // Write the updated inventory data back to the file
        WriteInventoryData(updatedData.str());

        std::cout << "Item quantity updated successfully!\n";
    }
    else
    {
        std::cout << "Item not found in the inventory.\n";
    }
}
void AddNewItemToInventory()
{
    // Read current inventory data from the file
    std::string inventoryData = ReadInventoryData();

    // Display current inventory
    std::cout << "Current Inventory:\n"
              << inventoryData << "\n";

    // Add new item to inventory
    std::string newItemName;
    std::string newItemQuantity;
    std::cout << "Enter the name of the new item: ";
    std::cin >> newItemName;
    std::cout << "Enter the quantity of the new item: ";
    std::cin >> newItemQuantity;

    // Append the new item to the inventory data
    std::ostringstream updatedData;
    updatedData << inventoryData << newItemName << "\t" << newItemQuantity << "\n";

    // Write the updated inventory data back to the file
    WriteInventoryData(updatedData.str());

    std::cout << "New item added to inventory successfully!\n";
}
void RemoveItemFromInventory()
{
    // Read current inventory data from the file
    std::string inventoryData = ReadInventoryData();

    // Display current inventory
    std::cout << "Current Inventory:\n"
              << inventoryData << "\n";

    // Remove item from inventory
    std::string itemToRemove;
    std::cout << "Enter the name of the item to remove: ";
    std::cin >> itemToRemove;

    // Find the line number of the item in the inventory
    int lineNumber = FindItemLineNumber(itemToRemove);

    if (lineNumber != -1)
    {
        // Remove the line corresponding to the item
        std::istringstream iss(inventoryData);
        std::ostringstream updatedData;
        std::string line;
        int currentLine = 0;

        while (std::getline(iss, line))
        {
            if (currentLine != lineNumber)
            {
                updatedData << line << "\n";
            }

            currentLine++;
        }

        // Write the updated inventory data back to the file
        WriteInventoryData(updatedData.str());

        std::cout << "Item removed from inventory successfully!\n";
    }
    else
    {
        std::cout << "Item not found in the inventory.\n";
    }
}

void Administrator::ManageInventory()
{
    while (true)
    {
        int inventoryChoice;
        std::cout << "\n\nInventory Management Options:\n"
                     "[1]  Display Inventory \n"
                     "[2]  Update Item Quantity\n"
                     "[3]  Add New Item to Inventory\n"
                     "[4]  Remove Item from Inventory\n"
                     "[5]  Exit Inventory Management\n"
                     "Enter your choice: ";
        std::cin >> inventoryChoice;

        switch (inventoryChoice)
        {

        case 1:
            displayInventory();
            break;
        case 2:
            UpdateItemQuantity();
            break;
        case 3:
            AddNewItemToInventory();
            break;
        case 4:
            RemoveItemFromInventory();
            break;
        case 5:
            cout << "Exiting from inventory: " << endl;
            return;
        default:
            std::cout << "Invalid choice\n";
            break;
        }
    }
}

void Administrator::AddOrUpdateDiscount()
{
    // Assume you have a collection of discounts (could be a map or other data structure)
    // For simplicity, I'll use a static variable here
    static double discountRate = 0.05; // Default discount rate

    std::cout << "Enter the new discount rate (e.g., 0.10 for 10%): ";
    std::cin >> discountRate;

    std::cout << "Discount added or updated successfully!\n";
    std::cout << "New Discount Rate: " << (discountRate * 100) << "%\n";
}

void Administrator::RemoveDiscount()
{
    // Assume you have a way to store and manage existing discounts
    // For simplicity, I'll use a static variable here
    static double discountRate = 0.05; // Default discount rate

    // Check if there is an existing discount
    if (discountRate > 0)
    {
        std::cout << "Removing existing discount...\n";
        discountRate = 0; // Set the discount rate to zero to remove the discount
        std::cout << "Discount removed successfully!\n";
    }
    else
    {
        std::cout << "No existing discount to remove.\n";
    }
}

void Administrator::ManageDiscountPromotion()
{
    std::cout << "Managing Discounts and Promotions...\n";

    // Add the ability for the administrator to update or add discounts
    std::cout << "Do you want to update or add discounts? (Y/N): ";
    char choice;
    std::cin >> choice;

    if (choice == 'Y' || choice == 'y')
    {
        std::cout << "1. Add new discount\n";
        std::cout << "2. Remove existing discount\n";
        int discountChoice;
        std::cout << "Enter your choice: ";
        std::cin >> discountChoice;

        switch (discountChoice)
        {
        case 1:
            // Implement logic to add or replace a discount
            AddOrUpdateDiscount();
            break;
        case 2:
            // Implement logic to remove an existing discount
            RemoveDiscount();
            break;
        default:
            std::cout << "Invalid choice\n";
            break;
        }
    }
}

void Administrator::ViewOrderHistory()
{
    std::ifstream orderFile("orders.txt");

    if (!orderFile.is_open())
    {
        std::cerr << "Error opening orders file.\n";
        return;
    }

    std::cout << "Order History:\n";

    std::string line;
    while (std::getline(orderFile, line))
    {
        std::cout << line << "\n";
    }

    orderFile.close();
}

void Administrator::AddNotification()
{
    std::ofstream notificationFile("notifications.txt", std::ios::app);

    if (!notificationFile.is_open())
    {
        std::cerr << "Error opening notifications file for writing.\n";
        return;
    }

    std::string notification;
    std::cout << "Enter the notification message: ";
    std::cin.ignore(); // Clear the newline character from the buffer
    std::getline(std::cin, notification);

    notificationFile << notification << "\n";

    std::cout << "Notification added successfully!\n";

    notificationFile.close();
}

void Administrator::RemoveNotification()
{
    std::ifstream notificationFileIn("notifications.txt");
    std::ofstream notificationFileOut("notifications_temp.txt");

    if (!notificationFileIn.is_open() || !notificationFileOut.is_open())
    {
        std::cerr << "Error opening notification files.\n";
        return;
    }

    std::cout << "Current Notifications:\n";

    int lineNumber = 1;
    std::string line;

    // Display the current notifications for selection
    while (std::getline(notificationFileIn, line))
    {
        std::cout << lineNumber << ". " << line << '\n';
        lineNumber++;
    }

    notificationFileIn.clear();                 // Clear the end-of-file flag
    notificationFileIn.seekg(0, std::ios::beg); // Move the file pointer back to the beginning

    // Ask the administrator to select a notification for removal
    std::cout << "\nEnter the number of the notification to remove: ";
    int notificationNumber;
    std::cin >> notificationNumber;

    lineNumber = 1;

    // Remove the selected notification from the file
    while (std::getline(notificationFileIn, line))
    {
        if (lineNumber != notificationNumber)
        {
            notificationFileOut << line << '\n';
        }
        lineNumber++;
    }

    std::cout << "Notification removed successfully!\n";

    notificationFileIn.close();
    notificationFileOut.close();

    // Rename the temporary file to replace the original notifications file
    std::remove("notifications.txt");
    std::rename("notifications_temp.txt", "notifications.txt");
}

void Administrator::RateMenuItem()
{
    std::cout << "Rating a Menu Item...\n";
    // Add logic for allowing administrators to rate menu items
}

// Definition of the DisplayFromFile function
void Administrator::DisplayFromFile(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << "\n";
        return;
    }

    std::cout << "Contents of " << filename << ":\n";

    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << "\n";
    }

    file.close();
}

void Administrator::ViewUsersFromFile()
{
    DisplayFromFile("users.txt");
}

void Administrator::ViewMenuItemsFromFile()
{
    DisplayFromFile("menu.txt");
}

void Administrator::ViewOrdersFromFile()
{
    DisplayFromFile("orders.txt");
}

void Administrator::ViewRatingsFromFile()
{
    DisplayFromFile("ratings.txt");
}

void Administrator::ViewPaymentsFromFile()
{
    DisplayFromFile("payments.txt");
}

void Administrator::CalculateMonthlyEarnings()
{
    std::cout << "Calculating Monthly Earnings...\n";

    // Load the orders from the "orders.txt" file
    std::ifstream ordersFile("orders.txt");
    if (!ordersFile.is_open())
    {
        std::cerr << "Error opening orders file.\n";
        return;
    }

    // Define arrays to store order items and their prices
    const int MAX_ITEMS = 150;
    std::string orderItems[MAX_ITEMS] = { "Hot Chocolate", "Salad", "Pie", "Smoothie", "Pasta", "Chai", "Fruit Salad", "Soup", "Coffee", "Espresso", "Latte", "Cappuccino", "Tea", "Hot Chocolate", "Iced Coffee", "Iced Tea", "Smoothie", "Sandwich", "Salad", "Soup", "Pastry", "Fruit Salad", "Ice Cream", "Cake", "Pie", "Cookie", "Pasta", "Daal Chawal", "Samosa Chaat", "Pakora Platter", "Bun Kebab", "Anda Paratha", "Chicken Tikka Role", "Shawarama", "Keema Naan", "Falafel Wrap", "Channa Chaat", "Gulab Jamun", "Gajjar ka Halwa", "Jalebi", "Kulfi", "Mango Lassi", "Chai", "Rooh Afza", "Lemon Soda", "Lassi", "Mineral Water", "Cappuccino", "Sandwich", "Pastry", "Fruit Salad", "Cookie", "Pasta", "Pie", "Soup" };
    double itemPrices[MAX_ITEMS] = { 2.5, 4.0, 3.0, 3.5, 5.0, 2.0, 4.5, 3.0, 2.5, 3, 3.5, 4.0, 2.0, 3.0, 3.0, 2.5, 2.5, 5.0, 7.0, 8.0, 4.0, 5.0, 6.0, 4.0, 6.5, 5.0, 2.0, 5.0, 1.5, 2.00, 2.00, 2.5, 1.0, 1.5, 2.0, 2.5, 2.0, 2.0, 1.5, 1.0, 1.0, 2.0, 1.0, 1.5, 1.0, 1.5, 0.5, 4.0, 7.0, 4.0, 6.0, 2.0, 5.0, 5.0 };

    // Initialize total earnings
    double totalEarnings = 0.0;

    // Process each order in the "orders.txt" file
    std::string line;
    while (std::getline(ordersFile, line))
    {
        // Assuming each order item is preceded by "order item: "
        size_t pos = line.find("order item: ");
        if (pos != std::string::npos)
        {
            std::string orderItem = line.substr(pos + 12); // 12 is the length of "order item: "

            // Trim leading and trailing whitespaces
            orderItem.erase(0, orderItem.find_first_not_of(" \t\r\n"));
            orderItem.erase(orderItem.find_last_not_of(" \t\r\n") + 1);

            // Find the index of the order item in the array
            int index = -1;
            for (int i = 0; i < MAX_ITEMS; ++i)
            {
                if (orderItems[i] == orderItem)
                {
                    index = i;
                    break;
                }
            }

            if (index != -1)
            {
                // Accumulate the total earnings
                totalEarnings += itemPrices[index];
            }
            else
            {
                std::cout << "Price not found for item: " << orderItem << "\n";
            }
        }
    }

    // Output the total earnings
    std::cout << "Total Earnings: $" << totalEarnings << "\n";
}

void Administrator::Logout()
{
    cout << "Directing to the Previous Page" << endl;
}
Customer::Customer(int customer_id, const std::string &customer_name, const std::string &user_type, const std::string &menu_file_name)
    : User(customer_id, customer_name, "default_password", user_type), MenuFileName(menu_file_name)
{
}

void Customer::ViewMenu() const
{
    std::ifstream menuFile(MenuFileName);

    if (!menuFile.is_open())
    {
        std::cerr << "Error opening menu file.\n";
        return;
    }

    std::cout << "Welcome to our " << GetUserType() << " Menu:\n\n";

    std::string category;
    while (std::getline(menuFile, category))
    {
        std::cout << std::string(50, '=') << "\n";
        std::cout << " " << category << "\n";
        std::cout << std::string(50, '=') << "\n";

        std::string menuItem;
        while (std::getline(menuFile, menuItem) && !menuItem.empty())
        {
            std::cout << " - " << menuItem << "\n";
        }

        // Add an extra line for better separation
        std::cout << "\n";
    }

    menuFile.close();
}

void Customer::PlaceOrder() const
{
    std::cout << GetUserType() << " placing order...\n";

    std::string orderItem;
    std::cout << "Enter the item you want to order: ";
    std::cin.ignore(); // Clear the newline character from the buffer
    std::getline(std::cin, orderItem);

    std::ifstream menuFile(MenuFileName);

    if (!menuFile.is_open())
    {
        std::cerr << "Error opening menu file.\n";
        return;
    }

    bool itemFound = false;
    std::string menuItem;
    while (std::getline(menuFile, menuItem))
    {
        if (menuItem.find(orderItem) != std::string::npos)
        {
            itemFound = true;
            break;
        }
    }

    menuFile.close();

    if (itemFound)
    {
        std::ofstream orderFile("orders.txt", std::ios::app);
        if (orderFile.is_open())
        {
            orderFile << "Customer ID: " << GetUserID() << "\n";
            orderFile << "Customer Name: " << GetUserName() << "\n";
            orderFile << "Order Item: " << orderItem << "\n\n";
            orderFile.close();
            std::cout << "Order placed successfully!\n";
        }
        else
        {
            std::cerr << "Error opening orders file for writing.\n";
        }
    }
    else
    {
        std::cout << "Item not found in the menu. Please order from the menu.\n";
    }
}

void Customer::ViewOrderHistory() const
{
    std::cout << GetUserType() << " viewing order history...\n";

    std::ifstream orderFile("orders.txt");

    if (!orderFile.is_open())
    {
        std::cerr << "Error opening orders file.\n";
        return;
    }

    std::cout << "\nOrder History for " << GetUserName() << " (ID: " << GetUserID() << "):\n\n";

    std::string line;
    bool displayOrder = false;
    std::cout << "----------------------\n";
    while (std::getline(orderFile, line))
    {
        if (line.find("Customer ID: " + std::to_string(GetUserID())) != std::string::npos)
        {
            displayOrder = true;
            std::cout << line << "\n";
        }
        else if (line.empty())
        {
            if (displayOrder)
            {
                // Display a separator between orders
                std::cout << "----------------------\n";
            }
            displayOrder = false; // Reset the flag after each order
        }
        else if (displayOrder)
        {
            // Display order details for the current user
            std::cout << line << "\n";
        }
    }

    orderFile.close();
}

void Customer::RateMenuItem() const
{
    std::cout << GetUserType() << " rating a menu item...\n";

    std::ifstream menuFile(MenuFileName);

    if (!menuFile.is_open())
    {
        std::cerr << "Error opening menu file.\n";
        return;
    }

    std::cout << "Menu Items:\n";

    std::string menuItem;
    int itemNumber = 1;

    // Display the menu items for selection
    while (std::getline(menuFile, menuItem))
    {
        std::cout << itemNumber << ". " << menuItem << '\n';
        itemNumber++;
    }

    menuFile.close();

    // Ask the customer to select a menu item to rate
    std::cout << "Enter the number of the menu item to rate: ";
    int menuItemNumber;
    std::cin >> menuItemNumber;

    menuFile.open(MenuFileName); // Reopen the menu file

    if (!menuFile.is_open())
    {
        std::cerr << "Error opening menu file.\n";
        return;
    }

    // Find the selected menu item
    for (int i = 1; i <= menuItemNumber; ++i)
    {
        std::getline(menuFile, menuItem);
    }

    menuFile.close();

    std::string rating;
    std::cout << "Enter your rating for '" << menuItem << "' out of 5 (x/5): ";
    std::cin >> rating;

    // Append the rating to the ratings file
    std::ofstream ratingsFile("ratings.txt", std::ios::app);

    if (!ratingsFile.is_open())
    {
        std::cerr << "Error opening ratings file for writing.\n";
        return;
    }

    ratingsFile << "Customer ID: " << GetUserID() << "\n";
    ratingsFile << "Customer Name: " << GetUserName() << "\n";
    ratingsFile << "Rated Item: " << menuItem << "\n";
    ratingsFile << "Rating: " << rating << "/5\n\n";

    std::cout << "Rating submitted successfully!\n";

    ratingsFile.close();
}

void Customer::CustomerMenu(Customer &customer)
{
    while (true)
    {
        int customerChoice;
        std::cout << "\n\nCustomer Options:\n"
                     "[1] View Menu\n"
                     "[2] Place Order\n"
                     "[3] View Order History\n"
                     "[4] Rate Menu Item\n" 
                     "[5] Logout\n"
                     "Enter your choice: ";
        std::cin >> customerChoice;

        switch (customerChoice)
        {
        case 1:
            customer.ViewMenu();
            break;
        case 2:
            customer.PlaceOrder();
            break;
        case 3:
            customer.ViewOrderHistory();
            break;
        case 4:
            customer.RateMenuItem();
            break;
        case 5:
            std::cout << "Logging out...\n";
            customer.Logout();
            return;
        default:
            std::cout << "Invalid choice\n";
            break;
        }
    }
}

void Customer::Logout() const
{
    std::cout << GetUserType() << " logging out...\n";
    // Implement logic for logout
}

Rating::Rating(int rating_id, int menu_item_id, int customer_id, int score, const std::string &comment)
    : RatingID(rating_id), MenuItemID(menu_item_id), CustomerID(customer_id), Score(score), Comment(comment) {}

void Rating::Rate()
{
    // Implement the rating logic here
    std::cout << "Rating " << Score << " given by Customer ID " << CustomerID << " for Menu Item ID " << MenuItemID << std::endl;
    std::cout << "Rating Menu Item...\n";
    // Add logic for allowing customers to rate menu items
    std::cout << "Rating ID: " << RatingID << "\n";
    std::cout << "Menu Item ID: " << MenuItemID << "\n";
    std::cout << "Customer ID: " << CustomerID << "\n";
    std::cout << "Score: " << Score << "\n";
    std::cout << "Comment: " << Comment << "\n";
}

Payment::Payment(int payment_id, int order_id, double amount, const std::string &payment_status)
    : PaymentID(payment_id), OrderID(order_id), Amount(amount), PaymentStatus(payment_status) {}

void Payment::ProcessPayment() {
    std::cout << "Processing Payment...\n";

    // Display the order details
    std::cout << "Order ID: " << OrderID << "\n";
    std::cout << "Amount: $" << Amount << "\n";

    // Offer payment options
    std::cout << "Select Payment Method:\n";
    std::cout << "[1] Cash\n";
    std::cout << "[2] Card\n";

    int paymentChoice;
    std::cout << "Enter your choice: ";
    std::cin >> paymentChoice;

    // Process payment based on user's choice
    if (paymentChoice == 1) {
        // Cash payment
        std::cout << "Payment Successful - Cash\n";
        PaymentStatus = "Paid - Cash";
    } else if (paymentChoice == 2) {
        // Card payment
        std::string cardNumber, cardName, cvv, expiryDate;

        // Prompt user for card details
        std::cout << "Enter Card Number: ";
        std::cin >> cardNumber;

        // Validate card number manually
        if (cardNumber[15] == '\0') {
            std::cout << "Enter Name on Card: ";
            std::cin >> cardName;

            std::cout << "Enter CVV: ";
            std::cin >> cvv;

            std::cout << "Enter Expiry Date (MM/YYYY): ";
            std::cin >> expiryDate;

            // Simulate processing (replace with actual payment gateway integration)
            std::cout << "Processing payment...\n";

            // Simulate success
            bool paymentSuccess = true;  // Always set to true for automatic success

            if (paymentSuccess) {
                std::cout << "Payment Successful - Card\n";
                PaymentStatus = "Paid - Card";
            } else {
                std::cout << "Payment Failed - Card\n";
                PaymentStatus = "Failed - Card";
            }
        } else {
            std::cout << "Invalid Card Number. Must be 16 digits.\n";
            PaymentStatus = "Failed - Card";
        }
    } else {
        std::cout << "Invalid choice. Payment Failed.\n";
        PaymentStatus = "Failed";
    }

    std::cout << "Payment Status: " << PaymentStatus << "\n";
}
CafeStaff::CafeStaff(int user_id, const std::string& user_name, const std::string& password)
    : User(user_id, user_name, password, "Staff")
{
    // Additional initialization for CafeStaff if needed
}

void CafeStaff::ViewMenu() const
{
    // Implementation to display the cafe's available items
    std::cout << "\nViewing menu as CafeStaff...\n";
    // Add code to retrieve and display the menu items
}

int CafeStaff::nextOrderID = 1;

void CafeStaff::ProcessOrder() const {
    // Read and display pending orders from order.txt
    std::ifstream orderFile("orders.txt");
    if (!orderFile.is_open()) {
        std::cerr << "Error opening order file.\n";
        return;
    }

    std::cout << "Pending Orders:\n";

    std::string line;
    while (std::getline(orderFile, line)) {
        std::cout << line << "\n";
    }

    orderFile.close();

    // Ask staff to select an order to process
    int orderIDToProcess;
    std::cout << "Enter the Order ID to process (or 0 to cancel): ";
    std::cin >> orderIDToProcess;

    if (orderIDToProcess == 0) {
        std::cout << "Order processing canceled.\n";
        return;
    }

    // Process the selected order directly from the original file
    std::ifstream orderFileIn("orders.txt");
    std::ofstream processedOrderFile("processed_orders.txt");

    if (!orderFileIn.is_open() || !processedOrderFile.is_open()) {
        std::cerr << "Error opening order files.\n";
        return;
    }

    bool orderProcessed = false;
    bool orderFound = false;

    while (std::getline(orderFileIn, line)) {
        // Check for both "Order ID" and "Order Item" lines in the same block
        if (line.find("customer id: " + std::to_string(orderIDToProcess)) != std::string::npos) {
            orderFound = true;
            processedOrderFile << line << "\n";
            processedOrderFile << "Order ID: " << nextOrderID << "\n";
            std::string currentItem;
            while (std::getline(orderFileIn, currentItem) && !currentItem.empty()) {
                if (currentItem.find("order item: ") != std::string::npos) {
                    orderProcessed = true;
                    // Move the processed order to the processed_orders.txt file
                    processedOrderFile << currentItem << "\n";
                    processedOrderFile << "Status: Processed\n";
                } else {
                    processedOrderFile << currentItem << "\n";
                }
            }
        } else {
            processedOrderFile << line << "\n";
        }
    }

    orderFileIn.close();
    processedOrderFile.close();

    // Increment the next order ID for the next order
    nextOrderID++;

    // Rename the processed_orders.txt file to keep track of processed orders
    std::rename("processed_orders.txt", "processed_orders_backup.txt");

    if (orderFound) {
        if (orderProcessed) {
            std::cout << "Order with ID " << orderIDToProcess << " processed successfully.\n";
        } else {
            std::cout << "No order items found for Order ID " << orderIDToProcess << ".\n";
        }
    } else {
        std::cout << "Order with ID " << orderIDToProcess << " not found.\n";
    }
}


void CafeStaff::AddMenuItem() const
{
    std::cout << "Adding new menu item as CafeStaff...\n";

}

void CafeStaff::RemoveMenuItem() const
{

    std::cout << "Removing menu item as CafeStaff...\n";

}

void CafeStaff::Logout() const
{
    // Implementation to logout the CafeStaff user
    std::cout << "Logging out as CafeStaff...\n";
    // Add code for logout actions
}

void CafeStaff::StaffMenu(CafeStaff& staff)
{
    while (true)
    {
        int staffChoice;
        Administrator admin(1221, "DefaultName", "hello");
        std::cout << "CafeStaff Options:\n[1] View Menu\n[2] Add Menu Item\n[3] Remove Menu Item\n[4] Process Order\n[5] Logout\nEnter your choice: ";
        std::cin >> staffChoice;

        switch (staffChoice)
        {
        case 1:
            admin.ViewMenu();
            break;
        case 2:
            admin.AddMenuItem();
            break;
        case 3:
            admin.RemoveMenuItem();
            break;
        case 4:
            staff.ProcessOrder();
            break;
        case 5:
            std::cout << "Logging out...\n";
            staff.Logout();
            return;
        default:
            std::cout << "Invalid choice\n";
            break;
        }
    }
}

//Adding out Menu item
MenuItem::MenuItem(int item_id, const std::string& item_name, const std::string& item_description, double price, int quantity_in_stock)
    : ItemID(item_id), ItemName(item_name), ItemDescription(item_description), Price(price), QuantityInStock(quantity_in_stock)
{
    // Additional initialization for MenuItem if needed
}

int MenuItem::GetItemID() const
{
    return ItemID;
}

std::string MenuItem::GetItemName() const
{
    return ItemName;
}

std::string MenuItem::GetItemDescription() const
{
    return ItemDescription;
}

double MenuItem::GetPrice() const
{
    return Price;
}

int MenuItem::GetQuantityInStock() const
{
    return QuantityInStock;
}

void MenuItem::UpdateStock(int new_quantity)
{
    // Method to update the stock quantity
    QuantityInStock = new_quantity;
}


int Order::orderCounter = 1;  // Initialize the static orderCounter

Order::Order(int customerID) : orderID(orderCounter++), customerID(customerID), itemCount(0), totalPrice(0.0), orderStatus("Pending") {}

void Order::AddItem(const std::string& item) {
    if (itemCount < maxItems) {
        itemsOrdered[itemCount++] = item;
        std::cout << "Added item to the order: " << item << "\n";
    }
    else {
        std::cout << "Maximum items reached in the order.\n";
    }
}

void Order::RemoveItem(const std::string& item) {
    for (int i = 0; i < itemCount; ++i) {
        if (itemsOrdered[i] == item) {
            // Remove the item by shifting elements
            for (int j = i; j < itemCount - 1; ++j) {
                itemsOrdered[j] = itemsOrdered[j + 1];
            }
            --itemCount;
            std::cout << "Removed item from the order: " << item << "\n";
            return;
        }
    }

    std::cout << "Item not found in the order.\n";
}

double Order::CalculateTotal() const {
    double total = 0.0;
    for (int i = 0; i < itemCount; ++i) {
        // Assume the prices are stored in a map or another data structure
        // You may need to modify this based on how your menu and pricing are implemented
        // For simplicity, assuming all items have a fixed price of $5.0
        total += 5.0;
    }
    return total;
}

void Order::ConfirmOrder() const {
    std::cout << "Order confirmed! Total price: $" << CalculateTotal() << "\n";
    // Call the method to process payment
    // processPayment();
    string orderStatus;
    orderStatus = "Confirmed";
}

void Order::CancelOrder() const {
    std::cout << "Order canceled.\n";
    string orderStatus;
    orderStatus = "Canceled";
}