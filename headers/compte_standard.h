#ifndef COMPTE_STANDARD
#define COMPTE_STANDARD
#include "compte.h"


class CompteStandard : public Compte{
    public :
        CompteStandard(Personne *client, Personne *conseiller): Compte(client, conseiller) {}
};

#endif
