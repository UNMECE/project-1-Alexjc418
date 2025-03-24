#include <iostream>
#include <iomanip>
#include <cstdlib>

struct Capacitor{
    double *time;
    double *voltage;
    double *current;
    double C;
};

void simulateConstantCurrent(Capacitor &cap, double I, double dt, int steps){
    cap.voltage[0] = 0.0;
    for (int i = 1; i < steps; ++i) {
        cap.voltage[i] = cap.voltage[i - 1] + (I * dt / cap.C);
        if (i % 200 == 0)
            std::cout << "Time: " << cap.time[i] << " , Voltage: " << cap.voltage[i] << "\n";
    }
}

void simulateConstantVoltage(Capacitor &cap, double R, double V0, double dt, int steps){
    cap.current[0] = V0 / R;
    for (int i = 1; i < steps; ++i) {
        cap.current[i] = cap.current[i - 1] - (cap.current[i - 1] * dt / (R * cap.C));
        cap.voltage[i] = V0 - cap.current[i] * R;
        if (i % 200 == 0)
            std::cout << "Time: " << cap.time[i] << " , Current: " << cap.current[i] << " , Voltage: " << cap.voltage[i] << "\n";
    }
}

int main(){
    const double dt = 1e-10;
    const double finalTime = 5e-6;
    const int steps = static_cast<int>(finalTime / dt);
    const double R = 1e3;
    const double C = 100e-12;
    const double I = 1e-2;
    const double V0 = 10.0;

    Capacitor cap;
    cap.C = C;
    cap.time = new double[steps];
    cap.voltage = new double[steps];
    cap.current = new double[steps];

    for (int i = 0; i < steps; ++i)
        cap.time[i] = i * dt;

    std::cout << "\nCurrent Sim:\n";
    simulateConstantCurrent(cap, I, dt, steps);

    std::cout << "\nVoltage Sim:\n";
    simulateConstantVoltage(cap, R, V0, dt, steps);

    delete[] cap.time;
    delete[] cap.voltage;
    delete[] cap.current;

    return 0;
}
