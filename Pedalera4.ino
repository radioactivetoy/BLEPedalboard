/*
    BLE_MIDI Example by neilbags
    https://github.com/neilbags/arduino-esp32-BLE-MIDI

    Based on BLE_notify example by Evandro Copercini.
    Creates a BLE MIDI service and characteristic.
    Once a client subscibes, send a MIDI message every 2 seconds
*/
// Bluetooth Includes
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>  // Check if needed
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define SERVICE_UUID        "03b80e5a-ede8-4b33-a751-6ce34ec4c700"
#define CHARACTERISTIC_UUID "7772e5db-3868-4112-a1a9-f2669d106bf3"

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Bluetooth Setup
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
bool connected = true;

// GPIO for each button

int button_0 = 23;
//int button_1 = 
//int button_2 =
//int button_3 =
//int button_4 =
//int button_mode =

int buttondelay = 1200; // Button delay time to prevent flapping - Setting this lower than 1,2s crashes the thr android app

// CC Numner for modes 0 (preset) and 1 (effect)
uint8_t ccnumber[5][2] = {{0x14, 0x19}, {0x15, 0x1A}, {0x16, 0x1B}, {0x17, 0x1C}, {0x18, 0x1D}};
int opmode = 0; // current operation modes 0 (preset) and 1 (effect)
volatile int pushedbutton=0; // Pushed Button
volatile bool sendmidi = false;
int pushed=0; // Test code remove

uint8_t midiPacket[] = {
  0x80,  // header
  0x80,  // timestamp, not implemented
  0xb0,  // Continuous controller Chanel 1
  0x14,  // #20
  0x7F   // 7F press 0 Release
};

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void setup() {
  Serial.begin(115200);

  // Bluetooth Setup
  BLEDevice::init("BLE Floorboard");

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  // Create the BLE Service
  BLEService *pService = pServer->createService(BLEUUID(SERVICE_UUID));
  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      BLEUUID(CHARACTERISTIC_UUID),
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_WRITE_NR
                    );
  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());
  // Start the service
  pService->start();
  // Start advertising
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(pService->getUUID());
  pAdvertising->start();

  // Display Setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  
  // SetupPins
  pinMode(button_0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button_0), buttonevent_0, FALLING);
}

void loop() {
  if (deviceConnected) {
    if (!connected) { //First screen update / uknown patch
      connected = true;
      display.clearDisplay();
      display.setCursor(40, 5);
      display.setTextSize(5);
      display.setTextColor(WHITE);
      // Display static text
      display.println("?");
      display.setCursor(20, 50);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.println("MODE: PRESSET");
      display.display();
    }
    if (sendmidi) {
      // Send Push
      midiPacket[3] = ccnumber[pushed][opmode]; // test code, change to pushedbutton
      midiPacket[4] = 0x7F; // CC Max Value
      pCharacteristic->setValue(midiPacket, 5); // packet, length in bytes
      pCharacteristic->notify();
      // Update Display
      display.clearDisplay();
      display.setCursor(40, 5);
      display.setTextSize(5);
      display.setTextColor(WHITE);
      // Display static text
      display.println(pushed + 1); // test code, change to pushedbutton+1
      display.setCursor(20, 50);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      // Display static text
      display.println("MODE: PRESSET");
      display.display();
      // Send release - Not needed on the thr
      //midiPacket[4]=0x00; // CC Min Value (Release)
      //pCharacteristic->setValue(midiPacket, 5); // packet, length in bytes
      //pCharacteristic->notify();
      delay(buttondelay); // 
      pushed = (pushed + 1) % 5; // Testcode
      sendmidi = false;
    }

  } else if (connected) { // Update the display only when Connectio status is changed
    connected = false;
    display.clearDisplay();
    display.setCursor(1, 1);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("RadioactiveToy");
    display.println("BLE Pedalboard");
    display.println("Bluetooth not connected");
    display.display();
  }
}


void buttonevent_0() {
  sendmidi = true;
  pushedbutton=0;
}
