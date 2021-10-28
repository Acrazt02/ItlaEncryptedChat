#include <iostream>
#include <string>
#include <future>
#include <vector>

#include "Server.h"
#include "Client.h"
#include "MessageEncryptor.h"

using namespace std;

vector<future<void>> futures;

static void msgRecv(Client& client);

int main()
{

    MessageEncryptor encryptor;

    cout << "Bienvenido. Desea crear o unirte a un servidor? [C/U]" << endl;
    cout << ">>";
    string opt;
    cin >> opt;

    if (opt[0] == 'C') {
        Server server = Server();
        cout << "Servidor iniciado!" << endl;
        server.Start();
        server.Listen();
    }
    else {

        string nickName, ipAdrress;

        cout << "Escoge un nombre de usuario: ";
        cin >> nickName;

        Client client = Client(nickName);

        do {

            cout << "Escriba la dirrecion ip del servidor: ";
            cin >> ipAdrress;

            cout << "Estableciendo conexion..." << endl;

            client.Connect(ipAdrress, 10500);

            if (client.isConnected()) {
                cout << "Conexion establecida!" << endl;;
            }
            else {
                cout << "ERROR: El servidor " + ipAdrress + " no existe!" << endl;
                cout << "Por favor pruebe con una nueva dirrecion ip.";
            }

        } while (!client.isConnected());

        string data, msg;

        futures.push_back(async(launch::async, msgRecv, ref(client)));
        //cout << endl << nickName + ">>";

        while (true) {
            
            getline(cin, data);

            if (data.size() > 0) {
                cout << endl << endl << nickName + ">>";
                string msg = encryptor.encrypt(nickName + ">>" + data);
                client.sendData(msg);
            }
        }
    }
}

static void msgRecv(Client& client) {

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
                               {'>', 74} };

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

    //MessageEncryptor encryptor;

    string msg, temp;

    while (true) {
        msg = client.getData();
        if (msg.size() > 0) {

            string encryptedMsg = msg;

            //
            vector<array<int, 4>> results;

            istringstream iss(encryptedMsg);
            string result;

            int i = 0;

            vector<int> elements;

            while (iss >> result) {
                elements.push_back(stoi(result));
            }

            array<int, 4> element;
            int index = 0;
            for (int i = 0; i < elements.size() / 4; i++) {
                for (int j = 0; j < 4; j++) {
                    element[j] = elements[index + j];
                }
                index += 4;
                results.push_back(element);
            }

            //Instantiate inverted map for decoding
            for (map<char, int>::iterator i = convertionTable.begin(); i != convertionTable.end(); ++i)
                invertedConvertionTable[i->second] = i->first;

            //Now multiply msgMatrix by inverseModifierMatrix for each one
            vector<array<double, 4>> decodedMsgResults;

            for (int i = 0; i < results.size()/*13*/; i++) { //Go thru each msg block

                array<double, 4> decodedMsg = { 0,0,0,0 };
                for (int j = 0; j < 4; j++) { //Go thru each letter
                    for (int k = 0; k < 4; k++) { //Go thru each modifier value

                        decodedMsg[j] += results[i][k] * inverseModifierMatrix[k][j];
                    }
                }

                decodedMsgResults.push_back(decodedMsg);
            }

            /*
            for (int i = 0; i < decodedMsgResults.size(); i++) {
                std::cout << "\nResultados del bloque decodificado #" << i << " [ " << decodedMsgResults[i][0] << ", " << decodedMsgResults[i][1] << ", " << decodedMsgResults[i][2] << ", " << decodedMsgResults[i][3] << "] " << endl;
            }*/

            //cout << "\nMensaje decodificado";

            string decodedMsg = "";

            for (int i = 0; i < decodedMsgResults.size(); i++) {
                for (int k = 0; k < decodedMsgResults[i].size(); k++) {

                    float x = decodedMsgResults[i][k];
                    x = x + 0.5 - (x < 0);
                    int y = (int)x;

                    decodedMsg += invertedConvertionTable[y];
                    //cout << invertedConvertionTable[y];
                }
            }
            //
            cout << endl << "Mensaje codificado: " << msg << endl;
            cout << endl << decodedMsg << endl;
            cout << endl << client.getNickName() + ">>";
            msg = "";
        }
    }
}

