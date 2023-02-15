#include <Adafruit_NeoPixel.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

int numPixel = 60;
int ledPin = 5;
Adafruit_NeoPixel strip(numPixel, ledPin, NEO_GRB + NEO_KHZ800);

int brightness;
int red;
int green;
int blue;

void setup() {
  Serial.begin(115200);

  strip.begin();
  strip.setBrightness(10);

  initMPU();
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  //  serialMonitor(a, g);
  serialPlotter(a, g);
  
  strip.clear();
  mapBrightness(a, g);
  strip.setBrightness(brightness);

  mapColors(a, g);
  for(int i = 0; i < numPixel; i++){
      strip.setPixelColor(i, red, green, blue);
  }
  
  strip.show();
}

void mapColors(sensors_event_t a, sensors_event_t g){
  float newRed = map(a.acceleration.y, -10, 10, 0, 255);
  red = newRed;

  float newGreen = map(a.acceleration.z, -10, 10, 0, 255);
  green = newGreen;

  float newBlue = map(a.acceleration.x, -10, 10, 0, 255);
  blue = newBlue;
}

void mapBrightness(sensors_event_t a, sensors_event_t g){
  float newBrightness = map(g.gyro.x, -10, 10, 10, 255);
  brightness = newBrightness;
}
