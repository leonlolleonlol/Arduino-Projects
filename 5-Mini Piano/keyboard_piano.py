import serial
from pynput import keyboard

# Replace with your actual port, e.g., 'COM3' on Windows or '/dev/ttyUSB0' on Linux/Mac
arduino_port = 'COM3'  
baud_rate = 9600

# Open serial connection
ser = serial.Serial(arduino_port, baud_rate)
print(f"Connected to {arduino_port} at {baud_rate} baud. Start typing keys (qwertyuiop or 1234567890-)...")

# Define the valid keys you want to use
valid_keys = set("qwertyuiop1234567890-")

def on_press(key):
    try:
        k = key.char.lower()  # get character key (lowercase)
        if k in valid_keys:
            ser.write(k.encode())  # send key to Arduino
    except AttributeError:
        pass  # ignore special keys like Shift, Ctrl, etc.

with keyboard.Listener(on_press=on_press) as listener:
    listener.join()
