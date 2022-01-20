#pragma once

class LandingGear {
    bool is_engaged;
public:
    LandingGear();

    void engage();
    void disengange();
    bool get_engaged();
};