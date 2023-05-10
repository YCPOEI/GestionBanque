#include "Db.h"

using namespace std;

char *zErrMsg = 0;


 sqlite3 * Db::open(){
    sqlite3 *db;
    if(sqlite3_open("mydb.db",&db)){ cerr << "Erreur à l'ouverture de la BDD : " << zErrMsg << endl;
    }
    return db;
}

 int Db::close(sqlite3 * db){
    sqlite3_close (db);
    return 0;
}

int ExecPreparedStatement(std::string sql, vector<std::string> * params){
    sqlite3 *db=Db::open();
    sqlite3_stmt * stmt;

    if(sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr)){
        cout << "Erreur de prepared statement" << endl;
        Db::close(db);
        return 1;
    } 

    if(params->size()>0){
        for(int i=1;i<=(int)params->size();i++){
            sqlite3_bind_text(stmt,i,(*params)[i-1].c_str(),strlen((*params)[i-1].c_str()),SQLITE_TRANSIENT);
        } 
    }
    sqlite3_step(stmt);
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    Db::close(db);
    return 0;
}


vector<Personne *> *  ExecPreparedStatementReturnPersonnes(std::string sql, vector<std::string> * params){
    sqlite3 *db=Db::open();
    sqlite3_stmt * stmt;

    if(sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr)){
        cout << "Erreur de prepared statement" << endl;
        Db::close(db);
        return NULL;
    } 

    if(params->size()>0){
        for(int i=1;i<=(int)params->size();i++){
            sqlite3_bind_text(stmt,i,(*params)[i-1].c_str(),strlen((*params)[i-1].c_str()),SQLITE_TRANSIENT);
        } 
    }
    vector<Personne *> *personnes = new vector<Personne *>();
    while(sqlite3_step(stmt)!=SQLITE_DONE){
        personnes->push_back(new Personne(string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))),string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))),string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)))));
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    Db::close(db);
    return personnes;
}
/*
vector<Compte *> *  ExecPreparedStatementReturnCompte(std::string sql, vector<std::string> * params){
    sqlite3 *db=open();
    sqlite3_stmt * stmt;

    if(sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr)){
        cout << "Erreur de prepared statement" << endl;
        close(db);
        return NULL;
    } 

    if(params->size()>0){
        for(int i=1;i<=(int)params->size();i++){
            sqlite3_bind_text(stmt,i,(*params)[i-1].c_str(),strlen((*params)[i-1].c_str()),SQLITE_);
            cout <<(*params)[i-1].c_str();
        } 
    }
    vector<Personne *> personnes;
    while(sqlite3_step(stmt)!=SQLITE_DONE){
        personnes.push_back(new Personne(sqlite3_column_text(stmt, 1),sqlite3_column_text(stmt, 2),sqlite3_column_text(stmt, 3)));
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    close(db);
    return 
}

vector<Operation *> *  ExecPreparedStatementReturnOperation(std::string sql, vector<std::string> * params){
    sqlite3 *db=open();
    sqlite3_stmt * stmt;

    if(sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr)){
        cout << "Erreur de prepared statement" << endl;
        close(db);
        return NULL;
    } 

    if(params->size()>0){
        for(int i=1;i<=(int)params->size();i++){
            sqlite3_bind_text(stmt,i,(*params)[i-1].c_str(),strlen((*params)[i-1].c_str()),SQLITE_);
            cout <<(*params)[i-1].c_str();
        } 
    }
    vector<Personne *> personnes;
    while(sqlite3_step(stmt)!=SQLITE_DONE){
        personnes.push_back(new Personne(sqlite3_column_text(stmt, 1),sqlite3_column_text(stmt, 2),sqlite3_column_text(stmt, 3)));
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    close(db);
    return 
}*/


 int Db::create(){
    sqlite3 *db=open();
    string sql ="CREATE TABLE IF NOT EXISTS Client (" \
        "client_id INTEGER PRIMARY KEY," \
        "nom TEXT NOT NULL," \
        "prenom TEXT NOT NULL," \
        "adresse TEXT NOT NUll)";
    sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);

    sql="CREATE TABLE IF NOT EXISTS Conseiller (" \
        "conseiller_id INTEGER PRIMARY KEY," \
        "nom TEXT NOT NULL," \
        "prenom TEXT NOT NULL," \
        "adresse TEXT NOT NUll)";
    sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
    
    sql="CREATE TABLE IF NOT EXISTS Compte (" \
        "compte_id INTEGER PRIMARY KEY," \
        "solde REAL NOT NULL," \
        "client_id INTEGER NOT NULL," \
        "conseiller_id INTEGER NOT NULL," \
        "type TEXT NOT NULL)";
    sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);

    sql="CREATE TABLE IF NOT EXISTS Operation (" \
        "operation_id INTEGER PRIMARY KEY," \
        "compte_id INTEGER NOT NULL," \
        "date TEXT NOT NULL," \
        "nom TEXT NOT NULL," \
        "somme REAL NOT NULL," \
        "FOREIGN KEY(Compte_id) REFERENCES Compte(Compte_id))";
    sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
    close(db);
    return 0;
}

 int Db::drop(){
    sqlite3 *db=open();
    string sql="DROP TABLE IF EXISTS Client; DROP TABLE IF EXISTS Conseiller; DROP TABLE IF EXISTS Compte; DROP TABLE IF EXISTS Operation;";
    sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
    close(db);
    return 0;
}

 int Db::reset(){
    //string sql="DELETE FROM Clients; DELETE FROM Conseiller; DELETE FROM Compte; DELETE FROM Operations;"
    //sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
    drop();
    create();
    return 0;
}

//Client
 int Db::new_client(Client * c){
    string sql = "INSERT INTO Client(nom, prenom, adresse) VALUES(?,?,?)";
    vector<string> params;
    params.push_back(c->getNom());
    params.push_back(c->getPrenom());
    params.push_back(c->getAdresse());

    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return 0;
}

 int Db::delete_client(Client * c){
    string sql = "DELETE FROM Client WHERE nom = ? AND prenom = ? AND adresse = ?";
    vector<string> params;
    params.push_back(c->getNom());
    params.push_back(c->getPrenom());
    params.push_back(c->getAdresse());

    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return 0;
}
 vector<Client *> * Db::get_Client(string nom, string prenom){
    string sql = "SELECT * FROM Client WHERE nom = ? AND prenom = ?";
    vector<string> params;
    params.push_back(nom);
    params.push_back(prenom);

    vector<Personne *> * personne=ExecPreparedStatementReturnPersonnes(sql, &params);
    return (vector<Client *>*)personne;
    
}
 Client * Db::get_Client(int id){
    string sql = "SELECT * FROM Client WHERE client_id = ?";
    vector<string> params;
    params.push_back(to_string(id));
    vector<Personne *> * personne=ExecPreparedStatementReturnPersonnes(sql, &params);
    if(personne->size()>0){
        return (Client *)((*personne)[0]);
    }else{
        return NULL;
    }

}
 std::vector<Client *> *  Db::get_Client(){
    string sql = "SELECT * FROM Client";
    vector<string> params;
    vector<Personne *> * personne=ExecPreparedStatementReturnPersonnes(sql, &params);
    return (vector<Client *>*)personne;
}

//Conseiller
 int Db::new_conseiller(Conseiller * c){
    string sql = "INSERT INTO Conseiller(nom, prenom, adresse) VALUES(?,?,?)";
    vector<string> params;
    params.push_back(c->getNom());
    params.push_back(c->getPrenom());
    params.push_back(c->getAdresse());

    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return 0;
}

int Db::delete_conseiller(Conseiller * c){
    string sql = "DELETE FROM Conseiller WHERE nom = ? AND prenom = ? AND adresse = ?";
    vector<string> params;
    params.push_back(c->getNom());
    params.push_back(c->getPrenom());
    params.push_back(c->getAdresse());

    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return 0;
}

Conseiller * Db::get_Conseiller(int id){
    string sql = "SELECT * FROM Conseiller WHERE conseiller_id = ?";
    vector<string> params;
    params.push_back(to_string(id));

    vector<Personne *> * personne=ExecPreparedStatementReturnPersonnes(sql, &params);
    if(personne->size()>0){
        return (Conseiller *)((*personne)[0]);
    }else{
        return NULL;
    }

}

std::vector<Conseiller *> * Db::get_Conseiller(string nom, string prenom){    
    string sql = "SELECT * FROM Conseiller WHERE nom = ? AND prenom = ?";
    vector<string> params;
    params.push_back(nom);
    params.push_back(prenom);

    vector<Personne *> * personne=ExecPreparedStatementReturnPersonnes(sql, &params);
    return (vector<Conseiller *>*)personne;

}

std::vector<Conseiller *> * Db::get_Conseiller(){
    string sql = "SELECT * FROM Conseiller";
    vector<string> params;
    vector<Personne *> * personne=ExecPreparedStatementReturnPersonnes(sql, &params);
    return (vector<Conseiller *>*)personne;
}
/*
//Compte
 int new_compte(Compte c){
    string sql = "INSERT INTO Compte(solde, client,conseiller,type) VALUES(?,?,?,?)";

    vector<string> params;
    params.push_back(c->solde);
    params.push_back(c->client);
    params.push_back(c->conseiller);
    params.push_back(c->type);
    
    if(ExecPreparedStatement(sql,params)){
        cout << " : " << zErrMsg << endl;
    } return 0;
}

 int delete_compte(Compte c){
    string sql = "DELETE FROM Compte WHERE solde = ?, client = ?, Conseiller = ?, type = ? ";
    
    vector<string> params;
    params.push_back(c->solde);
    params.push_back(c->client);
    params.push_back(c->conseiller);
    params.push_back(c->type);
    
    if(ExecPreparedStatement(sql,params)){
        cout << " : " << zErrMsg << endl;
    }
    return 0;
}

// int delete_compte(Client c); ?
 Compte getCompte(int ID){
    string sql ="SELECT * FROM Compte WHERE compte_id = ?";
    
    vector<string> params;
    params.push_back(I);
    
    if(ExecPreparedStatement(sql,params)){
        cout << " : " << zErrMsg << endl;
    }
    return NULL;
}

 std::vector<Compte*> getCompte(Client * c){
    vector<Comptes *> comptes;
    
    string sql = "SELECT (solde,client,conseiller,type) FROM Compte " \
    "INNER JOIN Client " \
    "WHERE Compte.client_id = Client.ID  AND Client.nom = ?, Client.prenom = ?, Client.adresse = ?";
    
    vector<string> params;
    params.push_back(c->getNom());
    params.push_back(c->getPrenom());
    params.push_back(c->getAdresse());
    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return NULL;
}

 std::vector<Compte*> getCompte(Conseiller * c){
    string sql = "SELECT (solde,client,conseiller,type) FROM Compte " \
    "INNER JOIN Conseiller " \
    "WHERE Compte.client_id = Client.ID  AND Conseiller.nom = ?, Conseiller.prenom = ?, Conseiller.adresse = ?";
    
    vector<string> params;
    params.push_back(c->getNom());
    params.push_back(c->getPrenom());
    params.push_back(c->getAdresse());
    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return NULL;
}

//Ope
 int new_ope(Operation o, int compte_ID){
    string sql = "INSERT INTO Operation(compte_id,date,nom,somme) VALUES(?,?,?,?)";
    vector<string> params;
    params.push_back(compte_ID);
    params.push_back(o->getDate());
    params.push_back(o->getNom());
    params.push_back(o->getSomme());
    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return 0;
}
 int delete_ope(int id){
    string sql = "DELETE * FROM Operation WHERE operation_id = ? "
    
    vector<string> params;
    params.push_back(ID);
    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return 0;
}

//Détruit toutes les opération liées au compte

 int delete_ope(int compte_id){
    
    string sql = "DELETE * FROM Operation WHERE compte_id = ?";
    vector<string> params;
    params.push_back(compte_id);
    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return NULL;
}

 Operation * get_ope(int operation_id){
   string sql = "SELECT * FROM Operation WHERE operation_id = ?";
    vector<string> params;
    params.push_back(operation_id);
    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return NULL;
}

 std::vector<Operation *> get_ope(Compte c){
    
    string sql = "SELECT * FROM Operation INNER JOIN Compte WHERE Compte.compte_id = Operation.compte_id AND Compte.solde = ?, Compte.client_id= ?, Compte.comseiller_id = ?" ;
    vector<string> params;
    params.push_back(compte_id);
    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    get_ope(c->id)
    return NULL;
}   */