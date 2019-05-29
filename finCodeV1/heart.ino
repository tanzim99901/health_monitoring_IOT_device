/*Function: calculate the heart rate*/
void sum()
{
  if (data_effect)
  {
    long int numerator1, numerator;
    numerator1 = 60 * count_limit;
    numerator = numerator1 * 1000;
    Serial.print("Numerator: ");
    Serial.println(numerator);
    heart_rate = (numerator) / (temp[count_limit] - temp[0]); //60*20*1000/20_total_time
    Serial.print("Heart_rate_is:\t");
    Serial.println(heart_rate);
    if (heart_rate > heart_threshold) heart_rate = 0;
    Heart = heart_rate;
  }
  if (error)
  {
    heart_rate = 0;
    Heart = heart_rate;
    Serial.print("Heart rate sensor is ");
    Serial.println(Heart);
  }
  data_effect = 1; //sign bit
  error = 0;
  done = 1;
}
/*Function: Interrupt service routine.Get the sigal from the external interrupt*/
void interrupt()
{
  temp[counter] = millis();
  Serial.print("Counter: ");
  Serial.println(counter, DEC);
  Serial.print("Temp[");
  Serial.print(counter, DEC);
  Serial.print("]: ");
  Serial.println(temp[counter]);
  switch (counter)
  {
    case 0:
      sub = temp[counter] - temp[count_limit];
      Serial.print("Sub: ");
      Serial.println(sub);
      break;
    default:
      sub = temp[counter] - temp[counter - 1];
      Serial.print("Sub: ");
      Serial.println(sub);
      break;
  }
  if (sub > max_heartpluse_duty) //set 2 seconds as max heart pluse duty
  {
    data_effect = 0; //sign bit
    counter = 0;
    err_count++;
    if (err_count > iterations)
    {
      Serial.println("Disconnected");
      error = 1;
      err_count = 0;
    }
    else Serial.println("Heart rate measure error,test will restart!" );
    arrayInit();
  }
  if (error)
  {
    Serial.println("BIG ERROR!!!");
    counter = 0;
    sum();
  }
  if ((counter == count_limit && data_effect))
  {
    counter = 0;
    sum();
  }
  else if (counter != count_limit && data_effect)
    counter++;
  else
  {
    counter = 0;
    data_effect = 1;
  }

}
/*Function: Initialization for the array(temp)*/
void arrayInit()
{
  for (unsigned char i = 0; i < count_limit; i ++)
  {
    temp[i] = 0;
  }
  temp[count_limit] = millis();
}

void read_heart_rate()
{
  if (!digitalRead(heart_pin)) low = 1;
  if (digitalRead(heart_pin) && low)
  {
    interrupt();
    high = 1;
    low = 0;
  }
}
