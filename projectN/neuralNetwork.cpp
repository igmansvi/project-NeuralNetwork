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
#include "neural.hpp"
/* Main function */
int main() {
    consoleLog("Starting Neural Network...");
    // neuralNetworkTest::testForwardPropagation({0.1, 0.3, 0.2});
    neuralNetworkTest::testCustomNetwork(4, 3, 2, {0.1, 0.4, 0.2, 0.3});
    return 0;
}