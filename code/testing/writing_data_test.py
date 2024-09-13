from time import time, ctime
from datetime import datetime

# Set range number for testing
range_length = 50

# Set time in unit seconds
t = time()

# Convert time from unit seconds to a date + time
local_time = datetime.fromtimestamp(t)

# Convert the date + time into a format that can be used in a file name
formatted_time = local_time.strftime("%Y-%m-%d_%H-%M-%S")

# Open and
with open(f"Trial {formatted_time}.csv", "w") as data:
    data.write("Timestamp,Force\n")

    for force in range(range_length):

        current_time = ctime(time())
        data.write(f"{current_time},{force}\n")
