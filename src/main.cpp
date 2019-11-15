#include <Arduino.h>
#include <string.h>
#include <drone.h>
#include <joystick.h>



String ssid = "TELLO-FE2F50";                               //Creating a string that is the SSID (The drones identity)
String password = "";                                       //Creating the password which is nothing
int JoystickButton = 15;                                    //button in pin 15
int JoystickX = 34;                                         //x in pin 34
int JoystickY = 35;                                         //y in pin 35


Drone drone(ssid, password);                                //Making an instance of our drone class with the ssid and password as param
Joystick joystick(JoystickButton, JoystickX, JoystickY);    //Making an instance of our joystick class with pinnumbers as our param (pins: btn, x, y)

void setup()                                                //Setup function
{
  Serial.begin(9600);                                       //begins the serial connection at 9600 bits per second. The default setting on esp32 is the same              
  drone.joystick = &joystick;                               //& means - use this location                            

  for (size_t i = 0; i < 5; i++)                            //We make sure that the program has started running with a counter in the console                      
  {
    Serial.println(i);
    delay(1000);
  }

  joystick.addButtonListener(&drone);                       //Running the addButtonListener from the joystick class on the drone                          
  drone.connect();                                          //Running the connect function from the drone class
  drone.setIp ("192.168.10.1");                             //Running the setIp function from drone class with the drones default ip as param

  
}

// vigtig detalje


void loop()                                                 //Loop function (runs aprox 60 times per second)
{
  joystick.loop();                                          //Running the loop function from our joystick class
  drone.loop();                                             //Running the loop function from our drone class
}   