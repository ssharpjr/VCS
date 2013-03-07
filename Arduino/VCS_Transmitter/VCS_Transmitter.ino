/*
VCS Transmitter - VCS Project
Read the position of the switch and send the correct query string 
via WiFi web client to a database.
February 2013
*/

/*
6 Position Cam Switch Settings
These are the status codes that will be sent in the query strings.

Position 0: Off
Pin 15 = Position 1: Status 1 (Supervisor)
Pin 16 = Position 2: Status 2 (Processor) 
Pin 17 = Position 3: Status 3 (Material Handler)
Pin 18 = Position 4: Status 4 (Quality Auditor) 
Pin 19 = Position 5: Status 5 (Maintenance)
*/


// Supporting Modules
#include <SPI.h>
#include <WiFi.h>

////////////////////////////////////////////////////////////////////////////////

// Press Specific Variables.
int press_id = 101;  // This is the PRESS_ID of the press being monitored.
int status_id;  // This is the STATUS_ID that will be sent to the database.
int startup_id;  // This code tells the DB that the system just turned on.


boolean debugger = false;  // Verbose output
int debounceDelay = 1000;  // Milliseconds to wait before checking the switch.
int ledState = LOW;  // used to blink without delay
long previousMillis = 0;
long interval = 1000;


// WiFi Settings
//char ssid[] = "TPIWAP";
//char key[] = "7D98B2D509";
//char ssid[] = "101";
//char key[] = "94618f48467dd92b6b2e6520d3";
char ssid[] = "IC2B4UC1";
char key[] = "N3tM45t3R!2010";
int keyIndex = 1;
int status = WL_IDLE_STATUS;

// VCS Server IP Address
IPAddress server(192,168,10,106); // my laptop

// Initialize the client library
WiFiClient client;


// Cam Switch Settings
// Build an array based on the Cam Switch connections.
const int pinCount = 5;  // number of positions on the Cam Switch (plus OFF).
const int pinList[pinCount] = {15, 16, 17, 18, 19};  // Connected pins.  A1-A5 set as digital.


// LED Settings (74HC595 Shift Register)
int powerPin = 9;
int networkPin = 8;
int latchPin = 5;
int clockPin = 6;
int dataPin = 3;
byte leds = 0;


// *** SETUP *** //
void setup() {
  // Setup Cam Switch pins
  for (int i=0; i<pinCount; i++) {
      pinMode(pinList[i], INPUT_PULLUP);  // Active low, connect switch common to Ground
      digitalWrite(pinList[i], HIGH);
  }

  // Setup LED pins
  pinMode(powerPin, OUTPUT);
  pinMode(networkPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  

  // Turn on Power LED
  digitalWrite(powerPin, HIGH);
  //leds = 128;  // Turn on Power LED in the shift register.
  //activateLeds();
  
  // Setup Serial debugger
  Serial.begin(9600);
  while (!Serial) {
    ;  // Wait for serial port to connect.
  }
  delay(1000);  // Output delay.  First line is always garbled.
  Serial.println();
  Serial.println("Arduino Online");
  Serial.println();
  
  // Run LED POST
  Serial.println("Running Visual Feedback Test...");
  Serial.println();
  ledPost();
  leds = 0;
  activateLeds();

    
  // Setup WiFi
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present!");
    //while (true);  // Do not continue
    while (true) {
      digitalWrite(networkPin, HIGH);
      delay(500);
      digitalWrite(networkPin, LOW);
      delay(500);
    }
  }
  
  // Attempt to connect to WiFi network.
  while (status != WL_CONNECTED) {
    Serial.println("WiFi Shield Online");
    Serial.println();
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" Network ...");
    //status = WiFi.begin(ssid, keyIndex, key);  // WEP
    status = WiFi.begin(ssid, key);  // WPA/WPA2
    
    // Blink networkPin until connection is established.
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(networkPin, ledState);
    }
    //tenCountDot();
    //delay(10000);  
    // Wait 10 seconds for WiFi to connect.
    for (int i = 0; i < 10; i++) {
      digitalWrite(networkPin, HIGH);
      delay(500);
      digitalWrite(networkPin, LOW);
      delay(500);
    }
  }
  
  
  //  Connection established.
  //  Turn on LEDs.
  digitalWrite(networkPin, HIGH);
  Serial.println("Connected");
  printCurrentNet();
  printWifiData();

////////////////////////////////////////////////////////////////////////////////
  
  // Setup Cam Switch
  Serial.println("Setting switch startup position to OFF");
  int  currentPosition = -1;
  Serial.println();
  startup_id = 1;  // Toggle the startup flag.
  status_id = 0;  // Set initial status to OFF.
  clientRequest();  // Send the startup status to the database.
  startup_id = 0; // Toggle the startup flag.

  

}




// *** LOOP *** //
void loop() {
    static int previousPosition = -1;
    static boolean unused = false;
    static unsigned long timer = 0;
    int currentPosition = -1;
    //int status_id;  // Machine status ID based on Cam Switch position.

    // Scan through the switch pins looking for the current position.
    for (byte i=0; i<pinCount; i++) {
        if (digitalRead(pinList[i]) == LOW)
            currentPosition = i;
    }
    
    // Debugger
    if (debugger == true) {
    Serial.print("Running Position: ");
    Serial.println(currentPosition);
    }
    
    // If the current position is different from the previous position.
    // Meaning the switch has moved.
    if (currentPosition != previousPosition) {
        timer = millis();  // Start a timer.
        unused = true;  // Set an UNUSED flag.
        previousPosition = currentPosition;
    }

      // If the timer reaches "N" and the UNUSED flag is set,
      // meaning the switch has stopped moving.
      if (millis() - timer > debounceDelay  && unused) {
        // Act on the current position.
        
        switch (currentPosition) {
          case -1:
            Serial.println("Position 0:  OFF");
            Serial.println();
            status_id = 0;
            //leds = 192;  // Turn off LEDs
            leds = 0;
          break;
          case 0:  // position 1 - Supervisor
            Serial.println("Position 1:  SV");
            Serial.println();
            status_id = 1;
            //leds = 193;  // Turn on LED 1
            leds = 1;
          break;
          case 1:  // position 2 - Processor
            Serial.println("Position 2:  PR");
            Serial.println();
            status_id = 2;
            //leds = 194;  // Turn on LED 2
            leds = 2;
          break;
          case 2:  // position 3 - Material Handler
            Serial.println("Position 3:  MH");
            Serial.println();
            status_id = 3;
            //leds = 196;  // Turn on LED 3
            leds = 4;
          break;
          case 3:  // position 4 - Quality Auditor
            Serial.println("Position 4:  QA");
            Serial.println();
            status_id = 4;
            //leds = 200;  // Turn on LED 4
            leds = 8;
          break;
          case 4:  // position 5 - Maintenance
            Serial.println("Position 5:  MT");
            Serial.println();
            status_id = 5;
            //leds = 208;  // Turn on LED 5
            leds = 16;
          break;
          default:
            Serial.println("Unknown status code");
            Serial.println();
          break;
        }
        activateLeds();  // Turn on LEDs.
        clientRequest();  // Send the query string.
        unused = false; // Clear the UNUSED flag.
      } 
}

