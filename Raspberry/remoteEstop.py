from bluedot import BlueDot
    
stopped = False
def Estop():
    bd = BlueDot()
    while True:
        bd.wait_for_press()
        if stopped == False:
            stopped = True
        else:
            stopped = False
