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

help :
	@echo "TODO ¯\_(ツ)_/¯"
