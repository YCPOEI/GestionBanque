#include "compte.h"
#include "personne.h"

Operation::Operation(std::string date, std::string nom, float somme){
    this->date=date;
    this->nom=nom;
    this->somme=somme;
}

Operation::~Operation(){
    std::cout << "Operation supprimee" << std::endl;
}

std::ostream& operator<<(std::ostream& Str, Operation& oper){
    std::cout << "Date:[" << oper.getDate() <<"] Nom:[" << oper.getNom() << "] Somme:[" ;
    if(oper.getSomme()>=0){
        std::cout << "+";
    }
    return Str << std::fixed << std::setprecision(2) << oper.getSomme() << "]";
}


std::string Operation::getDate(){
    return this->date;
}

void Operation::setDate(std::string date){
    this->date=date;
}

std::string Operation::getNom(){
    return this->nom;

}

void Operation::setNom(std::string nom){
    this->nom=nom;

}

float Operation::getSomme(){
    return this->somme;
}

void Operation::setSomme(float somme){
    this->somme=somme;

}

std::string currentDateTime() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
 
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%m-%d-%Y", now);
    return buffer;
}

Client *  Compte::getClient(){
    return this->client;
}

Conseiller *  Compte::getConseiller(){
    return this->conseiller;
}

void Compte::setConseiller(Conseiller *  conseiller){
    this->conseiller=conseiller;
}


void Compte::deposer(float n) {
    this->solde += n;
    this->historique.push_back(Operation(currentDateTime(),"Depot",n));
}

void Compte::retirer(float n) {
    this->solde -= n;
    this->historique.push_back(Operation(currentDateTime(),"Retrait",-n));

}

float Compte::getSolde(){
    return solde;
}

float Compte::consulterSolde(void) {
    std::cout <<  "Votre solde est de " << std::fixed << std::setprecision(2) << solde << " Euros" << std::endl;
    return solde;
}

void Compte::consulterOperations(void) {
    std::cout << "Liste des operations : " << std::endl;
    for(size_t i=0;i<this->historique.size(); i++){
        std::cout << historique[i] << std::endl;
    }
}

void Compte::consulterDebits(void) {
    std::cout << "Liste des debits : " << std::endl;
    for(size_t i=0;i<this->historique.size(); i++){
        if(historique[i].getSomme()<0){std::cout <<historique[i] << std::endl;}
    }
}

void Compte::consulterCredits(void) {
    std::cout << "Liste des credits : " << std::endl;
    for(size_t i=0;i<this->historique.size(); i++){
        if(historique[i].getSomme()>0){std::cout << historique[i] << std::endl;}
    }
}


//Compte::Compte(Client client, Conseiller conseiller)


Compte::~Compte() {
    /*for(Operation op : historique){
        //std::cout << "Test : " << this->historique[i] <<std::endl;
        delete op.get();
        //this->historique.erase(historique.begin() + i);

    }*/
    historique.clear();
    this->client->Personne::supprimerCompte(this);
    if(this->conseiller !=NULL){
    this->conseiller->Personne::supprimerCompte(this);
    }
    std::cout << "Compte supprime" << std::endl;

}

std::ostream& operator<<(std::ostream& Str, Compte& compte){
    return Str << "Client:[" << compte.getClient() <<"] Conseiller:[" << compte.getConseiller() << "] Solde:["<< std::fixed << std::setprecision(2) << compte.getSolde() <<"]";
}

OperationRecurrente::OperationRecurrente(std::string date, std::string nom, float somme, int recurrence, Compte * compte):Operation(date,  nom, somme)
{   this->compte = compte;
    this->recur = recurrence;
    this->actif = true;
    this->count = 0;

    this->activerRecurrence();

    
}

void OperationRecurrente::recurrenceActive(void) {
    while (this->actif) {
        std::cout << "Opération recurrente : "; 
         if (this->nom == "Depot") {
            std::cout << "depot de ";
            this->compte->deposer(somme);
        } else if (this->nom == "Retrait") {
            std::cout << "retait de " ;
            this->compte->retirer(somme);
        }
        std::cout << somme << std::endl;
        this->count++;
        std::cout << " c'est l'opération n " << count << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(recur*1000));
       //usleep(recur * 1000000);
       
    }
}

void OperationRecurrente::activerRecurrence(void) {
    this->actif = true;
    std::thread t(&OperationRecurrente::recurrenceActive, this);
    //t.join();
    t.detach();

}

void OperationRecurrente::annulerRecurrence(void) {
    std::cout << "Annulation de la recurrence"<<std::endl;
    this->actif = false;
}

OperationRecurrente::~OperationRecurrente(){
    annulerRecurrence();
    std::cout << "Operation recurrente supprimee" << std::endl;
}