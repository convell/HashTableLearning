// Program Information ////////////////////////////////////////////////////////
/**
 * @file HashClass.cpp
 *
 * @brief Implementation file for HashClass class
 * 
 * @details Implements the constructor method of the HashClass class
 *
 * @version 1.10 
 *          Michael Leverington (06 April 2016)
 *          Updated with probing
 *
 *          1.00 
 *          Michael Leverington (06 November 2015)
 *          Original code
 *
 * @Note Requires HashClass.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef HASH_CLASS_CPP
#define HASH_CLASS_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "HashClass.h"

using namespace std;

// Class Implementation  //////////////////////////////////////////////////////

template<typename DataType>
DataNode<DataType>::DataNode
       (
        // no parameters
       )
     : usedState( UNUSED )
   {
    // no action here
   }

template<typename DataType>
HashClass<DataType>::HashClass
       (
        // no parameters
       )
     : tableLength( DEFAULT_HASH_TABLE_LENGTH ), 
       maxProbeAttempts( DEFAULT_PROBE_ATTEMPT_LIMIT ),
       hashLetterCount( DEFAULT_HASH_LETTER_COUNT ),
       hashList( new DataNode<DataType>[ DEFAULT_HASH_TABLE_LENGTH ] )
   {
    // no action here
   }
           
template<typename DataType>
HashClass<DataType>::HashClass
       ( 
        const HashClass<DataType> &copied 
       )
     : tableLength( copied.tableLength ), 
       maxProbeAttempts( copied.maxProbeAttempts ),
       hashLetterCount( copied.hashLetterCount ),
       hashList( new DataNode<DataType>[ copied.tableLength ] )
   {
    copyList( copied.hashList );
   }

template<typename DataType>
HashClass<DataType>::~HashClass
       (
        // no parameters
       )
   {
    delete [] hashList;
   }

template <typename DataType>
const HashClass<DataType>& HashClass<DataType>:: operator = 
                                              ( const HashClass &rhHashTable )
   {
    int dummyMaxProbes, dummyTotalProbes;

    if( this != &rhHashTable )
       {
        resizeList( rhHashTable.tableLength, CLEAR_LIST, 
                                           dummyMaxProbes, dummyTotalProbes );

        maxProbeAttempts = rhHashTable.maxProbeAttempts;
        
        hashLetterCount = rhHashTable.hashLetterCount;

        copyList( rhHashTable.hashList );
       }

    return *this;
   }

template <typename DataType>
bool HashClass<DataType>::setTableLength
       ( 
        int newTableLength,
        bool clearListFlag,
        int &maxProbes,
        int &totalProbes
       )
   {
    return resizeList( newTableLength, clearListFlag, maxProbes, totalProbes );
   }

template <typename DataType>
void HashClass<DataType>::setHashLetterCount
       ( 
        int newHashLetterCount
       )
   {
    hashLetterCount = newHashLetterCount;
   }

template <typename DataType>
void HashClass<DataType>::setProbeAttempts
       ( 
        int newNumProbeAttempts
       )
   {
    maxProbeAttempts = newNumProbeAttempts;
   }

template <typename DataType>
bool HashClass<DataType>::addItem
       ( 
        const DataType &newData,
        int &probeAttempts
       )
   {
    // implement method

    return false;
   }

template <typename DataType>
int HashClass<DataType>::findItem
       ( 
        const DataType &dataItem,
        int &probeAttempts
       ) const
   {
    // implement method

    return 0;
   }

template <typename DataType>
bool HashClass<DataType>::removeItem
       ( 
        const DataType &dataItem,
        int &probeAttempts
       )
   {
    // implement method

    return false;
   }

template<typename DataType>
bool HashClass<DataType>::isEmpty
       ( 
        // no parameters
       ) const
   {
    // implement method

    return false;
   }

template<typename DataType>
void HashClass<DataType>::clearList
       (  
        // no parameters     
       )
   {
    // implement method
   }

template<typename DataType>
void HashClass<DataType>::showStructure
       (
        // no parameters
       ) const
   {
    // implement method
   }

template<typename DataType>
int HashClass<DataType>::hash
       (
        const DataType &dataItem,
        int workingTableLength
       ) const
   {
    // implement method

    return 0;
   }

template <typename DataType>
int HashClass<DataType>::addItemHelper
       ( 
        DataNode<DataType> *destHashTable,
        const DataType &newData
       )
   {
    // implement method

    return 0;
   }

template<typename DataType>
bool HashClass<DataType>::resizeList
       (       
        int newSize,
        bool clearFlag,
        int &maxProbes,
        int &totalProbes
       )
   {
    // implement method

    return false;
   }

template<typename DataType>
void HashClass<DataType>::copyList 
       ( 
        const DataNode<DataType> *copiedList
       )
   {
    // implement method
   }

template<typename DataType>
int HashClass<DataType>::toPower
     ( 
      int base, 
      int exponent 
     ) const
   {
    // implement method

    return 0;
   }

#endif	// define HASH_CLASS_CPP





