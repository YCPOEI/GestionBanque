#include <iostream>
#include "../headers/compte_ligne.h"

void CompteLigne::consultationEnLigne() {
    std::cout << "Consultation en ligne" << std::endl;
    this->consulterOperations();
}