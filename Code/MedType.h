// Program Information ////////////////////////////////////////////////////////
/**
 * @file MedType.h
 *
 * @brief Definition file for MedType class
 * 
 * @details Specifies all data of the MedType class,
 *          along with the constructor,
 *          MedType class is entered and stored as a string
 *
 * @author Michael Leverington
 *
 * @version 1.00 (30 October 2015)
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_MEDTYPE_H
#define CLASS_MEDTYPE_H

// Header files ///////////////////////////////////////////////////////////////

#include <ostream>
#include <stdexcept>

using namespace std;

// Class constants ////////////////////////////////////////////////////////////

   const char NAME_DEFAULT[] = "Name Default";
   const char CODE_NUM_DEFAULT[] = "Code Num Default";

// Class definition ///////////////////////////////////////////////////////////

class MedType
   {
    public:

       static const char NULL_CHAR = '\0';
       static const char COMMA = ',';
       static const char SPACE = ' ';
       static const char BASE_STR_LEN = 20;
       static const int STD_NAME_LEN = 100;

       MedType();
       MedType( const char *patientName, const char *medCodeNum, 
                                                         char patientGender );
       MedType( const MedType &newMedObject );

       ~MedType();

       const MedType &operator = ( const MedType &rhMed );

       void setAccount( const char *patientName, const char *medicalCodeNum, 
                                                          char patientGender );
       void getAccount( char *patientName, char *medicalCodeNum, 
                                                    char &patientGender ) const;

       int compareTo( const MedType &rhMed ) const throw ( logic_error );

       void toString( char *medStr );

       int hash( int numLetters, int hashTableLength );

    private:

       void copyString( char *destination, const char *source ) const;
       void concatString( char *destination, const char *source ) const;
       void concatChar( char *destination, const char source ) const;
       int getStrLen( const char *str ) const;
       char toUpper( char letter ) const;

       char *name;
       char *medCodeNum;
       char gender;
   };

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_MEDTYPE_H



