import threading
import queue
import time

import random
from paho.mqtt import client as mqtt_client



# configuration for MQTT #
broker = 'broker.emqx.io'
port = 1883
topic = "tzumi/mqtt"
# generate client ID with pub prefix randomly
client_id = f'python-mqtt-{random.randint(0, 1000)}'
username = 'emqx'
password = 'public'
##########################

### MQTT functions ###
def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)
    client = mqtt_client.Client(client_id)
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client

def publish(client, msg):
    result = client.publish(topic, msg)
    status = result[0]
    if status == 0:
        print(f"Send `{msg}` to topic `{topic}`")
    else:
        print(f"Failed to send message to topic {topic}")

#######################

#https://stackoverflow.com/questions/5404068/how-to-read-keyboard-input/53344690#53344690

def read_kbd_input(inputQueue):
    print('Ready for keyboard input:')
    while (True):
        input_str = input()
        inputQueue.put(input_str)





def send_mqtt_message(client, some_text):
    publish(client, some_text)

    # The rest of your program goes here.

    time.sleep(0.01)