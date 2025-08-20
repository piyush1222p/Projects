# Projects Repository

Welcome to the **Projects** repository by [Piyush Shukla](https://github.com/piyush1222p). This repository showcases C++ projects with an emphasis on practical applications and object-oriented programming principles. The primary project included is a comprehensive **Bank Management System**.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [File Descriptions](#file-descriptions)
- [License](#license)
- [Author](#author)

---

## Overview

This repository contains a robust **Bank Management System** written in C++. It is designed to demonstrate key programming concepts such as object-oriented design, data persistence using JSON, and secure user authentication. The system enables users to manage bank accounts and perform essential banking operations through a command-line interface.

---

## Features

- **Account Management:**  
  - Create, access, and manage personal bank accounts with unique credentials.
- **Secure Authentication:**  
  - Login functionality using account numbers and passwords.
- **Banking Operations:**  
  - Deposit and withdraw funds.
  - Balance inquiries.
  - Fund transfers between accounts.
- **Data Persistence:**  
  - All account information is stored securely in a JSON file using the [nlohmann/json](https://github.com/nlohmann/json) library.
- **Object-Oriented Architecture:**  
  - The system is modular, maintainable, and follows best practices in C++ development.

---

## Project Structure

```
.
├── .gitignore
├── BankManagementSystem.c++
├── accounts.json
├── json.hpp
```

---

## Getting Started

### Prerequisites

- C++ compiler (e.g., `g++`, `clang++`)
- [nlohmann/json](https://github.com/nlohmann/json) header file (`json.hpp`) — included in this repository
- Familiarity with basic C++ and command-line operations

### Compilation

```sh
g++ BankManagementSystem.c++ -o BankManagementSystem
```

### Running the Application

```sh
./BankManagementSystem
```

---

## Usage

1. **Launch** the application using the command above.
2. **Navigate** the interactive menu to:
    - Create a new account
    - Log in to an existing account
3. **Perform Operations:**
    - Deposit or withdraw funds
    - Check your account balance
    - Transfer money to another account
4. **Data is automatically saved** to `accounts.json` after every operation.

---

## File Descriptions

- **BankManagementSystem.c++**:  
  Contains the main implementation of the banking system, including the `BankAccount` and `Bank` classes, user interface logic, and file handling.
- **accounts.json**:  
  Stores all account data in JSON format. Example:
    ```json
    [
      {
        "AccountHolderName": "Piyush Shukla",
        "AccountNumber": "9315310130",
        "Balance": 13140.0,
        "Password": "Piyush@34354961"
      }
    ]
    ```
    > **Note:** Passwords are stored in plain text for demonstration only. Do not use real or sensitive credentials.
- **json.hpp**:  
  Single-header JSON library ([nlohmann/json](https://github.com/nlohmann/json)) for C++.
- **.gitignore**:  
  Specifies files and directories to be excluded from version control.

---

## License

This repository does not currently include an open source license. For usage, modification, or distribution permissions, please contact the repository owner.

---

## Author

**Piyush Shukla**  
[GitHub: piyush1222p](https://github.com/piyush1222p)

---

[View on GitHub](https://github.com/piyush1222p/Projects)