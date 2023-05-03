#include "personne.h"

Personne::Personne(std::string nom,std::string prenom,std::string adresse){
    this->nom=nom;
    this->prenom=prenom;
    this->adresse=adresse;
}

std::string Personne::getNom(){
    return this->nom;
}

void Personne::setNom(std::string nom){
    this->nom=nom;
}

std::string Personne::getPrenom(){
    return this->prenom;
}

void Personne::setPrenom(std::string prenom){
    this->prenom=prenom;
}

std::string Personne::getAdresse(){
    return this->adresse;
}

void Personne::setAdresse(std::string adresse){
    this->adresse=adresse;
}

std::vector<Compte*> Personne::getListeCompte(){
    return this->liste_compte;
}

void Personne::ajouterCompte(Compte* compte){
    this->liste_compte.push_back(compte);
}


void Personne::afficherComptes(){
    for(Compte *c:this->liste_compte)
    {
        std::cout << *c << std::endl;
        //std::cout << "operations : ";
        //c->consulterOperations();
        //std::cout << std::endl;
    }
}

void Personne::supprimerCompte(Compte * compte){
    for (size_t i=0;i<liste_compte.size();i++){
        if(liste_compte[i]==compte){
            liste_compte[i]=nullptr;
            //std::cout << "Pointertodelete: " << this->liste_compte[i] << std::endl;
            liste_compte.erase(liste_compte.begin() +i);
            break;
        }
    }
}

std::ostream& operator<<(std::ostream& Str, Personne& personne){
    return Str << "Nom:[" << personne.getNom() <<"] Prenom:[" << personne.getPrenom() << "] Adresse:[" << personne.getAdresse() << "]";
}

/*
    PARTIE CLIENT
*/

Client::~Client(){
    for (Compte* cpt : liste_compte){
        delete cpt;
    }
    liste_compte.clear();

    std::cout << "Client supprime" << std::endl;
}


void Client::supprimerCompte(int index){
    delete this->liste_compte[index];
    this->liste_compte.erase(liste_compte.begin() + index);
}

/*
    PARTIE CONSEILLER
*/

Conseiller::~Conseiller(){
    for (size_t i=0;i<liste_compte.size();i++){
        liste_compte[i]->setConseiller(NULL);
    }
    std::cout << "Conseiller supprime" << std::endl;
}

void Conseiller::supprimerCompte(int index){
    this->liste_compte.erase(liste_compte.begin() + index);
}
//void Conseiller::supprimerCompte(int index){
 //   this->liste_compte.erase(liste_compte.begin() + index,liste_compte.begin() + index);

