#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RH_ASK.h>  // RadioHead library for RF communication

// Define pins for the relay, LED, and buzzer
const int relayPin = D1;   // Pin controlling the relay (motor)
const int ledPin = D2;     // Pin controlling the LED
const int buzzerPin = D3;  // Pin controlling the Buzzer

// Define RF receiver
RH_ASK rf_driver;

// LCD setup (change the address if needed)
LiquidCrystal_I2C lcd(0x3F, 16, 2);  // LCD address, 16 columns, 2 rows

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);

  // Initialize the relay, LED, and buzzer pins as OUTPUT
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Initialize RF receiver
  if (!rf_driver.init()) {
    Serial.println("RF Init Failed!");
    while (1);
  }

  // Initialize LCD
  lcd.begin(16, 2);  
  lcd.print("Sea Border");
  lcd.setCursor(0, 1);
  lcd.print("Security System");

  delay(2000);
  lcd.clear();
}

void loop() {
  // Variable to hold the incoming data from RF receiver
  char receivedMessage[10];

  // Check if data is available from the RF receiver
  if (rf_driver.available()) {
    uint8_t len = sizeof(receivedMessage);
    if (rf_driver.recv((uint8_t*)receivedMessage, &len)) {
      receivedMessage[len] = '\0';  // Null-terminate the string

      Serial.print("Received: ");
      Serial.println(receivedMessage);

      // Handle different button presses based on the received message
      if (strcmp(receivedMessage, "1") == 0) {
        handleButtonPress(1);
      } 
      else if (strcmp(receivedMessage, "2") == 0) {
        handleButtonPress(2);
      }
      else if (strcmp(receivedMessage, "3") == 0) {
        handleButtonPress(3);
      }
      else if (strcmp(receivedMessage, "4") == 0) {
        handleButtonPress(4);
      }
    }
  }
}

void handleButtonPress(int button) {
  // Turn off the LED and Buzzer by default
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(relayPin, LOW);  // Turn off the motor initially
  
  // Display appropriate message and handle the actions based on button press
  switch (button) {
    case 1:
      lcd.clear();
      lcd.print("Distance: 1 km");
      digitalWrite(relayPin, HIGH);  // Turn on the motor
      digitalWrite(ledPin, HIGH);    // Turn on the LED
      digitalWrite(buzzerPin, HIGH); // Turn on the Buzzer
      break;
      
    case 2:
      lcd.clear();
      lcd.print("Distance: 2 km");
      digitalWrite(relayPin, LOW);   // Turn off the motor
      digitalWrite(ledPin, LOW);     // Turn off the LED
      digitalWrite(buzzerPin, LOW);  // Turn off the Buzzer
      break;
      
    case 3:
      lcd.clear();
      lcd.print("Distance: 3 km");
      digitalWrite(relayPin, LOW);   // Turn off the motor
      digitalWrite(ledPin, LOW);     // Turn off the LED
      digitalWrite(buzzerPin, LOW);  // Turn off the Buzzer
      break;
      
    case 4:
      lcd.clear();
      lcd.print("Distance: 4 km");
      digitalWrite(relayPin, LOW);   // Turn off the motor
      digitalWrite(ledPin, LOW);     // Turn off the LED
      digitalWrite(buzzerPin, LOW);  // Turn off the Buzzer
      break;
      
    default:
      lcd.clear();
      lcd.print("Invalid input");
      break;
  }
}