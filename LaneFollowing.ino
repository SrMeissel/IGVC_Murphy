// River Schreckengost
// Arduino-Vision Lane-Following Skeleton Code
// Requires libraries for ArduCAM 

#include <Wire.h>
#include <ArduCAM.h>
#include <SPI.h>

// Define camera model and pins
#define ARDUCAM_SHIELD_REVC     // Change this based on your ArduCAM model
#define CS_PIN    10            // Chip Select pin for ArduCAM
ArduCAM myCAM(ARDUCAM_SHIELD_REVC, CS_PIN);

// Camera parameters
#define BMPIMAGEOFFSET 66
#define CAM_WIDTH   640    // Camera image width
#define CAM_HEIGHT  480    // Camera image height

// Threshold for black/white detection
#define THRESHOLD 100

// Zones for steering
#define ZONE_WIDTH (CAM_WIDTH / 3)
#define MIDDLE_ZONE (CAM_WIDTH / 2)

// Variables for detected shape
int shapeX = 0;
int shapeY = 0;
int shapeWidth = 0;
int shapeHeight = 0;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Initialize ArduCAM
  Wire.begin();
  myCAM.write_reg(ARDUCHIP_TEST1, 0x55);
  uint8_t vid, pid;
  myCAM.wrSensorReg8_8(0xFF, 0x01);
  myCAM.rdSensorReg8_8(OV5642_CHIPID_HIGH, &vid);
  myCAM.rdSensorReg8_8(OV5642_CHIPID_LOW, &pid);
  if ((vid != 0x56) || (pid != 0x42)) {
    Serial.println(F("Camera not found!"));
    while (1);
  }
  myCAM.set_format(JPEG);
  myCAM.InitCAM();
  myCAM.OV5642_set_JPEG_size(OV5642_320x240);
  myCAM.clear_fifo_flag();
  myCAM.write_reg(ARDUCHIP_FRAMES, 0x00);
}

void loop() {
  // Capture image
  myCAM.flush_fifo();
  myCAM.clear_fifo_flag();
  myCAM.start_capture();

  while (!myCAM.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK));

  // Get image size
  uint32_t length = myCAM.read_fifo_length();
  if (length >= MAX_FIFO_SIZE) {
    Serial.println(F("Image too large!"));
    return;
  }

  // Read image data
  byte buffer[length];
  myCAM.CS_LOW();
  myCAM.set_fifo_burst();
  SPI.transfer(0x3C);
  myCAM.set_fifo_burst();
  for (int i = 0; i < length; i++) {
    buffer[i] = SPI.transfer(0x00);
  }
  myCAM.CS_HIGH();

  // Detect white lines and calculate centroid
  int middleRow = CAM_HEIGHT / 2;
  int zone1 = ZONE_WIDTH;
  int zone2 = 2 * ZONE_WIDTH;
  int whitePixelsZone1 = 0;
  int whitePixelsZone2 = 0;
  int whitePixelsZone3 = 0;
  int centroidZone1 = 0;
  int centroidZone2 = 0;
  int centroidZone3 = 0;

  for (int i = 0; i < CAM_WIDTH; i++) {
    // Convert RGB values to black/white
    byte r = buffer[BMPIMAGEOFFSET + 3 * (middleRow * CAM_WIDTH + i)];
    byte g = buffer[BMPIMAGEOFFSET + 3 * (middleRow * CAM_WIDTH + i) + 1];
    byte b = buffer[BMPIMAGEOFFSET + 3 * (middleRow * CAM_WIDTH + i) + 2];
    int brightness = (r + g + b) / 3;

    // Check if pixel is white
    if (brightness > THRESHOLD) {
      if (i < zone1) {
        whitePixelsZone1++;
        centroidZone1 += i;
      } else if (i < zone2) {
        whitePixelsZone2++;
        centroidZone2 += i;
      } else {
        whitePixelsZone3++;
        centroidZone3 += i;
      }
    }
  }

  // Calculate centroids
  if (whitePixelsZone1 > 0) {
    centroidZone1 /= whitePixelsZone1;
  }
  if (whitePixelsZone2 > 0) {
    centroidZone2 /= whitePixelsZone2;
  }
  if (whitePixelsZone3 > 0) {
    centroidZone3 /= whitePixelsZone3;
  }

  // Calculate steering values
  int centerLine = CAM_WIDTH / 2;
  int steerValue = centerLine - centroidZone2;

  // Print steering value
  Serial.print(F("Steering value: "));
  Serial.println(steerValue);

  // Draw polygon around detected shape (white line)
  shapeX = centroidZone2 - (shapeWidth / 2);
  shapeY = middleRow - (shapeHeight / 2);
  shapeWidth = whitePixelsZone2;
  shapeHeight = 10;

  // Add code to command steering values for your robot based on the steerValue

  delay(500);
}
