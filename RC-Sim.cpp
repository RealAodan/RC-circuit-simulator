#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;

// ----- Prototypes -----
void Run_Charging();
void Run_Discharging();
double InputPositiveDouble(const string& prompt);
double Cut_Off_Frequency(double R, double C);
void Quick_Seperator();
void Template(double i, double volt, int dec);
void writeCSVRow(ofstream& file, double t, double vc);
void writeCSVHeader(ofstream& file, double R, double C, double fc);



int main(){
    bool a = true;
    while(a){

    // Display menu
    cout << "\n--- Main Menu ---\n";
    cout << "1. RC Charging \n";
    cout << "2. RC Discharging \n";
    cout << "3. Exit \n";

    int user;

    cout << "Please select an option: ";
    cin >> user;

    switch (user)
    {
    case 1:
        Quick_Seperator();
        Run_Charging();

        break;

    case 2:
        Quick_Seperator();
        Run_Discharging();

        break;
    
    case 3:
        return 0;
    
    default:
        cout << "\n{Select a valid option!}\n";
        break;
    }

}
}

// ----- Functions -----
double Cut_Off_Frequency(double R, double C){
    double PI = 3.14159265358979323846;
    double fc = 1.0 / (2 * PI * R * C);
    cout << endl << "Cutoff frequency: " << setprecision(5) << fixed << fc << defaultfloat << endl;
    return fc;
}

void Template(double i, double volt, int dec){
    cout << fixed << setprecision(dec)
     << setw(12) << right << i
     << setw(15) << right << volt << defaultfloat
     << endl;
}

void Run_Charging(){
    cout << "\n--- Charging ---\n";
    double R = InputPositiveDouble("Enter a Resistance (ohms): ");
    double C = InputPositiveDouble("Enter a Capacitance (farads): ");
    double V = InputPositiveDouble("Enter a Charging Voltage (volts): ");
    double t_end = InputPositiveDouble("Time length of the simulation (seconds): ");
    double t_dt = InputPositiveDouble("Enter a time step (seconds): ");
    
    int dec;
    cout << "Enter how many decimals you'd like: "; cin >> dec;
    // CSV export?
    char a;
    cout << "Would you like the data exported in a CSV file? (y/n): "; cin >> a;
    ofstream file;                 // declare file stream
    bool exportCSV = (a == 'y' || a == 'Y');

    if (exportCSV) {
        file.open("rc_charging.csv");
    }

    double fc = Cut_Off_Frequency(R, C);

    if (exportCSV) {
    writeCSVHeader(file, R, C, fc);
    }


    // Based on the following equation: Vc(t) = V(1-e^(-t/(RC)))
    // Header
    cout << endl << setw(12) << "Time (s)" << setw(17) << "Volt (V)" 
    << endl << "-----------------------------" << endl;

    for (double i = 0; i <= t_end + 1e-12; i += t_dt)
    {
        double V_equation = V * (1 - exp((-i)/(R * C)));
        Template(i, V_equation, dec);
        if (exportCSV) {
            writeCSVRow(file, i, V_equation);
        }

    }
    if (exportCSV) {
        file.close();
        cout << "\nSaved: rc_charging.csv\n";
    }
    
}

void Run_Discharging(){
    cout << "\n--- Discharging ---\n";
    double R = InputPositiveDouble("Enter a Resistance (ohms): ");
    double C = InputPositiveDouble("Enter a Capacitance (farads): ");
    double V = InputPositiveDouble("Enter a Initial Voltage (volts): ");
    double t_end = InputPositiveDouble("Time length of the simulation (seconds): ");
    double t_dt = InputPositiveDouble("Enter a time step (seconds): ");

    int dec;
    cout << "Enter how many decimals you'd like: "; cin >> dec;
    // CSV export?
    char a;
    cout << "Would you like the data exported in a CSV file? (y/n): "; cin >> a;
    ofstream file;                 // declare file stream
    bool exportCSV = (a == 'y' || a == 'Y');

    if (exportCSV) {
        file.open("rc_discharging.csv");
    }


    double fc = Cut_Off_Frequency(R, C);

    if (exportCSV) {
        writeCSVHeader(file, R, C, fc);
    }
    
    // Based on the following equation: Vc(t) = Ve^(-t/(RC)))
    // Header
    cout << endl << setw(12) << "Time (s)" << setw(17) << "Volt (V)" 
    << endl << "-----------------------------" << endl;

    for (double i = 0; i <= t_end + 1e-12; i += t_dt)
    {
        double V_equation = V * (exp((-i)/(R * C)));
        Template(i, V_equation, dec);
        if (exportCSV) {
            writeCSVRow(file, i, V_equation);
        }

    }
    if (exportCSV) {
        file.close();
        cout << "\nSaved: rc_discharging.csv\n";
    }
}

void Quick_Seperator(){
    cout << "\n/////////////////////////////////////////////////\n";
}

double InputPositiveDouble(const string& prompt){
    while (true){
    
        double x;
        cout << prompt;
        cin >> x;

        if (x > 0)
        {
            return x;
        }
        else if (x <= 0)
        {
            cout << "Please enter a positive number." << endl;
        }
}
}

void writeCSVHeader(ofstream& file, double R, double C, double fc){
    file << "R (Ohms)," << R << "\n";
    file << "C (Farads)," << C << "\n";
    file << "Cutoff Frequency (Hz)," << fc << "\n\n";
    file << "Time (s),Vc (V)\n";
}

void writeCSVRow(ofstream& file, double t, double vc){
    file << t << "," << vc << "\n";
}
    
    
