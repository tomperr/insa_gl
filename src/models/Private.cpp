#include "Private.hpp"

string Private::filename = "";
bool Private::fileHasBeenRead = false;
bool Private::objectsHaveBeenLinked = false;
map<string, Private> Private::privates = map<string, Private>();

bool Private::GetTrust()
{
    return profile->GetTrust();
}

void Private::SetTrust(bool newTrust)
{
    profile->SetTrust(newTrust);
}

void Private::AddScore(int toBeAdded)
{
    this->GetProfile()->AddToScore(toBeAdded);
}