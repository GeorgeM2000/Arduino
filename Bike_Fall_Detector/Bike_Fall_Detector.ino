// Libraries
#include <Arduino_LSM9DS1.h>
#include <ArduinoBLE.h>
#include <Arduino_APDS9960.h>
#include <math.h>

#define GREEN 23
#define RED 22

BLEService bike_fall_service("5321");
BLEBoolCharacteristic bike_fall_detection_bool("0001", BLERead | BLENotify);

unsigned long fall_time;
bool cancel_fall_state = false;


void setup() {

  // Initialize LED
  pinMode(GREEN, OUTPUT);
  
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
  // Turn on red LED for 1 second and turn it off.
  digitalWrite(RED, HIGH);
  delay(1000);
  digitalWrite(RED, LOW);

  // Turn off the green LED and cancel the fall.
  digitalWrite(GREEN, LOW);
  cancel_fall = true;
}

void loop() {

  BLEDevice central = BLE.central();

  bool fall_detected;
  bool ble_signal_sent;
  bool timer_started;
  
  
  // Initialize accelerometer X,Y and Z axis values.
  float Ax, Ay, Az;

  // If the accelerometer is available.
  if(IMU.accelerationAvailable()) {

    // Read the X,Y and Z axis values.
    IMU.readAcceleration(Ax, Ay, Az);

    // Check if Y axis value is above a custom threshold.
    if(abs(Ay) > 0.6 && !cancel_fall) {

      // If it is, a fall has been detected.
      fall_detected = true;
      
      if (central){
        
        // Turn on LED.
        digitalWrite(GREEN, HIGH);

        // If the timer has not started.
        if(!timer_started){
          
          // Start timer
          fall_time = millis();   
          timer_started = true;
                            
        }

        // If a BLE signal has not been sent and 30 seconds have passed.
        if(millis() - fall_time > 30 * 1000.0 && !ble_signal_sent) {

          // Send a BLE signal, set "ble_signal_sent" to true and turn off the green led.
          ble_signal_sent = true;
          digitalWrite(GREEN, LOW);
          sendHelpDetectionBool.writeValue(fall_detected);       
          
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
