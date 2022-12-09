# ESP32
ESP32 some code samples

### Server with multiple clients at same time
This code uses FREE-RTOS Tasks to manage multiple clients connections at same time.   
[multi_clients](multi_clients.ino)   
    
To connect a client use a Telnet conection to port 80
```
$> telnet [esp32-server-ip] 80
```
This sample implements a ECHO service
