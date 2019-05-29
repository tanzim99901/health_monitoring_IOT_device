#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);  // (RX of Arduino,TX of Arduino)

void setup()
{
  Serial.begin(9600);     
  while (!Serial.available());  // wait for serial monitor

  // Start the software serial for communication with the ESP8266
  mySerial.begin(9600); // set this according to the default baud rate of ESP8266

  Serial.println("");
  Serial.println("Remember to to set Both NL & CR in the serial monitor.");
  Serial.println("Ready");
  Serial.println("");
}

void loop()
{
  // listen for communication from the ESP8266 and then write it to the serial monitor
  if ( mySerial.available() )   {
    Serial.write( mySerial.read() );
  }

  // listen for user input and send it to the ESP8266
  if ( Serial.available() )       {
    mySerial.write( Serial.read() );
  }
}
