import tkinter as tk
import requests

window = tk.Tk()
window.title("ESP32 Remote")
window.geometry("400x400")


def forward():
    requests.get("http://192.168.4.1/forward")


button1 = tk.Button(window, text="FORWARD", command=forward)
button1.grid(row=0, column=3)


def left():
    requests.get("http://192.168.4.1/left")


button2 = tk.Button(window, text="LEFT", command=left)
button2.grid(row=3, column=1)


def right():
    requests.get("http://192.168.4.1/right")


button3 = tk.Button(window, text="RIGHT", command=right)
button3.grid(row=3, column=5)


def brake():
    requests.get("http://192.168.4.1/brake")


button4 = tk.Button(window, text="BRAKE", command=brake)
button4.grid(row=6, column=3)


def stop():
    requests.get("http://192.168.4.1/stop")


button5 = tk.Button(window, text="STOP", command=stop)
button5.grid(row=1, column=9)


def reverse():
    requests.get("http://192.168.4.1/reverse")


button6 = tk.Button(window, text="REVERSE", command=reverse)
button6.grid(row=6, column=9)


def accelerate():
    requests.get("http://192.168.4.1/accelerate")


button7 = tk.Button(window, text="ACCELERATE", command=accelerate)
button7.grid(row=12, column=9)

window.bind("<KeyPress-w>", lambda event: forward())
window.bind("<KeyPress-a>", lambda event: left())
window.bind("<KeyPress-d>", lambda event: right())
window.bind("<KeyPress-s>", lambda event: brake())
window.bind("<KeyPress-q>", lambda event: stop())
window.bind("<KeyPress-r>", lambda event: reverse())
window.bind("<KeyPress-e>", lambda event: accelerate())
window.mainloop()
