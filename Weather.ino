#include <SoftwareSerial.h>
#include <string.h>
//  Sensor configuration
SoftwareSerial mySerial(16, 17); // RX, TX

char                 databuffer[35];
double               temp;

const int buttonPin = 4;  // D4 (GPIO 4)
int eventCount = 0;
bool buttonState = false;
bool lastButtonState = false;

void getBuffer()                                                                    //Get weather status data
{
  int index;
  for (index = 0; index < 35; index ++)
  {
    if (mySerial.available())
    {
      databuffer[index] = mySerial.read();
      if (databuffer[0] != 'c')
      {
        index = -1;
      }
    }
    else
    {
      index --;
    }
  }
}

int transCharToInt(char *_buffer, int _start, int _stop)                             //char to int）
{
  int _index;
  int result = 0;
  int num = _stop - _start + 1;
  int _temp[num];
  for (_index = _start; _index <= _stop; _index ++)
  {
    _temp[_index - _start] = _buffer[_index] - '0';
    result = 10 * result + _temp[_index - _start];
  }
  return result;
}

int transCharToInt_T(char *_buffer)
{
  int result = 0;
  if (_buffer[13] == '-') {
    result = 0 - (((_buffer[14] - '0') * 10) + (_buffer[15] - '0'));
  }
  else {
    result = ((_buffer[13] - '0') * 100) + ((_buffer[14] - '0') * 10) + (_buffer[15] - '0');
  }
  return result;
}

int WindDirection()                                                                  //Wind Direction
{
  return transCharToInt(databuffer, 1, 3);
}

float WindSpeedAverage()                                                             //air Speed (1 minute)
{
  temp = 0.44704 * transCharToInt(databuffer, 5, 7);
  return temp;
}

float WindSpeedMax()                                                                 //Max air speed (5 minutes)
{
  temp = 0.44704 * transCharToInt(databuffer, 9, 11);
  return temp;
}

float Temperature()                                                                  //Temperature ("C")
{
  temp = (transCharToInt_T(databuffer) - 32.00) * 5.00 / 9.00;
  return temp;
}

float RainfallOneHour()                                                              //Rainfall (1 hour)
{
  temp = transCharToInt(databuffer, 17, 19) * 25.40 * 0.01;
  return temp;
}

float RainfallOneDay()                                                               //Rainfall (24 hours)
{
  temp = transCharToInt(databuffer, 21, 23) * 25.40 * 0.01;
  return temp;
}

int Humidity()                                                                       //Humidity
{
  return transCharToInt(databuffer, 25, 26);
}

float BarPressure()                                                                  //Barometric Pressure
{
  temp = transCharToInt(databuffer, 28, 32);
  return temp / 10.00;
}




void setup()
{
  Serial.begin(115200);
  mySerial.begin(9600);
    pinMode(buttonPin, INPUT_PULLUP);  // Set the button pin as input with internal pull-up resistor
 
}

void loop()
{
  //testing
   Serial.print("Testing ");
   // check wifi connection

  // Read data from Weather sation
  //ReadWeatherStation();

  // Counting FAW 
  CountingFAW();
  // Send data to server via wifi

  // Delay
    delay(1000);

}

void ReadWeatherStation(){
  getBuffer();
  Serial.print("Wind Direction: ");
  Serial.print(WindDirection());
  Serial.println("  ");
  Serial.print("Average Wind Speed (One Minute): ");
  Serial.print(WindSpeedAverage());
  Serial.println("m/s  ");
  Serial.print("Max Wind Speed (Five Minutes): ");
  Serial.print(WindSpeedMax());
  Serial.println("m/s");
  Serial.print("Rain Fall (One Hour): ");
  Serial.print(RainfallOneHour());
  Serial.println("mm  ");
  Serial.print("Rain Fall (24 Hour): ");
  Serial.print(RainfallOneDay());
  Serial.println("mm");
  Serial.print("Temperature: ");
  Serial.print(Temperature());
  Serial.println("C  ");
  Serial.print("Humidity: ");
  Serial.print(Humidity());
  Serial.println("%  ");
  Serial.print("Barometric Pressure: ");
  Serial.print(BarPressure());
  Serial.println("hPa");
  Serial.println("");
  Serial.println("");

}
void CountingFAW() {
  buttonState = digitalRead(buttonPin);

  // Check for a button press (when the button state changes from HIGH to LOW)
  if (buttonState == LOW && lastButtonState == HIGH) {
    eventCount++;
    Serial.print("Event Count: ");
    Serial.println(eventCount);
    delay(200);  // Debounce delay to prevent multiple counts from a single press
  }

  lastButtonState = buttonState;
}
