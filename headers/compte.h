#ifndef BANQUE_COMPTE
#define BANQUE_COMPTE

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
//#include <unistd.h>
#include <thread>
#include "personne.h"
#include "smart_pointer.h"


class Personne;
class Client;
class Conseiller;
class Operation {
    protected:
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
        float solde = 0;
        Client * client; 
        Conseiller * conseiller;
        std::vector<Operation> historique;
    protected:
        Compte(Client * client, Conseiller * conseiller) :  client(client), conseiller(conseiller) {};/*{
            this->client = client;
            this->conseiller = conseiller;
            this->solde=0;
        };*/
    public:
        Client * getClient();
        Conseiller * getConseiller();
        void setConseiller(Conseiller * conseiller);
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


class OperationRecurrente : public Operation {
    private :
        int recur;
        bool actif;
        int count;
        Compte *compte;
    public :
        OperationRecurrente(std::string date, std::string nom, float somme, int recur, Compte *compte);
        ~OperationRecurrente();

        void recurrenceActive(void);
        void activerRecurrence(void);
        void annulerRecurrence(void);

};

#endif
