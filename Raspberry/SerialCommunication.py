import serial

def send_state_message(state_serial_port, state_message_id):
    state_message = f"{state_message_id},{state}\n"
    state_serial_port.write(message.encode())

def send_motor_message(motor_serial_port, motor_message_id, left_direction, right_direction, left_speed, right_speed):
    motor_message = f"{motor_message_id},{left_direction},{right_direction},{left_speed},{right_speed}\n"
    motor_serial_port.write(message.encode())

def receive_ultrasonic_data(): 
    print("hi")


# Serial port configuration
state_serial_port = serial.Serial('/dev/ttyUSB0', 9600)  # Replace '/dev/ttyUSB0' with the appropriate serial port

# Serial port configuration
motor_serial_port = serial.Serial('/dev/ttyUSB0', 9600)  # Replace '/dev/ttyUSB0' with the appropriate serial port


# Example usage
state_message_id = 1
state = "manual" #manual, autonomous, debug, Estopped

# Example motor usage
motor_message_id = 1
left_direction = "CCW" #CCW or CW
right_direction = "CCW" #CCW or CW
left_speed = 500
right_speed = 500



# Send the state message
send_state_message(state_serial_port, state_message_id, state)

# Send the motor message
send_motor_message(motor_serial_port, motor_message_id, left_direction, right_direction, left_speed, right_speed)

# Close the state serial port
state_serial_port.close()

# Close the motor serial port
serial_port.close()


