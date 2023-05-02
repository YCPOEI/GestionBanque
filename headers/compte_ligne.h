#ifndef COMPTE_LIGNE
#define COMPTE_LIGNE

#include "compte.h"


class CompteLigne : public Compte {
    public:
        CompteLigne(Personne *client, Personne *conseiller): Compte(client, conseiller) {}
        void consultationEnLigne(void);
};

#endif