#include "User.h"

//default constructor
User::User() 
{
    id = 0;
    username = "";
    password = "";
}

//parameterized constructor
User::User(int id, string user, string pass) 
{
    this->id = id;
    this->username = user;
    this->password = pass;
}

//virtual destructor
User::~User()
{

}

//setters
void User::setID(int id)
{
    this->id = id;
}

void User::setUsername(const string& user)
{
    username = user;
}

void User::setPassword(const string& pass)
{
    password = pass;
}

//getters
int    User::getID() const
{
    return id;
}

string User::getUsername() const
{
    return username;
}

string User::getPassword() const
{
    return password;
}

//a boolean function that checks the validity and authenticity of the user's entered password
bool User::checkPassword(const string& pass) const
{
    return password == pass;
}

//a function that loads the user's details from a file
void User::loadFromFile(ifstream& in)
{
    in >> id >> username >> password;
}

//a function that saves the user's details to a file
void User::saveToFile(ofstream& out) const {
    out << id << "\n"
        << username << "\n"
        << password << "\n";
}
