#ifndef COMPTE_EPARGNE
#define COMPTE_EPARGNE

#include "compte.h"

class CompteEpargne : public Compte {
    private:
        float interet;
    public:
        CompteEpargne(Personne *client, Personne *conseiller, float interet): Compte(client, conseiller), interet(interet){};
        float getInteret(void);
        float calculInteret();
};

#endif