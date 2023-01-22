/*
  The bike fall detector is an application that detects and alerts people when an accident occurs. You can find the application here https://github.com/GeorgeM2000/Bike-Fall-Detector
  This application uses the Arduino Nano 33 BLE(Bluetooth Low Energy) Sense board to detect accidents. When an accident is detected, the BLE functionality 
  embedded in the board sends a bluetooth signal to the application. An accident occurs when the bike leans far left or right enough so that a threshold is surpassed.
  When an accident is detected, the user has 30 seconds to disable the BLE signal by waving his/her hand above the Arduino board.
*/

// Libraries
#include <Arduino_LSM9DS1.h>
#include <ArduinoBLE.h>
#include <Arduino_APDS9960.h>
#include <math.h>

#define GREEN 23
#define RED 22
#define BLUE 24


BLEService bike_fall_service("5321");
BLEBoolCharacteristic bike_fall_detection_bool("0001", BLERead | BLENotify);

unsigned long fall_time;
bool cancel_fall_state = false;
bool fall_detected = false;
bool ble_signal_sent = false;
bool timer_started = false;


void setup() {

  // Initialize LED
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  // Check if IMU is working properly.
  if(!IMU.begin()) {
    while(1);
  }


  // Check if BLE is working properly.
  if(!BLE.begin()) {
    while(1); 
  }

  if (!APDS.begin()) {
    while(1);
  }

  // Setting up BLE
  String BLE_address = BLE.address();

  BLE.setDeviceName("Bike Fall Detector");

  BLE.setAppearance(1088);

  BLE.setLocalName("BLE Bike Fall Detection");

  BLE.setAdvertisedService(bike_fall_service);

  bike_fall_service.addCharacteristic(bike_fall_detection_bool);
  BLE.addService(bike_fall_service);
  bike_fall_detection_bool.writeValue(fall_detected);

  BLE.advertise();

  BLE.setEventHandler(BLEConnected, bleConnectHandler);

  BLE.setEventHandler(BLEDisconnected, bleDisconnectHandler);
  
}

void cancel_fall() {
  // Turn off the green LED
  digitalWrite(GREEN, HIGH);

  // Turn on red LED for 1 second and turn it off.
  digitalWrite(RED, LOW);
  delay(3000);
  digitalWrite(RED, HIGH);

  // Cancel the fall.
  cancel_fall_state = true;
}

void loop() {

  BLEDevice central = BLE.central();
  
  // Initialize accelerometer X,Y and Z axis values.
  float Ax, Ay, Az;

  // If the accelerometer is available.
  if(IMU.accelerationAvailable()) {

    // Read the X,Y and Z axis values.
    IMU.readAcceleration(Ax, Ay, Az);

    // Check if Y axis value is above a custom threshold.
    if(abs(Ay) > 0.8 && !cancel_fall_state) {

      // If it is, a fall has been detected.
      fall_detected = true;
      
      if (central){
        
        // Turn on LED.
        digitalWrite(GREEN, LOW);

        // If the timer has not started.
        if(!timer_started){
          
          // Start timer
          fall_time = millis();   
          timer_started = true;
                            
        }

        // If a BLE signal has not been sent and 30 seconds have passed.
        if(millis() - fall_time > 30 * 1000.0 && !ble_signal_sent) {

          // Turn off the green LED
          digitalWrite(GREEN, HIGH);

          // Turn on the blue led
          digitalWrite(BLUE, LOW);

          // Send a BLE signal, set "ble_signal_sent" to true and turn off the green led.
          ble_signal_sent = true;
          bike_fall_detection_bool.writeValue(fall_detected);     

          delay(3000);

          // Turn on the blue led
          digitalWrite(BLUE, HIGH);       
          
        } 
        else {

          // If gesture sensor is available.
          if(APDS.gestureAvailable()) {

            // Read gesture
            int gesture = APDS.readGesture();

            switch(gesture) {
            case GESTURE_UP:
                cancel_fall();
                break;
            case GESTURE_DOWN:
                cancel_fall();
                break;
            case GESTURE_LEFT:
                cancel_fall();
                break;
            case GESTURE_RIGHT:
                cancel_fall();
                break;
            default:
              // ignore
              break;
            }
          }
        }
      }
    } 
    // If Y axis value is greater than 0.0 and less than 0.6.
    else if(Ay > 0.0 && Ay < 0.6){

      digitalWrite(BLUE, HIGH);
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);

      // Set below variables to false.
      fall_detected = false;
      ble_signal_sent = false;
      timer_started = false;
      cancel_fall_state = false;
    }
  }
}


void bleConnectHandler(BLEDevice central) {}

void bleDisconnectHandler(BLEDevice central) {}
