.PHONY = all reset build clean help

#Variables
include .env

all : reset build clean

build : $(BLD)main.exe 

#Targets
$(BLD)main.exe : $(OBJ)main.o $(patsubst $(SRC)%.cpp, $(OBJ)%.o, $(wildcard $(SRC)*.cpp))
	@echo "Building executable"
	@mkdir -p $(BLD)
	@$(CPPC) $(CFLAGS) $^ -o $@

$(OBJ)main.o : main.cpp
	@echo "Compiling $@"
	@mkdir -p $(OBJ)
	@$(CPPC) $(CFLAGS) -c $^ -o $@ -I $(HDR)

$(OBJ)%.o : $(SRC)%.cpp
	@echo "Compiling $@"
	@mkdir -p $(OBJ)
	@$(CPPC) $(CFLAGS) -c $^ -o $@ -I $(HDR)

clean :
	@echo "Cleaning project"
	@rm -rf $(OBJ) *.o

reset : 
	@echo "Rebuilding project"
	@rm -rf $(BLD) *.exe

lib:
	@echo "Compilation de la librairie"
	@g++ -Wall -Wextra -shared -o Db.o src/Db.cpp -I Db.h

	@echo "Comression de la librairie"
	@ar -rsc Db.a Db.o
	
	@echo "rajout de la librairie dans le build"
	@mv Db.a /build/Db.a
	
	@echo "Nettoyage du dossier"
	@rm *.o

	@echo "Librairie Compilée" 

help :
	@echo "all   : Reset, build, clean"
	@echo "reset : Supprime l'executable"
	@echo "build : Créé l'executable"
	@echo "clean : Supprime les .o"
	@echo "lib   : Compile la base de données sous forme d'une librairie "
	@echo "help  : Affiche cette aide"
