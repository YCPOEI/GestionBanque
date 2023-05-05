#ifndef COMPTE_LIGNE
#define COMPTE_LIGNE

#include "compte.h"
#include "smart_pointer.h"



class CompteLigne : public Compte {
    public:
        CompteLigne(Client * client, Conseiller  * conseiller): Compte(client, conseiller) {}
        void consultationEnLigne(void);
};

#endif