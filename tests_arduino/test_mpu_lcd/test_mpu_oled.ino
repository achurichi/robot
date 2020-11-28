#include <MPU9250.h>
#include "U8glib.h"

MPU9250 mpuSensor;

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_FAST); // Dev 0, Fast I2C / TWI
int X_pos = 0;

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;
    Serial.println("started");

    mpuSensor.init();
}

void loop()
{
    serializeJson(mpuSensor.read(), Serial);
    Serial.println();

    u8g.firstPage();
    do
    {
        draw();
    } while (u8g.nextPage());

    if (X_pos > -250) // horizontal scroll
        X_pos--;
    else
        X_pos = 0;
}

void draw(void)
{

    u8g.drawStr(X_pos, 15, " We are testing this I2C Display"); // horizontal scroll
    u8g.drawLine(0, 18, 127, 18);                               // space line

    u8g.setFont(u8g_font_osb18); // font change
    u8g.drawStr(12, 44, "SH1106");

    u8g.setFont(u8g_font_5x7);
    // u8g.setFont(u8g_font_9x15);
    u8g.drawStr(0, 62, "Testing OLED Screen");
}
