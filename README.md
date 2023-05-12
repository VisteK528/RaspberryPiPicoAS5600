# AS5600 Library for Raspberry Pi Pico

## General info
AS5600 i2C address - ```0x36```

## Register map of AS5600
- Raw angle(7:0) - ```0x0D```
- Raw angle(11:8) - ```0x0C```

## Available functions
```c
float getRawAngle(i2c_inst_t *i2c, const uint8_t ADDRESS);
```

