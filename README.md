# 🏦 Bank & ATM Management System

A menu-driven Bank and ATM Management System developed in C++ using Object-Oriented Programming principles. The project simulates basic banking operations including account management, ATM services, fund transfers, and payment record management.

## Features

### Bank Management
- Create new bank accounts
- Deposit money
- Withdraw money
- Transfer funds between accounts
- Make payments
- Search account details
- Edit account information
- Delete accounts
- Display all account records
- View payment history
- Automatic loading of account and payment records on startup
- Persistent data storage using file handling

### ATM Module
- User login
- Balance inquiry
- Cash withdrawal
- Account details
- Logout functionality

## Technologies Used

- C++
- Object-Oriented Programming (OOP)
- STL (Vector)
- Menu-Driven Console Application
- File Handling (fstream)

## OOP Concepts Used

- Classes & Objects
- Encapsulation
- Abstraction
- Modular Programming
- Function Decomposition

## Project Structure


main.cpp
│
├── Account Class
├── PaymentRecord Structure
├── BankManagementSystem Class
├── ATMSystem Class
└── Main Menu


## System Workflow


Main Menu
│
├── ATM System
│     ├── Login
│     ├── Check Balance
│     ├── Withdraw
│     └── Account Details
│
└── Bank Management
      ├── Create Account
      ├── Deposit
      ├── Withdraw
      ├── Transfer
      ├── Payment
      ├── Search
      ├── Edit
      ├── Delete
      └── View Records


## How to Run

### Compile

bash
g++ main.cpp -o bank


### Run

bash
./bank


## Future Improvements

- File handling for permanent data storage
- Database integration (MySQL/PostgreSQL)
- PIN-based authentication
- Password encryption
- Transaction logs
- GUI implementation
- Online banking features
- Build a REST API
- JWT Authentication

## Learning Outcomes

- Applied Object-Oriented Programming concepts
- Implemented modular software design
- Practiced STL containers
- Built a menu-driven console application
- Simulated real-world banking operations
