// Program Information ////////////////////////////////////////////////////////
/**
 * @file HashClass.h
 *
 * @brief Definition file for HashClass
 * 
 * @details Specifies all data and other members of the HashClass
 *
 * @version 1.10 
 *          Michael Leverington (06 April 2016)
 *          Updated with probing
 *
 *          1.00 
 *          Michael Leverington (06 November 2015)
 *          Original code
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef HASH_CLASS_H
#define HASH_CLASS_H

// Header files ///////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

// Class constants ////////////////////////////////////////////////////////////

enum NodeState { USED, UNUSED };

// Class definition ///////////////////////////////////////////////////////////

template <typename DataType>
struct DataNode
   {
    DataNode();

    NodeState usedState;

    DataType nodeData;
   };

template <typename DataType>
class HashClass
   {
    public:

       // constants
       static const char TAB = '\t';
       static const int DEFAULT_HASH_TABLE_LENGTH = 10;
       static const int DEFAULT_HASH_LETTER_COUNT = 3;
       static const int DEFAULT_PROBE_ATTEMPT_LIMIT = 10;
       static const int FAILED_PROBE_PROCESS = -1;
       static const int STD_STR_LEN = 50;
       static const int LARGE_STR_LEN = 100;
       static const bool CLEAR_LIST = true;
       static const bool NO_LIST_CLEAR = false;

       // constructor
       HashClass();
       HashClass( const HashClass<DataType> &copied );

       // destructor
       ~HashClass();

       // assignment operator
       const HashClass &operator = (const HashClass<DataType> &rhData );

       // modifiers
       bool setTableLength( int newTableLength, bool clearListFlag,
                                           int &maxProbes, int &totalProbes );
       void setHashLetterCount( int newHashLetterCount );
       void setProbeAttempts( int newNumProbeAttempts );

       // adds item to hash table, returns success,
       //   reports probe attempts
       bool addItem( const DataType &newData, int &probeAttempts );

       // finds item in hash table, returns index,
       //   reports probe attempts
       int findItem( const DataType &dataItem, int &probeAttempts ) const;

       // removes item from hash table, returns success
       //   reports probe attempts
       bool removeItem( const DataType &dataItem, int &probeAttempts );

       // sets all elements of hash table to UNUSED
       void clearList();

       // accessors
       bool isEmpty() const;
       void showStructure() const;

    private:

       // calls DataType hash operation
       int hash( const DataType &dataItem, int workingTableLength ) const;

       // adds item to new hash table, returns count of probe attempts
       int addItemHelper( DataNode<DataType> *destHashTable, 
                                                   const DataType &newData );

       // resize hash table
       // if clear flag set, table size can be set to any size
       //   and table will be cleared
       // if clear flag not set, table size cannot be reduced in size;
       //   new table will be initialized and cleared,
       //   and data rehashed from previous hash list;
       //   returns false if attempt to shrink table 
       bool resizeList( int newSize, bool clearFlag, 
                                           int &maxProbes, int &totaProbes );

       // copies an outside hash table list into this object
       void copyList( const DataNode<DataType> *copiedList );

       // utility for calculating quadratic probing
       int toPower( int base, int exponent ) const;

       int tableLength;
       int maxProbeAttempts;
       int hashLetterCount;

       DataNode<DataType> *hashList;    
   };

#endif	// define HASH_CLASS_H



