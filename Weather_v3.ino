#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <string.h>
#include "Adafruit_SI1145.h"

Adafruit_SI1145 uv = Adafruit_SI1145();
SoftwareSerial mySerial(16, 17); // RX, TX
const char* ssid = "Fatlab";
const char* password = "12345678@!";
const char* mqtt_server = "192.168.1.113";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

char                 databuffer[35];
double               temp;

void getBuffer()      //Get weather status data
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

float BarPressure()              //Barometric Pressure
{
  temp = transCharToInt(databuffer, 28, 32); // read pressure value in millibar
  return temp / 100; // convert millibar to pascals
}

float Temperature()                                                                  //Temperature ("C")
{
  temp = (transCharToInt_T(databuffer) - 32.00) * 5.00 / 9.00; // convert *F to *C
  return temp;
}

int Humidity()                                                                       //Humidity
{
  return transCharToInt(databuffer, 25, 26);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  if(!uv.begin()){
    Serial.println("Didn't find Si1145");
    while(1);
  }
}

void ReadAndPublishData(){
  float Vis = uv.readVisible();
  Serial.println(Vis);
  char VisString[8];
  dtostrf(Vis, 1, 2, VisString);
  client.publish("esp32/Vis", VisString);

  float barPress = BarPressure();
  Serial.println(barPress);
  char barPString[8];
  dtostrf(barPress, 1, 2, barPString);
  client.publish("esp32/barP", barPString);

  float temperature = Temperature();
  char tempString[8];
  dtostrf(temperature, 1, 2, tempString);
  client.publish("esp32/temperature", tempString);

  float humid = Humidity();
  char humidString[8];
  dtostrf(humid, 1, 2, humidString);
  client.publish("esp32/humidity", humidString);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  getBuffer();

  ReadAndPublishData();
  delay(3000);
}
