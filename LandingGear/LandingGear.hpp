#pragma once

class LandingGear {
    bool is_engaged;
public:
    LandingGear();

    void engage();
    void disengange();
    [[nodiscard]] bool get_engaged() const;
};