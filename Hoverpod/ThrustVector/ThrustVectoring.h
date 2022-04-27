#ifndef THRUSTVECTORING_H_INCLUDED
#define THRUSTVECTORING_H_INCLUDED

class ThrustVectoring{

    public:
        //ThrustVectoring Default methods
        ThrustVectoring();
        ThrustVectoring(double reading[]);

        //components array setter
        void setComponents(double x, double y, double z);

        //method to update vector components
        void newReading(double reading[3]);

        //method to return vector components
        double * getThrustComponents();
};


#endif