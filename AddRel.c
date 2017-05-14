#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "AddRel.h"
#include "networkWriter.h"
#include "familynetwork.h"

#define father 0
#define mother 6
#define son 1
#define daughter 7 
#define brother 2
#define sister 8
#define wife 9
#define husband 3
#define aunt 10
#define uncle 4
#define grandmother 11
#define grandfather 5

#define men 0
#define women 1
#define WHITE 0
#define GRAY  1
#define BLACK 2

typedef struct _listitem
{
    void* data;               /* Pointer to the data for this node */
    struct _listitem * next;  /* Link to the next item in the list */
} LISTITEM_T;

static int count = 0;              /* number of items in the queue */
static LISTITEM_T * head = NULL;   /* front item in the queue */
static LISTITEM_T * tail = NULL;   /* end item in the queue */



/*typedef struct _adjVertex
    {
    void * pVertex;          
    unsigned int weight;      
    struct _adjVertex* next;  
    } ADJACENT_T;
*/

char* colorName[] = {"WHITE", "GRAY", "BLACK"};

typedef struct _vertex
    {
    char * key;              
    void * data;
    int color;
    int dValue;
    int  gender;                            
    struct _vertex * next;   
    struct _vertex * pFrom; 
    struct _vertex * parent;    
    ADJACENT_T * adjacentHead;        
    ADJACENT_T * adjacentTail;    
		}VERTEX_T;



VERTEX_T * vListHead = NULL;
VERTEX_T * vListTail = NULL;
PERSON_T * vListTail2 = NULL;
PERSON_T * vListHead2 = NULL;


int bGraphDirected = 1;       
int weightSum = 0;            
int bHasNeg = 0;              
int vertexCount = 0; 

int maxGraphVertices = 9999;     /* not used for linked list implementation */                              
/* but needed for networkWriter */
VERTEX_T* currentVertex = NULL; 


char input[64];
char first[64] = "";
char last[64]  = "";
char relation[32];
char* key1 = NULL;
char* key2 = NULL;
char* newString = NULL;
char* newString2 = NULL;
char buffere[128];

int retRel;
int gender;
int retVal = 0;
int retValEdge = 0;
int retVal_Vertex1 = 0;
int retVal_Vertex2 = 0;
int retval2 = 0;
char input2[64];
char buffer[128];
int weight = 0;
int i = 0;


void printVertexInfo(VERTEX_T* pVertex)
{
    printf("== Vertex key |%s| - data |%s|\n",
     pVertex->key, (char*) pVertex->data);
}

int countAdjacent(VERTEX_T * pVertex)
{
    int count = 0;
    ADJACENT_T * pAdjacent = pVertex->adjacentHead;
    while (pAdjacent != NULL)
       {
       count += 1;
       pAdjacent = pAdjacent->next;
       }
    return count;
}

void colorAll(int color)
{
    VERTEX_T* pVertex = vListHead;
    while (pVertex != NULL)
       {
       pVertex->color = color;
       pVertex = pVertex->next;
       }
}

int enqueueMin(void* data)
{
   int bOk = 1;
   LISTITEM_T * newItem = (LISTITEM_T *)calloc(1,sizeof(LISTITEM_T));
   if (newItem == NULL)
       {
       bOk = 0;
       }
   else
       {
       newItem->data = data;  /* store the data */
       if (head == NULL)       /* nothing in the queue yet */
          {
    head = newItem;      
          }
       else
          {
    tail->next = newItem;  /* add to the end of the queue */ 
          }
       tail = newItem;         /* either way the new item is now the end */
       count++;
       }
   return bOk;

}

VERTEX_T * findVertexByKey(char* key, VERTEX_T** pPred) 
    {
    VERTEX_T * pFoundVtx = NULL;
    VERTEX_T * pCurVertex = vListHead;
    *pPred = NULL;
   
    while ((pCurVertex != NULL) && (pFoundVtx == NULL))
       {
       if (strcmp(pCurVertex->key,key) == 0)
          {
          pFoundVtx = pCurVertex;
          }

       else
          {
          *pPred = pCurVertex;
          pCurVertex = pCurVertex->next;
          }
       }
    return pFoundVtx;
    }

void freeAdjacencyList(VERTEX_T *pVertex)
{
   ADJACENT_T * pCurRef = pVertex->adjacentHead;
   while (pCurRef != NULL)
      {
      ADJACENT_T * pDelRef = pCurRef;
      pCurRef = pCurRef->next;
      free(pDelRef);
      }
   pVertex->adjacentHead = NULL;
   pVertex->adjacentTail = NULL;
}

char** getAdjacentVertices(char* key, int* pCount)
{
    char** keyArray = NULL;
    VERTEX_T * pDummy = NULL;
    VERTEX_T * pFoundVtx = findVertexByKey(key,&pDummy);
    if (pFoundVtx != NULL)
       {
       *pCount = countAdjacent(pFoundVtx);
       if (*pCount > 0)
          {
    int i = 0;
    keyArray = (char**) calloc(*pCount, sizeof(char*));
          if (keyArray != NULL)
       {
       ADJACENT_T * pAdjacent = pFoundVtx->adjacentHead;
       while (pAdjacent != NULL)
          {
    VERTEX_T* pVertex = (VERTEX_T*) pAdjacent->pVertex;
    keyArray[i] = strdup(pVertex->key);
    pAdjacent = pAdjacent->next;
    i += 1;
          }
       }
          } 
       } 
    else
       {
       *pCount = -1;
       }
    return keyArray;
}

int findEdge(char* key1, char* key2)
{
    int weight = -1;
    int bEdgeExists = 0;
    VERTEX_T * pDummy = NULL;
    VERTEX_T * pFrom = findVertexByKey(key1,&pDummy); 
    ADJACENT_T * pCurRef = pFrom->adjacentHead;
    while ((pCurRef != NULL) && (!bEdgeExists))
       {
       VERTEX_T * pFrom = (VERTEX_T*) pCurRef->pVertex;
       if (strcmp(pFrom->key,key2) == 0)
          {
    weight = pCurRef->weight;  
          bEdgeExists = 1;
          }
       else
          {
    pCurRef = pCurRef->next;
          }
       } 
    return weight;
}


void initAll()
{
    VERTEX_T* pVertex = vListHead;
    while (pVertex != NULL)
       {
       pVertex->dValue = 999999999;
       pVertex->parent = NULL;
       enqueueMin(pVertex);
       pVertex = pVertex->next;
       }
}


void queueMinDebug()
{
   int i, j;
   printf("count = %d   head = %p  tail = %p\n",
    count, head, tail);
   if (count > 0)
      {
      printf("Contents: \n");
      LISTITEM_T * item = head;
      while (item != NULL)
        {
  printf("\t\t%s\n", item->data);
  item = item->next;
  }
      }
}

int enqueue(void* data)
{
   int bOk = 1;
   LISTITEM_T * newItem = (LISTITEM_T *)calloc(1,sizeof(LISTITEM_T));
   if (newItem == NULL)
       {
       bOk = 0;
       }
   else
       {
       newItem->data = data;  /* store the data */
       if (head == NULL)       /* nothing in the queue yet */
          {
    head = newItem;      
          }
       else
          {
    tail->next = newItem;  /* add to the end of the queue */ 
          }
       tail = newItem;         /* either way the new item is now the end */
       count++;
       }
   return bOk;
}


/* Get the next item in the queue. This is the element 
 * at the front of the queue.
 * Returns the data stored at the front of the queue.
 * Also removes that item from the queue.
 * Returns NULL if the queue is empty.
 */
void * dequeue()
{
   void * returnData = NULL;
   if (count > 0)
      {
      LISTITEM_T * firstItem = head;
      returnData = firstItem->data;
      head = firstItem->next;
      if (head == NULL)  /* if that was the last item on the queue */
    tail = NULL;
      free(firstItem);
      count--;
      }
   return returnData;
}


/* Find out how many items are currently in the queue.
 * Return number of items in the queue (could be zero)
 */
int queueSize()
{
   return count;
}


/* Clear so we can reuse 
 */
void queueClear()
{
    int i = 0;
    LISTITEM_T * item = head;
    LISTITEM_T * freeItem = NULL;
    while (item != NULL)
       {
       freeItem = item;
       item = item->next;
       free(freeItem);
       }
    /* reset head, tail and count */
    head = NULL;
    tail = NULL;
    count = 0;
}

int getMaxVertices()
{
    return maxGraphVertices;
}

/* Return the "directed" flag
 */
int isDirected()
{
    return bGraphDirected;
}

/* Reset the current vertex list pointer to the head
 * of the list. Used for iterating through the vertices
 * in order to get their keys for the networkWriter module.
 */
void resetVertexList()
{
    currentVertex = vListHead;
}

/* Get the key of the current vertex, then
 * move the current pointer to the next vertex in the list.
 *   returns key of the current vertex or NULL if we are at
 *       the end of the list
 */
char * getNextVertex()
{
     
    char* key = NULL;
    if (currentVertex != NULL)
       {
       key = currentVertex->key;
       currentVertex = currentVertex->next;
       } 
    return key;     
}
 

/* Free all memory associated with the graph and
 * reset all parameters.
 */
void clearGraph()
{
    VERTEX_T * pCurVertex = vListHead;
    while (pCurVertex != NULL)
       {
       freeAdjacencyList(pCurVertex);
       VERTEX_T * pDelVtx = pCurVertex;
       pCurVertex = pCurVertex->next;
       free(pDelVtx->key);
       free(pDelVtx);
       }

    vListHead = NULL;  
    vListTail = NULL; 
    bGraphDirected = 0;

}


void traverseBreadthFirst(VERTEX_T* pVertex,char* endkey,void (*vFunction)(VERTEX_T*))
{
    VERTEX_T * pCurrentVertex = NULL;
    VERTEX_T * pAdjVertex = NULL;    
    queueClear();
    colorAll(WHITE);
    pVertex->color = GRAY;
    enqueue(pVertex);
    while (queueSize() > 0)
       {
       pCurrentVertex = (VERTEX_T*) dequeue();
       if (pCurrentVertex->color != BLACK)
          {
          (*vFunction)(pCurrentVertex);
          printf("with %s\n",endkey);
          pCurrentVertex->color = BLACK;
    ADJACENT_T* pAdjacent = pCurrentVertex->adjacentHead;
    while (pAdjacent != NULL)
             {
       pAdjVertex = (VERTEX_T*) pAdjacent->pVertex;
       if (pAdjVertex ->color != BLACK)
           {
     pAdjVertex->color = GRAY;
     enqueue(pAdjVertex);
           }
       pAdjacent = pAdjacent->next;
             }
    }
       } /* end while queue has data */
}


void findVertexGender(int Relation, PERSON_T** pPred2)
  {
   /* VERTEX_T * pFoundVtx = NULL;
    VERTEX_T * pCurVertex = vListHead;
    *pPred = NULL;
   
    while ((pCurVertex != NULL) && (pFoundVtx == NULL))
       {
       if (strcmp(pCurVertex->key,key) == 0)
          {
          pFoundVtx = pCurVertex;
          }

       else
          {
          *pPred = pCurVertex;
          pCurVertex = pCurVertex->next;
          }
       }
    return pFoundVtx;*/
   
  }

int addVertex(char* key, void* pData)
    {
    int bOk = 1;
    VERTEX_T * pPred;
    VERTEX_T * pFound = findVertexByKey(key, &pPred);

    if (pFound != NULL)  
       {
        printf("Exist again!!\n");
       bOk = -1;
       }
    else
       {
       VERTEX_T * pNewVtx = (VERTEX_T *) calloc(1,sizeof(VERTEX_T));
       
       char * pKeyval = strdup(key);

       if ((pNewVtx == NULL) || (pKeyval == NULL))
          {
	         bOk = 0;  
	        }
       else
          {
	        pNewVtx->key = pKeyval;
          pNewVtx->data = pData;
	  if (vListHead == NULL)  
	     {
	     vListHead = pNewVtx;
	     }
	  else
	     {
	     vListTail->next = pNewVtx; 
	     }
	  vListTail = pNewVtx;
	  vertexCount++; 
	  }

       }
  return bOk;
  } 


int edgeExists(VERTEX_T* pFrom, VERTEX_T* pTo)
   {
    int bEdgeExists = 0;
    ADJACENT_T * pAdjacent = pFrom->adjacentHead;

    while ((pAdjacent != NULL) && (!bEdgeExists))
       {
       if (pAdjacent->pVertex == pTo)
          {
	        bEdgeExists = 1;  
          }
       else
          {
	         pAdjacent = pAdjacent->next;
          }
       } 
    return bEdgeExists;
    }


void* findVertex(char* key)
    {
    void* pData = NULL;
    VERTEX_T * pDummy = NULL;
    VERTEX_T * pFoundVtx = findVertexByKey(key,&pDummy);

    if (pFoundVtx != NULL)
       {
       pData = pFoundVtx->data;
       }

    return pData; 
    }

int addEdge(char* key1, char* key2, int weight)
    {
    int bOk = 1;
    VERTEX_T * pDummy = NULL;
    VERTEX_T * pFromVtx = findVertexByKey(key1,&pDummy);
    VERTEX_T * pToVtx = findVertexByKey(key2,&pDummy);
    if ((pFromVtx == NULL) || (pToVtx == NULL))
       {
       bOk = 0;
       }
    else if (edgeExists(pFromVtx,pToVtx))
       {
       bOk = -1;	   
       }
    else
       {
       weightSum = weightSum + weight;
       if (weight < 0)
	         {
            bHasNeg = 1;
            }
       ADJACENT_T * pNewRef = (ADJACENT_T*) calloc(1,sizeof(ADJACENT_T));

       if (pNewRef == NULL)
          {
	       bOk = 0;
          }
       else
          {
	         pNewRef->pVertex = pToVtx;
           pNewRef->weight = weight; 
	         if (pFromVtx->adjacentTail != NULL)
              {
	            pFromVtx->adjacentTail->next = pNewRef;
	            }
          else
	            {
	            pFromVtx->adjacentHead = pNewRef;
	            }
	         pFromVtx->adjacentTail = pNewRef;
           } 
       }

       if ((bOk) && (!bGraphDirected))
          {
          ADJACENT_T * pNewRef2 = (ADJACENT_T*) calloc(1,sizeof(ADJACENT_T));
          
          if (pNewRef2 == NULL)
            {
	          bOk = 0;
            }
          else
          {
	         pNewRef2->pVertex = pFromVtx;
           pNewRef2->weight = weight; 
	         
           if (pToVtx->adjacentTail != NULL)
              {
	             pToVtx->adjacentTail->next = pNewRef2;
	             }
          else
	             {
	            pToVtx->adjacentHead = pNewRef2;
	             }
	  
      pToVtx->adjacentTail = pNewRef2;
            } 
        } 
    return bOk;
  }


int AddRel(char* relation)
    {
    int relVal = -1;
    
  

    if(strcasecmp(relation,"mother")==0)
        {
        relVal = mother;      
        }
    if(strcasecmp(relation,"father")==0)
        {
        relVal = father;
        }

    if(strcasecmp(relation,"son")==0)
        {
        relVal = son;
        }
    if(strcasecmp(relation,"daughter")==0)
        {
         relVal = daughter;
        }
    if(strcasecmp(relation,"brother")==0)
        {
        relVal = brother;  
        }
    if(strcasecmp(relation,"sister")==0)
        {
        relVal = sister; 
        }

 if(strcasecmp(relation,"wife")==0)
        {
        relVal = wife;
        }

 if(strcasecmp(relation,"husband")==0)
        {
        relVal = husband; 
        }
 if(strcasecmp(relation,"uncle")==0)
        {
        relVal = uncle;
        }
 if(strcasecmp(relation,"aunt")==0)
        {
        relVal = aunt; 
        }
 if(strcasecmp(relation,"grandmother")==0)
        {
        relVal = grandmother;
        }
 if(strcasecmp(relation,"grandfather")==0)
        {
        relVal = grandfather;
        }
    return relVal;   
}

void relAsk(char* first,char* last,char* relation)
    {

    retRel = AddRel(relation);
    key1 = strdup(first);
    key2 = strdup(last);
    weight = 0;

    if(retRel==-1)
      {
      printf("\tError please enter a valid relationship\n");
      }


   /* if(retRel>=0&&retRel<6)
      {
      printf("\n%s is men",first);
      }
    if(retRel>5&&retRel<12);
      } 
      */
  newString = strdup(relation);
  
  PERSON_T * pPred2;
  VERTEX_T * pPred;
  VERTEX_T * pFound = findVertexByKey(key1, &pPred);

  if(pFound != NULL)
    {
    printf("again\n");
    findVertexGender(retRel,&pPred2);

    }

    if(strcasecmp(newString,"Father") == 0 || strcasecmp(newString,"mother") == 0)
      {
      newString2 = "son or daughter";
      weight = 1;
      }
    else if(strcasecmp(newString,"grandfather") == 0 || strcasecmp(newString,"grandmother") == 0)
      {
      newString2 = "grandson or grandDaughter";
      }
    else if(strcasecmp(newString,"brother") == 0 || strcasecmp(newString,"sister") == 0)
      {
      newString2 = "brother or sister";
      }
    else if(strcasecmp(newString,"husband") == 0)
      {
      newString2 = "wife";
      }
    else if(strcasecmp(newString,"wife") == 0)
      {
      newString2 = "husband";
      }
    else if(strcasecmp(newString,"son") == 0 || strcasecmp(newString,"daughter") == 0)
      {
      newString2 = "mother or father";
      }

 retVal_Vertex1 = addVertex(key1,newString);
 retVal_Vertex2 = addVertex(key2,newString2);


if(retRel != -1)
{
		   if (retVal_Vertex1 == 1 || retVal_Vertex2 == 1 ) 
		      {
		      printf("\n\tRelation |%s| ,|%s| added\n",key1,key2);
		      }
		   else if (retVal_Vertex1 < 0 || retVal_Vertex2 < 0)
		      {
		      printf("\t>>> Relation |%s|,|%s| already exists\n", key1,key2);
		      }
		   else 
		      {
		      printf("\t>>> Memory allocation error or graph full!\n");
		      }
		   

retValEdge = addEdge(first,last,weight);
//printf("\n%d\n",retValEdge);

  if (retValEdge == 1) 
		       {
		       printf("\tAdded Relation from |%s| with |%s|\n",first,last);
		       }
		       else if (retVal < 0)
		       {
		       printf("\t>>> Relation from |%s| with |%s| already exists!\n",
				  first,last);
		       }
		       else 
		       {
		       printf("\t\n>>> doesn't exist or memory allocation error!\n");
		       }      
    printf("\n\n\t------------------------------------------------\n");     
    }
}

void traverseDepthFirst(VERTEX_T* pVertex, void (*vFunction)(VERTEX_T*))
{
    VERTEX_T * pAdjVertex = NULL;    
    ADJACENT_T* pAdjacent = pVertex->adjacentHead;
    while (pAdjacent != NULL)
       {
       pAdjVertex = (VERTEX_T*) pAdjacent->pVertex;
       if (pAdjVertex->color == WHITE)
     {
     pAdjVertex->color = GRAY;
           traverseDepthFirst(pAdjVertex,vFunction);
           }
       pAdjacent = pAdjacent->next;  
       } /* end while queue has data */
    /* when we return from the bottom, call the 
     * function and color this node black.
     */
    (*vFunction)(pVertex);
    pVertex->color = BLACK;
}




int printBreadthFirst(char* startKey,char* endkey)
{
   int retval = 1;
   VERTEX_T * pDummy = NULL;
   VERTEX_T * pVertex = findVertexByKey(startKey,&pDummy);
   VERTEX_T * pVertex2 = findVertexByKey(endkey,&pDummy);
   if (pVertex == NULL && pVertex2 == NULL)
      {
      retval = -1;
      }
   else
      {
      traverseBreadthFirst(pVertex,endkey,&printVertexInfo);
      }
   return retval;
}

/*void printDepthFirst()
{
   VERTEX_T* pVertex = vListHead;
   if (pVertex == NULL)
      {
      printf("The graph is empty\n");
      }
   else
      {
      colorAll(WHITE);
      while (pVertex != NULL)
         {
         if (pVertex->color == WHITE)
            {
            printf("\nStarting new traversal from |%s|\n",
            pVertex->key);
            pVertex->color = GRAY;
            traverseDepthFirst(pVertex,&printVertexInfo);
            }
         pVertex = pVertex->next;
         }
      }
}
*/

