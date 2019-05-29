#include <SoftwareSerial.h>


SoftwareSerial SoftSerial(10, 11);  // (RX of Arduino,TX of Arduino)
char ssid[] = "Zeus";            // your network SSID (name)
char pass[] = "google123456";        // your network password

#define default_baud_rate 115200  // set this as the default baud rate of the ESP8266 module
String target_baud_rate = "9600"; // set this as the baud rate you want to change into
int target;

void setup()
{
  // Setup WiFI
  Serial.begin(115200);
  target  = target_baud_rate.toInt();
  
  // initialize serial for ESP module
  SoftSerial.begin(default_baud_rate);
  while(!Serial.available());    // wait for serial monitor

  // reset module
  SoftSerial.println("AT+RST");
  Serial.println("AT+RST");
  char value;
  while (SoftSerial.available()) {
    value = SoftSerial.read();
    Serial.println(value);

  }

  // check AT commands
  SoftSerial.println(F("AT"));
  Serial.println(F("AT"));
  delay(1000);

  while (SoftSerial.available()) {
    value = SoftSerial.read();
    Serial.println(value);

  }

  // change baud rate
  Serial.println("AT+UART_DEF=" + target_baud_rate + ",8,1,0,0");
  SoftSerial.println("AT+UART_DEF=" + target_baud_rate + ",8,1,0,0");
  delay(1000);


  while (SoftSerial.available()) {
    value = SoftSerial.read();
    Serial.println(value);

  }
  // Restart SoftwareSerial for the new baud rate for the WiFi

  SoftSerial.end();
  SoftSerial.begin(target);

}

void loop()
{
  // empty loop
}
