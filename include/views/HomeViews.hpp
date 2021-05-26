#ifndef HOMEVIEWS_HPP
#define HOMEVIEWS_HPP

#include <iostream>
#include "Authentification.hpp"
#include "User.hpp"
#include "User_profile.hpp"

class HomeViews {

    public:
    // Le numéro rendu est le choix de l'utilisateur
    // /!\ Attention dépend de si l'utilisateur est connecté
    // ET du type d'utilisateur
    static int Home(); 
};

#endif