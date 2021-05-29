#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>

class Model
{
    protected:
    static std::string filename;        // Contient le nom du fichier à lire
    static bool fileHasBeenRead;        // Drapeau de référence pour savoir si on a déjà lu le fichier
    static bool objectsHaveBeenLinked;  // Drapeau de référence pour savoir si on a déjà fais la "navigation"

    // Ces méthodes doivent être re-définies dans les filles.
    // Elles ne sont PAS virtuelles. (liaison statique)
    public:
    static void ReadAll();
    static void LinkAll();
    static void EmptyData();
};

// Initialisation des variables statiques
// dans le fichier Model.cpp


#endif