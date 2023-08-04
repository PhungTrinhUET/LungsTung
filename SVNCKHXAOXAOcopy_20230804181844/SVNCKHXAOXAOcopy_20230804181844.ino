#define BLYNK_TEMPLATE_ID "TMPL6sTv2f4J4"
#define BLYNK_TEMPLATE_NAME "UETVNU"

#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_NODE_MCU_BOARD
#include "BlynkEdgent.h"

#include "DHTesp.h"

#define DHTPIN 16
#define DHTTYPE DHTesp::DHT11
unsigned long timeShowOled = millis();

DHTesp dht;
BlynkTimer timer;
WidgetLED LEDCONNECT(V0);
#define NHIETDO V1
#define DOAM V2

void setup()
{
  Serial.begin(115200);
  delay(100);
  BlynkEdgent.begin();

  dht.setup(DHTPIN, DHTTYPE);
  timer.setInterval(1000L, updateBlynk);
}

void loop()
{
  BlynkEdgent.run();
  timer.run();

  if (millis() - timeShowOled > dht.getMinimumSamplingPeriod())
  {
    float t = dht.getTemperature();
    float h = dht.getHumidity();
    if (dht.getStatusString() == "OK")
    {
      showData(t, h);
    }
    timeShowOled = millis();
  }
}

void updateBlynk()
{
  if (LEDCONNECT.getValue())
    LEDCONNECT.off();
  else
    LEDCONNECT.on();
  Blynk.virtualWrite(NHIETDO, dht.getTemperature());
  Blynk.virtualWrite(DOAM, dht.getHumidity());
}

void showData(float t, float h)
{
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");
}
