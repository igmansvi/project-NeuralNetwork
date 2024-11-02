/**
 * @file neuralNetwork.cpp
 * @author Mansvi Kumar
 * @details Basic Neural Network Implementation
 * @brief single block Neuron
 * --! layers -> Input, Hidden, Output
 * --! network management -> collection of layers
 */
/* lib */
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <json.hpp>
using namespace std;
using json = nlohmann::json;
/* Utility functions */
void consoleLog(const string str, int time = 33) {
    for(char c: str) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(time));
    } cout << endl;
}
/* single units of neuralNetwork -neuron- */
class neuron {

};
/* layer units to define network architecture */
class layer {
    
};
/* network representation and management */
class neuralNetwork {

};
/* Main function */
int main() {
    consoleLog("Starting Neural Network...");
    return 0;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @note
 * to compile code
 * -> type { runneuralnetwork } on terminal
 * -> as function defined in powershell profile
 * [
 *      #Function to run and compile Neural Network
        function runneuralnetwork {
            # Change directory to the project folder
            cd "C:\Users\Victus\Desktop\projectN"
            
            # Compile the neuralNetwork.cpp file with necessary include and library paths
            g++ neuralNetwork.cpp -o neuralNetwork -IC:/Users/Victus/Desktop/projectN/include
            
            # Check if the compilation was successful and run the executable
            if ($?) {
                .\neuralNetwork  # Run the compiled program
            } else {
                Write-Host "Compilation failed."  # Inform user if compilation failed
            }
        }
 * ]
 * or
 * -> type {  cd "c:\Users\Victus\Desktop\projectN\" ; if ($?) { g++ neuralNetwork.cpp -o neuralNetwork -IC:/Users/Victus/Desktop/projectN/include } ; if ($?) { .\neuralNetwork } }
 */
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------