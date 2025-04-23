# 🔐 Simple C++ Password Manager

A simple, secure, and beginner-friendly password manager built in **C++**, using basic file encryption and a master password system. All passwords are stored locally in an encrypted format using a basic XOR cipher.

---

## 📁 Features

- Add new passwords for different services.
- View saved usernames and passwords.
- Master password authentication system.
- Data is saved locally in encrypted form.
- Console-based user interface.

---

## 📦 Files Structure

├── main.cpp # Main C++ application (Password Manager) 
├── password.txt # Encrypted storage of saved credentials 
├── master.hash # Hashed master password 
├── README.md # Project documentation

---

## 🚀 Getting Started

### 🔧 Requirements

- C++17 or above
- A compiler (like `g++` or MSVC)
- Windows OS (uses `windows.h` for output encoding)

**##❗️Note**
A Python-based GUI frontend is currently under development, but is not yet integrated. The current version runs solely in the console.

### 🧪 Compile and Run

```bash
g++ main.cpp -o password_manager
./password_manager
---
