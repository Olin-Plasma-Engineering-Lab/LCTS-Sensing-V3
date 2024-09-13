from datetime import datetime
from time import ctime, time

import serial

# Set time in unit seconds
t = time()

# Convert time from unit seconds to a date + time
local_time = datetime.fromtimestamp(t)

# Convert the date + time into a format that can be used in a file name
formatted_time = local_time.strftime("%Y-%m-%d_%H-%M-%S")


# Define the COM port the microcontroller is connected to
CONTROLLER_COMM_PORT = "COM11"

# Set baud rate
BAUD_RATE = 115200

# Open the COM port to start communications
try:
    serial_port = serial.Serial(CONTROLLER_COMM_PORT, BAUD_RATE, timeout=1)
except serial.serialutil.SerialException:
    print(
        f"Device not found on port {CONTROLLER_COMM_PORT}. Close any programs (Arduino IDE) that may be using port"
    )
else:
    with open(f"Trial {formatted_time}.csv", "w") as data:

        # Set starting time to keep track of elapsed time between measurements
        while True:
            sensor_output = serial_port.readline().decode()
            print(sensor_output)
            # print(sensor_output)
            # print(type(sensor_output))

            # force, elapsed_time = (sensor for sensor in sensor_output.split(","))

            # force = sensor_output
            data.write(ctime(time()))
            data.write(",")
            data.write(sensor_output)
            # data.write(",")
            # data.write(force)
            data.write("\n")
