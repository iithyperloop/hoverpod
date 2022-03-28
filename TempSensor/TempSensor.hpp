
// This code is for the TMP36 temperature sensor for arduino

enum class TempSensorStatus
{
    STATUS_OK,
    STATUS_TOO_HOT
};

class TempSensor 
{
    float temp;
public:
    TempSensor(float initial_temp);
    float get_temp();
    void set_temp(float new_temp);
};
