#include "Db.h"

using namespace std;

char *zErrMsg = 0;


static sqlite3 * open(){
    sqlite3 *db;
    if(sqlite3_open("mydb.db",&db)){ cerr << "Erreur à l'ouverture de la BDD : " << zErrMsg << endl;
    }
    return db;
}

static int close(sqlite3 * db){
    sqlite3_close (db);
}

int ExecPreparedStatement(std::string sql, vector<std::string> * params){
    sqlite3 *db=open();
    sqlite3_stmt * stmt;

    if(sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr)){
        cout << "Erreur de prepared statement" << endl;
        close(db);
        return 1;
    } 

    if(params->size()>0){
        for(int i=1;i<=(int)params->size();i++){
            sqlite3_bind_text(stmt,i,(*params)[i-1].c_str(),strlen((*params)[i-1].c_str()),SQLITE_STATIC);
            cout <<(*params)[i-1].c_str();
        } 
    }
    sqlite3_step(stmt)
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    close(db);
}


vector<Personne *> *  ExecPreparedStatementReturnPersonnes(std::string sql, vector<std::string> * params){
    sqlite3 *db=open();
    sqlite3_stmt * stmt;

    if(sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr)){
        cout << "Erreur de prepared statement" << endl;
        close(db);
        return 1;
    } 

    if(params->size()>0){
        for(int i=1;i<=(int)params->size();i++){
            sqlite3_bind_text(stmt,i,(*params)[i-1].c_str(),strlen((*params)[i-1].c_str()),SQLITE_STATIC);
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
/*
vector<Compte *> *  ExecPreparedStatementReturnCompte(std::string sql, vector<std::string> * params){
    sqlite3 *db=open();
    sqlite3_stmt * stmt;

    if(sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr)){
        cout << "Erreur de prepared statement" << endl;
        close(db);
        return 1;
    } 

    if(params->size()>0){
        for(int i=1;i<=(int)params->size();i++){
            sqlite3_bind_text(stmt,i,(*params)[i-1].c_str(),strlen((*params)[i-1].c_str()),SQLITE_STATIC);
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
        return 1;
    } 

    if(params->size()>0){
        for(int i=1;i<=(int)params->size();i++){
            sqlite3_bind_text(stmt,i,(*params)[i-1].c_str(),strlen((*params)[i-1].c_str()),SQLITE_STATIC);
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


static int create(){
    string sql ="CREATE IF NOT EXISTS Client ("\
        "client_id INTEGER PRIMARY KEY,"\
        "nom TEXT NOT NULL,"\
        "prenom TEXT NOT NULL,"\
        "adresse TEXT NOT NUll)";
    sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);

    sql="CREATE IF NOT EXISTS Conseiller ("\
        "conseiller_id INTEGER PRIMARY KEY,"\
        "nom TEXT NOT NULL,"\
        "prenom TEXT NOT NULL,"\
        "adresse TEXT NOT NUll)";
    sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
    
    sql="CREATE IF NOT EXISTS Compte ("\
        "compte_id INTEGER PRIMARY KEY,"\
        "solde REAL NOT NULL,"\
        "client_id INTEGER NOT NULL,"\
        "conseiller_id INTEGER NOT NULL,"\
        "type TEXT NOT NULL)";
    sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);

    sql="CREATE IF NOT EXISTS Operation ("\
        "operation_id INTEGER PRIMARY KEY,"\
        "compte_id INTEGER NOT NULL,"\ 
        "date TEXT NOT NULL,"\
        "nom TEXT NOT NULL,"\
        "somme REAL NOT NULL,
        FOREIGN KEY(Compte_id) REFERENCES Compte(Compte_id))";
    sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
    return 0;

}
static int reset(){
    //string sql="DELETE FROM Clients; DELETE FROM Conseiller; DELETE FROM Compte; DELETE FROM Operations;"
    //sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
    drop();
    create();
    return 0;
}
static int drop(){
    string sql="DROP TABLE IF EXISTS Client; DROP TABLE IF EXISTS Conseiller; DROP TABLE IF EXISTS Compte; DROP TABLE IF EXISTS Operation;"
    sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
    return 0;
}

//Client
static int new_client(Client * c){
    string sql = "INSERT INTO Client(nom, prenom, adresse) VALUES(?,?,?)";
    vector<string> params;
    params.push_back(c->nom);
    params.push_back(c->prenom);
    params.push_back(c->adresse);

    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return 0;
}

static int delete_client(Client * c){
    string sql = "DELETE FROM Client WHERE nom = ? AND prenom = ? AND adresse = ?";
    vector<string> params;
    params.push_back(c->nom);
    params.push_back(c->prenom);
    params.push_back(c->adresse);

    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return 0;
}
static Client * get_Client(string nom, string prenom){
    string sql = "SELECT * FROM Client WHERE nom = ? AND prenom = ?";
    vector<string> params;
    params.push_back(c->nom);
    params.push_back(c->prenom);

    vector<Client *> * personne=ExecPreparedStatementReturnPersonnes(sql, &params);
    if(personne->size()>0){
       return personne[0];
    }else{
        return NULL;
    }
    
}
static Client * get_Client(int id){
    string sql = "SELECT * FROM Client WHERE client_id = ?";
    vector<string> params;
    params.push_back(id);
    vector<Client *> * personne=ExecPreparedStatementReturnPersonnes(sql, &params);
    if(personne->size()>0){
        return personne[0];
    }else{
        return NULL;
    }

}
static std::vector<Client *> get_Client(){
    string sql = "SELECT * FROM Client";
    sqlite3 *db=open();
    vector<Client *> * personne=ExecPreparedStatementReturnPersonnes(sql, &params);
    if(personne->size()>0){
        return personne[0];
    }else{
        return NULL;
    }
}

//Conseiller
static int new_conseiller(Conseiller * c){
    string sql = "INSERT INTO Conseiller(nom, prenom, adresse) VALUES(?,?,?)";
    vector<string> params;
    params.push_back(c->nom);
    params.push_back(c->prenom);
    params.push_back(c->adresse);

    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return 0;
}

static int delete_conseiller(Conseiller * c){
    string sql = "DELETE FROM Conseiller WHERE nom = ? AND prenom = ? AND adresse = ?";
    vector<string> params;
    params.push_back(c->nom);
    params.push_back(c->prenom);
    params.push_back(c->adresse);

    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return 0;
}

static Conseiller get_Conseiller(int id){
    string sql = "SELECT * FROM Conseiller WHERE conseiller_id = ?";
    vector<string> params;
    params.push_back(id);

    vector<Conseiller *> * personne=ExecPreparedStatementReturnPersonnes(sql, &params);
    if(personne->size()>0){
        return personne[0];
    }else{
        return NULL;
    }

}

static std::vector<Conseiller *> get_Conseiller(string nom, string prenom){    
    string sql = "SELECT * FROM Conseiller WHERE nom = ? AND prenom = ?";
    vector<string> params;
    params.push_back(c->nom);
    params.push_back(c->prenom);

    vector<Conseiller *> * personne=ExecPreparedStatementReturnPersonnes(sql, &params);
    if(personne->size()>0){
        return personne[0];
    }else{
        return NULL;
    }

}

static std::vector<Conseiller *> get_Conseiller(){
    string sql = "SELECT * FROM Conseiller";
    vector<Conseiller *> * personne=ExecPreparedStatementReturnPersonnes(sql, &params);
    if(personne->size()>0){
        return personne[0];
    }else{
        return NULL;
    }
}

//Compte
static int new_compte(Compte c){
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

static int delete_compte(Compte c){
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

//static int delete_compte(Client c); ?
static Compte getCompte(int ID){
    string sql ="SELECT * FROM Compte WHERE compte_id = ?";
    
    vector<string> params;
    params.push_back(I);
    
    if(ExecPreparedStatement(sql,params)){
        cout << " : " << zErrMsg << endl;
    }
    return NULL;
}

static std::vector<Compte*> getCompte(Client * c){
    vector<Comptes *> comptes;
    
    string sql = "SELECT (solde,client,conseiller,type) FROM Compte "\
    "INNER JOIN Client "\
    "WHERE Compte.client_id = Client.ID  AND Client.nom = ?, Client.prenom = ?, Client.adresse = ?";
    
    vector<string> params;
    params.push_back(c->nom);
    params.push_back(c->prenom);
    params.push_back(c->adresse);
    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return NULL;
}

static std::vector<Compte*> getCompte(Conseiller * c){
    string sql = "SELECT (solde,client,conseiller,type) FROM Compte "\
    "INNER JOIN Conseiller "\
    "WHERE Compte.client_id = Client.ID  AND Conseiller.nom = ?, Conseiller.prenom = ?, Conseiller.adresse = ?";
    
    vector<string> params;
    params.push_back(c->nom);
    params.push_back(c->prenom);
    params.push_back(c->adresse);
    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return NULL;
}

//Ope
static int new_ope(Operation o, int compte_ID){
    string sql = "INSERT INTO Operation(compte_id,date,nom,somme) VALUES(?,?,?,?)";
    vector<string> params;
    params.push_back(compte_ID);
    params.push_back(o->date);
    params.push_back(o->nom);
    params.push_back(o->somme);
    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return 0;
}
static int delete_ope(int id){
    string sql = "DELETE * FROM Operation WHERE operation_id = ? "
    
    vector<string> params;
    params.push_back(ID);
    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return 0;
}
/*
Détruit toutes les opération liées au compte
*/
static int delete_ope(int compte_id){
    
    string sql = "DELETE * FROM Operation WHERE compte_id = ?";
    vector<string> params;
    params.push_back(compte_id);
    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return NULL;
}

static Operation * get_ope(int operation_id){
   string sql = "SELECT * FROM Operation WHERE operation_id = ?";
    vector<string> params;
    params.push_back(operation_id);
    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    return NULL;
}

static std::vector<Operation *> get_ope(Compte c){
    
    string sql = "SELECT * FROM Operation INNER JOIN Compte WHERE Compte.compte_id = Operation.compte_id AND Compte.solde = ?, Compte.client_id= ?, Compte.comseiller_id = ?" ;
    vector<string> params;
    params.push_back(compte_id);
    if(ExecPreparedStatement(sql, &params)){
        cout << "Erreur a l'insertion : " << zErrMsg << endl;
    }
    get_ope(c->id)
    return NULL;
}   