/**
 * @file neuralNetwork.java
 * @brief A simple implementation of a basic feed forward neural network in Java
 */

import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

/**
 * @brief Utility class providing helper methods
 */
class Utils {
    /**
     * @brief Prints a string to console with delay between characters
     * @param str The string to print
     * @param time Delay in milliseconds between characters
     */
    public static void consoleLog(String str, int time) {
        for (char c : str.toCharArray()) {
            System.out.print(c);
            try {
                Thread.sleep(time);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println();
    }
}

/**
 * @brief Represents a single neuron in the neural network
 * 
 * Each neuron has weights for each input connection and a bias term.
 * It uses the sigmoid activation function.
 */
class Neuron {
    /** Weights for each input connection */
    private List<Double> weights;
    /** Bias term */
    private double bias;

    /**
     * @brief Constructs a neuron with random weights and bias
     * @param numInputs Number of input connections to this neuron
     */
    public Neuron(int numInputs) {
        weights = new ArrayList<>(numInputs);
        Random rand = new Random();
        for (int i = 0; i < numInputs; i++) {
            weights.add(rand.nextGaussian());
        }
        bias = rand.nextGaussian();
    }

    /**
     * @brief Computes the neuron's output for given inputs
     * @param inputs List of input values
     * @return Output of the neuron after applying the activation function
     */
    public double activate(List<Double> inputs) {
        if (inputs.size() != weights.size()) {
            throw new IllegalArgumentException("Number of inputs must match number of weights");
        }
        
        double sum = bias;
        for (int i = 0; i < weights.size(); i++) {
            sum += weights.get(i) * inputs.get(i);
        }
        return sigmoid(sum);
    }

    /**
     * @brief Sigmoid activation function
     * @param x Input value
     * @return Sigmoid of x: 1/(1+e^(-x))
     */
    private double sigmoid(double x) {
        return 1.0 / (1.0 + Math.exp(-x));
    }

    /**
     * @brief Get the weights of this neuron
     * @return List of weights
     */
    public List<Double> getWeights() {
        return weights;
    }

    /**
     * @brief Get the bias of this neuron
     * @return The bias value
     */
    public double getBias() {
        return bias;
    }
}

/**
 * @brief Represents a layer of neurons in the neural network
 */
class Layer {
    /** List of neurons in this layer */
    private List<Neuron> neurons;

    /**
     * @brief Constructs a layer with specified number of neurons
     * @param numNeurons Number of neurons in this layer
     * @param numInputsPerNeuron Number of inputs to each neuron
     */
    public Layer(int numNeurons, int numInputsPerNeuron) {
        neurons = new ArrayList<>(numNeurons);
        for (int i = 0; i < numNeurons; i++) {
            neurons.add(new Neuron(numInputsPerNeuron));
        }
    }

    /**
     * @brief Computes the outputs of all neurons in this layer
     * @param inputs List of input values to the layer
     * @return List of outputs from all neurons in the layer
     */
    public List<Double> activateLayer(List<Double> inputs) {
        List<Double> outputs = new ArrayList<>();
        for (Neuron neuron : neurons) {
            outputs.add(neuron.activate(inputs));
        }
        return outputs;
    }

    /**
     * @brief Get all neurons in this layer
     * @return List of neurons
     */
    public List<Neuron> getNeurons() {
        return neurons;
    }
}

/**
 * @brief Neural network implementation
 */
class NeuralNetworkImpl {
    /** List of layers in the network */
    private List<Layer> layers;

    /**
     * @brief Constructs a default neural network with 3 layers (3-3-3)
     */
    public NeuralNetworkImpl() {
        this(Arrays.asList(3, 3, 3));
    }

    /**
     * @brief Constructs a neural network with custom layer sizes
     * @param layerSizes List containing the number of neurons in each layer
     */
    public NeuralNetworkImpl(List<Integer> layerSizes) {
        if (layerSizes.size() < 2) {
            throw new IllegalArgumentException("Neural network must have at least 2 layers");
        }
        
        layers = new ArrayList<>();
        
        // Handle first layer specially
        int firstInputSize = layerSizes.get(0); // For first layer, inputs = neurons for simplicity
        layers.add(new Layer(layerSizes.get(0), firstInputSize));
        
        // For remaining layers, inputs come from previous layer
        for (int i = 1; i < layerSizes.size(); i++) {
            layers.add(new Layer(layerSizes.get(i), layerSizes.get(i-1)));
        }
    }

    /**
     * @brief Performs forward propagation through the network
     * @param inputs List of input values to the network
     * @return List of lists containing outputs at each layer, including the input
     */
    public List<List<Double>> forward(List<Double> inputs) {
        if (inputs.size() != layers.get(0).getNeurons().get(0).getWeights().size()) {
            throw new IllegalArgumentException("Input size must match first layer's input size");
        }
        
        List<List<Double>> allOutputs = new ArrayList<>();
        allOutputs.add(new ArrayList<>(inputs)); // Store the original input
        
        List<Double> currentOutputs = inputs;
        
        for (Layer layer : layers) {
            currentOutputs = layer.activateLayer(currentOutputs);
            allOutputs.add(new ArrayList<>(currentOutputs)); // Make a copy
        }
        return allOutputs;
    }

    /**
     * @brief Saves the network outputs to a JSON file
     * @param filename Name of the file to save to
     * @param layerOutputs List of lists containing outputs at each layer
     */
    public void saveAsJson(String filename, List<List<Double>> layerOutputs) {
        try (FileWriter file = new FileWriter(filename)) {
            file.write("{\n  \"initial_input\": " + layerOutputs.get(0).toString() + ",\n");
            
            for (int i = 0; i < layers.size(); i++) {
                file.write("  \"layer_" + (i + 1) + "_input\": " + layerOutputs.get(i).toString() + ",\n");
                file.write("  \"layer_" + (i + 1) + "_output\": " + layerOutputs.get(i + 1).toString() + ",\n");
            }
            
            file.write("  \"final_output\": " + layerOutputs.get(layerOutputs.size() - 1).toString() + "\n}");
        } catch (IOException e) {
            System.out.println("Unable to open file for writing: " + e.getMessage());
        }
    }
}

/**
 * @brief Test class for neural network functionality
 */
class NeuralNetworkTest {
    /**
     * @brief Tests forward propagation with default network
     * @param dataSet Input data for testing
     */
    public static void testForwardPropagation(List<Double> dataSet) {
        NeuralNetworkImpl nn = new NeuralNetworkImpl();
        List<List<Double>> outputs = nn.forward(dataSet);
        Utils.consoleLog("Output from forward propagation: ", 33);
        System.out.println(outputs.get(outputs.size() - 1));
        nn.saveAsJson("neuralNetwork.json", outputs);
    }

    /**
     * @brief Tests forward propagation with custom network
     * @param inputNeurons Number of neurons in input layer
     * @param hiddenNeurons Number of neurons in hidden layer
     * @param outputNeurons Number of neurons in output layer
     * @param dataSet Input data for testing
     */
    public static void testCustomNetwork(int inputNeurons, int hiddenNeurons, int outputNeurons, List<Double> dataSet) {
        if (dataSet.size() != inputNeurons) {
            throw new IllegalArgumentException("Input data size must match number of input neurons");
        }
        
        NeuralNetworkImpl nnCustom = new NeuralNetworkImpl(Arrays.asList(inputNeurons, hiddenNeurons, outputNeurons));
        List<List<Double>> outputs = nnCustom.forward(dataSet);
        Utils.consoleLog("Output from custom network forward propagation: ", 33);
        System.out.println(outputs.get(outputs.size() - 1));
        nnCustom.saveAsJson("neuralNetwork.json", outputs);
    }
}

/**
 * @brief Main public class that must match the filename exactly (neuralNetwork.java)
 */
public class neuralNetwork {
    /**
     * @brief Entry point of the program
     * @param args Command line arguments (not used)
     */
    public static void main(String[] args) {
        Utils.consoleLog("Starting Neural Network...", 33);
        NeuralNetworkTest.testCustomNetwork(4, 3, 2, Arrays.asList(0.1, 0.4, 0.2, 0.3));
    }
}