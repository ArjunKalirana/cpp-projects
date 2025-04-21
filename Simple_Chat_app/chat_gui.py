import socket
import threading 
import tkinter as tk
from datetime import datetime 

client=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
client.connect(("127.0.0.1",54000))

window=tk.Tk()
window.title("Chat Client")

frame=tk.Frame(window)
scrollbar =tk.Scrollbar(frame)
messages =tk.Listbox(frame,height=15,width=50,yscrollcommand=scrollbar.set)
scrollbar.pack(side=tk.RIGHT,fill=tk.Y)
messages.pack(side=tk.LEFT,fill=tk.BOTH)
messages.pack()
frame.pack()


entry_field = tk.Entry(window,width=40)
entry_field.pack()
entry_field.focus()

def recieve():
    while True:
        try:
            msg=client.recv(1024).decode("utf8")
            messages.insert(tk.END,f"[Server]:{msg}")
        except:
            break

def send():
    msg =entry_field.get()
    messages.insert(tk.END,f"[You]:msg")
    client.send(msg.encode("utf8"))
    entry_field.delete(0,tk.END)

send_button=tk.Button(window,text="Send",command=send)
send_button.pack()

threading.Thread(target=recieve).start()
window.mainloop()