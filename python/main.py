import serial
from pynput.keyboard import Key, Controller
import time

keyboard = Controller()

ser = serial.Serial('COM4', 115200)

def parse_data(data):
    axis = data[0]  # 0 for X, 1 for Y
    value = int.from_bytes(data[1:3], byteorder='big', signed=True)
    print(f"Received data: {data}")
    print(f"axis: {axis}, value: {value}")
    return axis, value

def move_mouse(axis, value):
    if axis == 0:  # X-axis (left/right movement)
        if value < 0:
            keyboard.press('a')
            keyboard.release('d')
        elif value > 0:
            keyboard.press('d')
            keyboard.release('a')
            
        else:
            keyboard.release('a')
            
            keyboard.release('d')
            
    elif axis == 1:  # Y-axis (up/down movement)
        if value < 0:
            keyboard.press('w')
            
            keyboard.release('s')
            
        elif value > 0:
            keyboard.press('s')
            
            keyboard.release('w')
            
        else:
            keyboard.release('s')
            
            keyboard.release('w')
            
    if axis == 2:  # Button 1
        if value:
            keyboard.press('z')
        else:
            keyboard.release('z')
    elif axis == 3:  # Button 2
        if value:
            keyboard.press('x')
        else:
            keyboard.release('x')
    elif axis == 4:  # Button 3
        if value:
            keyboard.press('c')
        else:
            keyboard.release('c')
    elif axis == 5:  # Button 4
        if value:
            keyboard.press('v')
        else:
            keyboard.release('v')

try:
    # sync package
    while True:
        print('Waiting for sync package...')
        while True:
            data = ser.read(1)
            if data == b'\xff':
                break
            else:
                print(f"Received error: {data}")

        # Read 4 bytes from UART
        data = ser.read(3)
        axis, value = parse_data(data)
        move_mouse(axis, value)

except KeyboardInterrupt:
    print("Program terminated by user")
except Exception as e:
    print(f"An error occurred: {e}")
    #pass
finally:
    ser.close()


