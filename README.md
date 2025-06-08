# Employee-Management-System

This is a simple console-based Employee Management System implemented in C++. It allows users to register, log in, and perform basic CRUD (Create, Read, Update, Delete) operations on employee records.
## Table Of Content
- [Features](##Features)
- [How to Complie and Run](##HowtoCompileandRun)
- [Usage](##Usage)
- [Important Notes and Limitations](##ImportantNotesandLimitations)
## Features
- User Authentication:
  - **Sign Up:** Create a new user account with a username and password.
  - **Login:** Authenticate as an existing user to access employee management functionalities.
    
- Employee Management:
  - **Add Employee:** Create a new employee record with ID, Name, Salary, and Department.
  - **View All Employees:** Display a formatted table of all registered employees, including their net salary (after tax).
  - **View Single Employee:** Retrieve and display detailed information for a specific employee by their ID.
  - **Update Employee:** Modify an existing employee's salary or department by their ID.
  - **Delete Employee:** Remove an employee record from the system by their ID.
- Calculations: Automatically calculates net salary after a 10% tax deduction.
- Input Validation: Basic error handling for invalid numeric inputs.
- Cross-Platform Console Clearing: Uses system("cls") for Windows and system("clear") for Unix-like systems (Linux/macOS) to clear the console screen.
## How to Compile and Run
To compile and run this program, you will need a C++ compiler (like g++).<br>

**Save the code:** Save the provided C++ code into a file named ***EmployeeManegmentSystem.cpp***.<br>

**Open a terminal or command prompt:** Navigate to the directory where you saved ***EmployeeManegmentSystem.cpp***.<br>

**Compile the code:** Execute the following command:
 > g++ EmployeeManegmentSystem.cpp -o EmployeeManegmentSystem<br>
 
***This command compiles the source code and creates an executable file named employee_management (or EmployeeManegmentSystem.exe on Windows).***<br>

**Run the program:** Execute the compiled program: 
 > ./EmployeeManegmentSystem<br>

(On Windows, you might just type employee_management.exe or employee_management)<br>

## Usage
Once the program starts, you will be presented with a main menu:<br>
LOGIN: If you have an existing account.<br>
SIGNUP: To create a new account.<br>
Exit: To close the application.<br>
### Signing Up
Choose 2. SIGNUP.<br>
Enter a desired username and password. Your credentials will be saved to database.txt.<br>
### Logging In
Choose 1. LOGIN.<br>
Enter your registered username and password.<br>
Upon successful login, you'll enter the Employee Menu:<br>
- 1\. Add Employee: Input details for a new employee.<br>
- 2\. View All Employees: See a tabular list of all current employees.<br>
- 3\. View Single Employee (by ID): Enter an Employee ID to display their specific Name, Department, Salary, and Net Salary.<br>
- 4\. Update Employee: Change an employee's salary or department.<br>
- 5\. Delete Employee: Remove an employee record.<br>
- 6\. Exit Employee Menu: Return to the main Login/Signup menu.<br>
## Important Notes and Limitations
- **No Data Persistence for Employees:** All employee data is stored in memory (std::vector<Employee>) and will be lost when the program terminates. For real-world use, you would need to implement saving and loading employee data to a file (e.g., CSV, JSON, or a binary file).<br>
- **Plaintext Password Storage:** User authentication details (username and password) are stored in a plain text file (database.txt). This is a significant security vulnerability. For any production application, passwords should always be hashed and salted.<br>
- **Basic Error Handling:** Input validation is present for numeric inputs, but more comprehensive error handling for other scenarios (e.g., duplicate employee IDs, invalid string inputs) could be added.<br>
- **Console-Based:** This is a command-line interface (CLI) application.<br>

