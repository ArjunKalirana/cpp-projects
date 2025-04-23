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

### 🧪 Compile and Run

```bash
g++ main.cpp -o password_manager
./password_manager
🔐 Master Password Setup
On first run, you'll be asked to set a master password.

It will be saved (hashed) in master.hash.

On future runs, this password will be required for access.

🧠 How It Works
Your passwords are stored in password.txt after being XOR-encrypted using the master password.

The master password is hashed and compared every time you start the app.

The saved credentials are decrypted on load.

❗️Note
A Python-based GUI frontend is currently under development, but is not yet integrated. The current version runs solely in the console.

🛡️ Disclaimer
This is an educational project and should not be used for storing real passwords. XOR encryption and simple hash functions are not secure for production.

✨ Future Improvements
Integrate a Tkinter-based GUI (currently under development).

Use secure encryption like AES.

Cross-platform support.

Search/filter services.

📄 License
This project is open-source and free to use under the MIT License.

Would you like me to generate a version with Markdown styling preview (like emojis, colored titles,
