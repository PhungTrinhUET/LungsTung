# Import các thư viện cần thiết
import paho.mqtt.client as mqtt  # Thư viện MQTT cho việc kết nối và gửi dữ liệu đến ThingsBoard
import json  # Thư viện để làm việc với định dạng JSON
import time  # Thư viện cho việc quản lý thời gian
import requests  # Thư viện để tạo yêu cầu HTTP để lấy dữ liệu thời tiết từ OpenWeatherMap

# Cấu hình ThingsBoard
THINGSBOARD_HOST = "localhost"  # Địa chỉ máy chủ ThingsBoard
THINGSBOARD_PORT = 1883  # Cổng MQTT của ThingsBoard
ACCESS_TOKEN = "hsZZXuwcy8f20SuUmqCs"  # Mã thông báo để xác thực thiết bị trên ThingsBoard

# Cấu hình OpenWeatherMap
OWM_API_KEY = "8252e515e33a03b23f9179c37ee1c2c3"  # Khóa API của OpenWeatherMap
CITY_NAME = "Hanoi"  # Tên thành phố cần lấy thông tin thời tiết

# Hàm lấy thông tin thời tiết từ OpenWeatherMap
def get_weather_data():
    # Gửi yêu cầu HTTP để lấy thông tin thời tiết từ OpenWeatherMap
    url = f"http://api.openweathermap.org/data/2.5/weather?q={CITY_NAME}&appid={OWM_API_KEY}"
    response = requests.get(url)

    # Kiểm tra nếu yêu cầu thành công (status code 200)
    if response.status_code == 200:
        # Trích xuất dữ liệu thời tiết từ phản hồi JSON
        weather_data = response.json()
        # Chuyển độ Kelvin sang độ Celsius và lấy nhiệt độ và độ ẩm
        temperature = weather_data["main"]["temp"] - 273.15
        humidity = weather_data["main"]["humidity"]
        return temperature, humidity
    else:
        # In thông báo lỗi nếu yêu cầu thất bại và trả về giá trị None
        print("Failed to retrieve weather data.")
        return None, None

# Hàm được gọi khi thiết bị kết nối đến ThingsBoard
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    client.subscribe("v1/devices/me/telemetry")

# Hàm được gọi khi kết nối đến ThingsBoard bị ngắt
def on_disconnect(client, userdata, rc):
    if rc != 0:
        print(f"Unexpected disconnection. Reconnecting...")
        client.reconnect()

# Hàm gửi dữ liệu đến ThingsBoard
def send_data(client):
    # Lấy thông tin thời tiết từ OpenWeatherMap
    temperature, humidity = get_weather_data()
    
    # Nếu thông tin thời tiết có sẵn
    if temperature is not None and humidity is not None:
        # Tạo một đối tượng JSON chứa các giá trị cảm biến
        sensor_data = {
            "temperature": temperature,
            "humidity": humidity,
            "longitude": 105.78271302380897,
            "latitude": 21.038727889822503
        }
        # Gửi dữ liệu lên ThingsBoard qua MQTT
        client.publish("v1/devices/me/telemetry", json.dumps(sensor_data))
    else:
        # In thông báo lỗi nếu không thể lấy thông tin thời tiết
        print("Failed to retrieve weather data.")

# Tạo một đối tượng MQTT client
client = mqtt.Client()
client.username_pw_set(ACCESS_TOKEN)  # Cấu hình thông tin xác thực

client.on_connect = on_connect
client.on_disconnect = on_disconnect

# Kết nối đến ThingsBoard
client.connect(THINGSBOARD_HOST, THINGSBOARD_PORT, 60)

# Vòng lặp chính
try:
    while True:
        # Gửi dữ liệu đến ThingsBoard và đợi 5 giây
        send_data(client)
        time.sleep(5)
except KeyboardInterrupt:
    # Ngắt kết nối khi người dùng nhấn Ctrl+C
    client.disconnect()
