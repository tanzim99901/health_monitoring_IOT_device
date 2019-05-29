void call ()
{

  esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");//start a TCP connection.

  if ( esp.find("OK")) {

    Serial.println("TCP connection ready");

  } delay(2000);

  //String celcius = Celcius;
  //String heart = Heart;
  if (gorom >= 98) gorom = 24;
  if (chest >= 160) chest = 70;

  Celcius = temperature;
  //Heart = heart_rate;
  //Voltage = voltage;
  //Voltage = Voltage + "%";

  //Celcius = "30.00";
  //Heart = "88";
  //Voltage = "70%";
  String getRequest = "GET /iot/dataesp8266.php?celcius=" + Celcius + "&beat=" + Heart + "\r\nHost:" + server + "\r\n\r\n\r\n\r\n\r\n";
  //\r\n\r\n\r\n\r\n\r\n
  //String getRequest = "GET http://tanzim99901.atwebpages.com/play.html\r\nHost:185.176.43.88\r\n\r\n\r\n\r\n\r\n";
  String sendCmd = "AT+CIPSEND=";
  sendCmd += getRequest.length();
  sendCmd += "\r\n";

  // esp.print("GET /iot/dataesp8266.php?");
  // esp.print("celcius=");
  //esp.print(Celcius);
  //esp.print("&beat=");
  // esp.print(Heart);
  //esp.println();
  esp.println(sendCmd);
  delay(1000);

  if (esp.find(">")) {
    Serial.println("Sending..");
    esp.print(getRequest);

    if ( esp.find("SEND OK")) {
      Serial.println("Packet sent");
      //String tmpResp, tmpFin;
      /*while (esp.available()) {

        tmpResp = esp.readString();

        //Serial.println(tmpResp);

        }
        tmpFin = tmpResp.substring(241, tmpResp.length());
        int closed = tmpFin.indexOf('C');
        tmpFin = tmpResp.substring(241, 241 + closed);
        Serial.println(tmpFin);
        if (tmpFin.indexOf('1') != -1) digitalWrite(redpin, HIGH);
        else if (tmpFin.indexOf('0') != -1) digitalWrite(redpin, LOW);*/
      /*if (tmpFin == "1") digitalWrite(redpin, HIGH);
        else if (tmpFin == "0") digitalWrite(redpin, LOW);*/
      //Serial.println(tmpResp);
      //Serial.println(tmpResp.length());
      digitalWrite(led_pin, HIGH);
      sent_packet = 1;
      // close the connection

      esp.println("AT+CIPCLOSE");
      delay(2000);
    }

  }

}


//reset the esp8266 module

void reset() {

  esp.println("AT+RST\r\n");

  delay(1000);

  if (esp.find("OK") )
  {
    Serial.println("Module Reset");
    digitalWrite(led_pin, HIGH);
  }

  delay(1000);
  digitalWrite(led_pin, LOW);
  esp.println("AT+CWMODE=3\r\n");
  if (esp.find("OK") )
  {
    Serial.println("Mode changed");
    digitalWrite(led_pin, HIGH);
  }
  delay(1000);
  digitalWrite(led_pin, LOW);
}

void reset_only() {

  esp.println("AT+RST\r\n");

  delay(1000);

  if (esp.find("OK") )
  {
    Serial.println("Module Reset");
    digitalWrite(led_pin, HIGH);
    delay(500);
    digitalWrite(led_pin, LOW);

  }
  delay(1000);
  //esp.println("AT+CWMODE=3\r\n");
  //if (esp.find("OK") ) Serial.println("Mode changed");
  //delay(1000);
}

void mode_only() {

  //esp.println("AT+RST\r\n");

  //delay(1000);

  //if (esp.find("OK") ) Serial.println("Module Reset");
  //delay(1000);
  esp.println("AT+CWMODE=3\r\n");
  if (esp.find("OK") )
  {
    Serial.println("Mode changed");
    digitalWrite(led_pin, HIGH);
    delay(500);
    digitalWrite(led_pin, LOW);

  }
  delay(1000);
}

//connect to your wifi network

void connectWifi() {

  String cmd = "AT+CWJAP=\"" + ssid + "\",\"" + password + "\"";

  esp.println(cmd);

  delay(2000);

  if (esp.find("OK")) {

    Serial.println("Connected!");
    connection = 1;
    digitalWrite(led_pin, HIGH);
  }

  else {
    Serial.println("Cannot connect to wifi");
    connection = 0;
    digitalWrite(led_pin, LOW);
  }
  if (!connection)
  {
    connectWifi();
  }
}
