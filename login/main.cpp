#include "login.h"


int main () 
{
    cout << "Hello World!" <<endl;

//Leitura de Usuarios Cadastrados
    vector<user> users = load_valid_users("users.txt");

//Printa Usuarios
     for (int i = 0; i < users.size(); i++)
        cout << users[i].username + "     " + users[i].password << endl; 

//Leitura de username e senha
    user aut = login();

//Autenticacao
    int valido = autenticate_user(users, aut);
 
    return 0;
}