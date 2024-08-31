//Title: Chemist.h
//Author: Jackson Keyser
//Date: 3/7/2022
//Description: This is part of the project 2 in CMSC 202 @ UMBC
// This is the non-pointer version header files


#include "Chemist.h"

Chemist::Chemist(){
    // Sets generic chemist name
    m_myName = "Chemist";
}

Chemist::Chemist(string name){
    // Sets chemist name to name given by the user
    m_myName = name;
}

string Chemist::GetName(){
    // Returns the name of the chemist to the user
    return m_myName;
}

void Chemist::SetName(string name){
    // Sets chemist name to name given by the user
    m_myName = name;
}

int Chemist::CheckSubstance(Substance theSubstance){
    // Loops through all substances
    for(int i = 0; i < PROJ2_SIZE; i++){
        // If the names match, the substance exists
        if(m_mySubstances[i].m_name == theSubstance.m_name){
            // Returns the index position in which the substance exists
            return i;
        }
    }
    // If the substance does not exist in the array
    return -1;
}

void Chemist::AddSubstance(Substance theSubstance, int index){
    // Used for filling in the chemist's subtances array
    m_mySubstances[index] = theSubstance;
}

void Chemist::IncrementQuantity(Substance theSubstance){
    // Loops through all substances in chemist's array
    for(int i = 0; i < PROJ2_SIZE; i++){
        // When the correct substance is found
        if(theSubstance.m_name == m_mySubstances[i].m_name){
            // Increments the substance by 1
            m_mySubstances[i].m_quantity = m_mySubstances[i].m_quantity + 1;
        }
    }
}

bool Chemist::DecrementQuantity(Substance theSubstance){
    // Loops through all substances in chemist's array
    for(int i = 0; i < PROJ2_SIZE; i++){
        // When the correct substance is found
        if(theSubstance.m_name == m_mySubstances[i].m_name){
            // Decrements the substance by 1
            m_mySubstances[i].m_quantity = m_mySubstances[i].m_quantity - 1;
            return true;
        }
    }
    // If no decrementing took place
    return false;
}

bool Chemist::CheckQuantity(Substance substanceOne, Substance substanceTwo){
    // Declares and initializes two integer variables for storing the quantity of each substance
    int substanceOneQuantity = 0;
    int substanceTwoQuantity = 0;

    // Loops through all of chemist's substances
    for(int i = 0; i < PROJ2_SIZE; i++){
        // If the first substance is found
        if(substanceOne.m_name == m_mySubstances[i].m_name){
            // Stores the quantity of the substance into a variable
            substanceOneQuantity = m_mySubstances[i].m_quantity;
        }
        // If the second substance is found
        if(substanceTwo.m_name == m_mySubstances[i].m_name){
            // Stores the quantity of the substance into a variable
            substanceTwoQuantity = m_mySubstances[i].m_quantity;
        }
    }

    // If there is at lesst 1 of each substance
    if(substanceOneQuantity != 0 && substanceTwoQuantity != 0){
        return true;
    // If at least 1 of the 2 substances is 0
    }else{
        return false;
    }
}

Substance Chemist::GetSubstance(int substanceIndex){
    // Declares and initializes a substance structure at the index the user wants
    Substance substanceWanted = m_mySubstances[substanceIndex];
    return substanceWanted;
}

int Chemist::GetTotalSubstances(){
    // Declares and initializes an int variable for keeping track the amount of subtances where there is at least 1 of
    int counter = 0;

    // Loops through all substances
    for(int i = 0; i < PROJ2_SIZE; i++){
        // If there is at least 1 of this substance
        if(m_mySubstances[i].m_quantity > 0){
            // Increments counter by 1
            counter = counter + 1;
        }
    }
    return counter;
}