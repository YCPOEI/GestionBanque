#ifndef COMPTE
#define COMPTE

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include "personne.h"

class Personne;
class Operation {
    private:
        std::string date;
        std::string nom;
        float somme;
    public:
        Operation(std::string date, std::string nom, float somme);
        ~Operation();
        std::string getDate();
        void setDate(std::string date);
        std::string getNom();
        void setNom(std::string nom);
        float getSomme();
        void setSomme(float somme);
};
std::ostream& operator<<(std::ostream& Str, Operation& oper);

class Compte {
    private: 
        float solde;
        Personne* client, * conseiller;
        std::vector<Operation*> historique;
        
    protected:
        Compte(Personne *client, Personne *conseiller);

    public:
        Personne * getClient();
        Personne * getConseiller();
        void setConseiller(Personne * conseiller);
        void deposer(float n);
        void retirer(float n);
        float getSolde();
        float consulterSolde(void);
        void consulterOperations(void);
        void consulterDebits(void);
        void consulterCredits(void);

        ~Compte();
    
};
std::ostream& operator<<(std::ostream& Str, Compte& compte);

#endif