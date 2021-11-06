
#include "login.h"


vector<user> load_valid_users(string n_file)
{
    vector<user> users;

    string userpass;

    ifstream file(n_file);

    while (getline(file,userpass))
    {
        stringstream ss(userpass);

        while (ss.good())
        {
            user temp;
            getline(ss, temp.username , '/');
            getline(ss, temp.password);

            users.push_back(temp);
        }
    }

    // Close the file
    file.close(); 

    return users;
}

int autenticate_user(vector<user> users, user aut)
{
    int valido = 1;

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].username == aut.username)
        {
            if (users[i].password == aut.password)
            {
                cout << "Bem vindo " + aut.username +"!" <<endl;
                valido = 1;
                return valido;
            }
            else
            {
                cout << "Senha Incorreta!" <<endl;
                valido = 0;
                return valido;
            }
        }
    }

    cout << "Usuario nao encontrado!" <<endl;
    return valido;

    
}

user login()
{
    user aut;

    cout << "Digite seu username:" << endl;
    cin >> aut.username;
       
    cout << "Digite sua senha:" << endl;
    cin >> aut.password;

    return aut;
}