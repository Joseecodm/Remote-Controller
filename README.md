# Remote Presentation Controller

A simple wireless presentation controller using a single ESP32, two push-buttons (“Next” and “Back”), an LED indicator, and a local Mosquitto MQTT broker. Python on your laptop subscribes to the broker and simulates arrow key presses to advance or rewind slides.

---

## 📂 Repository Structure

REMOTE-CONTROLLER/

├── ESP32/

│ └── controller.ino # Arduino sketch for ESP32

├── Mosquitto/

│ ├── mosquitto.conf # Broker configuration

│ └── start-broker.bat # Windows batch script to launch broker

├── Python/

│ └── controller.py # Python subscriber & keyboard simulator

├── docs/

│ └── connection.png # Wiring diagram

└── README.md # You are here


---

## ⚙️ Prerequisites

1. **Hardware**  
   - ESP32 DevKit C  
   - 2 × Push-buttons (2-pin)  
   - 1 × LED + 220 Ω resistor  
   - Breadboard & jumper wires  
   - Windows PC (or Linux/Mac) on same LAN  

2. **Software**  
   - [Arduino IDE](https://www.arduino.cc/en/software) (with ESP32 board support)  
   - [Mosquitto MQTT](https://mosquitto.org/download/)  
   - Python 3.7+  
     ```bash
     pip install paho-mqtt pynput
     ```

---

## 🔧 1. Configure & Launch Mosquitto Broker

1. **Edit** `Mosquitto/mosquitto.conf` and set your laptop’s LAN IP (e.g. `192.168.100.13`):
    ```conf
    listener 1883 192.168.100.13
    allow_anonymous true
    log_dest file mosquitto.log
    persistence true
    persistence_location .
    log_type error
    log_type warning
    log_type notice
    log_type information
    ```
2. **Start** broker by double-clicking `Mosquitto/start-broker.bat`.  
   You should see:

```bash
'Opening ipv4 listen socket on 192.168.100.13:1883.'
```

---

## ⚙️ Prerequisites

1. **Hardware**  
   - ESP32 DevKit C  
   - 2 × Push-buttons (2-pin)  
   - 1 × LED + 220 Ω resistor  
   - Breadboard & jumper wires  
   - Windows PC (or Linux/Mac) on same LAN
 
2. **Software**  
   - [Arduino IDE](https://www.arduino.cc/en/software) (with ESP32 board support)  
   - [Mosquitto MQTT](https://mosquitto.org/download/)  
   - Python 3.7+  
     ```bash
     pip install paho-mqtt pynput
     ```
## 🔌 Diagrama de Conexión

![Diagrama de Conexión](docs/connection.png)

- **Botón NEXT**: GPIO4 → botón → GND  
- **Botón BACK**: GPIO21 → botón → GND  
- **LED**: GPIO16 → resistencia 220 Ω → LED → GND 
---

## 🔧 1. Configure & Launch Mosquitto Broker

1. **Edit** `Mosquitto/mosquitto.conf` and set your laptop’s LAN IP (e.g. `192.168.100.13`):
    ```conf
    listener 1883 192.168.100.13
    allow_anonymous true
    log_dest file mosquitto.log
    persistence true
    persistence_location .
    log_type error
    log_type warning
    log_type notice
    log_type information
    ```
2. **Start** broker by double-clicking `Mosquitto/start-broker.bat`.  
   You should see:

Edit controller.py if you changed your broker IP or topic.

Run:

```bash
python controller.py
```

You should see:

```bash
Connecting to broker MQTT in 192.168.100.13:1883...
Connected to broker!
Subscribed to topic 'josee/control/presentacion'
Waiting for messages…
   
-> Avanzar diapositiva
<- Retroceder diapositiva
 ```

Now, pressing Next or Back on your ESP32 will publish to MQTT, and your laptop script will simulate the right/left arrow keys to change slides.

---

## 🛠️ Troubleshooting
No serial output? Close Arduino Serial Monitor before running Python.

MQTT connect fails? Verify mosquitto.conf IP and that firewall allows port 1883.

Buttons stuck LOW? Make sure pins use INPUT_PULLUP and buttons go to GND.

LED not blinking? Check wiring and that your code toggles digitalWrite(pinLED, …).

---

##📄 License

Feel free to tweak any section or add your own notes!
