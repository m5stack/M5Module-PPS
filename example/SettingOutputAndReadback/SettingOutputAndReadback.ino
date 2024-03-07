#include <M5Unified.h>
#include <M5GFX.h>
#include "M5ModulePPS.h"

M5GFX display;
M5Canvas canvas(&display);
M5ModulePPS pps;

#define OUTPUT_VOLTAGE 5.0f
#define OUTPUT_CURRENT 5.0f

void setup() {
    M5.begin();
    display.begin();
    display.setEpdMode(epd_mode_t::epd_fastest);
    canvas.setColorDepth(8);
    canvas.setFont(&fonts::efontCN_12);
    canvas.createSprite(display.width(), display.height());
    canvas.setTextSize(2);

    while (!pps.begin(&Wire, M5.In_I2C.getSDA(), M5.In_I2C.getSCL(),
                      MODULE_POWER_ADDR, 400000U)) {
        Serial.println("module pps connect error");
        canvas.clear(BLACK);
        canvas.setTextColor(RED);
        canvas.drawCenterString("No i2c device", display.width() / 2,
                                display.height() / 2);
        canvas.pushSprite(0, 0);
        delay(100);
    }

    pps.setOutputVoltage(OUTPUT_VOLTAGE);
    pps.setOutputCurrent(OUTPUT_CURRENT);
    pps.setPowerEnable(true);
}

void loop() {
    float voltage_readback = pps.getReadbackVoltage();
    float current_readback = pps.getReadbackCurrent();
    float vin              = pps.getVIN();
    int mode               = pps.getMode();

    canvas.fillSprite(BLACK);
    canvas.setFont(&Font2);
    canvas.setTextColor(WHITE);
    canvas.drawCenterString("Module PPS", display.width() / 2, 0);

    canvas.setCursor(10, 50);
    canvas.setTextColor(WHITE);
    canvas.setTextSize(2);
    canvas.printf("VIN: ");
    canvas.setTextColor(GREEN);
    canvas.setTextSize(3);
    canvas.printf("%.2fV", vin);

    canvas.setCursor(10, 100);
    canvas.setTextColor(WHITE);
    canvas.setTextSize(2);
    canvas.printf("Mode: ");
    canvas.setTextColor(GREEN);
    canvas.setTextSize(3);
    if (mode <= 1)
        canvas.printf("CV");
    else
        canvas.printf("CC");

    canvas.setTextColor(WHITE);
    canvas.setCursor(10, 150);
    canvas.setTextSize(2);
    canvas.printf("Voltage: ");
    canvas.setTextColor(GREEN);
    canvas.setTextSize(3);
    canvas.printf("%.2fV", voltage_readback);

    canvas.setCursor(10, 200);
    canvas.setTextColor(WHITE);
    canvas.setTextSize(2);
    canvas.printf("Current: ");
    canvas.setTextColor(GREEN);
    canvas.setTextSize(3);
    canvas.printf("%.2fA", current_readback);

    canvas.pushSprite(0, 0);
}