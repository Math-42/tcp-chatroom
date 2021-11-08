#pragma once
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Cryptography {
    public:
        Cryptography();
        Cryptography(long long int privateKey);
        ~Cryptography();

        bool isPrime(long long int a);
        long long int nearPrime(int prime);
        long long int producePrime();
        bool __gcd(long long int a, long long int b);
        long long int TransformMessage(long long int c, long long int d, long long int n);
        long long int createEKey(long long int phi);
        long long int createDKey(long long int eKey, long long int phi);
        void CreateKey();

        string RSA(string message);
        string _RSA(string message);

        long long int publicKey;
        long long int n;

    private:
        long long int privateKey;
};
