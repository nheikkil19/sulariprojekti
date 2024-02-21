from pynput.keyboard import Key, Listener
import socket
from time import sleep

file = open('output.csv', 'w', encoding="utf-8")
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
    elif key == Key.page_up:
        print("pgup")
    elif key == Key.page_down:
        print("pgdown")
    elif key == Key.esc:
        sock.close()
        file.close()
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
    elif key == Key.page_up:
        print("pgup release")
        sock.sendall("faster".encode('utf-8'))
    elif key == Key.page_down:
        print("pgdown release")
        sock.sendall("slower".encode('utf-8'))
 


      
# Collect events until released
with Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    
    while True:
        response = sock.recv(64)
        if ("bump" not in response.decode()) and ("slope" not in response.decode()):
            numbers = response.decode().replace("\r\n", "").split(",")
            numbers_new = [0, 0, 0]
            numbers_new[0] = str(int(numbers[0]) / 16384 * 9.81)
            numbers_new[1] = str(int(numbers[1]) / 16384 * 9.81)
            numbers_new[2] = str(int(numbers[2]) / 16384 * 9.81)
            result = ",".join(numbers_new) + "\n"
            file.write(result)
            print(result, end="")
        else:
            print(response)
    listener.join()


