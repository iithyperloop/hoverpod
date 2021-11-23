#ifndef MOTOR_H
#define MOTOR_H


class Motor
{   private:
        double speed;
        
    public:
        Motor();
        virtual ~Motor();

        double getSpeed() { 
            return speed; 
            }
        
        void setSpeed(double val) {
            if (val > 0) {
                speed = val;
            }
            else {
                speed = 0;
            }
        }

    
};

#endif // MOTOR_H
