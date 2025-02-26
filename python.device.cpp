import os
import cv2

DEVICE_PATH = "/dev/laptop_camera"

def check_camera_device():
    if os.path.exists(DEVICE_PATH):
        with open(DEVICE_PATH, "r") as device:
            print("Kernel Response:", device.read().strip())
        return True
    else:
        print("Camera driver not found! Make sure kernel module is loaded.")
        return False

def open_camera():
    cap = cv2.VideoCapture(0)
    if not cap.isOpened():
        print("Error: Could not open camera.")
        return
    print("Press 'q' to exit.")
    while True:
        ret, frame = cap.read()
        if not ret:
            print("ERROR: Couldn't capture frame.")
            break
        cv2.imshow("Laptop Camera", frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    cap.release()
    cv2.destroyAllWindows()

if _name_ == '_main_':
    if check_camera_device():
        open_camera()
	
