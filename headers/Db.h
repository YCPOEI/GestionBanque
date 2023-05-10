#include <sqlite3.h>
#include <iostream>
#include "personne.h"
#include <vector>
#include <string>


class Db
{
    
    public:
        //DB
        static sqlite3 * open();
        static int close(sqlite3 * db);
        static int create();
        static int reset();
        static int drop();
        
        //Client
        static int new_client(Client * c);
        static int delete_client(Client * c);
        static Client * get_Client(int ID);
        static std::vector<Client *> get_Client(std::string firstname, std::string name);
        static std::vector<Client *> get_Client();

        //Conseiller
        static int new_conseiller(Conseiller * c);
        static int delete_conseiller(Conseiller * c);
        static Conseiller get_Conseiller(int ID);
        static std::vector<Conseiller *> get_Conseiller(std::string firstname, std::string name);
        static std::vector<Conseiller *> get_Conseiller();

        //Compte
        static int new_compte(Compte c);
        static int delete_compte(Compte c);
        //static int delete_compte(Client c); ?
        static Compte getCompte(int ID);
        static std::vector<Compte*> getCompte(Client * c);
        static std::vector<Compte*> getCompte(Conseiller * c);
        
        //Ope
        static int new_ope();
        static int delete_ope(Operation o);
        static int delete_ope(Compte c);
        static Operation * get_ope(int ID);
        static std::vector<Operation *> get_ope(Compte c);

};