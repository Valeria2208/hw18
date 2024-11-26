//
//  main.cpp
//  hw18
//
//  Created by Valeria Dudinova on 26.11.2024.
//

#include <iostream>

using namespace std;

// Клас для винятків з неправильною розмірністю масиву
class ArraySizeException {
public:
    const char* what() const {
        return "Array size must be 4x4.";
    }
};

// Клас для винятків, якщо в масиві є некоректні дані
class ArrayDataException {
private:
    int row, col;
public:
    ArrayDataException(int r, int c) : row(r), col(c) {}

    void printError() const {
        cout << "Invalid data at [" << row << "][" << col << "]." << endl;
    }
};

// Клас для обчислення значень у масиві
class ArrayValueCalculator {
public:
    static int charToInt(const char* str) {
        int result = 0;
        int sign = 1; // Для перевірки негативних чисел
        int i = 0;

        if (str[0] == '-') {
            sign = -1;
            i = 1; // Почати перетворення після знака
        }

        while (str[i] != '\0') {
            if (str[i] < '0' || str[i] > '9') {
                throw "Non-numeric character detected.";
            }
            result = result * 10 + (str[i] - '0');
            i++;
        }

        return result * sign;
    }

    static int doCalc(const char arr[4][4][10], int rows, int cols) {
        // Перевірка розмірності масиву
        if (rows != 4 || cols != 4) {
            throw ArraySizeException();
        }

        int sum = 0;

        // Обхід всіх елементів масиву
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                try {
                    sum += charToInt(arr[i][j]);
                } catch (...) {
                    throw ArrayDataException(i, j);
                }
            }
        }

        return sum;
    }
};

int main() {
    // Коректний масив
    const char validArray[4][4][10] = {
        {"1", "2", "3", "4"},
        {"5", "6", "7", "8"},
        {"9", "10", "11", "12"},
        {"13", "14", "15", "16"}
    };

    // Масив з некоректними даними
    const char invalidDataArray[4][4][10] = {
        {"1", "2", "X", "4"},
        {"5", "6", "7", "8"},
        {"9", "10", "11", "12"},
        {"13", "14", "15", "16"}
    };

    try {
        cout << "Calculating valid array:" << endl;
        int result = ArrayValueCalculator::doCalc(validArray, 4, 4);
        cout << "Sum: " << result << endl;
    } catch (const ArraySizeException& e) {
        cout << "Array size error: " << e.what() << endl;
    } catch (const ArrayDataException& e) {
        e.printError();
    }

    try {
        cout << "Calculating invalid data array:" << endl;
        int result = ArrayValueCalculator::doCalc(invalidDataArray, 4, 4);
        cout << "Sum: " << result << endl;
    } catch (const ArraySizeException& e) {
        cout << "Array size error: " << e.what() << endl;
    } catch (const ArrayDataException& e) {
        e.printError();
    }

    return 0;
}
