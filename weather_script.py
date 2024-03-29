import requests
import json
import psycopg2
import pandas as pd
import time
import datetime

# INFORMATION
USERNAME_ACCOUNT = "tenant@thingsboard.org"
PASSWORD_ACCOUNT = "tenant"
SCHEDULE_MINUTE = 1
TIME_RANGE = SCHEDULE_MINUTE * 60
END_TS = int(time.time()) * 1000
START_TS = int(END_TS / 1000 - TIME_RANGE) * 1000
ENTITY_ID = "ec7c07a0-8dc1-11ee-8a88-fb01c5fb7257"
TYPE = "DEVICE"
DATABASE = "weather"
USERNAME_DB = "postgres"
PASSWORD_DB = "123456"
HOST = "localhost"
PORT = "5432"


def calculate_date_time(timeseries):
    datetime_object = pd.to_datetime(timeseries, unit='ms')
    return datetime_object


def get_access_token():
    url_login = "http://localhost:8080/api/auth/login"
    data_login = {'username': USERNAME_ACCOUNT,
                  'password': PASSWORD_ACCOUNT, }
    headers_login = {
        'accept': 'application/json',
        'Content-Type': 'application/json',
    }
    response = requests.post(
        url_login, headers=headers_login, data=json.dumps(data_login))
    data = json.loads(response.text)
    token = data['token']
    print("TOKEN IS: ")
    print("======================================================================================")
    print(token)
    print("======================================================================================")
    return token


def get_data(start_ts, end_ts, entity_id, type, token):
    url_get_data = "http://localhost:8080/api/plugins/telemetry/"+type+"/" + \
        entity_id + "/values/timeseries"
    querystring = {"keys": "outsideHumidity,outsideMaxTemp,outsideMinTemp,outsideTemp",
                   "startTs": start_ts, "endTs": end_ts}

    headers_get_data = {
        "accept": "application/json",
        "X-Authorization": "Bearer " + token
    }

    
    response = requests.get(
        url_get_data, headers=headers_get_data, params=querystring)
    # response.raise_for_status()
    print(response.text)
    data = response.json()
    print("DATA IS: ")
    print(data)
    print("======================================================================================")
    return data
    # except requests.exceptions.RequestException as e:
    #     print(f"Không thể lấy dữ liệu từ API: {e}")
    #     return None
    # except json.JSONDecodeError as e:
    #     print(f"Không thể giải mã phản hồi JSON: {e}")
    #     return None


def send_data_to_database(data, database, user, password, host, port):
    conn = psycopg2.connect(database=database, user=user,
                            password=password, host=host, port=port)
    cur = conn.cursor()

    outsideHumidityArr = data['outsideHumidity']
    outsideMaxTempArr = data['outsideMaxTemp']
    outsideMinTempArr = data['outsideMinTemp']
    outsideTempArr = data['outsideTemp']

    for i in range(len(data['outsideHumidity'])):
        cur.execute("""
                    INSERT INTO "weatherData"("dataTime", "outsideHumidity", "outsideMaxTemp", "outsideMinTemp", "outsideTemp") VALUES (%s,%s,%s,%s,%s);
                    """,
                    (calculate_date_time(outsideHumidityArr[i]['ts']), outsideHumidityArr[i]['value'], outsideMaxTempArr[i]['value'], outsideMinTempArr[i]['value'], outsideTempArr[i]['value']))
    conn.commit()
    cur.close()
    conn.close()
    print("SUCCESS: SEND DATA TO DATABASE!!!")
    print("======================================================================================")


if __name__ == "__main__":
    start_ts = START_TS
    end_ts = END_TS
    entity_id = ENTITY_ID
    type = TYPE
    database = DATABASE
    user = USERNAME_DB
    password = PASSWORD_DB
    host = HOST
    port = PORT
    while True:
        now = "NOW: " + \
            str(str(datetime.datetime.utcnow().strftime('%Y-%m-%d %H:%M:%S')))
        minute_left = "DATA WILL BE GOT IN: " + \
            str(SCHEDULE_MINUTE - 1 - datetime.datetime.now().minute %
                SCHEDULE_MINUTE) + " minutes"
        print(now + " || " + minute_left, end="\r", flush=True)
        if (datetime.datetime.now().minute % SCHEDULE_MINUTE == 0):
            print("SEND DATA AT: " + str(datetime.datetime.utcnow()))
            token = get_access_token()
            data = get_data(start_ts=start_ts, end_ts=end_ts,
                            entity_id=entity_id, type=type, token=token)
            if data is not None:
                send_data_to_database(data=data, database=database,
                                      user=user, password=password, host=host, port=port)
            time.sleep(60)
