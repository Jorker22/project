
#ifndef ABSTRACTNETWORK_H
#define ABSTRACTNETWORK_H

typedef struct _person
{
    struct _person * father;  
	struct _person * mother;
	struct _person * brother;
	struct _person * sister;
	struct _person * uncle;
	struct _person * aunt;
	struct _person * grandfather;
	struct _person * grandmother;
	struct _person * husband;
	struct _person * wife;
	struct _person * son;
	struct _person * daughter;

}REL_T;


typedef struct _adjVertex
    {
    void * pVertex;          
    unsigned int weight;      
    struct _adjVertex* next;  
    } ADJACENT_T;


typedef struct _information
    {
    char name[64];
    int Relation; 
    struct _information * next;   
    struct _information * pFrom;    
    ADJACENT_T * adjacentHead;        
    ADJACENT_T * adjacentTail;   

    }PERSON_T;

int printBreadthFirst(char* startKey,char* endkey);

//void printDepthFirst();

int AddRel(char* relation);

int addEdge(char* key1, char* key2, int weight);

void relAsk(char* first,char* last,char* relation);

char check_Relation(REL_T* first[],REL_T* last[],int count);

int addVertex2(char* key, void* pData, PERSON_T * pPerson1);


#endif

