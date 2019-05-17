#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;



/*RTC Connections
 * SCL pin -> Analógico 5
 * SDA pin -> Analógico 4
 */


int ledPin = 13;
int analogPin4 = A4;
float read_val1, real_val1 = 0;
float read_val2, real_val2 = 0;
float read_val3, real_val3 = 0;
float read_val4, real_val4 = 0;
unsigned long time;
char serialData;
boolean config = false;


void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial.begin(57600);
    
    if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
     rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}
void loop()
{
   if(time <= 10000)
   {
    initialize();
   }else{
     Serial.print("LENDO DADOS");
     Serial.println("");
//     val = analogRead(analogPin4);
     read_val1 = 4.9850;
     read_val2 = 4.9960;
     read_val3 = 4.4150;
     read_val4 = 5.0060;

     real_val1 = converse_channel1(read_val1);
     real_val2 = converse_channel23(read_val2);
     real_val3 = converse_channel32(read_val3);
     real_val4 = converse_channel4(read_val4);
     Serial.print("Channel 1 in: ");
     Serial.println(read_val1, 10);
     Serial.print("Channel 1 real: ");
     Serial.println(real_val1, 10);
     
     Serial.print("Channel 2: ");
     Serial.println(read_val2, 10);
     Serial.print("Channel 2 real: ");
     Serial.println(real_val2, 10);
     
     Serial.print("Channel 3: ");
     Serial.println(read_val3, 10);
     Serial.print("Channel 3 real: ");
     Serial.println(real_val3, 10);
     
     Serial.print("Channel 4: ");
     Serial.println(read_val4, 10);
     Serial.print("Channel 4 real: ");
     Serial.println(real_val4, 10);

     DateTime now = rtc.now();
     Serial.print("[DATA]  ");
     Serial.print(now.hour(), DEC);
      Serial.print(':');
      Serial.print(now.minute(), DEC);
      Serial.print(':');
      Serial.print(now.second(), DEC);
     

     digitalWrite(ledPin, HIGH);
     delay(1000);
     digitalWrite(ledPin, LOW);
     delay(1000);
   }
}

void initialize()
{
    time = millis();
    Serial.print("INICIALIZANDO - Time: ");
    Serial.println(time);
    
    blinkLed();
    readChar();
}

void blinkLed()
{
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  delay(200);
}

void readChar()
{
  if(Serial.available()> 0)
    {
      serialData = Serial.read();
      config = true;
      configMode();
    }
}
  
void configMode()
{
  if(config and (serialData == 0x63 or serialData ==0x43))
    {
      Serial.println("ENTROU MODO CONFIG RTC");
      time = 50000;
      config = false;
//      setRTC();
    }
}

//void setRTC()
//{
//  int i;
//  for(i=0; i<10; i++)
//  {
//    digitalWrite(ledPin, HIGH);
//    delay(200);
//    digitalWrite(ledPin, LOW);
//    delay(200);
//    digitalWrite(ledPin, HIGH);
//    delay(200);
//    digitalWrite(ledPin, LOW);
//    delay(2000);  
//  }
//  
//}

float converse_channel1(float data_in)
{
//  Vreal = (Vlido - Voff")/G - Voff'
    float Voff1 = 0.0067;
    float Voff2 = 0.015;
    float gain = 10.9;
    float Vreal;

    Vreal = ((data_in - Voff2)/gain) - Voff1;

    return Vreal;
}

float converse_channel23(float data_in)
{
//  Vreal = (Vlido - Voff")/G - Voff'
    float Voff1 = 0.0066;
    float Voff2 = 0.0245;
    float gain = 10.93;
    float Vreal;

    Vreal = ((data_in - Voff2)/gain) - Voff1;

    return Vreal;
}

float converse_channel32(float data_in)
{
//  Vreal = (Vlido - Voff")/G - Voff'
    float Voff1 = 0.0076;
    float Voff2 = -0.025;
    float gain = 10.9;
    float Vreal;

    Vreal = ((data_in - Voff2)/gain) - Voff1;

    return Vreal;
}

float converse_channel4(float data_in)
{
//  Vreal = (Vlido - Voff")/G - Voff'
    float Voff1 = 0.0030;
    float Voff2 = 0.062;
    float gain = 10.9;
    float Vreal;

    Vreal = ((data_in - Voff2)/gain) - Voff1;

    return Vreal;
}
