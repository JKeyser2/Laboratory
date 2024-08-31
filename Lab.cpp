//Title: Chemist.h
//Author: Jackson Keyser
//Date: 3/7/2022
//Description: This is part of the project 2 in CMSC 202 @ UMBC
// This is the non-pointer version header files


#include "Lab.h"

Lab::Lab(){
    
}

void Lab::LoadSubstances(){

    // Declares string variables for storing the information from the txt file
    string name, type, formula, substance1, substance2;
    // Declares and initializes an int variable for storing the quantity of each substance
    int quantity = 0;
    // Declares and initializes an int variable for storing the index position of the chemist array
    int index = 0;


    ifstream infile(PROJ2_DATA);

    // If the file opened successfully
    if(infile.is_open()){
        // Loops thtough all of the substances
        for(int i = 0; i < PROJ2_SIZE; i++){
            getline(infile, name, DELIMETER);
            getline(infile, type, DELIMETER);
            getline(infile, formula, DELIMETER);
            getline(infile, substance1, DELIMETER);
            getline(infile, substance2);
            quantity = 0;

            // Stores each substance into the array of substance structures
            m_substances[i] = Substance(name, type, formula, substance1, substance2, quantity);

            // Declares a substance structure
            Substance theSubstance = Substance(name, type, formula, substance1, substance2, quantity);

            // Puts substance structure in the chemist's array with its index
            m_myChemist.AddSubstance(theSubstance, index);
            // Increments index by 1
            index++;
        }
        // Lets the user know that the substances loaded in
        cout << PROJ2_SIZE << " substances loaded" << endl;
    // If the file was unable to be opened
    }else{
        cout << "The file cannot be opened" << endl;
    }
}

void Lab::StartLab(){
    // Displays the title of the game
    LabTitle();
    // Loads all of the substances from the txt file
    LoadSubstances();

    // Declares and initializes string variable for storing the name of the chemist
    string chemistName = "";

    cout << "What is the name of your Chemist?" << endl;
    // Allows for the user to enter a title with spaces
    getline(cin, chemistName);
    // Sets the chemist name to the name given by the user
    m_myChemist.SetName(chemistName);

    // Declares and initializes int variable for storing user choice
    int userInput = 0;
    // Declares and initializes bool variable for when the user quits out of the game
    bool userQuit = FALSE_STRING;

    do{
        userInput = MainMenu();

        if(userInput == OPTION_ONE){
            DisplaySubstances();
        }
        if(userInput == OPTION_TWO){
            SearchSubstances();
        }
        if(userInput == OPTION_THREE){
            CombineSubstances();
        }
        if(userInput == OPTION_FOUR){
            CalcScore();
        }
        if(userInput == OPTION_FIVE){
            // Sets userQuit boolean to true. Program will end
            userQuit = TRUE_STRING;
        }

    // Keeps displaying the menu of options until the user quits out of the game
    }while(userQuit == FALSE_STRING);

    
}

void Lab::DisplaySubstances(){
    // Declare and initialize a counter variable for finding out how many substances the chemist has at least 1 of
    int counter = 0;
    // Declare and initialize another counter variable for numbering all of the substances
    int counter2 = 1;
    // Declare and inialize a structure temporary variable for storing each substance from the chemist's array
    Substance theSubstance;
    // Loops through all of the substances
    for(int i = 0; i < PROJ2_SIZE; i++){
        // Gets the substance from the chemist's array at this index
        theSubstance = m_myChemist.GetSubstance(i);
        // If the chemist has this substance
        if(theSubstance.m_quantity != 0){
            // Counter increases by 1
            counter += 1;
        }
    }
    cout << "My chemist has " << counter << " different substances in inventory currently" << endl;

    // Loops through all subtances
    for(int i = 0; i < PROJ2_SIZE; i++){
        // Gets the substance from the chemist's array at this index
        theSubstance = m_myChemist.GetSubstance(i);
        // Printing out each substance's name, formula, and quantity
        cout << counter2 << ". " << theSubstance.m_name << " (" << theSubstance.m_formula << ") " << theSubstance.m_quantity << endl;
        // Increments the counter by 1
        counter2++;
    }
}

int Lab::MainMenu(){
    int userInput = 0;

    // If the chemist has 1 of every substance
    if(m_myChemist.GetTotalSubstances() == PROJ2_SIZE){
        //cout << "WINNER WINNER CHICKEN DINNER" << endl;
        // Exits out of the game
        //return OPTION_FIVE;
    }

    cout << "What would you like to do?" << endl;
    cout << "1. Display your Chemist's Substances" << endl;
    cout << "2. Search for Elements" << endl;
    cout << "3. Attempt to Merge Substances" << endl;
    cout << "4. See Score" << endl;
    cout << "5. Quit" << endl;
    cin >> userInput;

    // If user input is not 1-5
    while(userInput < MIN_USER_INPUT || userInput > MAX_USER_INPUT){
        cout << "That is not one of the options. Enter a value 1-5" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Display your Chemist's Substances" << endl;
        cout << "2. Search for Elements" << endl;
        cout << "3. Attempt to Merge Substances" << endl;
        cout << "4. See Score" << endl;
        cout << "5. Quit" << endl;
        cin >> userInput;
    }

    return userInput;
}

void Lab::SearchSubstances(){

    // Creates a substance structure
    Substance myElement;

    // Declares and initializes an int variable for getting an index position from the array of substances
    int index = 0;
    // Picks an index from one of the 29 elements 
    index = rand() % NUMBER_ELEMENTS;

    // Sets substance structure to be the element at the randomly chosen index in the substances array
    myElement = m_substances[index];

    // Increases the quantity of the substance in the lab array by 1
    m_substances[index].m_quantity = m_substances[index].m_quantity + 1;


    // Increments the substance in the chemist's array by 1
    m_myChemist.IncrementQuantity(myElement);

    cout << myElement.m_name << " Found!" << endl;
}

void Lab::CombineSubstances(){

    // Declare and initialize 2 int variables for storing which substances the user wants to combine
    int substanceOneIndex = 0;
    int substanceTwoIndex = 0;
    // Declare and initialize an int variable for giving each substance a number

    // Uses function to request the user for an index of their first substance
    RequestSubstance(substanceOneIndex);
    // If the user does not type -1 which shows all of the substances, they will enter a second substance
    if(substanceOneIndex != LIST_KNOWN_SUBSTANCES){
        RequestSubstance(substanceTwoIndex);
    // If the user wants to see all substances, they will see them and then be sent back to the menu
    }else{
        return;
    }
    // If the second index was used to look at the array of substances
    if(substanceTwoIndex == LIST_KNOWN_SUBSTANCES){
        // Goes back to menu
        return;
    }
    // Creates 2 substance structures from the chemist's array at the given indexes
    Substance substanceOne = m_myChemist.GetSubstance(substanceOneIndex-1);
    Substance substanceTwo = m_myChemist.GetSubstance(substanceTwoIndex-1);

    //cout << "SUBSTSNCE 1: " << substanceOne.m_formula << endl;
    //cout << "SUBSTANCE 2: " << substanceTwo.m_formula << endl;

    // Stores the names of the substance structures into string variables
   string substanceNameOne = substanceOne.m_formula;
   string substanceNameTwo = substanceTwo.m_formula;

    // Declares and inializes an int variable for storing the index position of where the substances can be combined
   int indexCombined = 0;


    // Declares and initializes a bool variable for storing whether or not the 2 substances can be combined
    bool canBeCombined = false;
    // Declares a boolean variable for storing whether or not there is enough of each substance for combination
    bool atLeastOneOfEach = false;

    // Uses function to find the index position of the substance that can be formed
    indexCombined = SearchFormulas(substanceNameOne, substanceNameTwo);

    // If there is an index position for a substance that can be created
    if(indexCombined != CANNOT_COMBINE){
        // Set boolean to true
        canBeCombined = true;
    }
   // If the substances cannot be combined
   if(canBeCombined == false){
       cout << "It is impossible to merge these 2 materials" << endl;
    // If the 2 substances can be combined
    // If the substances can be combined
   }else{
       // Creates a substance structure from the chemist's array at the given index for the substance to be created
        Substance substanceThree = m_myChemist.GetSubstance(indexCombined);
       // Runs function to see if there is enough of each substance for merging
       atLeastOneOfEach = m_myChemist.CheckQuantity(substanceOne, substanceTwo);
       // If there is enough of each substance
       if(atLeastOneOfEach == true){
           // Decrements the 2 combined substances by 1
           m_myChemist.DecrementQuantity(substanceOne);
           m_myChemist.DecrementQuantity(substanceTwo);
           // Increments the created substance by 1
           m_myChemist.IncrementQuantity(substanceThree);
           cout << substanceNameOne << " combined with " << substanceNameTwo << " to make " << substanceThree.m_name << "!" << endl;

        // If there is not enough of each substance
       }else{
           cout << "You do not have enough of at least 1 of the substances" << endl;
       }
   }


}

void Lab::RequestSubstance(int &substanceIndex){
    // Declares and initializes a counter variable for numbering all of the substances
    int counter = 1;

    cout << "Which substances would you like to merge?" << endl;
    cout << "To list known substances enter -1" << endl;
    cin >> substanceIndex;

    // Initializes a substance structure
    Substance theSubstance;

    // If the user wants to see all known substances
    if(substanceIndex == LIST_KNOWN_SUBSTANCES){
        // Loops through all subtances
        for(int i = 0; i < PROJ2_SIZE; i++){
            // Sets the substance structure equal to that of the chemist's at the given index position
            theSubstance = m_myChemist.GetSubstance(i);
            // Printing out each substance's name, formula, and quantity
            cout << counter << ". " << theSubstance.m_name << " (" << theSubstance.m_formula << ") " << theSubstance.m_quantity << endl;
            // Increments the counter by 1
            counter++;
        }
        return;
    }

    // If the user input is above 283 or under 1 (excluding -1 as it is used to list known substances)
    while(substanceIndex > PROJ2_SIZE || (substanceIndex < FIRST_OPTION && substanceIndex != LIST_KNOWN_SUBSTANCES)){
        cout << "Must be a number between 1-283" << endl;
        cin >> substanceIndex;
    }
}

int Lab::SearchFormulas(string substanceNameOne, string substanceNameTwo){
    // Declares and intializes and int variable for storing the index position of the substance
    // that can be created from combining 2 other substances
    int indexCombined = 0;

    // Loops through all substances
   for(int i = 0; i < PROJ2_SIZE; i++){
       // If the 2 substances can be combined
       if((m_substances[i].m_substance1 == substanceNameOne && m_substances[i].m_substance2 == substanceNameTwo) || (m_substances[i].m_substance1 == substanceNameTwo && m_substances[i].m_substance2 == substanceNameOne)){
           // Sets the index to the current index
           indexCombined = i;
           return indexCombined;
       }   
   }
   // If the 2 substances cannot be combined
   return -1;
}

void Lab::CalcScore(){
    int totalSubstancesFound = 0;
    totalSubstancesFound = m_myChemist.GetTotalSubstances();


    cout << "*** The Chemist ***" << endl;
    cout << "The Great Chemist " << m_myChemist.GetName() << endl;
    cout << "There are " << PROJ2_SIZE << " substances to find" << endl;
    cout << "You have found " << m_myChemist.GetTotalSubstances() << " so far." << endl;
    cout << "This is " << ((float(totalSubstancesFound))/PROJ2_SIZE) * 100 << "%" << endl;
}


