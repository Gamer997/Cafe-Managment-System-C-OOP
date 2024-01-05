#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
class User
{
protected:
    int UserID;
    std::string UserName;
    std::string Password;
    std::string UserType;
    std::string MenuFileName;

    // Update the User class constructor to accept the menu file name

public:
    User(int user_id, const std::string &user_name, const std::string &password, const std::string &user_type);
    User(int user_id, const std::string &user_name, const std::string &password, const std::string &user_type, const std::string &menu_file_name)
        : UserID(user_id), UserName(user_name), Password(password), UserType(user_type), MenuFileName(menu_file_name) {}
    void Register();
    bool Login(const std::string &entered_password) const;
    int GetUserID() const;
    std::string GetUserName() const;
    std::string GetUserPassword() const;
    std::string GetUserType() const;
    virtual void ViewMenu() const;
    virtual void PlaceOrder() const;
    virtual void ViewOrderHistory() const;
};

class UserManagementSystem
{
public:
    bool RegisterUser(User &user);
    bool AuthenticateUser(const std::string &user_type, int user_id, const std::string &entered_password);

private:
    bool CheckUserExists(const User &user);
};

class Administrator : public User
{
public:
    Administrator(int user_id, const std::string &user_name, const std::string &password);

    // Add other necessary methods for the Administrator class
    void AdminMenu(Administrator &admin);
    void ViewMenu() const override;
    void AddMenuItem();
    void RemoveMenuItem();
    void ManageInventory();
    void ManageDiscountPromotion();
    void ViewOrderHistory();
    void AddNotification();
    void RemoveNotification();
    void RateMenuItem();
    void DisplayFromFile(const std::string &filename);
    void ViewUsersFromFile();
    void ViewMenuItemsFromFile();
    void ViewOrdersFromFile();
    void ViewRatingsFromFile();
    void ViewPaymentsFromFile();
    void CalculateMonthlyEarnings();
    void Logout();
    void AddOrUpdateDiscount();
    void RemoveDiscount();

    std::string GetMenuTypeFromAdmin() const;

};

class Customer : public User
{
private:
    string MenuFileName; // Assuming this is the member variable for the menu file name

public:
    Customer(int customer_id, const std::string &customer_name, const std::string &user_type, const std::string &menu_file_name);
    virtual void ViewMenu() const;
    void PlaceOrder() const;
    void ViewOrderHistory() const;
    void RateMenuItem() const;
    void Logout() const;
    void CustomerMenu(Customer &customer);
};
class Student : public Customer
{
public:
    Student(int customer_id, const std::string &customer_name)
        : Customer(customer_id, customer_name, "Student", "student_menu.txt") {}

    // Override ViewMenu to provide specific implementation for students if needed
    void ViewMenu() const override
    {
        Customer::ViewMenu(); // Call the base class implementation
        // Add specific implementation for student menu if needed
    }
};

class Faculty : public Customer
{
public:
    Faculty(int customer_id, const std::string &customer_name)
        : Customer(customer_id, customer_name, "Student", "student_menu.txt") {}

    // Override ViewMenu to provide specific implementation for students if needed
    void ViewMenu() const override
    {
        Customer::ViewMenu(); // Call the base class implementation
    }
};

class Non_Faculty : public Customer
{
public:
    Non_Faculty(int customer_id, const std::string &customer_name)
        : Customer(customer_id, customer_name, "Non_Faculty", "non_faculty_menu.txt") {}

    // Override ViewMenu to provide specific implementation for non-faculty if needed
    void ViewMenu() const override
    {
        Customer::ViewMenu(); // Call the base class implementation
        // Add specific implementation for non-faculty menu if needed
    }
};
struct InventoryItem
{
    std::string itemName;
    int quantity;
};

class Rating
{
    private:
     int RatingID;
    int MenuItemID;
    int CustomerID;
    int Score;
    std::string Comment;

    public:
    public:
    Rating(int rating_id, int menu_item_id, int customer_id, int score, const std::string &comment);
    void Rate();

};

class Payment {
private:
    int PaymentID;
    int OrderID;
    double Amount;
    std::string PaymentStatus;

public:
    Payment(int payment_id, int order_id, double amount, const std::string &payment_status);
    void ProcessPayment();
};
class CafeStaff : public User
{
public:
    CafeStaff(int user_id, const std::string& user_name, const std::string& password);

    void ViewMenu() const;
    void ProcessOrder() const;
    void AddMenuItem() const;
    void RemoveMenuItem() const;
    void Logout() const;
    void StaffMenu(CafeStaff& staff);
private:
    static int nextOrderID;
};

class MenuItem
{
private:
    int ItemID;
    std::string ItemName;
    std::string ItemDescription;
    double Price;
    int QuantityInStock;

public:
    MenuItem(int item_id, const std::string& item_name, const std::string& item_description, double price, int quantity_in_stock);

    // Getter methods for attributes
    int GetItemID() const;
    std::string GetItemName() const;
    std::string GetItemDescription() const;
    double GetPrice() const;
    int GetQuantityInStock() const;

    // Method to update the stock quantity
    void UpdateStock(int new_quantity);
};
class Order {
private:
    static int orderCounter;  // Static counter to generate unique order IDs
    int orderID;
    int customerID;
    static const int maxItems = 10;  // Maximum items in the order
    std::string itemsOrdered[maxItems];
    int itemCount;
    double totalPrice;
    std::string orderStatus;

public:
    // Constructor
    Order(int customerID);

    // Methods
    void AddItem(const std::string& item);
    void RemoveItem(const std::string& item);
    double CalculateTotal() const;
    void ConfirmOrder() const;
    void CancelOrder() const;
};