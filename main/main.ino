#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

const int ledPin = 2; // Pin for the built-in LED
const int buttonPin = 0; // Pin for the built-in button (assuming GPIO0)

void setup() {
    Serial.begin(115200);
    bleKeyboard.begin();
    pinMode(ledPin, OUTPUT); // Set the LED pin as output
    pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as input with pull-up resistor
}

void loop() {
    // Check if the button is pressed (buttonPin is LOW when pressed)
    if (digitalRead(buttonPin) == LOW) {
        if (bleKeyboard.isConnected()) {
            Serial.println("BLE Keyboard Connected!");

            // Simulate "Win + R" (open "Run" window)
            bleKeyboard.press(KEY_LEFT_GUI);  // Windows key
            bleKeyboard.press('r');           // R key
            bleKeyboard.releaseAll();
            delay(500);  // Wait for half a second

            // Type "cmd" to open the command prompt
            bleKeyboard.print("cmd");
            bleKeyboard.write(KEY_RETURN);    // Press Enter to open cmd
            delay(1000);  // Wait a bit for the cmd to open

            bleKeyboard.write(KEY_RETURN);  // Go to the next line after the loading bar

            // Manually type "www.google.com"
            bleKeyboard.print("start www.makerworld.com");
            delay(500);  // Short delay to ensure the text is typed out

            bleKeyboard.write(KEY_RETURN);    // Press Enter to execute the command
            delay(2000);  // Wait for the browser to open

            // Blink the LED for 2 seconds
            digitalWrite(ledPin, HIGH);  // Turn on the LED
            delay(500);                  // Wait for half a second
            digitalWrite(ledPin, LOW);   // Turn off the LED
            delay(500);                  // Wait for half a second
            digitalWrite(ledPin, HIGH);  // Turn on the LED
            delay(1000);                 // Wait for one second
            digitalWrite(ledPin, LOW);   // Turn off the LED           

            delay(5000); // Wait 5 seconds before restarting the loop
        }
    } else {
        // If the button is not pressed, do nothing and loop
        delay(100);
    }
}
