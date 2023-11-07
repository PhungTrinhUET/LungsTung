import paho.mqtt.client as mqtt
import json
import time

# Cấu hình ThingsBoard
THINGSBOARD_HOST = "localhost"  # Đổi thành địa chỉ IP hoặc tên miền ThingsBoard của bạn
THINGSBOARD_PORT = 1883
ACCESS_TOKEN = "hsZZXuwcy8f20SuUmqCs"  # Sử dụng token của bạn ở đây

def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    client.subscribe("v1/devices/me/telemetry")

def on_disconnect(client, userdata, rc):
    if rc != 0:
        print(f"Unexpected disconnection. Reconnecting...")
        client.reconnect()

def send_data(client):
    data = {
        "temperature": 28.8,
        "humidity": 82.8,
        "longitude": 105.78271302380897 ,  # Thay đổi giá trị này thành longitude thực tế
        "latitude": 21.038727889822503  # Thay đổi giá trị này thành latitude thực tế
    }

    client.publish("v1/devices/me/telemetry", json.dumps(data))

client = mqtt.Client()
client.username_pw_set(ACCESS_TOKEN)

client.on_connect = on_connect
client.on_disconnect = on_disconnect

client.connect(THINGSBOARD_HOST, THINGSBOARD_PORT, 60)

try:
    while True:
        send_data(client)
        time.sleep(5)  # Đợi 5 giây trước khi gửi lần tiếp theo
except KeyboardInterrupt:
    client.disconnect()
