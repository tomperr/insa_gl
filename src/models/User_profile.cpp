#include "User_profile.hpp"

string User_profile::filename = "./ressources/user_profiles.csv";
bool User_profile::fileHasBeenRead = false;
bool User_profile::objectsHaveBeenLinked = false;
map<string, User_profile> User_profile::user_profiles = map<string, User_profile>();