from pynput.keyboard import Key, Controller
import time
keyboard = Controller()

while True:
    
 # Type a lower case A; this will work even if no key on the
    # physical keyboard is labelled 'A'
    keyboard.press('a')
    time.sleep(0.5)
    keyboard.release('a')

    keyboard.press('d')
    time.sleep(0.5)
    keyboard.release('d')