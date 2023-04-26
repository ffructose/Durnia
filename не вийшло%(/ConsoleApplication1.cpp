#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>

using namespace std;

int EPOCH = 100;

double sigmoid_output(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivative(double x)
{
    return x * (1 - x);
}

double func(double x1, double x2, double x3)
{
    return log(fabs(cos(x1))) + tan(x2) + 1 / tan(x3);
}


class Neuron
{
public:

    double *inputs = new double[4];
    double *weights = new double[4];

    double error;

    double get_output()
    {
        return sigmoid_output(weights[0] * inputs[0] + weights[1] * inputs[1] + weights[2] * inputs[2]);
    }

    void setInputs3(double a, double b, double c) 
    {
        this->inputs[0] = a;
        this->inputs[1] = b;
        this->inputs[2] = c;
    }

    void setInputs4(double a, double b, double c, double d)
    {
        this->inputs[0] = a;
        this->inputs[1] = b;
        this->inputs[2] = c;
        this->inputs[3] = d;
    }

    void randomizeWeights()
    {
        srand(time(NULL));
        weights[0] = (double)rand() / RAND_MAX;
        weights[1] = (double)rand() / RAND_MAX;
        weights[2] = (double)rand() / RAND_MAX;
    }

    void adjustWeights()
    {
        weights[0] += error * inputs[0];
        weights[1] += error * inputs[1];
        weights[2] += error * inputs[2];
    }

};


int main()
{
    double max = 0;
    double min = 0;
    double serZnach = 0;


    vector<vector<double>> trainInputs
    {
        {5.0, 6.0, 9.0},
        {5.0, 7.0, 7.0},
        {5.0, 7.0, 8.0},
        {5.0, 7.0, 9.0},
        {5.0, 8.0, 7.0},
        {5.0, 8.0, 8.0},
        {5.0, 8.0, 9.0},

        {6.0, 6.0, 7.0},
        {6.0, 6.0, 8.0},
        {6.0, 6.0, 9.0},
        {6.0, 7.0, 7.0},
        {6.0, 7.0, 8.0},
        {6.0, 7.0, 9.0},
        {6.0, 8.0, 7.0},
        {6.0, 8.0, 8.0},
        {6.0, 8.0, 9.0},
    };

    vector<vector<double>> controlInputs
    {
        {4.0, 6.0, 7.0},
        {4.0, 6.0, 8.0},
        {5.0, 6.0, 7.0},
        {5.0, 6.0, 8.0},
    };

    double *trainResults = new double[16];

    int iter = 0;
    for (auto e : trainInputs) {

        trainResults[iter] = func(e[0], e[1], e[2]);
        iter++;
    }

    double *controlResults = new double[4];

    iter = 0;
    for (const auto& e : controlInputs) {

        controlResults[iter] = func(e[0], e[1], e[2]);
        iter++;
    }

    for (int j = 0; j < 3; j++)
    {
        max = trainInputs[0][0];
        min = trainInputs[0][0];

        for (int i = 0; i < 16; i++)
        {
            if (max < trainInputs[i][j])
                max = trainInputs[i][j];
            if (min > trainInputs[i][j])
                min = trainInputs[i][j];
        }

        for (int i = 0; i < 4; i++)
        {
            if (max < controlInputs[i][j])
                max = controlInputs[i][j];
            if (min > controlInputs[i][j])
                min = controlInputs[i][j];
        }

        for (int i = 0; i < 16; i++)
        {
            trainInputs[i][j] = (max - trainInputs[i][j]) / (max - min);
        }

        for (int i = 0; i < 4; i++)
        {
            controlInputs[i][j] = (max - controlInputs[i][j]) / (max - min);
        }
    }



    for (int k = 0; k < 16; k++)
    {
        serZnach += trainResults[k];
    }

    for (int k = 0; k < 4; k++)
    {
        serZnach += controlResults[k];
    }

    serZnach = serZnach / 20.0;

    double *traind2 = new double[16];

    for (int i = 0; i < 16; i++)
    {
        if (trainResults[i] > serZnach)
            traind2[i] = 1;
        else
            traind2[i] = 0;
    }

    double *controld2 = new double[4];

    for (int i = 0; i < 4; i++)
    {
        if (controlResults[i] > serZnach)
            controld2[i] = 1;
        else
            controld2[i] = 0;
    }

    max = trainResults[0];
    min = trainResults[0];

    for (int i = 0; i < 16; i++)
    {
        if (max < trainResults[i])
            max = trainResults[i];
        if (min > trainResults[i])
            min = trainResults[i];
    }

    for (int i = 0; i < 4; i++)
    {
        if (max < controlResults[i])
            max = controlResults[i];
        if (min > controlResults[i])
            min = controlResults[i];
    }

    for (int i = 0; i < 16; i++)
    {
        trainResults[i] = (max - trainResults[i]) / (max - min);
    }

    for (int i = 0; i < 4; i++)
    {
        controlResults[i] = (max - controlResults[i]) / (max - min);
    }

    srand(time(NULL));

    Neuron hiddenNeuron1;
    Neuron hiddenNeuron2;
    Neuron hiddenNeuron3;
    Neuron hiddenNeuron4;
    Neuron outputNeuron1;
    Neuron outputNeuron2;
    outputNeuron1.weights[3] = (double)rand() / RAND_MAX;
    outputNeuron2.weights[3] = (double)rand() / RAND_MAX;

    hiddenNeuron1.randomizeWeights();
    hiddenNeuron2.randomizeWeights();
    hiddenNeuron3.randomizeWeights();
    hiddenNeuron4.randomizeWeights();
    outputNeuron1.randomizeWeights();
    outputNeuron2.randomizeWeights();

    int w = 13;

    cout<<"\n                            Control testing in the beggining\n\n";
    cout<<"    x1           x2           x3          d1       expected d1       d2      expected d2\n";
    for (int i = 0; i < 4; i++)
    {
        hiddenNeuron1.setInputs3(controlInputs[i][0],  controlInputs[i][1],  controlInputs[i][2]);
        hiddenNeuron2.setInputs3( controlInputs[i][0],  controlInputs[i][1],  controlInputs[i][2]);
        hiddenNeuron3.setInputs3( controlInputs[i][0],  controlInputs[i][1],  controlInputs[i][2]);
        hiddenNeuron4.setInputs3( controlInputs[i][0],  controlInputs[i][1],  controlInputs[i][2]);

        outputNeuron1.setInputs4(hiddenNeuron1.get_output(), hiddenNeuron2.get_output(), hiddenNeuron3.get_output(), hiddenNeuron4.get_output());
        outputNeuron2.setInputs4(hiddenNeuron1.get_output(), hiddenNeuron2.get_output(), hiddenNeuron3.get_output(), hiddenNeuron4.get_output());

        cout << fixed << setprecision(7) << controlInputs[i][0] << setw(w) << controlInputs[i][1] << setw(w) << controlInputs[i][2] << setw(w) << outputNeuron1.get_output() << setw(w) << controlResults[i] << setw(w) << outputNeuron2.get_output() << setw(w) << controld2[i] << endl;
    }

    int epoch = 0;
    while (epoch < EPOCH)
    {
        epoch++;
        for (int i = 0; i < 16; i++)
        {
            hiddenNeuron1.setInputs3(trainInputs[i][0], trainInputs[i][1], trainInputs[i][2]);
            hiddenNeuron2.setInputs3(trainInputs[i][0], trainInputs[i][1], trainInputs[i][2]);
            hiddenNeuron3.setInputs3(trainInputs[i][0], trainInputs[i][1], trainInputs[i][2]);
            hiddenNeuron4.setInputs3(trainInputs[i][0], trainInputs[i][1], trainInputs[i][2]);

            outputNeuron1.setInputs4(hiddenNeuron1.get_output(), hiddenNeuron2.get_output(), hiddenNeuron3.get_output(), hiddenNeuron4.get_output());
            outputNeuron2.setInputs4(hiddenNeuron1.get_output(), hiddenNeuron2.get_output(), hiddenNeuron3.get_output(), hiddenNeuron4.get_output());

            cout << "\n" << trainInputs[i][0] << "  " << trainInputs[i][1] << "  " << trainInputs[i][2] << "  " << outputNeuron1.get_output() << "  " << trainResults[i] << "  " << outputNeuron2.get_output() << "  " << traind2[i] << "\n";

            outputNeuron1.error = sigmoid_derivative(outputNeuron1.get_output()) * (trainResults[i] - outputNeuron1.get_output());

            outputNeuron2.error = sigmoid_derivative(outputNeuron2.get_output()) * (traind2[i] - outputNeuron2.get_output());

            hiddenNeuron1.error = (outputNeuron1.error * outputNeuron1.weights[0] + outputNeuron2.error * outputNeuron2.weights[0]) * sigmoid_derivative(hiddenNeuron1.get_output());
            hiddenNeuron2.error = (outputNeuron1.error * outputNeuron1.weights[1] + outputNeuron2.error * outputNeuron2.weights[1]) * sigmoid_derivative(hiddenNeuron2.get_output());
            hiddenNeuron3.error = (outputNeuron1.error * outputNeuron1.weights[2] + outputNeuron2.error * outputNeuron2.weights[2]) * sigmoid_derivative(hiddenNeuron3.get_output());
            hiddenNeuron4.error = (outputNeuron1.error * outputNeuron1.weights[3] + outputNeuron2.error * outputNeuron2.weights[3]) * sigmoid_derivative(hiddenNeuron4.get_output());

            outputNeuron1.adjustWeights();
            outputNeuron1.weights[3] = (double)rand() / RAND_MAX;
            outputNeuron2.adjustWeights();
            outputNeuron2.weights[3] = (double)rand() / RAND_MAX;
            hiddenNeuron1.adjustWeights();
            hiddenNeuron2.adjustWeights();
            hiddenNeuron3.adjustWeights();
            hiddenNeuron4.adjustWeights();
        }
    }

    cout << "\n\n                          Control testing after " << epoch << " epoch  \n\n";
    cout <<   "    x1           x2           x3          d1       expected d1       d2      expected d2" << endl;
    for (int i = 0; i < 4; i++)
    {
        hiddenNeuron1.setInputs3(trainInputs[i][0], trainInputs[i][1], trainInputs[i][2]);
        hiddenNeuron2.setInputs3(trainInputs[i][0], trainInputs[i][1], trainInputs[i][2]);
        hiddenNeuron3.setInputs3(trainInputs[i][0], trainInputs[i][1], trainInputs[i][2]);
        hiddenNeuron4.setInputs3(trainInputs[i][0], trainInputs[i][1], trainInputs[i][2]);

        outputNeuron1.setInputs4(hiddenNeuron1.get_output(), hiddenNeuron2.get_output(), hiddenNeuron3.get_output(), hiddenNeuron4.get_output());
        outputNeuron2.setInputs4(hiddenNeuron1.get_output(), hiddenNeuron2.get_output(), hiddenNeuron3.get_output(), hiddenNeuron4.get_output());

        cout << fixed  << setprecision(7) << controlInputs[i][0] << setw(w) << controlInputs[i][1] << setw(w) << controlInputs[i][2] << setw(w) << outputNeuron1.get_output() << setw(w) << controlResults[i] << setw(w) << outputNeuron2.get_output() << setw(w) << controld2[i] << endl;
    }

    return 0;
}