import os
import multiprocessing

import remoteEstop
import heading
import SerialCommunication

def Drive():
    liveEstop = multiprocessing.Process(target=remoteEstop.Estop)
    liveEstop.start()

    while True:
        if remoteEstop.stopped == False:
            leftWeight = 0
            rightWeight = 0
        else:
            print("ESTOP ACTIVATED")
            return

Drive()
