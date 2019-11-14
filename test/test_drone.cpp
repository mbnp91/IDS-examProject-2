#include <Arduino.h>
#include <drone.h>
#include <unity.h>

Drone drone("ssid", "pass");

void setUp(void)
{
}

void test_buttonPressed(void)
{

//TEST_ASSERT_TRUE(drone.ButtonPressed());
//TEST_ASSERT_FALSE(drone.ButtonPressed());
delay(500);
//TEST_ASSERT_EQUAL(digitalRead(JoystickButton), LOW);


}

void setup(){

    UNITY_BEGIN();

    RUN_TEST(test_buttonPressed);

    UNITY_END();


}

void loop(){


}