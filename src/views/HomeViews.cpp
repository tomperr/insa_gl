#include "HomeViews.hpp"

int HomeViews::Home()
{
    bool firstIteration = true;
    bool choiceIsCorrect = false;
    int choice;

    while(!choiceIsCorrect)
    {
        int maximumChoice = 0;

        if(firstIteration)
        {
            firstIteration = true;
        }
        else
        {
            cout << "Choix erroné !" << endl;
        }

        cout << "0 - Quitter" << endl;
        if(Authentification::isAuth())
            cout << "1 - Se déconnecter" << endl;
        else
            cout << "1 - Se connecter" << endl;

        cout << "2 - Calculer qualité de l'air" << endl;
        cout << "3 - Visualiser les données" << endl;
        cout << "4 - Classer les capteurs par similitude" << endl;
        cout << "5 - Calculer l'effet d'un \"cleaner\" sur une zone" << endl;

        maximumChoice = 5;

        if(Authentification::isAuth())
        {
            User* user = Authentification::getUser();

            User_profile* up = user->GetProfile();

            switch(up->GetRole())
            {
                case User_profile::Role::admin:
                {
                    cout << "6 - Panneau de contrôles administrateur" << endl;
                    maximumChoice = 6;
                    break;
                }

                case User_profile::Role::private_user:
                {
                    cout << "6 - Visualiser son score" << endl;
                    maximumChoice = 6;
                    break;
                }
            }
        }

        cout << "> ";
        cin >> choice;

        if(choice >= 0 && choice <= maximumChoice)
            choiceIsCorrect = true;
        else
            cout << "Erreur de saisie." << endl << endl;
    }
    
    return choice;
}