#ifndef _M5ModulePPS_H_
#define _M5ModulePPS_H_

#include <Arduino.h>
#include <Wire.h>

// I2C
#define MODULE_POWER_ADDR   0x35
#define MODULE_ID_L         0x00
#define MODULE_ID_H         0x01
#define MODULE_HW_VERSION   0x02
#define MODULE_SW_VERSION   0x03
#define MODULE_ENABLE       0x04
#define PSU_RUNNING_MODE    0x05
#define PSU_DATA_FLAG       0x07
#define PSU_VOUT_READBACK_1 0x08
#define PSU_IOUT_READBACK_1 0x0C
#define PSU_TEMP_READBACK_1 0x10
#define PSU_VIN_READBACK_1  0x14
#define PSU_VOUT_SET_1      0x18
#define PSU_IOUT_SET_1      0x1C
#define PSU_PSU_ID_W0       0x52
#define PSU_PSU_ID_W1       0x56
#define PSU_PSU_ID_W2       0x5A
#define I2C_ADDRESS_REG     0x5F

class M5ModulePPS {
   private:
    uint8_t _addr;
    TwoWire *_wire;
    uint8_t _sda;
    uint8_t _scl;
    uint32_t _speed;
    bool writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);
    bool readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);
    void float_to_bytes(float s, uint8_t *d);
    float bytes_to_float(uint8_t *s);

   public:
    bool begin(TwoWire *wire = &Wire, uint8_t sda = 21, uint8_t scl = 22,
               uint8_t addr = MODULE_POWER_ADDR, uint32_t speed = 100000U);
    uint16_t getID(void);
    void setPowerEnable(bool en);
    uint8_t getPowerEnable(void);
    uint8_t getMode(void);
    float getVIN(void);
    float getTemperature(void);
    float getVoltageReadback(void);
    float getReadbackVoltage(void);
    void setOutputVoltage(float vol);
    float getOutputVoltage(void);
    float getReadbackCurrent(void);
    void setOutputCurrent(float cur);
    float getOutputCurrent(void);
    void getUID(uint32_t *uid0, uint32_t *uid1, uint32_t *uid2);
    uint8_t setI2CAddress(uint8_t addr);
    uint8_t getI2CAddress(void);
};

#endif
