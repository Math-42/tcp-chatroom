#include "cryptography.hpp"

Cryptography::Cryptography(long long int privateKey){
	this->privateKey = privateKey;
}

Cryptography::~Cryptography(){}

bool Cryptography::isPrime(int a){
	for (int i = a-1; i > 1; i--)
		if (a%i == 0)
			return false;
	return true;
}

int Cryptography::nearPrime(int a){
	do{
		if(isPrime(a))
            return a;
		a++;
	} while (true);
}

bool Cryptography::__gcd(int a, int b){
	if(a == 0){
		if(b > 1)
			return false;
		else
			return true;
	 }
    return __gcd(b % a, a); 
}

int Cryptography::__xgcd(int a, int b, int & x, int & y){
    if(b == 0){
       x = 1;
       y = 0;
       return a;
    }

    int x1, y1, gcd = __xgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b)*y1;
    return gcd;
}

int Cryptography::cdn(int c, int d, int n){
    int value = 1;
    while(d > 0){
        value *= c;
        value %= n;
        d--;
    }
    return value;
}

int Cryptography::Coprime(int a, int b){
	vector<int> coprimes;
	for(int i = 2; i < b; i++)
		if(__gcd(i, a) && __gcd(i, b))
			coprimes.push_back(i);

	return coprimes[rand()%coprimes.size()];
}

void Cryptography::CreateKey(){
	int p = nearPrime(this->privateKey);
	int q = nearPrime(p + 2);
	this->n = p * q;
	int phi = (p - 1)*(q - 1);
	this->publicKey = Coprime(this->n, phi);
	this->privateKey = CalculateDecryptionKey(this->publicKey, phi);
}

int Cryptography::CalculateDecryptionKey(int publicKey, int phi){
	int x, y;
	__xgcd(publicKey, phi, x, y);
	if(x >= 0)
		return x;
	else
		return phi + x;
}

string Cryptography::RSA(string message){
	CreateKey();
	for(auto&a : message)
		a = cdn(a-97, this->publicKey, this->n);
	return message;
}

string Cryptography::_RSA(string message){
	for (auto&a : message) 
		a = 97 + cdn(a, this->privateKey, this->n);
	return message;
}