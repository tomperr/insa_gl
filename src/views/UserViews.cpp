#include "UserViews.hpp"

using namespace std;

string UserViews::GetUsername()
{
    cout << "Entrez votre identifiant utilisateur :" << endl;
    string username;
    cin >> username;

    return username;
}

string UserViews::GetPassword()
{
    cout << "Entrez votre mot de passe utilisateur :" << endl;
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