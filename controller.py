import paho.mqtt.client as mqtt
from pynput.keyboard import Controller, Key

# 1) Configuración MQTT
BROKER = "192.168.76.32"
PORT   = 1883
TOPIC  = "josee/control/presentacion"

# 2) Inicializar controlador de teclado
kb = Controller()

# 3) Callbacks
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Conectado al broker {}:{}".format(BROKER, PORT))
        client.subscribe(TOPIC)
        print("Suscrito al topico '{}'".format(TOPIC))
        print("Esperando mensajes...\n")
    else:
        print("Error de conexion, codigo:", rc)

def on_message(client, userdata, msg):
    cmd = msg.payload.decode().strip()
    if cmd == "NEXT":
        print("-> Avanzar diapositiva")
        kb.press(Key.right); kb.release(Key.right)
    elif cmd == "PREV":
        print("<- Retroceder diapositiva")
        kb.press(Key.left); kb.release(Key.left)
    else:
        print("Comando desconocido recibido:", cmd)

# 4) Crear cliente y asignar callbacks
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# 5) Conectar y arrancar loop
print("Conectando a broker MQTT en {}:{}...".format(BROKER, PORT))
client.connect(BROKER, PORT, keepalive=60)
client.loop_forever()
