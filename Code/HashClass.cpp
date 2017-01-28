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
/**
 * @brief Default/Initialization DataNode constructor
 *
 * @details sets usedState
 *          
 * @pre assumes Uninitialized DataNode object
 *
 * @post DataNode initizilied
 *
 * @par N/A
 * 
 * @exception None
 *
 * @return None
 *
 * @parm None
 *
 * @note None
 */
template<typename DataType>
DataNode<DataType>::DataNode
       (
        // no parameters
       )
     : usedState( UNUSED )
   {
    // no action here
   }

/**
 * @brief Default/Initialization HashClass constructor
 *
 * @details sets tableLength, MaxProbeAttemps,hashLetterCount,hashList
 *          
 * @pre assumes Uninitialized hashClass object
 *
 * @post hashClass initizilied
 *
 * @par N/A
 * 
 * @exception None
 *
 * @return None
 *
 * @parm None
 *
 * @note None
 */
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
   
/**
 * @brief Default/Initialization HashClass copy constructor
 *
 * @details sets tableLength, MaxProbeAttemps,hashLetterCount,hashList to copied class
 *          
 * @pre assumes Uninitialized hashClass object
 *
 * @post hashClass initizilied
 *
 * @par N/A
 * 
 * @exception None
 *
 * @return None
 *
 * @parm copied - a hashclass that has its values copied
 *
 * @note None
 */        
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

/**
 * @brief destructer HashClass
 *
 * @details deletes dynamic memory
 *          
 * @pre assumes initialized hashClass object
 *
 * @post hashClass uninitizilied
 *
 * @par N/A
 * 
 * @exception None
 *
 * @return None
 *
 * @parm None
 *
 * @note None
 */

template<typename DataType>
HashClass<DataType>::~HashClass
       (
        // no parameters
       )
   {
    delete [] hashList;
   }

/**
 * @brief assignment operator
 *
 * @details sets tableLength, MaxProbeAttemps,hashLetterCount,hashList to rhHashTable
 *          
 * @pre assumes initialized hashClass object
 *
 * @post hashClass values set to rhHashTable values
 *
 * @par N/A
 * 
 * @exception None
 *
 * @return None
 *
 * @parm rhHashTable - copied values from
 *
 * @note None
 */
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

/**
 * @brief setTableLength
 *
 * @details sets tableLength
 *          
 * @pre assumes initialized hashClass object
 *
 * @post tableLength to newTableLength and resizes
 *
 * @par Algorithm
 *      calls resizeList
 * 
 * @exception None
 *
 * @return bool of success
 *
 * @parm newTableLength, clearListFlag, maxProbes, TotalProbes
 *
 * @note None
 */
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

/**
 * @brief setHashLetterCount
 *
 * @details sets hashLetterCount to newHashLetterCount
 *          
 * @pre assumes initialized hashClass object
 *
 * @post sets hashLetterCount to newHashLetterCount
 *
 * @par N/A
 * 
 * @exception None
 *
 * @return None
 *
 * @parm newHashLetterCount - to change hashLetter to
 *
 * @note None
 */
template <typename DataType>
void HashClass<DataType>::setHashLetterCount
       ( 
        int newHashLetterCount
       )
   {
    hashLetterCount = newHashLetterCount;
   }

/**
 * @brief setProbeAttempts
 *
 * @details MaxProbeAttemps to newNumProbeAttempts
 *          
 * @pre assumes initialized hashClass object
 *
 * @post MaxProbeAttemps to newNumProbeAttempts
 *
 * @par N/A
 * 
 * @exception None
 *
 * @return None
 *
 * @parm newNumProbeAttempts
 *
 * @note None
 */
template <typename DataType>
void HashClass<DataType>::setProbeAttempts
       ( 
        int newNumProbeAttempts
       )
   {
    maxProbeAttempts = newNumProbeAttempts;
   }

/**
 * @brief addItem
 *
 * @details hashes item and adds it to the hashList
 *          
 * @pre assumes initialized hashClass object
 *
 * @post hashes item and adds it to the hashList
 *
 * @par N/A
 * 
 * @exception None
 *
 * @return bool of success
 *
 * @parm newData - data to add
 *       probeAttempts - attempts to add data
 *
 * @note None
 */
template <typename DataType>
bool HashClass<DataType>::addItem
       ( 
        const DataType &newData,
        int &probeAttempts
       )
   {
    int hashIndex = 0;
    probeAttempts = 0;
    
    hashIndex = hash(newData,tableLength);

    if (hashList[hashIndex].usedState==UNUSED)
    {
      hashList[hashIndex].nodeData = newData;
      hashList[hashIndex].usedState = USED;
    }
    else
    {
      probeAttempts = addItemHelper(hashList,newData);
    }
    return false;
   }

/**
 * @brief findItem
 *
 * @details returns int of items index
 *          
 * @pre assumes initialized hashClass object
 *
 * @post returns int of items index
 *
 * @par N/A
 * 
 * @exception None
 *
 * @return int of items index
 *
 * @parm dataItem - data to find
 *       probeAttempts - attempts to add data
 *
 * @note None
 */
template <typename DataType>
int HashClass<DataType>::findItem
       ( 
        const DataType &dataItem,
        int &probeAttempts
       ) const
   {
    int searchIndex = 0;
    DataType comparedData;

    while(searchIndex != tableLength)
    {
      searchIndex++;
      comparedData = hashList[searchIndex].nodeData;
      if (comparedData.compareTo(dataItem)==0)
      {
        return searchIndex;
      }
      
    }

    return -1;
   }

/**
 * @brief removeItem
 *
 * @details returns int of items index
 *          
 * @pre assumes initialized hashClass object
 *
 * @post removes dataItem
 *
 * @par algorithm
 *      calls findItem to get index to remove
 * 
 * @exception None
 *
 * @return success of operation
 *
 * @parm dataItem - data to remove
 *       probeAttempts - attempts to add data
 *
 * @note None
 */
template <typename DataType>
bool HashClass<DataType>::removeItem
       ( 
        const DataType &dataItem,
        int &probeAttempts
       )
   {
    int dataIndex = findItem(dataItem,probeAttempts);

    if (dataIndex < tableLength && dataIndex > 0)
    {
      hashList[dataIndex].usedState = UNUSED;
      return true;
    }

    return false;
   }

/**
 * @brief isEmpty
 *
 * @details returns if there is no data
 *          
 * @pre assumes initialized hashClass object
 *
 * @post returns a bool
 *
 * @par algorithm
 *      calls findItem to get index to remove
 * 
 * @exception None
 *
 * @return false
 *
 * @parm None
 *
 * @note None
 */
template<typename DataType>
bool HashClass<DataType>::isEmpty
       ( 
        // no parameters
       ) const
   {
    return false;
   }

/**
 * @brief clearList
 *
 * @details clears list by setting all to unused
 *
 * @pre N/a
 *
 * @post clears list by setting all to unused
 *
 * @par None     
 * 
 * @exception None
 *
 * @param None
 *
 * @return None
 *
 * @note None
 **/
template<typename DataType>
void HashClass<DataType>::clearList
       (  
        // no parameters     
       )
   {
    int forCounter;

    for (forCounter = 0; forCounter < tableLength; ++forCounter)
    {
      hashList[forCounter].usedState = UNUSED;
    }
   }

/**
 * @brief showStructure
 *
 * @details prints out data of hashList in order
 *
 * @pre N/a
 *
 * @post prints out data of hashList in order
 *
 * @par None     
 * 
 * @exception None
 *
 * @param None
 *
 * @return None
 *
 * @note None
 **/
template<typename DataType>
void HashClass<DataType>::showStructure
       (
        // no parameters
       ) const
   {
    int forCounter;
    char stringOut[LARGE_STR_LEN];

    for (forCounter = 0; forCounter < tableLength; ++forCounter)
    {
      if (hashList[forCounter].usedState == UNUSED)
      {
        cout << "Index " << forCounter << ": " <<  "UNUSED" << endl;
      }
      else
      {
        hashList[forCounter].nodeData.toString(stringOut);
        cout << "Index " << forCounter << ": " <<  stringOut << endl;
      }
    }
    cout << "- End of List -" << endl;

   }

/**
 * @brief hash
 *
 * @details calls hashlist of DataType
 *
 * @pre N/a
 *
 * @post returns hash of DataType
 *
 * @par None     
 * 
 * @exception None
 *
 * @param newSize, clearFlag, maxProbes, totalProbes
 *
 * @return int of hash value
 *
 * @note None
 **/
template<typename DataType>
int HashClass<DataType>::hash
       (
        const DataType &dataItem,
        int workingTableLength
       ) const
   {
    int hashIndex = 0;
    DataType tempDataType = dataItem;

    hashIndex = tempDataType.hash(hashLetterCount,workingTableLength);

    return hashIndex;
   }

/**
 * @brief addItemHelper
 *
 * @details does the probing of the addItem function
 *
 * @pre N/a
 *
 * @post adds data to hashlist and returns probeAttempts
 *
 * @par None     
 * 
 * @exception None
 *
 * @param destHashTable, newData
 *
 * @return returns probeAttempts
 *
 * @note None
 **/
template <typename DataType>
int HashClass<DataType>::addItemHelper
       ( 
        DataNode<DataType> *destHashTable,
        const DataType &newData
       )
   {
    int probeAttempts = 0;
    int hashIndex = hash(newData,tableLength);
    int tempHashIndex = hashIndex;
    int forIndex;

    while(probeAttempts != maxProbeAttempts)
    {

      for (forIndex = 0; forIndex < tableLength; ++forIndex)
      {
        tempHashIndex = hashIndex;
        tempHashIndex = tempHashIndex + toPower(forIndex,2);

        //if (tempHashIndex > tableLength)
        //{
          tempHashIndex = tempHashIndex % tableLength;
        //}

        if (destHashTable[tempHashIndex].usedState == UNUSED)
        {
          destHashTable[tempHashIndex].nodeData = newData;
          destHashTable[tempHashIndex].usedState = USED;
          return probeAttempts;
        }
        probeAttempts++;
      }
    }

    return FAILED_PROBE_PROCESS;
   }

/**
 * @brief resizeList
 *
 * @details clears list if param allows, or makes size bigger
 *
 * @pre N/a
 *
 * @post resizes list to the newSize
 *
 * @par None     
 * 
 * @exception None
 *
 * @param newSize, clearFlag, maxProbes, totalProbes
 *
 * @return bool if successfull or not
 *
 * @note None
 **/
template<typename DataType>
bool HashClass<DataType>::resizeList
       (       
        int newSize,
        bool clearFlag,
        int &maxProbes,
        int &totalProbes
       )
   {
    DataNode<DataType> *newHashList; 
    int forCounter;
    int hashIndex = 0;
    int probeAttempts = 0;
    int oldTableLength = tableLength;

    totalProbes = 0;
    maxProbes = 0;

    if (clearFlag==true)
    {
      delete[] hashList;
      hashList = new DataNode<DataType>[ newSize ];
      tableLength = newSize;
      maxProbeAttempts=maxProbes;
      clearList();
      return true;
    }
    else
    {
      if (oldTableLength < newSize)
      {
        newHashList = new DataNode<DataType>[ newSize ];
        for (forCounter = 0; forCounter < oldTableLength; ++forCounter)
        {
          if (hashList[forCounter].usedState == USED)
          {
            hashIndex = hash(hashList[forCounter].nodeData,newSize);
          }

          if (newHashList[hashIndex].usedState == UNUSED)
          {
             newHashList[hashIndex] = hashList[forCounter];
          }
          else
          {
           tableLength = newSize;
           probeAttempts = addItemHelper(newHashList,hashList[forCounter].nodeData);

           probeAttempts = -1;

            if(probeAttempts == FAILED_PROBE_PROCESS)
            {
              return false;
            }

            if (probeAttempts > maxProbes)
            {
              maxProbes = probeAttempts;
            }

            totalProbes += probeAttempts;
          }
        }


        delete[] hashList;
        hashList = new DataNode<DataType>[ tableLength ];

        for (forCounter = 0; forCounter < tableLength; ++forCounter)
        {
          hashList[forCounter] = newHashList[forCounter];
          hashList[forCounter].usedState = newHashList[forCounter].usedState;
        }

        return true;
      }
      else
      {
        return false;
      }
    }

    return false;
   }

/**
 * @brief copyList
 *
 * @details copies copiedList to this list
 *
 * @pre N/a
 *
 * @post copies copiedList to this list
 *
 * @par None     
 * 
 * @exception None
 *
 * @param copiedList - to copy data from
 *
 * @return None
 *
 * @note None
 **/
template<typename DataType>
void HashClass<DataType>::copyList 
       ( 
        const DataNode<DataType> *copiedList
       )
   {
    int forCounter;

    for (forCounter = 0; forCounter < tableLength; ++forCounter)
    {
      hashList[forCounter].nodeData = copiedList[forCounter].nodeData;
      hashList[forCounter].usedState = copiedList[forCounter].usedState;
    }
   }

/**
 * @brief power function
 *
 * @details does power operations
 * @pre N/a
 *
 * @post returns power operation
 *
 * @par Algorithm 
 *      
 * 
 * @exception None
 *
 * @param base, exponent
 *
 * @return None
 *
 * @note None
 **/
template<typename DataType>
int HashClass<DataType>::toPower
     ( 
      int base, 
      int exponent 
     ) const
   {
    int counter = 1;
    int result = base;

    while(counter < exponent)
    {
      result = result * base;
      counter++;
    }

    return result;
   }

#endif	// define HASH_CLASS_CPP





