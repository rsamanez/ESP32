#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif
#include <WiFi.h>

const char* ssid = "[YOUR-NETWORK-SSID]";
const char* password = "[YOUR-SSID-PASSWORD]";

void TaskClientSocket( void *pvParameters );

WiFiServer wifiServer(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  WiFi.begin(ssid,password);
  Serial.println("Connecting to Wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi network");
  Serial.println(WiFi.localIP());

  wifiServer.begin();
}

void loop() {
  WiFiClient client = wifiServer.available();
  if( client){
    Serial.println("New Client Connected...");
    xTaskCreatePinnedToCore(
    TaskClientSocket
    ,  "TaskClientSocket"
    ,  4098
    ,  &client
    ,  2  
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);
  }
}

void TaskClientSocket( void *pvParameters )
{
    WiFiClient clientHandle = *((WiFiClient*)pvParameters);
    for (;;) 
    {
      while(clientHandle.connected()){
        while(clientHandle.available()>0){
          char c = clientHandle.read();
          clientHandle.write(c); 
        }
        vTaskDelay(100);
      }
      clientHandle.stop();
      Serial.println("Client disconnected");
      vTaskDelete(NULL);
    }
}


