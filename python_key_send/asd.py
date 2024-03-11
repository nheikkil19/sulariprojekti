from pynput.keyboard import Key, Listener
import socket
from threading import Thread
from datetime import datetime
import os


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.settimeout(1)
sock.connect(("192.168.4.1", 333))
isEscPressed = False

OUTPUT = "output"
if not os.path.exists(OUTPUT):
    os.mkdir(OUTPUT)
date = datetime.now().strftime("%Y-%m-%d-%H-%M-%S")
file = open(f"{OUTPUT}/{date}.csv", "w", encoding="utf-8")
file.write("mag_x, mag_y, mag_z\n")


def on_press(key):
    global isEscPressed
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
    elif key == Key.page_up:
        print("pgup")
    elif key == Key.page_down:
        print("pgdown")
    elif key == Key.esc:
        isEscPressed = True
        sock.close()
        file.close()
        return False


def on_release(key):
    if key == Key.up:
        print("UP release")
        sock.sendall("forward".encode("utf-8"))
    elif key == Key.down:
        print("DOWN release")
        sock.sendall("back".encode("utf-8"))
    elif key == Key.left:
        print("LEFT release")
        sock.sendall("left".encode("utf-8"))
    elif key == Key.right:
        print("RIGHT release")
        sock.sendall("right".encode("utf-8"))
    elif key == Key.space:
        print("SPACE release")
        sock.sendall("stop".encode("utf-8"))
    elif key == Key.page_up:
        print("pgup release")
        sock.sendall("faster".encode("utf-8"))
    elif key == Key.page_down:
        print("pgdown release")
        sock.sendall("slower".encode("utf-8"))


def receiveData():
    global isEscPressed
    while not isEscPressed:
        try:
            response = sock.recv(64)
        except TimeoutError:
            continue
        except OSError:
            break
        try:
            numbers = response.decode().replace("\r\n", "").split(",")
            numbers_new = [str(int(number) / 16) for number in numbers]
            result = ",".join(numbers_new) + "\n"
            file.write(result)
        except (ValueError, IndexError):
            if "bump" in response.decode():
                print("bump detected")
            elif "slope" in response.decode():
                print("slope detected")
    return False


# Collect events until released
with Listener(on_press=on_press, on_release=on_release) as listener:

    readThread = Thread(target=receiveData)
    readThread.start()

    listener.join()
    readThread.join()
