from pynput.keyboard import Key, Listener
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(("192.168.4.1", 333))


def on_press(key):
    if key == Key.up:
        print("UP")
    elif key == Key.down:
        print("DOWN")
    elif key == Key.left:
        print("LEFT")
    elif key == Key.right:
        print("RIGHT")
    elif key == Key.space:
        print("SPACE")
    elif key == Key.esc:
        sock.close()
        exit()


def on_release(key):
    if key == Key.up:
        print("UP release")
        sock.sendall("forward".encode('utf-8'))
    elif key == Key.down:
        print("DOWN release")
        sock.sendall("back".encode('utf-8'))
    elif key == Key.left:
        print("LEFT release")
        sock.sendall("left".encode('utf-8'))
    elif key == Key.right:
        print("RIGHT release")
        sock.sendall("right".encode('utf-8'))
    elif key == Key.space:
        print("SPACE release")
        sock.sendall("stop".encode('utf-8'))


# Collect events until released
with Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()
