import time

import numpy as np

import serial
import serial.tools.list_ports

def find_arduino(port=None):
    """Get the name of the port that is connected to Arduino."""
    for p in serial.tools.list_ports.comports():
        if p.manufacturer and "Arduino" in p.manufacturer:
            return p.device
    raise IOError("No Arduino found")

port = find_arduino()

print(f"Connected to {port}")

arduino = serial.Serial(port, baudrate=9600, timeout=1)

time.sleep(2)

arduino.write(b'B')
print(f'Handshake sent :)')

while True:
    if arduino.in_waiting > 0:
        line = arduino.readline().decode('utf-8', errors='replace').strip()
        if line == 'A':
            print(f'Handshake succesful!')
            break
        else:
            time.sleep(0.05)
