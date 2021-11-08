#include "cryptography.hpp"

Cryptography::Cryptography(){
    this->privateKey = 0;
}
Cryptography::Cryptography(long long int privateKey){
    this->privateKey = privateKey;
}

Cryptography::~Cryptography(){}

bool Cryptography::isPrime(long long int number){
    int tmp = 2;
	while(tmp < number)
		if(!(number % tmp++))
			break;

	if(tmp == number)
		return true;
	return false;
}

long long int Cryptography::nearPrime(int prime){
	do{
		if(isPrime(prime))
            return prime;
		prime++;
	}while(true);
}

long long int Cryptography::producePrime(){
    long long int prime = 0;
	srand(time(0));
	while (true){
		prime = (rand() % 500);
		if(isPrime(prime))
		    break;
	}
	return prime;
}

bool Cryptography::__gcd(long long int a, long long int b){
    if(a == 0){
		if(b > 1)
			return false;
		else
			return true;
	 }
    return __gcd(b%a, a);
}

long long int Cryptography::createEKey(long long int phi){
    long long int eKey;
	while(true){
		eKey = rand()%phi;
		if(eKey >= 2 && __gcd(eKey, phi) == 1)
			break;
	}
	return eKey;
}

long long int Cryptography::createDKey(long long int eKey, long long int phi){
    
    long long int dKey = phi/eKey;
	while(true){
		if(((dKey*eKey) % phi) == 1)
			break;
		else 
			++dKey;
	}
	return dKey;
}

void Cryptography::CreateKey(){

    long long int p, q;
    if(this->privateKey != 0){
        p = producePrime();
        q = producePrime();
        while(p == q)
            p = producePrime();
    }else{
        p = nearPrime(this->privateKey);
	    q = nearPrime(p + 2);
    }

	this->n = p*q;
	long long int phi = (p - 1)*(q - 1);
	this->publicKey = createEKey(phi);
	this->privateKey = createDKey(this->publicKey, phi);
}

long long int Cryptography::TransformMessage(long long int msg, long long int key, long long int n){
    
    long long int value = 1;
    while(key > 0){
        value *= msg;
        value %= n;
        key--;
    }
    return value;
}

string Cryptography::RSA(string message){
	CreateKey();
	for(auto&a : message)
		a = TransformMessage(a-97, this->publicKey, this->n);
	return message;
}

string Cryptography::_RSA(string message){
	for (auto&a : message) 
		a = 97 + TransformMessage(a, this->privateKey, this->n);
	return message;
}