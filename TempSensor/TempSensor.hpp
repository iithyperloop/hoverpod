
// This code is for the TMP36 temperature sensor for arduino

class TempSensor 
{
    float temp;
public:
    TempSensor(float initial_temp);
    float get_temp();
    void set_temp(float new_temp);
};
