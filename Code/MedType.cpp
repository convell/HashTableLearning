// Program Information ////////////////////////////////////////////////////////
/**
 * @file MedType.cpp
 *
 * @brief Implementation file for MedType class
 * 
 * @details Implements member actions of the MedType class
 *
 * @author Michael Leverington
 *
 * @version 1.00 (30 October 2015)
 *
 * @Note Requires MedType.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_MEDTYPE_CPP
#define CLASS_MEDTYPE_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "MedType.h"

MedType::MedType
       ( 
        // no parameters
       )
     : name( new char[ BASE_STR_LEN ] ), 
       medCodeNum( new char[ BASE_STR_LEN ] ), 
       gender( 'O' )
   {
    copyString( name, NAME_DEFAULT );

    copyString( medCodeNum, CODE_NUM_DEFAULT );
   }

MedType::MedType
       ( 
        const char *patientName,     // in: new c-string name
        const char *medicalCodeNum,  // in: new c-string code number
        char patientGender           // in: new char gender
       )
     : name( new char[ BASE_STR_LEN ] ), 
       medCodeNum( new char[ BASE_STR_LEN ] )
   {
    copyString( name, NAME_DEFAULT );

    copyString( medCodeNum, CODE_NUM_DEFAULT );

    setAccount( patientName, medCodeNum, patientGender );    
   }

MedType::MedType
       ( 
        const MedType &newAcctObject    // in: copied account object
       )
     : name( new char[ BASE_STR_LEN ] ), 
       medCodeNum( new char[ BASE_STR_LEN ] )
   {
    copyString( name, NAME_DEFAULT );

    copyString( medCodeNum, CODE_NUM_DEFAULT );

    setAccount( newAcctObject.name, newAcctObject.medCodeNum, 
                                                       newAcctObject.gender );    
   }

MedType::~MedType
       ( 
        // no parameters
       )
   {
    delete name;

    delete medCodeNum;
   }

#include <iostream>
using namespace std;

const MedType &MedType::operator =
       (
        const MedType &rhMed // in: assigned medical data
       )
   {
    if( this != &rhMed )
       {
        setAccount( rhMed.name, rhMed.medCodeNum, rhMed.gender );
       }

    return *this;
   }
	
void MedType::setAccount
       (
        const char *patientName,     // in: assigned patient name
        const char *medicalCodeNum,  // in: assigned medical code number
        char patientGender           // in: assigned gender
       )
   {
    // make room for new name
    delete [] name;

    name = new char[ getStrLen( patientName ) + 1 ];

    copyString( name, patientName );

    delete [] medCodeNum;

    medCodeNum = new char[ getStrLen( medicalCodeNum ) + 1 ];

    copyString( medCodeNum, medicalCodeNum );

    gender = patientGender;
   }

void MedType::getAccount
       (
        char *patientName,    // out: patient name returned
        char *medicalCodeNum, // out: medical code number returned
        char &patientGender    // out: gender returned
       ) const
   {
    copyString( patientName, name );

    copyString( medicalCodeNum, medCodeNum );

    patientGender = gender;
   }

int MedType::compareTo
       (
        const MedType &rhMed
       )
     const throw ( logic_error )
   {
    int diff, index = 0;

    if( this == &rhMed )
       {
        return 0;
       }

    while( name[ index ] != NULL_CHAR && rhMed.name[ index ] != NULL_CHAR )
       {
        diff = toUpper( name[ index ] ) - toUpper( rhMed.name[ index ] );

        if( diff != 0 )
           {
            return diff;
           }

        index++;
       }

    return 0;
   }

void MedType::toString
       ( 
        char *medStr 
       )
   {
    const char DIVIDER[] = ", ";

    copyString( medStr, name );

    concatString( medStr, DIVIDER );

    concatString( medStr, medCodeNum );

    concatString( medStr, DIVIDER );

    concatChar( medStr, gender );
   }

int MedType::hash
       (
        int numLetters,
        int hashTableLength
       )
   {
    int index = 0, sum = 0;

    while( name[ index ] != NULL_CHAR && index < numLetters )
       {
        sum += int( name[ index ] );

        index++;
       }

    return sum % hashTableLength;
   }

void MedType::copyString
       ( 
        char *destination,  // out: destination string
        const char *source // in: source string
       ) const
   {
    int index = 0;

    while( source[ index ] != NULL_CHAR )
       {
        destination[ index ] = source[ index ];

        index++;

        destination[ index ] = NULL_CHAR;
       }
   }

void MedType::concatString
       ( 
        char *destination,  // out: destination string
        const char *source // in: source string
       ) const
   {
    int sourceIndex = 0, destIndex = getStrLen( destination );

    while( source[ sourceIndex ] != NULL_CHAR )
       {
        destination[ destIndex ] = source[ sourceIndex ];

        destIndex++; sourceIndex++;

        destination[ destIndex ] = NULL_CHAR;
       }
   }

void MedType::concatChar
       ( 
        char *destination,  // out: destination string
        const char source   // in: source char
       ) const
   {
    int index = getStrLen( destination );

    destination[ index ] = source;

    destination[ index + 1 ] = NULL_CHAR;
   }

int MedType::getStrLen
       ( 
        const char *str // in: string
       ) const
   {
    int index;

    for( index = 0; str[ index ] != NULL_CHAR; index++ );

    return index;
   }

char MedType::toUpper
       ( 
        char letter // in: test letter
       ) const
   {
    if( letter >= 'a' && letter <= 'z' )
       {
        letter = letter - 'a' + 'A';
       }

    return letter;
   }

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_MEDTYPE_CPP



