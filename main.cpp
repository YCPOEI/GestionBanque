#include <random>
#include <iostream>

#include "headers/menu.h"
#include "headers/Db.h"


using namespace std;


int main() {
    random_device rd;
    mt19937 e2(rd());
    uniform_real_distribution<float> dist(1,1000);
    cout << "####Creation personnes et comptes#####" << endl;
    SP<Client> cli1 = SP<Client>(new Client("David","Bastien","Angers"));
    SP<Client> cli2 = SP<Client>(new Client("Rochet","Emmanuel","Nantes"));
    SP<Conseiller> cons = SP<Conseiller>(new Conseiller("Cottrel", "Yoan", "St. Nazaire"));
    Compte * compteSt = (Compte *) new CompteStandard(cli1.get(), cons.get());
    Compte * compteEp = (Compte *) new CompteEpargne(cli1.get(), cons.get(), 4.6);
    Compte * compteLi = (Compte *) new CompteLigne(cli2.get(), cons.get());
    cout << "####Lien des personnes et comptes#####" << endl;
    cli1->ajouterCompte(compteSt);
    cons->ajouterCompte(compteSt);
    cli1->ajouterCompte(compteEp);
    cons->ajouterCompte(compteEp);
    cli2->ajouterCompte(compteLi);
    cons->ajouterCompte(compteLi);
    cout << "####Ajout de L'ARGENT!!!#####" << endl;

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
   ((CompteLigne *)compteLi)->consultationEnLigne();
    std::cout << "Interets : " << ((CompteEpargne *)compteEp)->calculInteret() << endl;

    cout<< endl  << "####Suppression d'un compte#####" << endl;
    cli1->afficherComptes();
    //compteEp->consulterOperations();
    delete compteEp;

    std::cout << "nb comptes" << cli1->getListeCompte().size() <<endl;
    cli1->afficherComptes();
    

    // TEST thread
    /*
    cout << endl << "####Fonctions TEST#####" << endl;
    OperationRecurrente test1 = OperationRecurrente("05/05/2023","Depot",100.0f,3,compteSt);
    std::cout << "Lance la pause" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1*1000));
    std::cout << "reprends le thread" << std::endl;
    test1.annulerRecurrence();
    compteSt->consulterSolde();*/

    cout << endl << "####Partie BDD#####" << endl;

    Db::create();
    Db::new_client(cli1.get());
    Db::new_client(cli2.get());
    Db::new_conseiller(cons.get());
    Db::new_conseiller(new Conseiller("Cottrel", "Yoan(mais mieux)", "St. Nazaire"));
    Db::new_conseiller(new Conseiller("Cottrel", "Yoan(mais pire)", "St. Nazaire"));
    cout << endl << "####Liste des conseillers#####" << endl;
    vector<Conseiller *> *consList=Db::get_Conseiller();
    for(int i=0;i<(int)consList->size();i++){
        cout << *(*consList)[i] <<endl;
    }

    cout << endl << "####Liste des clients#####" << endl;
    vector<Client *> * clientList=Db::get_Client();
    for(int i=0;i<(int)clientList->size();i++){
        cout << *(*clientList)[i] <<endl;
    }

    cout << endl << "####Juste le 1er client#####" << endl;
    Client * cliBdd1=Db::get_Client(1);
    cout << *cliBdd1<<endl;

    cout << endl << "####Emmanuel, ou es tu!?#####" << endl;
    vector<Client *> * cliBdd2=Db::get_Client("Rochet","Emmanuel");
    for(int i=0;i<(int)cliBdd2->size();i++){
        cout << *(*cliBdd2)[i] <<endl;
    }

    Db::reset();
    //afficheMenu();

/*
    cout<< endl  << "####Suppression d'un client#####" << endl;
    cons->afficherComptes();
    delete cli1.get();

    std::cout << "Post client supprime" << std::endl;
    cons->afficherComptes();
*/
    cout<< endl  << "####Suppression finale#####" << endl;
    //delete cli2;
    //delete cons;

    return 0;
}