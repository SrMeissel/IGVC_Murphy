# River Schreckengost
# 06/04/23

# Determine Heading 
import math

def calculate_gps_heading_distance(current_lat, current_long, waypoint_lat, waypoint_long):
    # Converting degrees to radians
    lat1 = math.radians(current_lat)
    long1 = math.radians(current_long)
    lat2 = math.radians(waypoint_lat)
    long2 = math.radians(waypoint_long)

    # Calculate differences in latitude and longitude
    dlat = lat2 - lat1
    dlong = long2 - long1

    # Calculate GPS heading (theta_gps)
    y = math.sin(dlong) * math.cos(lat2)
    x = math.cos(lat1) * math.sin(lat2) - math.sin(lat1) * math.cos(lat2) * math.cos(dlong)
    theta_gps = math.atan2(y, x)

    # Convert radians to degrees
    theta_gps = math.degrees(theta_gps)

    # Normalize the GPS heading to be within 0 to 360 degrees
    theta_gps = (theta_gps + 360) % 360

    # Calculate distance in meters using Haversine formula
    radius = 6371000  # Earth's radius in meters
    a = math.sin(dlat / 2) ** 2 + math.cos(lat1) * math.cos(lat2) * math.sin(dlong / 2) ** 2
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    distance = radius * c

    return theta_gps, distance

def calculate_compass_heading(theta_gps, compass_heading):
    # Calculate compass-based heading (theta)
    theta = theta_gps - compass_heading

    # Normalize the heading to be within 0 to 360 degrees
    theta = (theta + 360) % 360

    return theta

# Current position (latitude and longitude) of the robot
current_lat, current_long = map(float, input("Enter current latitude,longitude: ").split(','))

# List of waypoints (latitude and longitude)
waypoints = []
num_waypoints = int(input("Enter the number of waypoints: "))

for i in range(num_waypoints):
    waypoint_lat, waypoint_long = map(float, input(f"Enter latitude,longitude for waypoint {i+1}: ").split(','))
    waypoints.append((waypoint_lat, waypoint_long))

# Compass heading of the robot
compass_heading = float(input("Enter compass heading (in degrees): "))

# Calculate and print heading and distance for each waypoint
for i, waypoint in enumerate(waypoints):
    waypoint_lat, waypoint_long = waypoint
    theta_gps, distance = calculate_gps_heading_distance(current_lat, current_long, waypoint_lat, waypoint_long)
    theta = calculate_compass_heading(theta_gps, compass_heading)
    
    # Calculate the relative heading with respect to the robot's heading
    relative_heading = theta - compass_heading

    # Normalize the relative heading to be within -180 to +180 degrees
    if relative_heading > 180:
        relative_heading -= 360
    elif relative_heading < -180:
        relative_heading += 360

    # Determine if the heading is closer to the left or right
    if relative_heading > 0:
        direction = "right"
    else:
        direction = "left"

    print(f"Waypoint {i+1}:")
    print(f"GPS Heading: {theta_gps} degrees")
    print(f"Compass Heading: {theta} degrees")
    print(f"Relative Heading: {relative_heading} degrees")
    print(f"Direction: {direction}")
    print(f"Distance: {distance:.2f} meters\n")
