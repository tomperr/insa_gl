#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>

#include "Model.hpp"
#include "Measurement.hpp"

class Measurement;

using namespace std;

class Attribute : public Model
{
    protected:
        // Variables statiques
        static string filename;      
        static bool fileHasBeenRead;      
        static bool objectsHaveBeenLinked;

        // Navigations
        vector<Measurement*> measurements;

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
        static void SetFilename(string filename);

        // Getters
        string GetId();
        string GetUnit();
        string GetDescription();
        vector<Measurement*> GetMeasurements();

        // Setters
        void SetId(string id);
        void SetUnit(string unit);
        void SetDescription(string description);

        void AddMeasurements(Measurement* measurement);


};

#endif