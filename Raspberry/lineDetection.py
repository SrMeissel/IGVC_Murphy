import cv2
import numpy as np

# Set up camera capture
camera = cv2.VideoCapture(0)

# Set up screen divisions
screen_width = 640
screen_height = 480

row_height = screen_height // 3
row_midpoint = screen_height // 2
column_width = screen_width // 3

# Main loop
while True:
    # Read a frame from the camera
    ret, frame = camera.read()
   
    # Extract the middle row of pixels
    middle_row = frame[row_midpoint:row_midpoint + 1, :]
   
    # Convert RGB to grayscale
    gray = cv2.cvtColor(middle_row, cv2.COLOR_BGR2GRAY)
   
    # Apply threshold to convert to black and white
    _, thresh = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)
   
    # Find contours of white objects
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
   
    # Find the centroid of the largest contour
    largest_contour = max(contours, key=cv2.contourArea)
    M = cv2.moments(largest_contour)
    centroid_x = int(M['m10'] / M['m00'])
    centroid_y = int(M['m01'] / M['m00'])
   
    # Calculate the distance between centroid and centerline
    centerline = screen_width // 2
    distance = centroid_x - centerline
   
    # Calculate steering values
    steering_values = [0, 0, 0]
    if distance < -column_width:
        steering_values[0] = -1
    elif distance > column_width:
        steering_values[2] = 1
    else:
        steering_values[1] = distance / column_width
   
    # Output steering values
    print("Steering values:", steering_values)
   
    # Draw a polygon around the detected shape
    cv2.drawContours(middle_row, [largest_contour], 0, (0, 255, 0), 2)
   
    # Draw centerline
    cv2.line(middle_row, (centerline, 0), (centerline, row_height), (0, 0, 255), 2)
   
    # Draw centroid
    cv2.circle(middle_row, (centroid_x, centroid_y), 5, (255, 0, 0), -1)
   
    # Display the processed frame
    cv2.imshow('Processed Frame', middle_row)
   
    # Check for key press to exit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the camera and close windows
camera.release()
cv2.destroyAllWindows()
