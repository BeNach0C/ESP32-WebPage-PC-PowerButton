Español: 
========
Este proyecto requiere la apertura de puertos en un router, si no sabes que es eso, probablemente no deberías probar el proyecto; solicita ayuda a un profesional.
Este proyecto te permite correr un webserver en un ESP32 el cual después de ingresar una clave te permite encender tu PC con la ayuda de un circuito simple.
Este proyecto requiere un esp32, un computador con arduino IDE, un Transistor 2n2222 y una resistencia de 1KΩ.
Si no sabes configurar el arduino IDE preguntale a tu IA de preferencia, es sencillo.

Al inicio del archivo .ino hay que cambiar las credenciales de tu WiFi y la clave que deseas usar.
Para asignar la ip estática puedes correr el comando ipconfig en windows y ver los datos, en caso de otros dispositivos o si no te queda claro, cualquier IA te debería poder ayudar.

El código trae un debug por serial, una vez flasheado al esp32 puedes mantenerlo conectado al IDE y ver la salida presionando Ctrl-Shift-M con un baud de 115200 (valor por defecto).
El esp32 va conectado por usb a un cargador de telefono (uno de 5V 1A debería bastar).

Una vez el esp32 tenga flasheado el programa y esté verificado funcionando, hay que armar el circuito.
En la placa madre del PC hay un panel frontal (revisa el manual de la misma) el cual contiene dos pines (GND y 3.3V, ojalá revisar la polaridad con un tester), el GND ir al GND de el esp32, el positivo de la placa (probablemente 3.3V standby) debe ir al colector del transistor, el emisor a GND y la base conectada a través de la resistencia de 1KΩ a el GPIO4 del esp32.
Armando un cable "Y" simple con dos conectores hembra y uno macho por pin, se puede conectar tanto el esp32 como el botón de encendido de la caja del PC para no perder su funcionalidad.
En tu router hay que abrir el puerto 80 TCP a la ip estática asignada a el esp32 (se pueden usar otros puertos, 80 es el por defecto).
Si tu ip pública cambia con el tiempo, ve si puedes agregar un DDNS (recomiendo No-Ip, por lo menos en Nov/2025, ofrecen un dominio gratis).

English:
========
This project requires opening ports on a router. If you don't know what that is, you probably shouldn't attempt the project; seek help from a professional.
This project allows you to run a web server on an ESP32, which, after entering a password, allows you to turn on your PC using a simple circuit.
This project requires an ESP32, a computer with the Arduino IDE, a 2N2222 transistor, and a 1KΩ resistor.
If you don't know how to configure the Arduino IDE, ask your preferred AI, it's simple and it should get it right.

At the beginning of the .ino file, you need to change your Wi-Fi credentials and the password you want to use.
To assign a static IP address, you can run the ipconfig command in Windows and view the information. For other devices, or if you're still unsure, any AI ​​should be able help you. 

The code includes serial debugging. Once flashed to the ESP32, you can keep it connected to the IDE and view the output by pressing Ctrl-Shift-M with a baud rate of 115200 (default value).
The ESP32 should be connected via USB to a phone charger (a 5V 1A charger should suffice).

Once the ESP32 has the program flashed and verified to be working, you need to assemble the circuit. 
On the PC motherboard, there is a front panel (check your motherboard manual) which contains two pins (GND and 3.3V; ideally, check the polarity with a multimeter), connect the GND pin to the GND pin of the ESP32, the positive pin from the motherboard (probably 3.3V standby) should be connected to the transistor's collector, the emitter to GND, and the base connected through the 1KΩ resistor to the GPIO4 of the ESP32.
By assembling a simple Y-cable with two female and one male connector per pin, you can connect both the ESP32 and the PC case's power button without losing functionality.
On your router, you need to open TCP port 80 to the static IP address assigned to the ESP32 (you can also use other ports, 80 is the default).
If your public IP address changes over time, see if you can add a DDNS (I recommend No-IP; at least until November 2025, they offer a free domain).




NO soy responsable por ningún daño causado por intentar el proyecto, revisa todo con tester (multímetro).
I am NOT responsible for any damage caused by attempting the project, please check everything with a tester (multimeter).
