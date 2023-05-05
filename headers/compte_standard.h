#ifndef COMPTE_STANDARD
#define COMPTE_STANDARD
#include "compte.h"
#include "smart_pointer.h"


class CompteStandard : public Compte{
    public :
        CompteStandard(Client * client, Conseiller * conseiller): Compte(client, conseiller) {}
};

#endif
