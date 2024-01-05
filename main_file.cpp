#include "Header_file.h"
#include<iostream>
using namespace std;
int main() {
    UserManagementSystem userSystem;
    cout << " .--..--..--..--..--..--..--..--..--..--..--..--..--..--. " << endl;
    cout << "/ .. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\ \\ \\" << endl;
    cout << "\\ \\/\\ `\'\\ `\'\\ `\'\\ `\'\\ `\'\\ `\'\\ `\'\\ `\'\\ `\'\\ `\'\\ `\'\\ \\/\\" << endl;
    cout << " \\/ /`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\\/ /" << endl;
    cout << " / /\\                                                / /\\ " << endl;
    cout << "/ /\\ \\   _____         _      ____       __         / /\\ \\" << endl;
    cout << "\\ \\/ /  |  ___|_ _ ___| |_   / ___|__ _ / _| ___    \\ \\/ /" << endl;
    cout << " \\/ /   | |_ / _` / __| __| | |   / _` | |_ / _ \\    \\/ / " << endl;
    cout << " / /\\   |  _| (_| \\__ \\ |_  | |__| (_| |  _|  __/    / /\\ " << endl;
    cout << "/ /\\ \\  |_|  \\__,_|___/\\__|  \\____\\__,_|_|  \\___|   / /\\ \\" << endl;
    cout << "\\ \\/ /                                              \\ \\/ /" << endl;
    cout << " \\/ /                                                \\/ / " << endl;
    cout << " / /\\.--..--..--..--..--..--..--..--..--..--..--..--./ /\\ " << endl;
    cout << "/ /\\ \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\ /" << endl;
    cout << "\\ `\'\\ `\'\\ `\'\\ `\'\\ `\'\\ `\'\\ `\'\\ `\'\\ `\'\\ `\'\\ `\'\\ `\'\\ `\' /" << endl;
    cout << " `--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--' " << endl;


    while (true) {
        int choice;
        std::cout << "\nSelect Option:\n[1] Login\n[2] Register\n[3] Exit\nEnter your choice: ";
        std::cin >> choice;

        if (choice == 3) {
            std::cout << "Exiting...\n\n";
            std::cout << "******************************************" <<std:: endl;
            std::cout << "******Thanks for using our fast cafe******\n";
            std::cout << "******************************************" << std::endl;
            break;
        }

        int userId;
        std::string password;

        switch (choice) {
        case 1: {
            // Inside the login part of the main function
            int loginChoice;
            std::cout << "\nSelect User Type:\n [1] Administrator\n [2] Staff\n [3] Student\n [4] Faculty\n [5] Non-Faculty\nEnter your choice: ";
            std::cin >> loginChoice;

            std::string userType;
            std::string menuFileName;  

            switch (loginChoice) {
            case 1:
                userType = "Administrator";
                menuFileName = "admin_menu.txt";  // Setting the menu file name for the administrator
                break;
            case 2:
                userType = "Staff";
                menuFileName = "staff_menu.txt";  // Setting the menu file name for the staff
                break;
            case 3:
                userType = "Student";
                menuFileName = "student_menu.txt";  // Setting the menu file name for the student
                break;
            case 4:
                userType = "Faculty";
                menuFileName = "faculty_menu.txt";  // Setting the menu file name for the faculty
                break;
            case 5:
                userType = "Non_Faculty";
                menuFileName = "non_faculty_menu.txt";  // Setting the menu file name for the non-faculty
                break;
            default:
                std::cout << "Invalid choice\n";
                return 1;
            }

            cout << "Enter User ID: ";
            cin >> userId;
            cout << "Enter Password: ";
            cin >> password;
            string Name;
            cout << "Enter your Name: ";
            cin.ignore();
            getline(cin, Name);
            if (userSystem.AuthenticateUser(userType, userId, password)) {
                std::cout << "Login successful!\n";
                if (userType == "Administrator") {
                    Administrator admin(userId, Name, password);
                    admin.AdminMenu(admin);
                }
                // Add conditions for other user types and their respective menus
                else if (userType == "Student") {
                    Student student(userId, Name);
                    student.CustomerMenu(student);
                    // Add other operations for students
                }
                else if (userType == "Faculty") {
                    Faculty faculty(userId, Name);
                    faculty.CustomerMenu(faculty);
                    // Add other operations for faculty
                }
                else if (userType == "Non_Faculty") {
                    Non_Faculty nonFaculty(userId, Name);
                    nonFaculty.CustomerMenu(nonFaculty);
                }
                else if (userType == "Staff") {
                    CafeStaff staff(userId, Name, password);
                    staff.StaffMenu(staff);
                }
                else {
                    std::cout << "Invalid user choice\n" << std::endl;
                }
            }
            else {
                std::cout << "Login failed. Invalid credentials.\n";
            }

        } break;

        case 2: {

            int registerChoice;
            std::cout << "Select User Type for Registration:\n1. Administrator\n2. Staff\n3. Student\n4. Faculty\n5. Non-Faculty\nEnter your choice: ";
            std::cin >> registerChoice;

            std::string userType;
            std::string menuFileName;  // Add a variable to store the menu file name
            string Name;
            cin.ignore();
            cout << "Enter your Name: ";
            getline(cin, Name);
            switch (registerChoice) {
            case 1:
                userType = "Administrator";
                menuFileName = "admin_menu.txt";  // Setting the menu file name for the administrator
                break;
            case 2:
                userType = "Staff";
                menuFileName = "staff_menu.txt";  // Setting the menu file name for the staff
                break;
            case 3:
                userType = "Student";
                menuFileName = "students_menu.txt";  // Setting the menu file name for the student
                break;
            case 4:
                userType = "Faculty";
                menuFileName = "faculty_menu.txt";  // Setting the menu file name for the faculty
                break;
            case 5:
                userType = "Non_Faculty";
                menuFileName = "non_faculty_menu.txt";  // Setting the menu file name for the non-faculty
                break;
            default:
                std::cout << "Invalid choice\n";
                return 1;
            }

            std::cout << "Enter User ID: ";
            std::cin >> userId;
            std::cout << "Enter Password: ";
            std::cin >> password;

            User newUser(userId, Name, password, userType, menuFileName);

            // Register the user
            if (!userSystem.RegisterUser(newUser)) {
                std::cout << "Registration failed.\n";
            }
            else {
                std::cout << "Registration successful!\n";
            }

        } 
              break;

        default:
            std::cout << "Invalid choice\n";
            break;
        }
    }

    return 0;
}