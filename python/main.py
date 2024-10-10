import serial
import uinput
import time

ser = serial.Serial('/dev/ttyACM0', 115200)

# Create new mouse device
device = uinput.Device([
    uinput.KEY_A,
    uinput.KEY_D,
    uinput.KEY_W,
    uinput.KEY_S,
    uinput.KEY_Z,
    uinput.KEY_X,
    uinput.KEY_C,
    uinput.KEY_V,
])


def parse_data(data):
    axis = data[0]  # 0 for X, 1 for Y
    value = int.from_bytes(data[1:3], byteorder='big', signed=True)
    print(f"Received data: {data}")
    print(f"axis: {axis}, value: {value}")
    return axis, value

def move_mouse(axis, value):
    if axis == 0:    # X-axis
        if value < 0:
            device.emit(uinput.KEY_A, 1)
        elif value > 0:
            device.emit(uinput.KEY_D, 1)
        else:
            device.emit(uinput.KEY_A, 0)
            device.emit(uinput.KEY_D, 0)
    elif axis == 1:  # Y-axis
        if value < 0:
            device.emit(uinput.KEY_W, 1)
        elif value > 0:
            device.emit(uinput.KEY_S, 1)
        else:
            device.emit(uinput.KEY_W, 0)
            device.emit(uinput.KEY_S, 0)
    elif axis == 2:  # Botão 1
        device.emit(uinput.KEY_Z, value)
    elif axis == 3:  # Botão 2
        device.emit(uinput.KEY_X, value)
    elif axis == 4:  # Botão 3
        device.emit(uinput.KEY_C, value)
    elif axis == 5:  # Botão 4
        device.emit(uinput.KEY_V, value)



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
