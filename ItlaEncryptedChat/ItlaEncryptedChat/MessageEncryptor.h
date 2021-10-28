#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <array>
#include <sstream>

using namespace std;

class MessageEncryptor
{

public:
    MessageEncryptor();
    string encrypt(string unencryptedMsg);
    string decrypt(string encryptedMsg);

private:
    map<char, int> convertionTable = { {'A', 27},
                                   {'B', 26},
                                   {'C', 25},
                                   {'D', 24},
                                   {'E', 23},
                                   {'F', 22},
                                   {'G', 21},
                                   {'H', 20},
                                   {'I', 19},
                                   {'J', 18},
                                   {'K', 17},
                                   {'L', 16},
                                   {'M', 15},
                                   {'N', 14},
                                   {'Ñ', 13},
                                   {'O', 12},
                                   {'P', 11},
                                   {'Q', 10},
                                   {'R', 9},
                                   {'S', 8},
                                   {'T', 7},
                                   {'U', 6},
                                   {'V', 5},
                                   {'W', 4},
                                   {'X', 3},
                                   {'Y', 2},
                                   {'Z', 1},
                                   {'a', 28},
                                   {'b', 29},
                                   {'c', 30},
                                   {'d', 31},
                                   {'e', 32},
                                   {'f', 33},
                                   {'g', 34},
                                   {'h', 35},
                                   {'i', 36},
                                   {'j', 37},
                                   {'k', 38},
                                   {'l', 39},
                                   {'m', 40},
                                   {'n', 41},
                                   {'ñ', 42},
                                   {'o', 43},
                                   {'p', 44},
                                   {'q', 45},
                                   {'r', 46},
                                   {'s', 47},
                                   {'t', 48},
                                   {'u', 49},
                                   {'v', 50},
                                   {'w', 51},
                                   {'x', 52},
                                   {'y', 53},
                                   {'z', 54},
                                   {' ', 55},
                                   {'.', 56},
                                   {',', 57},
                                   {'0', 58},
                                   {'1', 59},
                                   {'2', 60},
                                   {'3', 61},
                                   {'4', 62},
                                   {'5', 63},
                                   {'6', 64},
                                   {'7', 65},
                                   {'8', 66},
                                   {'9', 67},
                                   {'+', 68},
                                   {'-', 69},
                                   {'/', 70},
                                   {'*', 71},
                                   {'"', 72},
                                   {'#', 73},
                                   {'>', 74}};

    map<int, char> invertedConvertionTable;

    //Matriz modificadora 4X4
    double modifierMatrix[4][4] = { {3,1,4,1},
                                   {5,9,2,6},
                                   {5,3,5,8},
                                   {9,7,3,2} };

    //Matriz modificadora inversa 4
    double inverseModifierMatrix[4][4] = { -0.214622642, -0.188679245, 0.112028302, 0.225235849,
                                          0.148584906, 0.20754717, -0.154481132, -0.079009434,
                                         0.419811321,0.0943396226, -0.0872641509, -0.143867925,
                                         -0.183962264, -0.0188679245, 0.16745283, -0.0212264151 };

};

