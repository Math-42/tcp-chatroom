#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

typedef struct user
{
    string username;
    string password;
} user;

vector<user> load_valid_users(string n_file);

int autenticate_user(vector<user> users, user aut);

user login();