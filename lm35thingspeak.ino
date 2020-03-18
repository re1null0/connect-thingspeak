#include <ESP8266WiFi.h>

String apiWritekey = "2XKXRU079VIMY7BR";
 // replace with your THINGSPEAK WRITEAPI key here
const char* ssid = "iPhone lol"; // your wifi SSID name
const char* password = "lolwro2019" ;// wifi pasword
#define LED D0  
const char* server = "api.thingspeak.com";// 3.3 is the supply volt  & 1023 is max analog read value
WiFiClient client;
 
void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();
  pinMode(LED, OUTPUT);  
  //digitalWrite(LED, HIGH);  
  //delay(5000); 
}
 
void loop() {
  int mq = analogRead(A0);
  
  if (client.connect(server,80))
  {  
    String tsData = apiWritekey;
           tsData +="&field1=";
           tsData += String(mq);
           tsData += "\r\n\r\n";
      
     
     if(mq<350){
      digitalWrite(LED, LOW);
      // wait for 1 second.
     }
     digitalWrite(LED, HIGH);
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(tsData.length());
     client.print("\n\n");  // the 2 carriage returns indicate closing of Header fields & starting of data
     client.print(tsData);
 
     Serial.print("mqerature: ");
     Serial.print(mq);
     Serial.println("uploaded to Thingspeak server....");
  }
  client.stop();
 
  Serial.println("Waiting to upload next reading...");
  Serial.println();
  digitalWrite(LED, LOW);
  if(mq <350){
    
    digitalWrite(LED, HIGH);
  }
  // thingspeak needs minimum 15 sec delay between updates
  delay(15000);
  
}
