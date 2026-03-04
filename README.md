# RC Circuit Simulator (C++)
A simple C++ project that simulates the charging and discharging behavior of an RC circuit using the exponential capacitor equations. 
This project was completed for practice purposes. 

---
## Features
- Simulate **RC Charging**
- Simulate **RC Discharging**
- Calculates **cutoff frequency**
- Adjustable **simulation time and timestep**
- Custom **decimal precision**
- **formatted table output**
- Optional **CSV export**

## Equations in the code

### RC Charging

Vc(t) = V (1 − e^(-t/RC))

### RC Discharging

Vc(t) = V e^(-t/RC)

### Cutoff Frequency

fc = 1 / (2πRC)

---
