/**
 * @file neuralNetwork.cpp
 * @author Mansvi Kumar
 * @details Basic Neural Network Implementation
 * @brief 
 * --! single block Neuron
 * --! layers -> Input, Hidden, Output
 * --! network management -> collection of layers
 * @note basic graph-based architecture implementation
 * --! data saved as json format
 */
/**
 * @todo documentation for functions and classes required
 * @todo add graph architecture using <map> and <list>
 * @todo implementing back propagation for training network
 * @todo optimize algorithms to facilitate training
 * @todo add more graph-based data-handling formats
 * @todo adding graph traversal algorithms and modulate design
 */
/* lib */
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <random>
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
    } 
    cout << endl;
}

/* single units of neuralNetwork -neuron- */
class neuron {
    vector<double> weights;
    double bias;
public:
    neuron(int numInputs) {
        weights.resize(numInputs);
        double min = 0.0, max = 1.0;
        random_device rad;
        default_random_engine generate(rad());
        normal_distribution<double> dis(min, max);
        for(auto &weight: weights) {
            weight = dis(generate);
        }
        bias = dis(generate);
    }
    
    double neuronActivate(const vector<double>& inputs) {
        double sum = bias;
        for(int i=0; i<weights.size(); i++) {
            sum += weights[i] * inputs[i];
        }
        return sigmoid(sum);
    }

    double sigmoid(double sum) {
        return (1.0 / (1.0 + exp(-sum)));
    }

    vector<double> getWeights() const {
        return weights;
    }
    
    double getBias() const {
        return bias;
    }
};

/* layer units to define network architecture */
class layer {
    vector<neuron> neurons;
public:
    layer(int numNeurons, int numInputsPerNeuron) {
        neurons.reserve(numNeurons);
        for(int i=0; i<numNeurons; i++) {
            neurons.emplace_back(numInputsPerNeuron);
        }
    }

    vector<double> layerActivate(const vector<double>& inputs) {
        vector<double> outputs;
        for(auto &neuron: neurons) {
            outputs.push_back(neuron.neuronActivate(inputs));
        }
        return outputs;
    }

    const vector<neuron>& getNeurons() const {
        return neurons;
    }
};

/* network representation and management */
class neuralNetwork {
    vector<layer> layers;
public:
    neuralNetwork(): neuralNetwork({3, 3, 3}) {};
    
    neuralNetwork(const vector<int>& layerSizes) {
        for(size_t i=0; i<layerSizes.size(); i++) {
            int numInputs = (i==0) ? 0 : layerSizes[i-1];
            layers.emplace_back(layerSizes[i], numInputs);
        }
    }

    vector<vector<double>> forward(const vector<double>& inputs) {
        vector<double> currentOutputs = inputs;
        vector<vector<double>> allOutputs;
        allOutputs.push_back(currentOutputs);

        for(auto &layer: layers) {
            currentOutputs = layer.layerActivate(currentOutputs);
            allOutputs.push_back(currentOutputs);
        }
        return allOutputs;
    }

    void saveAsJson(const string& filename, const vector<vector<double>>& layerOutputs) {
        json j;

        j["initial_input"] = layerOutputs[0];

        for (size_t i = 0; i < layers.size(); i++) {
            j["layer_" + to_string(i + 1) + "_input"] = layerOutputs[i];
            j["layer_" + to_string(i + 1) + "_output"] = layerOutputs[i + 1];
            
            json layerJson;
            for (const auto& neuron : layers[i].getNeurons()) {
                json neuronJson;
                neuronJson["weights"] = neuron.getWeights();
                neuronJson["bias"] = neuron.getBias();
                layerJson.push_back(neuronJson);
            }

            j["layer_" + to_string(i + 1) + "_neurons"] = layerJson;
        }

        j["final_output"] = layerOutputs.back();

        ofstream file(filename);
        if (file.is_open()) {
            file << j.dump(4);
            file.close();
        } else {
            cout << "Unable to open file for writing." << endl;
        }
    }
};

/* testing class */
class neuralNetworkTest {
public:
    static void testForwardPropagation(vector<double> dataSet) {
        neuralNetwork nn;
        vector<double> input = dataSet;
        vector<vector<double>> outputs = nn.forward(input);
        consoleLog("Output from forward propagation: ");
        for (double val : outputs.back()) {
            cout << val << " ";
        }
        cout << endl;
        nn.saveAsJson("neuralNetwork.json", outputs); 
    }

    static void testCustomNetwork(int inputNeurons, int hiddenNeurons, int outputNeurons, vector<double> dataSet) {
        neuralNetwork nnCustom({inputNeurons, hiddenNeurons, outputNeurons});
        vector<double> input = dataSet;
        vector<vector<double>> outputs = nnCustom.forward(input);
        consoleLog("Output from custom network forward propagation: ");
        for (double val : outputs.back()) {
            cout << val << " ";
        }
        cout << endl;
        nnCustom.saveAsJson("neuralNetwork.json", outputs);
    }
};

/* Main function */
int main() {
    consoleLog("Starting Neural Network...");
    // neuralNetworkTest::testForwardPropagation({0.1, 0.3, 0.2});
    neuralNetworkTest::testCustomNetwork(4, 3, 2, {0.1, 0.4, 0.2, 0.3});
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
