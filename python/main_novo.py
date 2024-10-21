import serial
import pyautogui
import time

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
            pyautogui.keyDown('a')
            pyautogui.keyUp('d')
        elif value > 0:
            pyautogui.keyDown('d')
            pyautogui.keyUp('a')
        else:
            pyautogui.keyUp('a')
            pyautogui.keyUp('d')
    elif axis == 1:  # Y-axis (up/down movement)
        if value < 0:
            pyautogui.keyDown('w')
            pyautogui.keyUp('s')
        elif value > 0:
            pyautogui.keyDown('s')
            pyautogui.keyUp('w')
        else:
            pyautogui.keyUp('w')
            pyautogui.keyUp('s')
    elif axis == 2:  # Button 1
        if value:
            pyautogui.keyDown('z')
        else:
            pyautogui.keyUp('z')
    elif axis == 3:  # Button 2
        if value:
            pyautogui.keyDown('x')
        else:
            pyautogui.keyUp('x')
    elif axis == 4:  # Button 3
        if value:
            pyautogui.keyDown('c')
        else:
            pyautogui.keyUp('c')
    elif axis == 5:  # Button 4
        if value:
            pyautogui.keyDown('v')
        else:
            pyautogui.keyUp('v')

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
finally:
    ser.close()


