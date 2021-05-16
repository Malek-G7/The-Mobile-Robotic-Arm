#define mvRange 3300 // range of ESP32 analog pin
#define adcRange 4096// ESP32 12 bit adc 2^12=4096 
#define mv_per_Cel 10 // LM35 outputs 10mV/C

float FunctionCel (int  tempReadC)
{
    float  mV, cel;
    mV = ((float)tempReadC / adcRange) * mvRange ;
    cel = mV / mv_per_Cel  ; // 10mV per cel
    return cel;
}
