#include <virtuabotixRTC.h>

/*RTC Connections
 * SCL pin -> Analógico 5
 * SDA pin -> Analógico 4
 */
virtuabotixRTC myRTC(6, 7, 8);


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
    Serial.begin(9600);
    myRTC.setDS1302Time(00, 02, 12, 6, 17, 5, 2019);
    
}


void loop()
{
   if(time <= 10000)
   {
    initialize();
   }else{
     Serial.print("LENDO DADOS");
     Serial.println("");

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

        
         // Le as informacoes do CI
      myRTC.updateTime(); 
    
      // Imprime as informacoes no serial monitor
      Serial.print("Data : ");
      // Chama a rotina que imprime o dia da semana
      imprime_dia_da_semana(myRTC.dayofweek);
      Serial.print(", ");
      Serial.print(myRTC.dayofmonth);
      Serial.print("/");
      Serial.print(myRTC.month);
      Serial.print("/");
      Serial.print(myRTC.year);
      Serial.print("  ");
      Serial.print("Hora : ");
      // Adiciona um 0 caso o valor da hora seja <10
      if (myRTC.hours < 10)
      {
        Serial.print("0");
      }
      Serial.print(myRTC.hours);
      Serial.print(":");
      // Adiciona um 0 caso o valor dos minutos seja <10
      if (myRTC.minutes < 10)
      {
        Serial.print("0");
      }
      Serial.print(myRTC.minutes);
      Serial.print(":");
      // Adiciona um 0 caso o valor dos segundos seja <10
      if (myRTC.seconds < 10)
      {
        Serial.print("0");
      }
      Serial.println(myRTC.seconds);
    
      delay( 1000);
  
     // Wait one second before repeating :)

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

void imprime_dia_da_semana(int dia)
{
  switch (dia)
  {
    case 1:
    Serial.print("Domingo");
    break;
    case 2:
    Serial.print("Segunda");
    break;
    case 3:
    Serial.print("Terca");
    break;
    case 4:
    Serial.print("Quarta");
    break;
    case 5:
    Serial.print("Quinta");
    break;
    case 6:
    Serial.print("Sexta");
    break;
    case 7:
    Serial.print("Sabado");
    break;
  }
}
