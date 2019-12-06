#ifndef  _SENSOR_MEASURE_H
#define  _SENSOR_MEASURE_H


typedef struct {
    int temperature_value;
    int humidity_value;
    int noise_value;
}sensor_value_t;


void Demo_SensorsMeasure(void);


#endif
