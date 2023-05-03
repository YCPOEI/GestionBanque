#include <random>
#include <iostream>
#include "headers/personne.h"
#include "headers/compte_epargne.h"
#include "headers/compte_standard.h"
#include "headers/compte_ligne.h"

using namespace std;

template<typename T> class SP {
    private:
        T* ptr;
    public:
        SP(T* ptr): ptr(ptr) {};
        ~SP() {
            delete this->ptr;
        }

        T* get() {
            return this->ptr;
        }

        T* operator->() {
            return this->ptr;
        }
};

int main() {
    random_device rd;
    mt19937 e2(rd());
    uniform_real_distribution<float> dist(1,1000);

    Client *cli1 = new Client("David","Bastien","Angers");
    Client *cli2 = new Client("Rocher","Emmanuel","Nantes");
    Conseiller *cons = new Conseiller("Cottrel", "Yoan", "St. Nazaire");
    CompteStandard *compteSt = new CompteStandard(cli1, cons);
    CompteEpargne *compteEp = new CompteEpargne(cli1, cons, 4.6);
    CompteLigne *compteLi = new CompteLigne(cli2, cons);
    
    cli1->ajouterCompte(compteSt);
    cons->ajouterCompte(compteSt);
    cli1->ajouterCompte(compteEp);
    cons->ajouterCompte(compteEp);
    cli2->ajouterCompte(compteLi);
    cons->ajouterCompte(compteLi);

    compteSt->deposer(dist(e2));
    compteSt->deposer(dist(e2));
    compteSt->retirer(dist(e2));
    compteSt->deposer(dist(e2));
    compteSt->deposer(dist(e2));
    compteSt->retirer(dist(e2));
    compteSt->retirer(dist(e2));
    compteSt->deposer(dist(e2));

    compteEp->deposer(dist(e2));
    compteEp->deposer(dist(e2));
    compteEp->retirer(dist(e2));
    compteEp->deposer(dist(e2));
    compteEp->retirer(dist(e2));
    compteEp->deposer(dist(e2));
    compteEp->retirer(dist(e2));
    compteEp->deposer(dist(e2));

    compteLi->deposer(dist(e2));
    compteLi->retirer(dist(e2));
    compteLi->deposer(dist(e2));
    compteLi->retirer(dist(e2));
    compteLi->deposer(dist(e2));
    compteLi->deposer(dist(e2));
    compteLi->retirer(dist(e2));
    compteLi->deposer(dist(e2));

   
    cout << "####Operations sur compte#####" << endl;
    compteSt->consulterOperations();
    compteSt->consulterSolde();

    compteEp->consulterCredits();
    compteEp->consulterDebits();

    cout << endl << "####Fonctions enfants#####" << endl;
    compteLi->consultationEnLigne();
    std::cout << "Interets : " << compteEp->calculInteret() << endl;

    cout<< endl  << "####Suppression d'un compte#####" << endl;
    cli1->afficherComptes();
    //compteEp->consulterOperations();
    delete compteEp;
    std::cout << "nb comptes" << cli1->getListeCompte().size() <<endl;
    cli1->afficherComptes();
    

    cout<< endl  << "####Suppression d'un client#####" << endl;
    cons->afficherComptes();
    delete cli1;
    cons->afficherComptes();


    delete cli2;
    delete cons;

    return 0;
}