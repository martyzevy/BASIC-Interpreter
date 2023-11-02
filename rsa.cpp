#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>

using namespace std;

bool getUserChoice(int p, int c, int n);
void encrypt(string file, long long n, string message);
void decrypt(string in, string out, long long n, int p, int q);
long long modularExponentiation(long long b, long long e, long long m);
int gcd(int num1, int num2);
long long extendedEuclidean(long long l);

int main(int argc, char* argv[]){
    int p = stoi(argv[1]);
    int q = stoi(argv[2]);

    //Main menu
    cout << "Please enter a command: DECRYPT, ENCRYPT, or EXIT" << endl;
    bool quit = false;
    while (!quit){
        quit = getUserChoice(p, q, 0);  
    }

    return 0;
}

bool getUserChoice(int p, int q, int n){
    //Get the user input
    string userInput;
    getline(cin, userInput);
    stringstream ss(userInput);
    string command; 
    ss >> command;

    if (command == "DECRYPT"){
        string input, output;
        ss >> input >> output;
        try{
            decrypt(input, output, p * q, p, q);
        }
        //If the GCD of e and L was not 1, the program terminates
        catch (invalid_argument& exception){
            cerr << exception.what() << endl;
            return true;
        }
        return false;  
    }

    else if (command == "ENCRYPT"){
        string fileName, message;
        ss >> fileName >> n;
        ss.ignore();    //Skip whitespace preceeding the message
        getline(ss, message);
        encrypt(fileName, n, message);
        return false;   
    }

    else if (command == "EXIT") return true;    

    //If the command is not ENCRYPT, DECRYPT, or EXIT
    else{
        cout << "Error: Invalid Command." << endl;
        return getUserChoice(p, q, n);
    }
}

void encrypt(string file, long long n, string message){
    ofstream outfile(file);
    //Ensure n is greater than 27
    while (n < 27){
        cout << "Error: n must be > 27. Enter a new value for n." << endl;
        cin >> n;
        encrypt(file, n, message);
    }

    int e = 65537;
    int x = 1 + log10(n/27) / 2.0;
    unsigned int idx = 0;
    int currX = 0;
    string m = "";

    while (idx < message.size()){
        /*When x characters have been added to M, add it to the output file 
        and move on to the next x characters*/
        if (currX == x){
            long long c = modularExponentiation(stoll(m), e, n);  
            outfile << c << " ";
            m = "";
            currX = 0;
        }

        //Converting the current character to an integer, then adding it to m
        if (message[idx] == ' '){
            m += "00";
        }
        else{
            int startVal = 96;
            if (static_cast<int>(message[idx]) < 97) startVal = 64; //If it is a capital letter
            //If the number is less than 10, it should have a leading zero
            if (static_cast<int>(message[idx]) - startVal < 10) m += "0" + to_string(static_cast<int>(message[idx]) - startVal);
            else m += to_string(static_cast<int>(message[idx]) - startVal);
        }
        idx++;
        currX++;
    }

    /*If the xth character came on the final index in message, we still need to add this 
    segment to the output file*/
    if (currX == x){
        long long c = modularExponentiation(stoll(m), e, n);  
        outfile << c << " ";
    }

    /*If x does not divide evenly into the message size, assume there is trailing whitespace
    and add this to the output file*/
    if (currX != x){
        for (int i = currX; i < x; i++){
            m += "00";
        }
        long long c = modularExponentiation(stoll(m), e, n);  
        outfile << c << " ";
    }
    outfile << endl;
}   

long long modularExponentiation(long long b, long long e, long long m){
    long long x = 1;
    long long r = b % m;
    while (e > 0){
        int bit = e % 2;    //The least significant bit
        if (bit == 1){
            x = (x * r) % m;
        }
        r = (r * r) % m;
        e /= 2; //Allows loop to access the next bit in the next iteration 
    }
    return x;
}

void decrypt(string in, string out, long long n, int p, int q){
    //Getting the decryption Key
    long long l = (p-1) * (q-1) / gcd(p-1, q-1);    //Least common multiple of p-1 and q-1
    int e = 65537;
    if (l <= e){
        throw invalid_argument("Error: L is too small");
    }
    if (gcd(e,l) != 1) throw invalid_argument("Error: poor values for p and q");
    long long d = extendedEuclidean(l); //d * e % l = 1

    ifstream ifile(in);
    ofstream ofile(out);
    string encryptedMessage;
    getline(ifile, encryptedMessage);
    stringstream ss(encryptedMessage);
    long long c;
    unsigned int x = 1 + log10(n/27) / 2.0;

    while (ss >> c){
        long long m = modularExponentiation(c, d, n);
        string m_string = to_string(m);
        while (m_string.size() < x * 2){
            //Need to add leading whitespace to the message if it is less than x * 2 characters long
            m_string = "0" + m_string;
        }
        //Convert M to x characters and spaces
        for (unsigned int i = 0; i < m_string.size(); i += 2){
            string curr = m_string.substr(i, 2);    //Two digits represent one letter
            int num = stoi(curr);
            char output;
            if (num == 0) output = ' ';
            else output = static_cast<char>(num + 96);
            ofile << output;
        } 
    }
    ofile << endl;
}

int gcd(int num1, int num2){
    while (num2 != 0){
        int r = num1 % num2;
        num1 = num2;
        num2 = r;
    }
    return num1;    //Greatest common denominator of num1 and num2
}

long long extendedEuclidean(long long l){
    int s = 0;
    int old_s = 1;

    int t = 1;
    long long old_t = 0;
    int r = 65537;
    int old_r = l;    //This will be the GCD in the end

    while (r != 0){
        int quotient = old_r / r;
        int temp = r;
        r = old_r - quotient * r;
        old_r = temp;
        temp = s;
        s = old_s - quotient * s;
        old_s = temp;
        temp = t;
        t = old_t - quotient * t;
        old_t = temp;
    }

    //If old_t is negative, add e * l until it is positive
    while (old_t < 0){
        old_t = old_t + 65537 * l;
    }

    return old_t;   //This is d
}