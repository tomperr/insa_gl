#include "Attribute.hpp"

// Initialisation des variables statiques
string Attribute::filename = "./ressources/attributes.csv";
bool Attribute::fileHasBeenRead = false;
bool Attribute::objectsHaveBeenLinked = false;
map<string, Attribute> Attribute::attributes = map<string, Attribute>();

Attribute::Attribute() {};

void Attribute::ReadAll()
{
    if(!Attribute::fileHasBeenRead)
    {
        ifstream file(Attribute::filename.c_str(), ifstream::in); 
    
        if(file.is_open())
        {
            string buffer;
            getline(file, buffer); // Enlever la première ligne (nom des colonnes)

            while(!file.eof())
            {
                Attribute newAttribute;

                getline(file, newAttribute.id, ';');

                if(file.eof()) break;

                getline(file, newAttribute.unit, ';');
                getline(file, newAttribute.description, ';');

                getline(file, buffer); // Enlever le \r\n de fin de ligne

                Attribute::attributes.insert(make_pair(newAttribute.id, newAttribute));
            }
        }

        Attribute::fileHasBeenRead = true;
    }
}

string Attribute::GetId()
{
    return this->id;
}

string Attribute::GetUnit()
{
    return this->unit;
}

string Attribute::GetDescription()
{
    return this->description;
}

void Attribute::SetId(string id)
{
    this->id = id;
}

void Attribute::SetUnit(string unit)
{
    this->unit = unit;
}

void Attribute::SetDescription(string description)
{
    this->description = description;
}