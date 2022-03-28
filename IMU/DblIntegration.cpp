#include <iostream>
#include <cmath>

float fun(const float x, const float y) {
    return pow(pow(x, 4) + pow(y, 5), 0.5);
}

// Function to find the double integral value
float doubleIntegral(const float step_x, const float step_y, const float lower_x, const float upper_x, const float lower_y, const float upper_y) {
    const float n1 = (upper_x - lower_x) / step_x + 1.f;
    const float n2 = (upper_y - lower_y) / step_y + 1.f;
    float arr[50][50], arr_2[50];
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            arr[i][j] = fun(lower_x + i * step_x, lower_y + j * step_y);
        }
    }
    for (int i = 0; i < n1; ++i) {
        arr_2[i] = 0;
        for (int j = 0; j < n2; ++j) {
            if (j == 0 || j == n2 - 1)
                arr_2[i] += arr[i][j];
            else if (j % 2 == 0)
                arr_2[i] += 2 * arr[i][j];
            else
                arr_2[i] += 4 * arr[i][j];
        }
        arr_2[i] *= step_y / 3;
    }
    float result = 0.f;
    for (int i = 0; i < n1; ++i) {
        if (i == 0 || i == n1 - 1)
            result += arr_2[i];
        else if (i % 2 == 0)
            result += 2 * arr_2[i];
        else
            result += 4 * arr_2[i];
    }
    result *= step_x / 3;
    return result;
}

int main() {
    float step_x = 1.2; //steps for x
    float step_y = 0.54; //steps for y
    float lower_x = 1.3; //lower limit of x
    float upper_x = 2.1; //upper limit of x
    float lower_y = 1.0; //lower limit of y
    float upper_y = 2.1; //upper limit of y
    std::cout << "double integration is : " << (step_x, step_y, lower_x, upper_x, lower_y, upper_y);
    return 0;
}
