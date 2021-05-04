#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include "Model.hpp"

using namespace std;

class Attribute : public Model
{
    protected:
    // Variables statiques
    static string filename;      
    static bool fileHasBeenRead;      
    static bool objectsHaveBeenLinked;

    // Attributs métiers
    string id;
    string unit;
    string description;

    public:
    // Données
    static map<string, Attribute> attributes;

    // Constructeur
    Attribute();

    // Méthodes statiques
    static void ReadAll();
    static void LinkAll();

    // Getters
    string GetId();
    string GetUnit();
    string GetDescription();

    // Setters
    void SetId(string id);
    void SetUnit(string unit);
    void SetDescription(string description);
};

#endif