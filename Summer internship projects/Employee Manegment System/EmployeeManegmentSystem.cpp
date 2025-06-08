
#include <iostream>  // For input/output operations (cin, cout)
#include <fstream>   // For file stream operations (ifstream, ofstream)
#include <string>    // For using std::string
#include <vector>    // For using std::vector to store Employee objects
#include <iomanip>   // For output formatting (setprecision, fixed, setw)
#include <limits>    // For numeric_limits, useful for robust input clearing
#include <algorithm> // For std::transform (to convert strings to lowercase for case-insensitive search)

#ifdef _WIN32
#include <windows.h> // Potentially needed for some Windows-specific console functions, though system("cls") might not strictly require it.
#endif

// --- Employee Class Definition ---
// Represents an individual employee with their details and related operations.
class Employee {
private:
    int EmployeeID;       // Unique identifier for the employee
    std::string Name;     // Employee's full name
    double Salary;        // Employee's gross salary
    std::string Department; // Department the employee belongs to

public:
    // Constructor: Initializes an Employee object with provided data.
    Employee(int id, std::string empName, double empSalary, std::string empDepartment)
        : EmployeeID(id), Name(empName), Salary(empSalary), Department(empDepartment) {}

    // Getter methods: Allow read-only access to employee attributes.
    // 'const' indicates that these methods do not modify the object's state.
    int getID() const { return EmployeeID; }
    std::string getName() const { return Name; }
    double getSalary() const { return Salary; }
    std::string getDepartment() const { return Department; }

    // Setter methods: Allow modification of specific employee attributes.
    void setSalary(double newSalary) { Salary = newSalary; }
    void setDepartment(std::string newDept) { Department = newDept; }

    // display() method: Prints the employee's information to the console.
    // This method is now simplified as viewemployee() will handle detailed tabular output,
    // and viewSingleEmployee() will use this for individual display.
    void display() const {
        std::cout << "ID: " << EmployeeID
                  << ", Name: " << Name
                  << ", Salary: " << std::fixed << std::setprecision(2) << Salary // Format salary to two decimal places
                  << ", Department: " << Department << std::endl;
    }

    // calculateNetSalary() method: Calculates salary after a 10% tax deduction.
    double calculateNetSalary() const {
        return Salary - (Salary * 0.10); // 10% tax deduction
    }
};

// --- Global Data Storage ---
// A global vector to store all Employee objects in memory.
// WARNING: Data stored here is LOST when the program exits.
// For persistent storage, you would need to implement file saving/loading.
std::vector<Employee> employees;

// --- Utility Function: Clear Screen ---
// Provides a cross-platform way to clear the console.
void clearScreen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Unix-like systems (Linux, macOS)
#endif
}

// --- Employee Management Functions ---

// Function to add a new employee to the system.
void addemployee() {
    int id;
    std::string Name, Department;
    double Salary;

    std::cout << "Enter EmployeeID: ";
    // Input validation for ID can be added here (e.g., check for unique ID)
    while (!(std::cin >> id)) {
        std::cout << "Invalid input. Please enter a number for EmployeeID: ";
        std::cin.clear(); // Clear error flags
        // Discard invalid input up to the newline character
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume the leftover newline character

    std::cout << "Enter Name: ";
    std::getline(std::cin, Name);

    std::cout << "Enter Salary: ";
    while (!(std::cin >> Salary)) {
        std::cout << "Invalid input. Please enter a number for Salary: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume the leftover newline character

    std::cout << "Enter Department: ";
    std::getline(std::cin, Department);

    employees.push_back(Employee(id, Name, Salary, Department));
    std::cout << "Employee Added Successfully.\n";
}

// Function to display all existing employees and their net salaries in a tabular format.
void viewemployee() {
    if (employees.empty()) {
        std::cout << "No Employees to Display.\n";
        return;
    }

    std::cout << "\n--- All Employees List ---\n";
    // Set up table headers with appropriate width
    std::cout << std::left // Align text to the left
              << std::setw(5) << "ID"
              << std::setw(20) << "Name"
              << std::setw(15) << "Salary"
              << std::setw(18) << "Net Salary"
              << std::setw(20) << "Department"
              << std::endl;
    // Print a separator line
    std::cout << std::string(78, '-') << std::endl; // Adjust length based on column widths

    // Iterate through the vector and print each employee's details in a row
    for (const auto& emp : employees) {
        std::cout << std::left
                  << std::setw(5) << emp.getID()
                  << std::setw(20) << emp.getName()
                  << std::setw(15) << std::fixed << std::setprecision(2) << emp.getSalary()
                  << std::setw(18) << std::fixed << std::setprecision(2) << emp.calculateNetSalary()
                  << std::setw(20) << emp.getDepartment()
                  << std::endl;
    }
    std::cout << std::string(78, '-') << std::endl; // Adjust length
    std::cout << "---------------------\n";
}

// Function to view a single employee's details by their ID.
void viewSingleEmployee() {
    int id;
    std::cout << "Enter Employee ID to view: ";
    while (!(std::cin >> id)) {
        std::cout << "Invalid input. Please enter a number for EmployeeID: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    // FIX: Consume the leftover newline character immediately after reading the ID.
    // This ensures that the subsequent std::cin.get() in the calling function (employeeManagementMenu)
    // will actually pause and wait for a new Enter press from the user.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool found = false;
    for (const auto& emp : employees) {
        if (emp.getID() == id) {
            found = true;
            std::cout << "\n--- Employee Details (ID: " << id << ") ---\n";
            // Explicitly display Name, Department, and Salary as requested
            std::cout << "Name: " << emp.getName() << std::endl;
            std::cout << "Department: " << emp.getDepartment() << std::endl;
            std::cout << "Salary: " << std::fixed << std::setprecision(2) << emp.getSalary() << std::endl;
            std::cout << "Net Salary (after tax): " << std::fixed << std::setprecision(2) << emp.calculateNetSalary() << std::endl;
            std::cout << "-------------------------------------------\n";
            break; // Found the employee, no need to continue searching
        }
    }
    if (!found) {
        std::cout << "Employee with ID " << id << " not found.\n";
    }
}

// Function to update an existing employee's salary or department.
void updateemployee() {
    int id;
    std::cout << "Enter Employee ID to update: ";
    while (!(std::cin >> id)) {
        std::cout << "Invalid input. Please enter a number for EmployeeID: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    bool found = false;
    // Iterate through the vector using a non-const reference to allow modification
    for (auto& emp : employees) {
        if (emp.getID() == id) {
            found = true;
            int choice;
            std::cout << "Employee Found! What do you want to update?\n";
            std::cout << "1. Update Salary\n2. Update Department\nChoose option: ";
            while (!(std::cin >> choice)) {
                std::cout << "Invalid input. Please enter 1 or 2: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline after 'choice'

            if (choice == 1) {
                double newSalary;
                std::cout << "Enter new salary: ";
                while (!(std::cin >> newSalary)) {
                    std::cout << "Invalid input. Please enter a number for salary: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                emp.setSalary(newSalary);
            } else if (choice == 2) {
                std::string newDept;
                std::cout << "Enter new department: ";
                std::getline(std::cin, newDept);
                emp.setDepartment(newDept);
            } else {
                std::cout << "Invalid option chosen for update.\n";
            }
            std::cout << "Employee Data Updated Successfully.\n";
            return; // Exit after updating
        }
    }
    if (!found) {
        std::cout << "Employee not found.\n";
    }
}

// Function to delete an employee from the system based on their ID.
void deleteemployee() {
    int id;
    std::cout << "Enter EmployeeID to delete: ";
    while (!(std::cin >> id)) {
        std::cout << "Invalid input. Please enter a number for EmployeeID: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    bool found = false;
    // Iterate and erase using an iterator
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if (it->getID() == id) {
            employees.erase(it); // Erase the employee from the vector
            found = true;
            std::cout << "Employee Deleted Successfully.\n";
            break; // Exit loop after deletion
        }
    }
    if (!found) {
        std::cout << "Employee not found.\n";
    }
}

// --- Authentication Functions ---

// Displays the main menu for the application (Login, Signup, Exit).
void displayMainMenu() {
    clearScreen();
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";
    std::cout << "                         Employee Management System                        \n\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~           MENU           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    std::cout << "1. LOGIN\n";
    std::cout << "2. SIGNUP\n";
    std::cout << "3. Exit\n";
    std::cout << "\nEnter your choice :";
}

// Displays the menu for employee management operations (Add, View All, View Single, Update, Delete, Exit).
void employeeManagementMenu() {
    int options;
    do {
        clearScreen();
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";
        std::cout << "                         Employee Management System                         \n\n";
        std::cout << "~~~~~~~~~~~~~~~~~~~           EMPLOYEE MENU           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        std::cout << "1. Add Employee\n";
        std::cout << "2. View All Employees\n";
        std::cout << "3. View Single Employee (by ID)\n";
        std::cout << "4. Update Employee\n";
        std::cout << "5. Delete Employee\n";
        std::cout << "6. Exit Employee Menu\n";
        std::cout << "Enter Your Choice: ";
        while (!(std::cin >> options) || (options < 1 || options > 6)) { // Updated range for validation
            std::cout << "Invalid input. Please enter a number between 1 and 6: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume the newline

        switch (options) {
            case 1: addemployee(); break;
            case 2: viewemployee(); break; // View all employees
            case 3: viewSingleEmployee(); break; // View single employee by ID
            case 4: updateemployee(); break; // Shifted from 3 to 4
            case 5: deleteemployee(); break; // Shifted from 4 to 5
            case 6: // Shifted from 5 to 6
                std::cout << "Returning to Main Menu...\n";
                break;
            default: // Should be caught by input validation, but as a fallback
                std::cout << "Invalid option. Please choose from 1 to 6.\n";
                break;
        }
        // Pause to allow user to read output before clearing screen for next menu display
        if (options != 6) { // Changed condition to match new exit option
            std::cout << "\nPress Enter to continue...";
            std::cin.get(); // Waits for user to press Enter
        }
    } while (options != 6); // Loop until user chooses to exit this menu (option 6)
}

// Handles user login.
void login() {
    std::string user, pass, u, p;
    clearScreen();
    std::cout << "Please enter your login details:\n";
    std::cout << "USERNAME :";
    std::cin >> user;
    std::cout << "PASSWORD :";
    std::cin >> pass;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline after password

    std::ifstream input("database.txt"); // Open file to read credentials
    bool loggedIn = false;

    if (input.is_open()) { // Check if file opened successfully
        while (input >> u >> p) { // Read username and password pairs
            if (u == user && p == pass) { // Compare input with stored credentials
                loggedIn = true;
                break; // Login successful, no need to read further
            }
        }
        input.close(); // Close the file
    } else {
        std::cout << "Error: User database file 'database.txt' not found or could not be opened.\n";
        std::cout << "Please try signing up first if you're a new user.\n";
        std::cout << "Press Enter to continue...";
        std::cin.get();
        return; // Return to main menu
    }

    if (loggedIn) {
        clearScreen();
        std::cout << "\nHello " << user << "!\n<LOGIN SUCCESSFUL>\n";
        std::cout << "Press Enter to continue...";
        std::cin.get(); // Wait for user to read success message
        employeeManagementMenu(); // Navigate to the employee management menu
    } else {
        std::cout << "\nLOGIN ERROR\nPlease check your username and password.\n";
        std::cout << "Press Enter to continue...";
        std::cin.get(); // Wait for user to read error message
    }
}

// Handles user registration.
void signup() {
    std::string reguser, regpass, u, p;
    clearScreen();
    std::cout << "Enter a new username :";
    std::cin >> reguser;
    std::cout << "Enter a new password :";
    std::cin >> regpass;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline

    // Optional: Check if username already exists before registering
    std::ifstream checkUser("database.txt");
    if (checkUser.is_open()) {
        while (checkUser >> u >> p) {
            if (u == reguser) {
                std::cout << "Username '" << reguser << "' already exists. Please choose a different one.\n";
                checkUser.close();
                std::cout << "Press Enter to continue...";
                std::cin.get();
                return; // Go back to main menu or re-prompt signup
            }
        }
        checkUser.close();
    }

    // Open file in append mode (ios::app) to add new credentials without overwriting
    std::ofstream reg("database.txt", std::ios::app);
    if (reg.is_open()) { // Check if file opened successfully for writing
        reg << reguser << ' ' << regpass << std::endl; // Write username and password
        reg.close(); // Close the file
        clearScreen();
        std::cout << "\nRegistration Successful!\n";
    } else {
        std::cout << "\nError: Could not open database file for registration.\n";
    }
    std::cout << "Press Enter to continue...";
    std::cin.get(); // Wait for user to acknowledge registration status
}

// --- Main Function ---
// The entry point of the program.
int main() {
    int choice;
    // Loop indefinitely until the user explicitly chooses to exit
    do {
        displayMainMenu(); // Show the main login/signup/exit menu
        while (!(std::cin >> choice)) { // Input validation for main menu choice
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume the leftover newline

        switch (choice) {
            case 1:
                login(); // Call login function
                break;
            case 2:
                signup(); // Call signup function
                break;
            case 3:
                std::cout << "Bye, Have a nice day.\n"; // Exit message
                break;
            default:
                std::cout << "Invalid input. Please choose from choices 1, 2 or 3.\n";
                std::cout << "Press Enter to continue...";
                std::cin.get(); // Wait for user to acknowledge error
                break;
        }
    } while (choice != 3); // Continue looping until choice is 3 (Exit)

    return 0; 
}
