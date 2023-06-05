from serial import Serial
from pynmeagps import NMEAReader
import time

stream = Serial('COM6', 9600, timeout=3)

latitude = 0
longitude = 0


def get_gps(latitude, longitude):
    nmr = NMEAReader(stream)

    (raw_data, parsed_data) = nmr.read()
    try:
        latitude = parsed_data.lat
        longitude = parsed_data.lon
        print(f"{latitude},{longitude}")
    except:
        pass
    return latitude, longitude



while True:
    (latitude, longitude) = get_gps(latitude, longitude)
    print(f"{latitude},{longitude}")
    time.sleep(0.1)