#include "SoftwareSerial.h"
#include <OneWire.h>
#include <DallasTemperature.h>
//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
#define R_switch 3
#define F_switch 4

#define batt_pin A0

#define heart_pin 2

#define led_pin 5

#define ONE_WIRE_BUS 4
//boolean led_state = LOW;//state of LED, each time an external interrupt
//will change the state of LED
unsigned char counter;
unsigned long temp[21];
unsigned long sub;
bool data_effect = true;
bool error = false;
int err_count = 0;
int iterations = 1;
int heart_rate;//the measurement result of heart rate
int heart_threshold = 200;
boolean low = 0;
boolean high = 0;
boolean done = 0;
const int max_heartpluse_duty = 2000;//you can change it follow your system's request.
//2000 meams 2 seconds. System return error
//if the duty overtrip 2 second.

const int count_limit = 10;

String ssid = "MISSD2";

String password = "222223227sd";

SoftwareSerial esp(10, 11);// RX, TX

float maxVolt = 5.00;
float voltage = 0.00;
float temperature = 0.00;

int gorom = 24;
int chest = 70;

String server = "192.168.101.114"; // www.example.com


//String temp , hum;
boolean connection = 0;
boolean sent_packet = 0;
boolean start = 1;


String Celcius, Heart, Voltage;

OneWire oneWire(ONE_WIRE_BUS);
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
/********************************************************************/

void setup() {
  Serial.begin(9600);

  pinMode(heart_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  sensors.begin();
  Serial.println("Please get your ear clip ready.");
  //while (digitalRead(F_switch));


  //while (!Serial.available());
  esp.begin(9600);


  Serial.println("Heart rate test begin.");
  digitalWrite(led_pin, LOW);
  delay(100);
  reset();
  delay(2000);
  connectWifi();
  delay(2000);
}

void loop () {
  //reset_only();
  //if (!start) delay(5000);
  //mode_only();
  //connectWifi();

  digitalWrite(led_pin, HIGH);
  Serial.println("DONE CONNECTION!");
  delay(1000);
  err_count = 0;
  while (!done)
  {
    read_heart_rate();
  }
  delay(200);
  done = 0;
  arrayInit();


  while (!sent_packet)
  {

    get_temp();
    //printVolts();
    call();
  }
  gorom++;
  chest++;
  sent_packet = 0;
  start = 0;
  delay(2000);
  Serial.println("PATHAY DISI>>");
  delay(2000);
  //reset();
  digitalWrite(led_pin, LOW);
  
  
  // WAITING TIME BETWEEN READINGS ///
  delay(30000); // SET TO 30 SECONDS
  ///////////////////////////////////


}

void get_temp()
{
  Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperature readings
  Serial.println("DONE");
  /********************************************************************/
  Serial.print("Temperature is: ");
  temperature = sensors.getTempCByIndex(0); // Why "byIndex"?
  Serial.println(temperature);
  // You can have more than one DS18B20 on the same bus.
  // 0 refers to the first IC on the wire
  delay(200);
}

void printVolts()
{
  int sensorValue = analogRead(batt_pin); //read the A0 pin value
  voltage = sensorValue * (maxVolt / 1023.00); //convert the value to a true voltage.
  voltage = (voltage / maxVolt) * 100;
  //lcd.setCursor(0, 0);
  //lcd.print("voltage = ");
  Serial.print(sensorValue); //print the voltage to LCD
  Serial.print("\t");
  Serial.println(voltage); //print the voltage to LCD

  delay(500);
  //lcd.print(" V");
  //if (voltage < 6.50) //set the voltage considered low battery here
  //{
  //digitalWrite(led_pin, HIGH);
  //}
}
