#include "menu.h"

std::string currentDateTime2() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
 
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%m-%d-%Y", now);
    return buffer;
}

int chooseMenuOption(std::string strChoice){
    try{
        int intChoice=stoi(strChoice);
        if(intChoice<1){
            throw 404;
        }
        return intChoice;
    }catch(...){
        cout << "Valeur Incorrecte" << endl;
        return 0;
    }
}

int verifClientConseillerExistent(std::vector<Client*> clients,std::vector<Conseiller*> conseillers){
    if((int)clients.size()==0){
        cout << "Il faudrait d'abord avoir des clients pour avoir des comptes" <<endl;
        return 0;
    }
    if((int)conseillers.size()==0){
        cout << "Il faudrait d'abord avoir un conseiller pour avoir des comptes" <<endl;
        return 0;
    }

    return 1;
}

Compte * ChoisirCompteDansListe(std::vector<Client*> clients){
    int nbChoix=1;
    cout<< "Liste des comptes:" << endl;
    for(int i=0;i<(int)clients.size();i++){
        for(int j=0;j<(int)clients[i]->getListeCompte().size();j++){
            cout << nbChoix << " : " << clients[i]->getListeCompte()[j]<<endl;
            nbChoix++;
        }
    }
    
    cout << "choisissez un compte" <<endl;
    std::string choix;
    cin >> choix;
    int intChoix=chooseMenuOption(choix);
    if(intChoix<nbChoix&&intChoix!=0){
        nbChoix=1;
        for(int i=0;i<(int)clients.size();i++){
            for(int j=0;j<(int)clients[i]->getListeCompte().size();j++){
                if(nbChoix==intChoix){
                    return clients[i]->getListeCompte()[j];
                }
            }
        }
        return NULL;
    }else{
        cout << "Valeur Incorrecte" << endl;
        return NULL;
    }
}


void afficheMenu(){
    int posInMenu=0;
    SP<std::vector<Client*>> clients=SP<std::vector<Client*>>(new std::vector<Client*>);
    SP<std::vector<Conseiller*>> conseillers=SP<std::vector<Conseiller*>>(new std::vector<Conseiller*>);
    //std::vector<SP<Conseiller>*> conseillers;
    while (posInMenu<10){
        if(posInMenu==0){
            cout << "_____________________" <<endl;
            cout<< "Choisir une operation:" << endl;
            cout << "_____________________" <<endl;
            cout<< "1 : Consulter Clients" << endl;
            cout<< "2 : Consulter Conseillers" << endl;
            cout<< "3 : Consulter Comptes d'une personne" << endl;
            cout<< "4 : Consulter Operations d'un compte" << endl;
            cout<< "5 : Ajouter Client" << endl;
            cout<< "6 : Ajouter Conseiller" << endl;
            cout<< "7 : Ajouter Compte" << endl;
            cout<< "8 : Lier Conseiller a un compte" << endl;
            cout<< "9 : Effectuer Operation" << endl;
            cout<< "10 : Supprimer Compte" << endl;
            cout<< ">=11 : Quitter" << endl;
            std::string choice;
            cin >> choice ;
            posInMenu=chooseMenuOption(choice);
        }else if(posInMenu==1){
            cout << "_____________________" <<endl;
            cout<< "Consulter Clients:" << endl;
            cout << "_____________________" <<endl;
            if((int)clients.get()->size()>0){
                for(int i=0;i<(int)clients.get()->size();i++){
                    cout << &(clients.get()[i]) <<endl;
                }
            }else{
                cout<< "Il n'y a aucun client!" << endl;
            }
            posInMenu=0;
        }else if(posInMenu==2){
            cout << "_____________________" <<endl;
            cout<< "Consulter Conseillers:" << endl;
            cout << "_____________________" <<endl;
            if((int)conseillers.get()->size()>0){
                for(int i=0;i<(int)conseillers.get()->size();i++){
                    cout << &(conseillers.get()[i]) <<endl;
                }
            }else{
                cout<< "Il n'y a aucun conseiller!" << endl;
            }
            posInMenu=0;
        }else if(posInMenu==3){
            cout << "_____________________" <<endl;
            cout<< "Consulter Comptes d'une personne:" << endl;
            cout << "_____________________" <<endl;
            cout<< "Liste des personnes:" << endl;
            int nbChoix=1;
            int preConditions=verifClientConseillerExistent(*clients.get(),*conseillers.get());
            if(preConditions!=0){
                cout<<"Liste des clients:"<<endl;
                for(int i=0;i<(int)clients.get()->size();i++){
                    cout << nbChoix << " : " << &(clients.get()[i])<<endl;
                    nbChoix++;
                }
            
                cout<<"Liste des conseillers:"<<endl;
                for(int i=0;i<(int)conseillers.get()->size();i++){
                    cout << nbChoix << " : " << &(conseillers.get()[i])<<endl;
                    nbChoix++;
                }
            
                cout<< "Choisir une personne:" << endl;
                std::string choix;
                int intChoix;
                cin >> choix;
                intChoix=chooseMenuOption(choix);
                if(intChoix>(int)clients.get()->size()+(int)conseillers.get()->size()){
                    cout << "Valeur Incorrecte" <<endl;
                }else{
                    if(intChoix>(int)clients.get()->size()){
                        cout<< "Liste des comptes de " << (*conseillers.get())[intChoix-(int)clients.get()->size()-1]->getNom() << (*conseillers.get())[intChoix-(int)clients.get()->size()-1]->getPrenom() << " : " << endl;
                        (*conseillers.get())[intChoix-(int)clients.get()->size()-1]->getListeCompte().size();
                        (*conseillers.get())[intChoix-(int)clients.get()->size()-1]->afficherComptes();
                    }else{
                        cout<< "Liste des comptes de " <<(*clients.get())[intChoix-1]->getNom() << (*clients.get())[intChoix-1]->getPrenom() << " : " << endl;
                        (*clients.get())[intChoix-1]->afficherComptes();
                    }
                }
            }
            posInMenu=0;

            
        }else if(posInMenu==4){
            cout << "_____________________" <<endl;
            cout<< "Consulter Operations d'un compte:" << endl;
            cout << "_____________________" <<endl;

            
            if((int)clients.get()->size()==0){
                cout << "Il faudrait d'abord avoir des clients pour avoir des comptes" <<endl;
            }else{
                ChoisirCompteDansListe(*clients.get())->consulterOperations();
            }
            
            posInMenu=0;
        }else if(posInMenu==5){
            cout << "_____________________" <<endl;
            cout << "Ajout d'un client" <<endl;
            cout << "_____________________" <<endl;
            cout << "Entrez le nom du client" <<endl;
            std::string cliNom;
            cin >> cliNom ;
            cout << "Entrez le prenom du client" <<endl;
            std::string cliPrenom;
            cin >> cliPrenom ;
            cout << "Entrez l'adresse du client" <<endl;
            std::string cliAdr;
            cin >> cliAdr ;
            clients.get()->push_back(new Client(cliNom,cliPrenom,cliAdr));
            std::cout << "Client cree: " << endl;
            posInMenu=0;
        }else if(posInMenu==6){
            cout << "_____________________" <<endl;
            cout << "Ajout d'un conseiller" <<endl;
            cout << "_____________________" <<endl;
            cout << "Entrez le nom du conseiller" <<endl;
            std::string consNom;
            cin >> consNom ;
            cout << "Entrez le prenom du client" <<endl;
            std::string consPrenom;
            cin >> consPrenom ;
            cout << "Entrez l'adresse du client" <<endl;
            std::string consAdr;
            cin >> consAdr ;
            Conseiller *cons = new Conseiller(consNom,consPrenom,consAdr);
            conseillers->push_back(cons);
            std::cout << "Conseiller cree: " << endl;
            posInMenu=0;
        }else if(posInMenu==7){
            cout << "_____________________" <<endl;
            cout<< "Ajout d'un compte:" << endl;
            cout << "_____________________" <<endl;
            
            int preConditions=verifClientConseillerExistent(*clients.get(),*conseillers.get()); //verifie si on peux bien creer un compte
            
            if(preConditions>0){
                std::string choix;
                cout << "Liste des clients:" <<endl;
                for(int i=0;i<(int)clients.get()->size();i++){
                    cout << i+1 << " : " << &(clients.get()[i])<<endl;
                }
                cout << "Choisissez un client" <<endl;
                cin >> choix;
                int intChoixCli=chooseMenuOption(choix);
                if(intChoixCli==0||intChoixCli>(int)clients.get()->size()){
                    std::cout << "Valeur Incorrecte";
                    preConditions=0;
                }
                
            
                cout << "Liste des conseillers:" <<endl;
                for(int i=0;i<(int)conseillers.get()->size();i++){
                    cout << i+1 << " : " << &(clients.get()[i])<<endl;
                }
                cout << "Choisissez un conseiller" <<endl;
                cin >> choix;
                int intChoixCons=chooseMenuOption(choix);
                if(intChoixCons==0||intChoixCons>(int)conseillers.get()->size()){
                    std::cout << "Valeur Incorrecte";
                    preConditions=0;
                }

                if(preConditions>0){
                    Compte * compteSt = (Compte *) new CompteStandard((*clients.get())[intChoixCli-1], (*conseillers.get())[intChoixCons-1]);
                    std::cout << "Compte cree: " << &compteSt  << endl;
                }
            }
            posInMenu=0;
        }else if(posInMenu==8){
            cout << "_____________________" <<endl;
            cout<< "Lier le conseiller a un compte:" << endl;
            cout << "_____________________" <<endl;
            
            int preConditions=verifClientConseillerExistent(*clients.get(),*conseillers.get());
            if(preConditions>0){
                cout << "Liste des conseillers:" << endl;
                for(int i=0;i<(int)conseillers.get()->size();i++){
                    cout << i+1 << " : " << &conseillers.get()[i];
                }
                cout << "Choisissez un conseiller:" << endl;
                std::string choix;
                cin >> choix;
                int intChoixCons=chooseMenuOption(choix);
                if(intChoixCons<(int)conseillers.get()->size()&&intChoixCons!=0){
                    Compte * cpt = ChoisirCompteDansListe(*clients.get());
                    if(cpt->getConseiller()!=NULL){
                       for(int i=0;i<(int)cpt->getConseiller()->getListeCompte().size();i++){
                            if(cpt==cpt->getConseiller()->getListeCompte()[i]){
                                cpt->getConseiller()->supprimerCompte(i);
                                break;
                            }
                       }
                    }
                    cpt->setConseiller((*conseillers.get())[intChoixCons-1]);
                    (*conseillers.get())[intChoixCons-1]->ajouterCompte(cpt);
                    cout << "Le changement de conseiller a bien ete effectue" << endl;
                }else{
                    cout << "Valeur Incorrecte" << endl;
                }
            }
            

            posInMenu=0;
        }else if(posInMenu==9){
            cout << "_____________________" <<endl;
            cout<< "Effectuer une operation sur un compte:" << endl;
            cout << "_____________________" <<endl;
            
                int preConditions=verifClientConseillerExistent(*clients.get(),*conseillers.get());
                    if(preConditions>0){
                    Compte * cpt = ChoisirCompteDansListe(*clients.get());
                    cout << "Entrez le montant de la transaction (negatif pour retrait):" << endl;
                    std::string choixMontant;
                    cin >> choixMontant;
                    float floatChoixOpe=0.0f;
                    try{
                        floatChoixOpe=stof(choixMontant);
                    }catch(...){
                        cout << "Valeur Incorrecte" << endl;
                    }
                    if(floatChoixOpe!=0.0f){
                        cout << "Type d'operation:" << endl;
                        cout << "1-Virement direct" << endl;
                        cout << "2-Operation recurrente" << endl;
                        std::string choixType;
                        cin >> choixType;
                        int intChoixOpe=chooseMenuOption(choixType);
                        if(intChoixOpe>0&&intChoixOpe<3){
                            if(intChoixOpe==1){
                                if(floatChoixOpe>0){
                                    cpt->deposer(floatChoixOpe);
                                }else{
                                    cpt->retirer(-floatChoixOpe);
                                }
                                cout << "La transaction a bien ete effectuee" << endl;
                            }
                            if(intChoixOpe==2){
                                cout << "Indiquez le temps entre chaque operation (secondes) :" << endl;
                                std::string choixRec;
                                cin >> choixRec;
                                int intChoixRec=chooseMenuOption(choixRec);
                                if(intChoixRec>0){
                                    if(floatChoixOpe>0){
                                        OperationRecurrente(currentDateTime2(),"Depot",floatChoixOpe,intChoixRec,cpt);
                                    }else{
                                        OperationRecurrente(currentDateTime2(),"Retrait",floatChoixOpe,intChoixRec,cpt);
                                    }
                                }else{
                                    cout << "Les valeurs rentrees sont incorrectes, operation annulee" <<endl;
                                }
                            }
                        }else{
                            cout << "Valeur Incorrecte" <<endl;
                        }
                        
                    }
                }
            

            posInMenu=0;
        }else if(posInMenu==10){
            cout << "_____________________" <<endl;
            cout<< "Supprimer un compte:" << endl;
            cout << "_____________________" <<endl;
            
            int preConditions=verifClientConseillerExistent(*clients.get(),*conseillers.get());
            if(preConditions>0){
                Compte * cpt = ChoisirCompteDansListe(*clients.get());
                delete cpt;
            }

            posInMenu=0;
        }
    }

}
