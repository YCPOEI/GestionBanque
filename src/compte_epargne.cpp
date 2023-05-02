#include "../headers/compte_epargne.h"
#include <iomanip>
float CompteEpargne::calculInteret()
{
    return this->getSolde() * this->interet /100;
}