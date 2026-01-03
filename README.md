# 🏧 ATM System – C++ Console Application

A C++ console-based ATM system that simulates real-world ATM operations with a strong focus on clean code, file handling, and structured programming. The project is designed to demonstrate how a complete banking workflow can be implemented using basic C++ concepts without external libraries or databases.

🚀 Features  
🔐 Login system with three attempts protection  
💸 Quick withdraw with predefined amounts  
💵 Normal withdraw with custom amount  
➕ Deposit money  
📊 Check account balance  
🔁 Logout and re-login  
💾 Persistent data storage using text files  

🛠️ Technologies Used  
🧠 C++  
📦 STL (vector, string)  
📂 File handling using fstream  
🖥️ Console application  

📂 Project Structure  
ATM-System-Cpp/  
├── ATM_System.cpp  
├── Clients.txt  
└── README.md  

💾 Data Storage  
All client data is stored in a text file called Clients.txt.  
Each line represents one client using the following format:  

AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance  

🧠 Project Design Overview  
The system uses a global session object to represent the currently logged-in client.  
All file operations are separated from business logic to keep the code clean and readable.  
Balance updates are handled through a single centralized function to avoid duplication.  
Menu navigation is implemented using enums for clarity and better control flow.  
The application flow is fully controlled and easy to follow.

🧹 Code Quality  
The project applies clean code principles such as avoiding duplicated logic, keeping each function responsible for a single task, using clear naming conventions, centralizing file updates, and maintaining a controlled and predictable program flow.

▶️ How to Run  
Clone the repository using:  
git clone https://github.com/your-username/ATM-System-Cpp.git  

Compile the project:  
g++ ATM_System.cpp -o ATM  

Run the application:  
./ATM  

👤 Sample Login Data  
You can test the system using the following sample data inside Clients.txt:  

1001#//#1234#//#Ahmed Ali#//#0100000000#//#5000  
1002#//#1111#//#Mohamed Salah#//#0111111111#//#8000  

🎯 Learning Outcomes  
Understanding how to work with text files as a simple database  
Building a complete console-based system from scratch  
Applying clean code principles in a real project  
Using enums to control menus and user choices  
Managing application flow and user session state  

🚀 Future Improvements  
Transfer between accounts  
Change PIN functionality  
Better input validation  
Convert the project to full OOP design  
Use binary files instead of text files  

📄 License  
This project is created for learning and educational purposes only.
