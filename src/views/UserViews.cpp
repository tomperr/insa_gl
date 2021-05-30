#include "UserViews.hpp"

using namespace std;

string UserViews::GetUsername()
{
    cout << "Connexion" << endl;
    cout << "Entrez votre identifiant utilisateur :" << endl;
    cout << "> ";
    string username;
    cin >> username;

    return username;
}

string UserViews::GetPassword()
{
    cout << "Entrez votre mot de passe utilisateur :" << endl;
    cout << "> ";
    string password;
    cin >> password;

    return password;
}

void UserViews::LoginSuccess()
{
    cout << "Connexion réussi !" << endl;
}

void UserViews::LoginFailed(int code)
{
    cout << "Connexion échoué : ";

    switch(code)
    {
        case 0:
        {
            cout << "Couple identifiant/mot de passe invalides !";
            break;
        }
        
        case 1:
        {
            // normalement ça n'arrive jamais
            cout << "Utilisateur déjà connecté !";
            break;
        }

        case 2:
        {
            cout << "Liste d'utilisateur vide !";
            break;
        }
    }

    cout << endl;
}

void UserViews::LogoutSuccess()
{
    cout << "Déconnexion réussi !" << endl;
}