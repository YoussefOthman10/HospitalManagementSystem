#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//base abstract class
class User 
{
protected:
    int id;
    string username;
    string password;

public:
    //default constructor
    User();

    //parameterized constructor
    User(int id, string user, string pass);
    
    //virtual destructor to ensure proper memory cleanup when deleting derived objects through a base class pointer
    virtual ~User();

    //setters
    void setID(int id);
    void setUsername(const string& user);
    void setPassword(const string& pass);
    
    //getters
    int getID() const;
    string getUsername() const;
    string getPassword() const;
    
    //a function that checks the validity and authenticity of the user's entered password
    bool checkPassword(const string& pass) const;

    //pure virtual functions that makes user an abstract class, displays info and gets role that will be used later with the derived classes
    virtual void getDetails() const = 0;
    virtual void updateDetails() = 0;

    //pure virtual functions that load from files and save to files using the fstream library that will later be overridden by derived classes
    virtual void loadFromFile(ifstream& in);
    virtual void saveToFile(ofstream& out) const;
};

#endif
