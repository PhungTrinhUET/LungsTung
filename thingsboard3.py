import paho.mqtt.client as mqtt
import json
import time
import requests  # Import thư viện requests

# Cấu hình ThingsBoard
THINGSBOARD_HOST = "localhost"
THINGSBOARD_PORT = 1883
ACCESS_TOKEN = "hsZZXuwcy8f20SuUmqCs"

# Cấu hình OpenWeatherMap
OWM_API_KEY = "8252e515e33a03b23f9179c37ee1c2c3"
CITY_NAME = "Hanoi"

def get_weather_data():
    # Gửi yêu cầu HTTP để lấy thông tin thời tiết từ OpenWeatherMap
    url = f"http://api.openweathermap.org/data/2.5/weather?q={CITY_NAME}&appid={OWM_API_KEY}"
    response = requests.get(url)

    if response.status_code == 200:
        weather_data = response.json()
        temperature = weather_data["main"]["temp"] - 273.15  # Chuyển độ Kelvin sang độ Celsius
        humidity = weather_data["main"]["humidity"]
        return temperature, humidity
    else:
        print("Failed to retrieve weather data.")
        return None, None

def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    client.subscribe("v1/devices/me/telemetry")

def on_disconnect(client, userdata, rc):
    if rc != 0:
        print(f"Unexpected disconnection. Reconnecting...")
        client.reconnect()

def send_data(client):
    sensor_data = {
        "temperature": 26,
        "humidity": 69,
        "longitude": 105.78271302380897,
        "latitude": 21.038727889822503
    }

    # Lấy dữ liệu thời tiết từ OpenWeatherMap
    temperature, humidity = get_weather_data()
    
    if temperature is not None and humidity is not None:
        sensor_data["temperature"] = temperature
        sensor_data["humidity"] = humidity

    client.publish("v1/devices/me/telemetry", json.dumps(sensor_data))

client = mqtt.Client()
client.username_pw_set(ACCESS_TOKEN)

client.on_connect = on_connect
client.on_disconnect = on_disconnect

client.connect(THINGSBOARD_HOST, THINGSBOARD_PORT, 60)

try:
    while True:
        send_data(client)
        time.sleep(5)
except KeyboardInterrupt:
    client.disconnect()
