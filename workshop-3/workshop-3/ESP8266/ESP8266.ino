#include <SoftwareSerial.h>  
                      
SoftwareSerial esp8266(10,11);                   
#define serialCommunicationSpeed 9600  // Set the Baud Rate (the Baud Rate of your Serial Monitor must match this!)
#define DEBUG true  // Setting a global variable, which can be accessed from all functions in the program              

void setup(){
  Serial.begin(serialCommunicationSpeed);           
  esp8266.begin(serialCommunicationSpeed);     
  InitWifiModule();                              
}

void loop(){

  if (esp8266.available()) {    
    if (esp8266.find("+IPD,")){
     delay(1000);
 
     int connectionId = esp8266.read()-48;                                                
     String webpage = "<h1>Hello World!</h1>";
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
 
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";    
     sendData(closeCommand,3000,DEBUG);
    }
  }
}

String sendData(String command, const int timeout)
{
    String response = "";                                             
    esp8266.print(command);                                          
    long int time = millis();                                      
    while( (time+timeout) > millis())                                 
    {      
      while(esp8266.available())                                      
      {
        char c = esp8266.read();                                     
        response+=c;                                                  
      }  
    }    
    Serial.print(response); 
    return response;                                                  
}

void InitWifiModule()
{
  sendData("AT+RST\r\n", 2000, DEBUG);                                                  
  sendData("AT+CWJAP=\"WIFI_name\",\"pwd\"\r\n", 2000, DEBUG);        
  delay (3000);
  sendData("AT+CWMODE=1\r\n", 1500, DEBUG);                                             
  delay (1500);
  sendData("AT+CIFSR\r\n", 1500, DEBUG);                                             
  delay (1500);
  sendData("AT+CIPMUX=1\r\n", 1500, DEBUG);                                             
  delay (1500);
  sendData("AT+CIPSERVER=1,80\r\n", 1500, DEBUG);                                     

}
