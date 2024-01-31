from pynput.keyboard import Key, Listener
import socket


def on_press(key):
    if key == Key.up:
        print("UP")
    elif key == Key.down:
        print("DOWN")
    elif key == Key.left:
        print("LEFT")
    elif key == Key.right:
        print("RIGHT")


def on_release(key):
    if key == Key.up:
        print("UP release")
    elif key == Key.down:
        print("DOWN release")
    elif key == Key.left:
        print("LEFT release")
    elif key == Key.right:
        print("RIGHT release")
    elif key == Key.esc:
        s.close()
        exit()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("192.168.4.1", 334))


# Collect events until released
with Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()

s.close()