import tkinter as tk
from tkinter import messagebox
import subprocess
from tkinter import simpledialog 
import os

def run_program(mode):
    try:
        # Prompt master password from user
        master_password = simpledialog.askstring("Master Password", "Enter Master Password:", show='*')
        if not master_password:
            return  # User cancelled

        if mode == "add":
            full_input = f"{master_password}\n1\n"
        elif mode == "view":
            full_input = f"{master_password}\n2\n"
        else:
            root.destroy()
            return

        # Run exe and provide full input
        subprocess.run(
            ["C:\\Users\\Dell\\Desktop\\C\\password_manager\\password_manager.exe"],
            input=full_input.encode(),
            shell=True
        )
    except Exception as e:
        messagebox.showerror("Error", f"An error occurred: {e}")


root = tk.Tk()
root.title("Password Manager")
root.geometry("300x200")
root.configure(bg="#222222")

tk.Label(root, text="Simple Password Manager", font=("Arial", 14, "bold"), fg="white", bg="#222222").pack(pady=10)
tk.Button(root, text="Add Password", command=lambda: run_program("add"), bg="#00aaff", fg="white", font=("Arial", 12)).pack(pady=5)
tk.Button(root, text="View Password", command=lambda: run_program("view"), bg="#00cc88", fg="white", font=("Arial", 12)).pack(pady=5)
tk.Button(root, text="Exit", command=lambda: run_program("exit"), bg="#cc4444", fg="white", font=("Arial", 12)).pack(pady=5)

root.mainloop()
