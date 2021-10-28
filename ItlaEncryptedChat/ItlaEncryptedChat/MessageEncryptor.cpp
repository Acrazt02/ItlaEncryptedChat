#include "MessageEncryptor.h"

MessageEncryptor::MessageEncryptor() {

}

string MessageEncryptor::encrypt(string unencryptedMsg){
	
    vector<vector<int>> msgMatrix;

	bool verbose = false;
	
	if (unencryptedMsg[unencryptedMsg.size()-1] == '#') {
		verbose = true;
	}

    int id = 0;

    int size = unencryptedMsg.size();

    int qtyOfmsgArrays, offset = 0;

    if (size % 4 == 0 && size >= 4) {
        qtyOfmsgArrays = size;
    }
    else {
        while (size % 4 != 0) {
            size++;
            offset++;
            unencryptedMsg += "Z";
        }
        qtyOfmsgArrays = size;
    }

    if (verbose) {
        cout << "\nHabra un total de " << qtyOfmsgArrays / 4 << " matrices bloques de mensaje. El mensaje tiene " << size - offset << " caracteres." << endl;

        if (offset > 0) {
            cout << "Se agregaron " << offset << " 'Z' al final del mensaje." << endl;
        }
    }

    //We are going to need 13 msgArrays
    for (int i = 0; i < size; i += 4) {

        vector<int> msgArray;

        if (verbose) {
            std::cout << "\nMatriz #" << id << " tendra: ";
            std::cout << "\n Letras : " << " [ " << unencryptedMsg[i + 0] << ", " << unencryptedMsg[i + 1] << ", " << unencryptedMsg[i + 2] << ", " << unencryptedMsg[i + 3] << "] ";
            std::cout << "\n Valores : " << " [ " << convertionTable[unencryptedMsg[i + 0]] << ", " << convertionTable[unencryptedMsg[i + 1]] << ", " << convertionTable[unencryptedMsg[i + 2]] << ", " << convertionTable[unencryptedMsg[i + 3]] << "] " << endl;
        }
        
        for (int j = 0; j < 4; j++) {
            msgArray.push_back(convertionTable[unencryptedMsg[i + j]]);
        }

        id++;
        msgMatrix.push_back(msgArray);
    }

    if (verbose) {
        cout << "\nMultiplicando por matriz inversa... \n";
    }

    //Now multiply msgMatrix by modifierMatrix for each one

    vector<array<int, 4>> results;

    for (int i = 0; i < msgMatrix.size(); i++) { //Go thru each msg block

        array<int, 4> result = { 0,0,0,0 };
        for (int j = 0; j < 4; j++) { //Go thru each letter
            for (int k = 0; k < 4; k++) { //Go thru each modifier value

                result[j] += msgMatrix[i][k] * modifierMatrix[k][j];
            }
        }

        results.push_back(result);
    }

    if (verbose) {
        for (int i = 0; i < results.size(); i++) {
            std::cout << "\nResultados de bloque #" << i << " [ " << results[i][0] << ", " << results[i][1] << ", " << results[i][2] << ", " << results[i][3] << "] " << endl;
        }

        cout << "\nEl mensaje ha sido condificado. \nEl resultado es: ";
        for (int i = 0; i < results.size(); i++) {
            for (int j = 0; j < results[i].size(); j++) {
                cout << " " << results[i][j];
            }
        }
    }
    else {
        cout << "\nEl mensaje ha sido condificado. \n Se enviara: ";
        for (int i = 0; i < results.size(); i++) {
            for (int j = 0; j < results[i].size(); j++) {
                cout << " " << results[i][j];
            }
        }
        cout << endl;
    }

    string encryptedMsg = "";

    for (int i = 0; i < results.size(); i++) {
        for (int j = 0; j < 4; j++) {
            encryptedMsg += " " + to_string(results[i][j]);
        }
    }

    return encryptedMsg;
}

string MessageEncryptor::decrypt(string encryptedMsg){

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
    for (int i = 0; i < elements.size()/4; i++) {
        for (int j = 0; j < 4; j++) {
            element[j] = elements[index+j];
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

    cout << "\nMensaje decodificado";

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

    return decodedMsg;
}