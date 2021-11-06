#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include <vector>

using namespace std;

typedef struct user
{
    string username;
    string password;
} user;


int main () 
{
    cout << "Hello World!" <<endl;

//Leitura de Usuarios Cadastrados
    vector<user> users;
    string userpass;

    ifstream file("users.txt");

    while (getline(file,userpass))
    {
        stringstream ss(userpass);

        while (ss.good())
        {
            user temp;
            getline(ss, temp.username , '/');
            // users[i].username = substr;
            getline(ss, temp.password);
            // users[i].password = substr;
            users.push_back(temp);
        }
    }

    // Close the file
    file.close(); 


//Printa Usuarios
     for (size_t i = 0; i < users.size(); i++)
        cout << users[i].username + "     " + users[i].password << endl; 

//Autenticacao
    user aut;
    int valido = -1;

    cout << "Digite seu username:" << endl;
    cin >> aut.username;
       
    cout << "Digite sua senha:" << endl;
    cin >> aut.password;

    
    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].username == aut.username)
        {
            if (users[i].password == aut.password)
            {
                cout << "Bem vindo " + aut.username +"!" <<endl;
                valido = 1;
            }
            else
            {
                cout << "Senha Incorreta!" <<endl;
                valido = 0;
            }
        }
    }

    if (valido == -1)
    {
        cout << "Usuario nao encontrado!" <<endl;
        return 0;

    }
    
    return 0;
}