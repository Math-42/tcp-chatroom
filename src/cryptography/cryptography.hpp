#pragma once
#include <vector>
#include <string>

using namespace std;

class Cryptography {
    public:
        Cryptography(long long int privateKey);
        ~Cryptography();

        bool isPrime(int a);
        int nearPrime(int a);
        bool __gcd(int a, int b);
        int __xgcd(int a, int b, int & x, int & y);
        int cdn(int c, int d, int n);
        int Coprime(int a, int b);
        void CreateKey();
        int CalculateDecryptionKey(int publicKey, int phi);

        string RSA(string message);
        string _RSA(string message);

        int publicKey;
        int n;

    private:
        int privateKey;
};
