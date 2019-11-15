#include <Arduino.h>
#include <drone.h>
#include <joystick.h>
#include <Position.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
 

Drone::Drone(String ssid, String password)                                     //Constructor for our drone 
{
    this->ssid = ssid;
    this->password = password; 
}


void Drone::connect()
{

    Serial.println("drone begin");
    //Serial.begin(9600);
    WiFi.mode(WIFI_STA);
    WiFi.begin(this->ssid.c_str(), this->password.c_str());
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        while(1) {
            delay(1000);
        }
    }
    if(udp.listen(udpPort)) {
        this->myIp = WiFi.localIP().toString();
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());
      
        udp.onPacket(
            [this](AsyncUDPPacket packet) -> void
            {
                // make a string from the data
                String s((char*)packet.data());
                s = s.substring(0, packet.length()); 
                s.trim();
                // send string to method
                this->commandResponse(s);
            }
        );
    }
    this->sendCommand("command");
}

void Drone::sendCommand(String command)
{
    udpSender.beginPacket(this->droneIp.c_str(), udpPort);
    udpSender.printf(command.c_str());
    udpSender.endPacket();    
}

void Drone::setIp(String ip)
{
    this->droneIp = ip;
}
        
void Drone::commandResponse(String response)
{
    Serial.print("got following response: ");
    Serial.println(response.c_str());
    Serial.print("message length: ");
    Serial.println(response.length());
}

void Drone::ButtonPressed()
{
    LiquidCrystal_I2C lcd(0x27,16,2);
    lcd.init();
    lcd.backlight(); 
    //lcd.clear();   
    lcd.setCursor(0,0); 
    pinMode(light, OUTPUT);

    if (flying == false)
    {
        this->flying = true;
        Serial.println("takeoff");
        this->sendCommand("takeoff");
        lcd.print("Taking off ");
        digitalWrite(light, HIGH);
    }
    else
    {
        Serial.println("land");
        this->sendCommand("land");
        lcd.print("Landing");
        digitalWrite(light, LOW);
        this->flying = false;
    }
}

void Drone::loop()
{
    LiquidCrystal_I2C lcd(0x27,16,2);
   

    // Using Position object to retrieve information
    Position joystickPosition = this->joystick->getPosition();

   
    
    if (joystickPosition.x == 2047)
    {
        this->sendCommand("right 50");
        Serial.println(joystickPosition.y);
        lcd.init();
        lcd.backlight(); 
        lcd.clear();   
        lcd.setCursor(0,0);
        lcd.print("Turning right, 50 cm");
         
        Serial.println("Turning right");
        delay(1000);
    } 
    
    else if (joystickPosition.x == -2048)
    {
        this->sendCommand("left 50");
        Serial.println(joystickPosition.y);
        lcd.init();
        lcd.backlight(); 
        lcd.clear();   
        lcd.setCursor(0,0);
        lcd.print("Turning left, 50 cm");
        Serial.println("Turning left");
        delay(1000);
    }

    if (joystickPosition.y == 2047)
    {
        this->sendCommand("back 50");
        Serial.println(joystickPosition.y);
        lcd.init();
        lcd.backlight(); 
        lcd.clear();   
        lcd.setCursor(0,0);
        lcd.print("Going back, 50 cm");
        Serial.println("Turning back");
        delay(1000);
    } 

    else if (joystickPosition.y == -2048)
    {
        this->sendCommand("forward 50");
        Serial.println(joystickPosition.y);
        lcd.init();
        lcd.backlight(); 
        lcd.clear();   
        lcd.setCursor(0,0);
        lcd.print("Going forward, 50 cm");
        Serial.println("Turning forward");
        delay(1000);
    }

}
