// Program Information ////////////////////////////////////////////////////////
/**
 * @file PA09.cpp
 *
 * @brief Driver program to exercise the heap class, with account information
 * 
 * @details Allows for testing the heap class,
 *          along with a timer class that will be used for evaluation
 *
 * @version 1.10 
 *          Michael Leverington (06 April 2016)
 *          Updated with probing
 *
 *          1.00 
 *          Michael Leverington (06 November 2015)
 *          Original code
 *
 * @Note Requires iostream, cstring, MedType.h, and HashClass.cpp
 */

// Precompiler directives /////////////////////////////////////////////////////

   // None

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>
#include <cstring>
#include "MedType.h"
#include "HashClass.cpp"

using namespace std;

// Global constant definitioans  //////////////////////////////////////////////

const char ENDLINE_CHAR = '\n';
const char NULL_CHAR = '\0';
const char DOUBLE_QUOTES = '\"';
const char COMMA = ',';
const char COLON = ':';
const int MAX_STR_LEN = 80;
const int ITEM_TO_PICK = 5;

enum cCodes { DUMMY, HC_1_TS, HC_1_RI, HC_1_ASSGND, 
                                            HC_1_RSZ, HC_1_CLRD, HC_1_CPYD };

// Free function prototypes  //////////////////////////////////////////////////

int getControlCode( istream &consoleIn );
bool getALine( istream &consoleIn, MedType &inputData );
bool getLine( istream &consoleIn, char *str, int length, char stopChar );
void displayCodeChoices();

// Main function implementation  //////////////////////////////////////////////

int  main()
   {
    MedType MT_returned, MT_removed;
    HashClass<MedType> HC_1, HC_2;
    int tableLength, letterCount, controlCode, itemCounter = 0;
    char patientName[ MAX_STR_LEN ], medicalCode[ MAX_STR_LEN ];
    char dummyStr[ MAX_STR_LEN ];
    char gender;
    int probeCountLimit, probeCount, resizeValue;
    int maxSingleItemProbeCount = 0, totalProbeCount = 0;
    bool resizeSuccess;

    // get table length
    getLine( cin, dummyStr, MAX_STR_LEN, COLON );
    cin >> tableLength;
    HC_1.setTableLength( tableLength, HashClass<MedType>::CLEAR_LIST, 
                                               probeCount, probeCountLimit );

    // get letter count
    getLine( cin, dummyStr, MAX_STR_LEN, COLON );
    cin >> letterCount;
    HC_1.setHashLetterCount( letterCount );

    // get max probes setting
    getLine( cin, dummyStr, MAX_STR_LEN, COLON );
    cin >> probeCountLimit;
    HC_1.setProbeAttempts( probeCountLimit );

    // get max probes setting
    getLine( cin, dummyStr, MAX_STR_LEN, COLON );
    cin >> resizeValue;

    displayCodeChoices();

    // get control code
    getLine( cin, dummyStr, MAX_STR_LEN, COLON );
    cin >> controlCode;

    cout << controlCode << endl << "Data Entry:" << endl;

    while( getALine( cin, MT_returned ) )
       {
        MT_returned.getAccount( patientName, medicalCode, gender );

        itemCounter++;

        if( itemCounter == ITEM_TO_PICK )
           {
            MT_removed = MT_returned;
           }

        HC_1.addItem( MT_returned, probeCount );

        if( probeCount > maxSingleItemProbeCount )
           {
            maxSingleItemProbeCount = probeCount;
           }

        if( probeCount == HashClass<MedType>::FAILED_PROBE_PROCESS )
           {
            cout << "Maximum probe attempts exceeded on item number "
                 << itemCounter << COMMA << endl
                 << "Add data failed, program aborted." << endl;

            return 0;
           }

        totalProbeCount += probeCount;
       }

    switch( controlCode )
       {
        case HC_1_TS:
           cout << endl << "HC_1 Hash Table Structure: " << endl;

           HC_1.showStructure();

           cout << "Total number of probes for loading hash table: "
                << totalProbeCount << endl;
           cout << "Maximum single item probe count: "
                << maxSingleItemProbeCount << endl;

           break;

        case HC_1_RI:
           cout << endl << "Test of removal operation" << endl;
           cout << endl << "Hash Table Structure before removal: " << endl;

           HC_1.showStructure();

           cout << "Total number of probes for loading hash table: "
                << totalProbeCount << endl;
           cout << "Maximum single item probe count: "
                << maxSingleItemProbeCount << endl;

           HC_1.removeItem( MT_removed, probeCount );

           MT_removed.getAccount( patientName, medicalCode, gender );

           cout << endl << "Removed Patient Name: " << patientName << endl;
           cout << endl 
                << "Hash Table Structure after removal: " << endl;

           HC_1.showStructure();

           cout << "Probes necessary for removal: " << probeCount << endl;

           break;

        case HC_1_ASSGND:
           cout << endl << "Test of HashClass assignment operation" << endl;

           cout << endl << "Hash Table Structure of object: " << endl;

           HC_1.showStructure();
 
           cout << "Total number of probes for loading hash table: "
                << totalProbeCount << endl;
           cout << "Maximum single item probe count: "
                << maxSingleItemProbeCount << endl;

           HC_2 = HC_1;

           cout << endl << "Hash Table Structure of assigned object: " << endl;

           HC_2.showStructure();

           break;

        case HC_1_RSZ:
           cout << endl << "Test of HashClass resize operation" << endl;

           cout << endl << "Hash Table Structure of object: " << endl;

           HC_1.showStructure();
 
           cout << "Total number of probes for loading hash table: "
                << totalProbeCount << endl;
           cout << "Maximum single item probe count: "
                << maxSingleItemProbeCount << endl;

           resizeSuccess = HC_1.setTableLength( resizeValue, 
                               HashClass<MedType>::NO_LIST_CLEAR, 
                                   maxSingleItemProbeCount, totalProbeCount );

           if( !resizeSuccess )
              {
               cout << "Hash table failed to resize due to probing failure; "
                    << "resize aborted." << endl;
              }

           else
              {
               cout << endl << "Hash Table Structure of assigned object: " << endl;

               HC_1.showStructure();

               cout << "Total number of probes for resizing hash table: "
                    << totalProbeCount << endl;
               cout << "Maximum single item probe count: "
                    << maxSingleItemProbeCount << endl;
              }

           break;

        case HC_1_CLRD:
           cout << endl << "Test of HashClass clearing operation" << endl;

           cout << endl << "Hash Table Structure before cleared: " << endl;

           HC_1.showStructure();

           cout << "Total number of probes for loading hash table: "
                << totalProbeCount << endl;
           cout << "Maximum single item probe count: "
                << maxSingleItemProbeCount << endl;

           HC_1.clearList();

           cout << endl << "Hash Table Structure after cleared: " << endl;

           HC_1.showStructure();

           break;

        case HC_1_CPYD:
           cout << endl << "Test of HashClass object copy operation" << endl;

           cout << endl << "Hash Table Structure of object: " << endl;

           HC_1.showStructure();

           cout << "Total number of probes for loading hash table: "
                << totalProbeCount << endl;
           cout << "Maximum single item probe count: "
                << maxSingleItemProbeCount << endl;

           // Non-standard action: Object instantiated in a location
           //   not at the beginning of the function
           HashClass<MedType> HC_3( HC_1 );
      
           cout << endl << "Hash Table Structure of copy constructed object" 
                << endl;

           HC_3.showStructure();

           break;
       } 

    return 0;
   }

// Free function implementation  //////////////////////////////////////////////

/**
 * @brief Displays test choices
 *
 * @details Various codes implement different tests on tree system
 *          
 * @param in: None
 *
 * @note Codes are all enumerated
 */
void displayCodeChoices()
   {
    cout << "Here is the list of codes for the various tests:" << endl;

    cout << "Show Hash Table Structure of input data : " << HC_1_TS << endl;
    cout << "Show remove item action                 : " << HC_1_RI << endl;
    cout << "Show object assignment operation        : " << HC_1_ASSGND << endl;
    cout << "Resize/Rehash Table                     : " << HC_1_RSZ << endl;
    cout << "Show Hash Table cleared action          : " << HC_1_CLRD << endl;
    cout << "Show Hash Table copied action           : " << HC_1_CPYD << endl;
    cout << endl << "Enter code number: ";
   }

/**

 * @brief Gets control code for testing ///////////////////////////////////////////////////// Remove?
 *
 * @details code is used in program to test individual actions
 *          
 * @param in: istream object
 *
 * @return out: operation code
 *
 * @note gets integer, cleans out end line characters
 */
int getControlCode( istream &consoleIn )
   {
    char inChar;
    int codeNum;

    consoleIn >> codeNum;

    while( inChar != ENDLINE_CHAR )
       {
        consoleIn.get( inChar );
       }

    return codeNum;
   }
/**
 * @brief Gets medical data along with priority key
 *
 * @details gets patient name, medical code, gender, and priority key
 *          
 * @param in: istream object
 * @param out: MedType data item
 * @param out: priority number
 *
 * @note resolution for redirected input, getline did not work
 */

bool getALine( istream &consoleIn, MedType &inputData )
   {
    char inChar;
    char inName[ MAX_STR_LEN ], medCode[ MAX_STR_LEN ];
    char gender;

    // get name, first call eats everything up to, and including double quote
    getLine( consoleIn, inName, MAX_STR_LEN, DOUBLE_QUOTES );
    getLine( consoleIn, inName, MAX_STR_LEN, DOUBLE_QUOTES );

    if( strcmp( inName, "QUIT" ) == 0 )
       {
        return false;
       }
   
    consoleIn >> inChar; // next comma

    // get medical code
    getLine( consoleIn, medCode, MAX_STR_LEN, COMMA );

    // get gender
    consoleIn >> gender;

    // set data in account
    inputData.setAccount( inName, medCode, gender );
            
    return true;
   }

/**
 * @brief Gets a line of text from an input stream     
 *
 * @details Gets a line of text from an input stream
 *        up to a specified character, 
 *        or a specified length (-1 to allow for the null char);
 *        ending character is not placed in the string
 *          
 * @param in: istream object
 * @param in: specified length
 * @param in: specified ending character
 * @param out: string
 *
 * @note resolution for redirected input, getline did not work
 */
bool getLine( istream &consoleIn, char *str, int length, char stopChar )
   {
    const char LOWEST_PRINTABLE_CHAR = 32;  // space
    const char HIGHEST_PRINTABLE_CHAR = 126;  // tilde 
    int index = 0;
    int inVal;
    bool istreamState = consoleIn.good();

    inVal = consoleIn.get();

    while( char( inVal ) != stopChar && index < length - 1  )
       {
        if( inVal >= LOWEST_PRINTABLE_CHAR 
                                    && inVal <= HIGHEST_PRINTABLE_CHAR )
           {
            str[ index ] = char( inVal );

            index++;

            str[ index ] = NULL_CHAR;
           }

        inVal = consoleIn.get();
       }

    return istreamState;
   }





