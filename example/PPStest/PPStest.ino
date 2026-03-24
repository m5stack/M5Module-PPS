// Minimal test app making calls to PPS module in tight loop, printing state to Serial
// Used to verify stability of the I2C interface to the module.
#include <M5Unified.h>
#include "M5ModulePPS.h"

M5ModulePPS pps;

#define OUTPUT_VOLTAGE 5.0f
#define OUTPUT_CURRENT 5.0f

void setup() 
{
    M5.begin();
    Serial.begin(1000000);

    Serial.printf("Attempting to connect to PPS\n");
    
    while (!pps.begin(&Wire, M5.In_I2C.getSDA(), M5.In_I2C.getSCL(), MODULE_POWER_ADDR, 400000U)) 
    {
        Serial.println("Connect error");
        delay(100);
    }

    Serial.printf("PPS connected\n");

    pps.setOutputVoltage(OUTPUT_VOLTAGE);
    pps.setOutputCurrent(OUTPUT_CURRENT);
    pps.setPowerEnable(true);
}

int cycle=0;
void loop() 
{

    float voltage_readback = pps.getReadbackVoltage();
    float current_readback = pps.getReadbackCurrent();
    float vin              = pps.getVIN();
    const char * modestr   = ((pps.getMode() <= 1) ? "CV" : "CC");

    Serial.printf("%d: Vin=%0.3fV Vout=%0.3fV Iout=%0.3fA Mode=%s\n",cycle++,vin,voltage_readback,current_readback,modestr);
}