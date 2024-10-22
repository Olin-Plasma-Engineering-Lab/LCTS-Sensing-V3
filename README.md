# LCTS-Sensing-V3

This is the repository for the sensing system used by the Olin Plasma Engineering Lab (OPEL) to measure thrust on the Low-Cost Thrust Stand.

## Brief System Overview
The system is comprised of two boards: a sender and a receiver. The sender is located in the vacuum chamber and is connected to a force sensor that measures thrust produced by the thrusters. The receiver board is located outside the vacuum chamber and exists to receive data sent by the sender board. The boards are connected via a wiring harness and electrical feedthrough on the vacuum chamber, and communicate using I2C.

The system allows for two way communication. This gets used so that the calibration system on the thrust stand within the vacuum chamber can be controlled using the receiver board outside the chamber.

## Repository Organization

- `code/`: This contains the code used by the systems
    - `Microcontroller/`: Code that gets uploaded to the microcontrollers
        - `Arduino/`: Arduino code that gets uploaded to the microcontrollers
            - `receiver/`: code for the receiver board
            - `sender/` (depreicated): code for the sender board for use with **STEPPER MOTOR CALIBRATION**
            - `sender_servo_calibration/`: code for the sender board for use with **SERVO MOTOR CALIBRATION** This is the most up to date script and the code that is actually used on the sender board
        - `Micropython/`: Location for future microcontroller code written in MicroPython. Not currently used but contains the MicroPython firmware
- `Testing/`: Contain a Python script that was used as a preliminary test for saving data to a CSV
- `data/`: Data recorded from unlabeled thruster tests
- `Hardware/`: KiCad projects and other needed files for the sender and receiver PCBs
    - `assets/`: OPEL logo for use on PCBs
    - `Parts/`: Parts needed fro the KiCad Project files
    - `receiver/`: KiCad project files for the receiver PCB
    - `sender/`: KiCad project files for the sender PCB
- `sensing_processor.py`: Script that is used to read data from the receiver and save to a CSV
    
##