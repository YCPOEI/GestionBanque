#ifndef BANQUE_PERSONNE
#define BANQUE_PERSONNE
#include <string>
#include <iostream>
#include <vector>
#include "compte.h"
#include "smart_pointer.h"


class Compte;

class Personne {
    protected :
        std::string nom, prenom, adresse;
        std::vector<Compte*> liste_compte;
        
    public:
        Personne(std::string nom,std::string prenom,std::string adresse);
        std::string getNom();
        void setNom(std::string nom);
        std::string getPrenom();
        void setPrenom(std::string prenom);
        std::string getAdresse();
        std::vector<Compte*> getListeCompte();
        void setAdresse(std::string adresse);
        void ajouterCompte(Compte *  compte){
            this->liste_compte.push_back(compte);
        }
        void afficherComptes();
        void supprimerCompte(Compte * compte);
};

class Client : public Personne{
    public:
        Client(std::string nom,std::string prenom,std::string adresse) : Personne(nom,prenom,adresse) {};
        ~Client();
        void supprimerCompte(int index);

};

class Conseiller : public Personne{
    public:
        Conseiller(std::string nom,std::string prenom,std::string adresse) : Personne(nom,prenom,adresse) {};
        ~Conseiller();
        void supprimerCompte(int index);

};  


std::ostream& operator<<(std::ostream& Str, Personne& personne);

#endif