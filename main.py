from pidev.SlaveMaster import SerialMaster, Arduino
from pidev import RPiMIB
import time

RPiMIB.openSPI()

a = Arduino(SerialMaster(baud=115200), 17)

FORMAT_LIST = 0
FORMAT_BYTE = 1
FORMAT_STRING = 2
NO_RESPONSE = 3

def release_candy():
    print(a.move_stepper([1, 1] + list((200).to_bytes(2, "little")), format_out=FORMAT_STRING))
    time.sleep(3)
    print(a.move_stepper([1, 0] + list((200).to_bytes(2, "little")), format_out=FORMAT_STRING))

release_candy()