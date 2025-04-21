# 🗨️ Simple Local Chat Application

A local network-based chat application using **C++ (for server and CLI client)** and a **Python GUI frontend**, built using **socket programming** and **multithreading**.

---

## 📂 Project Structure

| File | Language | Description |
|------|----------|-------------|
| `server.cpp` | C++ | Handles incoming socket connections and communication |
| `client.cpp` | C++ | (Optional) Command-line chat client |
| `chat_gui.py` | Python | GUI-based client for sending and receiving messages |

---

## 🚀 Features

- 🔌 Socket programming
- 🧵 Multithreading (handles multiple clients)
- 🖥️ GUI interface for chatting (Python)
- 🕒 Timestamp with each message
- 📁 Message logging system (Optional future feature)

---

## 🛠️ Technologies Used

- C++ (Sockets via WinSock)
- Python (Tkinter, socket)
- Windows Platform (WinSock API)

---

## 📸 Screenshots

![image](https://github.com/user-attachments/assets/a2ce73fa-d412-47f2-b17b-53317c00d79a)


---

## 💡 How to Run

### ⚙️ Requirements
- C++ Compiler (e.g., MinGW on Windows)
- Python 3.x installed
- Tkinter (usually comes with Python)

---

### 🖥️ Step-by-Step Instructions

#### 1️⃣ Compile and Run the Server
```bash
g++ server.cpp -o server -lws2_32
./server
2️⃣ Run the Python GUI Client
python chat_gui.py

3️⃣Run the C++ CLI Client
g++ client.cpp -o client -lws2_32
./client
