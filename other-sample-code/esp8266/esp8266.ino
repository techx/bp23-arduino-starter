#include <SoftwareSerial.h>                        
SoftwareSerial esp8266(10,11);                   
#define serialCommunicationSpeed 115200               
#define DEBUG true    

String wifi_network = "MIT GUEST";
String wifi_pwd = "";

void setup()

{
  Serial.begin(serialCommunicationSpeed);           
  esp8266.begin(serialCommunicationSpeed);     
  InitWifiModule();                              
}

void loop()                                                         
{

  if(esp8266.available())                                           
 {    
    if(esp8266.find("+IPD,"))
    {
     delay(1000);
 
     int connectionId = esp8266.read()-48;                                                
     String webpage = "<h1>This is a header text!</h1>\r\n";
     webpage += "<p>This is normal text!<p>";
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

String sendData(String command, const int timeout, boolean debug)
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
    if(debug)                                                        
    {
      Serial.print(response);
    }    
    return response;                                                  
}

void InitWifiModule()
{
  sendData("AT+RST\r\n", 2000, DEBUG);
  sendData("AT+CWMODE=3\r\n", 1500, DEBUG);                                             
  delay (1500);                             
  sendData("AT+CWLAP\r\n", 2000, DEBUG);        
  delay (2000);              
  sendData("AT+CWJAP=\"MIT GUEST\",\"\r\n", 2000, DEBUG);        
  delay (2000);
//  sendData("AT+CWMODE=1\r\n", 1500, DEBUG);                                             
//  delay (1500);
  sendData("AT+CIFSR\r\n", 1500, DEBUG);                                             
  delay (1500);
  sendData("AT+CIPMUX=1\r\n", 1500, DEBUG);                                             
  delay (1500);
  sendData("AT+CIPSERVER=1,80\r\n", 1500, DEBUG);                                     

}
