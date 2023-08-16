﻿#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>

int getValidInteger(){
    int value;
    while (true) {
        if (std::cin >> value && value > 0) {

            break;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }
    return value;
}

char getValidInput() {
    char value;
    while (true) {
        
        if (std::cin >> value && (value =='y' || value == 'n')) {
            break;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }
    return value;
}


double getValidAnswer() {
    double value;
    while (true) {

        if (std::cin >> value) {
            break;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }
    return value;
}
int main() {
    int j = 0;
    const int arraySize = 50;
    int numbers[arraySize];
    int correctCount = 0;
    double round_result;
    std::vector<int> incor_numbers;
    std::vector<double> cor_answer;
    std::vector<double> corr_result;
    std::vector<double> runTimes;
    double maxRuntime;
    double averageRuntime;

    std::cout << "Enter the maximum value for random numbers: ";
    int maxValue = getValidInteger();

    std::cout << "Enter the number of questions: ";
    int num_q = getValidInteger();

    std::cout << " Add '*'  und  '/'? (y/n): ";
    char op_idx = getValidInput();

    std::cout << "one correct answer get (3) scores, one incorrect answer get (-2)) " << std::endl;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < arraySize; ++i) {
        int randomNumber = std::rand() % maxValue;
        int absoluteValue = abs(randomNumber);
        numbers[i] = absoluteValue;
    }


    for (int i = 0; i < num_q; ++i) {
        int index1 = std::rand() % arraySize;
        int index2 = std::rand() % arraySize;
        int operand1 = numbers[index1];
        int operand2 = numbers[index2];

        int operatorIndex;
        if (op_idx == 'y' || op_idx == 'Y') {
            operatorIndex = std::rand() % 4;
        }
        else {
            operatorIndex = std::rand() % 2;
        }

        char operation;
        double result;

        switch (operatorIndex) {
        case 0:
            operation = '+';
            result = operand1 + operand2;
            break;
        case 1:
            operation = '-';
            result = operand1 - operand2;
            break;
        case 2:
            if (op_idx == 'y' || op_idx == 'Y') {
                operation = '*';
                result = operand1 * operand2;
                break;
            }
            else {
                continue;
            }
        case 3:
            if (op_idx == 'y' || op_idx == 'Y') {
                operation = '/';
                if (operand2 != 0) {
                    result = static_cast<double>(operand1) / operand2;
                    std::cout << std::fixed << std::setprecision(1);
                }
                else {
                    std::cout << "Division by zero is not allowed." << std::endl;
                    continue;
                }
                break;
            }
            else {
                continue;
            }
        }

        std::cout << "(" << (i + 1) << ")" << " " << operand1 << " " << operation << " " << operand2 << " = ";
        auto startTime = std::chrono::system_clock::now();

        double userAnswer = getValidAnswer();
        auto endTime = std::chrono::system_clock::now();
        std::chrono::duration<double> duration = endTime - startTime;
        double runtime = duration.count();
        runTimes.push_back(runtime);

        double tolerance = std::abs(result - userAnswer);
        if (tolerance < 0.05) {
            std::cout << "Correct!" << std::endl;
            correctCount++;
        }
        else {
            std::cout << "Incorrect!" << std::endl;
            incor_numbers.push_back(i + 1);
            cor_answer.push_back(result);

        }
        maxRuntime = *std::max_element(runTimes.begin(), runTimes.end());
        averageRuntime = 0.0;
        if (!runTimes.empty()) {
            double sum = std::accumulate(runTimes.begin(), runTimes.end(), 0.0);
            averageRuntime = sum / runTimes.size();
        }
    }
    std::cout << "Max runtime: " << maxRuntime << " seconds" << std::endl;
    std::cout << "Average runtime: " << averageRuntime << " seconds" << std::endl;
    std::cout << "Total correct answers: " << correctCount << std::endl;
    std::cout << "Total incorrect answers: " << (num_q - correctCount) << std::endl;
    std::cout << "score you got: " << (correctCount * 3 - (num_q - correctCount) * 2) << std::endl;

    for (int i = 0; i < (num_q - correctCount); ++i) {
        std::cout << "incorrect question number:" << incor_numbers[i] << "   ";
        std::cout << "correct answars:" << cor_answer[i] << std::endl;
    }
    std::cout << std::endl;

    return 0;
} 

