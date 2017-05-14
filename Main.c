#include<stdio.h>
#include<stdlib.h>
#include<math.h>
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



int main()
    {
    char buffer[64];
    int input4;
    int relVal = 0;
    int retval = 0;
    char input[64];
    char input3[64];
    char input2[64];
    char keystring1[64] = "";
    char keystring2[64] = "";
    char first[64] = "";
    char last[64]  = "";
    char relation[32];
    int retRel = -1;
    int  i = 0;
    int  count = 0;
    char outputBuffer[128];
    char outputFileName[64];
    int  keep = 50;
    int  vbvb = 0;
    FILE* pOut = NULL;
    int flag =0;
    char* newString = NULL;
    char filename[64] = "";
    int status = 0;

    PERSON_T* pPerson1 = NULL;
    PERSON_T* pPerson2 = NULL;
    PERSON_T** people  = NULL;


        while(1)
        {
        flag=0;
        printf("\n\n--------- Welcome to Family Bonding Platform -------------\n\n");
        printf("---------1:      Add a relationship    -------------------\n");
        printf("---------2:    Search a relationship   -------------------\n");
        printf("---------3: Save the information to files ----------------\n");
        printf("---------4:       Import the file      -------------------\n");
        printf("---------5:       Exit the program     -------------------\n\n");
        printf("---------6:        Traverse print      -------------------\n\n");
        while(flag!=1)
            {
            printf("\n\n \t   ---->> Please enter any choice(1-5):  ");
            fgets(buffer,sizeof(buffer),stdin);
            sscanf(buffer,"%d",&input4);
            switch (input4)

                {

                case 1:
                printf("\n\n\t------------------------------------------------\n");
                do
                {
                memset(first,0,sizeof(first));
        		printf("\n \t  -->> Person1:  ");
        		fgets(input3,sizeof(input3),stdin);
        		sscanf(input3,"%s",first);  

                if (strcasecmp(first,"DONE")==0)
                    {
                    flag = 1;
                    break;
                    }

                printf("\n \t  -->> RELATIONSHIP(Person1 with Person2):  ");
                fgets(buffer,sizeof(buffer),stdin);//
                sscanf(buffer,"%s",relation);//
                

                memset(input3,0,sizeof(input3));
        		printf("\n \t  -->> Person2:  ");
        		fgets(input3,sizeof(input3),stdin);
        		input3[strlen(input3) - 1] = '\0';  
        		sscanf(input3,"%s",last);


                if ((strlen(first) == 0) || (strlen(last) == 0))
        		   {
        		   printf("Input error - a key is empty!\n");
        		   }
        		else if (strcmp(first,last) == 0)
        		   {
        		   printf("Input error - 'From' must be different from 'To'!\n");
        		   }
            
                relAsk(first,last,relation);

                people = (PERSON_T**) calloc(1,sizeof(PERSON_T*));

                if (people == NULL) 
                    {
                    printf("Error allocating array\n");
                    exit(3);
                    }

                PERSON_T * pPerson1 = (PERSON_T *) calloc(1,sizeof(PERSON_T));

       
                if (pPerson1 == NULL)
            	    {
            	    printf("Memory allocation error ");
                    exit(4);
            	    }
                else
                    {
                    strcpy(pPerson1->name,first);

                    retRel = AddRel(relation);

                    if(retRel >= 0 && relVal <= 11)
                    {
                    if(retRel == 0)
                        {
                        pPerson1->Relation = father;
                        flag=1;
                        }
                    else if(retRel == 6)
                        {
                        pPerson1->Relation = mother;
                        flag=1;
                        }
                    else if(retRel == 1)
                        {
                        pPerson1->Relation = son;
                        flag=1;
                        }
                    else if(retRel == 7)
                        {
                        pPerson1->Relation = daughter;
                        flag=1;
                        }
                    else if(retRel = 2)
                        {
                        pPerson1->Relation = brother;
                        flag=1;
                        }
                    else if(retRel = 8)
                        {
                        pPerson1->Relation = sister;
                        flag=1;
                        }
                    else if(retRel = 9)
                        {
                        pPerson1->Relation = wife;
                        flag=1;
                        }
                    else if(retRel = 3)
                        {
                        pPerson1->Relation = husband;
                        flag=1;
                        }
                    else if(retRel = 10)
                        {
                        pPerson1->Relation = aunt;
                        flag=1;
                        }
                    else if(retRel = 4)
                        {
                        pPerson1->Relation = uncle;
                        flag=1;
                        }
                    else if(retRel = 11)
                        {
                        pPerson1->Relation = grandmother;
                        flag=1;
                        }
                    else if(retRel = 5)
                        {
                        pPerson1->Relation = grandfather;
                        flag=1;
                        }
                    else
                        {
                        flag = 1;
                        }
                    }

                    people[i] = pPerson1;
                   
                    //printf("Name:%s i = %d",people[count]->name,count);
                   // count++;    /*For checking i value*/
                    
                    i++;
                    }
                   
                    PERSON_T * pPerson2 = (PERSON_T *) calloc(1,sizeof(PERSON_T));

                    if(pPerson2 == NULL)
	                    {
	                    printf("Memory allocation error");
                        exit(5);
	                    }
                    else
                        {
                        strcpy(pPerson2->name,last);
                        }
                    }while(1);
                    break;

                    case 2:
                    printf("\n\n\t------------------------------------------------\n");
                    break;

                    case 3:
                    printf("\n\n \t ------------------------------------------------\n");
                     printf("Enter filename for output: ");
                    fgets(input,sizeof(input),stdin);
                    memset(filename,0,sizeof(filename));
                    sscanf(input,"%s",filename);
                    if (strlen(filename) == 0)
                        {
                        printf("  Please enter a filename!\n");
                        }
                    else
                        {
                        status = writeNetwork(filename);
                   if (status)
                        printf("Successfully saved network to file '%s'\n",filename);
                    else
                    printf("Error saving network information\n");
                     }

          
                    break;

                    case 4:
                    printf("\n\n\t------------------------------------------------\n");
                    break;


                    case 5 :
                    printf("\n\n\t------------------------------------------------\n");
                    return 0;
                    break;

                    case 6 :
                    {
                int count;
                int weight = 0;
                char** adjacentKeys = NULL;
                memset(input,0,sizeof(input));
        printf("Enter key value: ");
        fgets(input,sizeof(input),stdin);
        input[strlen(input) - 1] = '\0';  
        sscanf(input,"%s",keystring1);  
                adjacentKeys = getAdjacentVertices(keystring1,&count);
                if (count == 0)
           {
           printf(">>> Vertex |%s| has no adjacent vertices\n",
                  keystring1);
           }
                else if (count < 0)
           { 
           printf(">>> Vertex |%s| does not exist\n",
                  keystring1);
           }
        else
           {
           int i = 0;
           printf("The following vertices are incident from |%s|\n",
              keystring1);
           for (i = 0; i < count; i++)
              {
              printf("     %s ",adjacentKeys[i]);
                      weight = findEdge(keystring1,adjacentKeys[i]);
                      if(weight == 1)
                        {
                         printf(" son or daughter\n");
                        }
                      if(weight == 2)
                        {
                         printf("grandson or grandDaughter\n");
                        }
                      if(weight == 3)
                        {
                         printf("brother or sister\n");
                        }
                      if(weight == 4)
                        {
                         printf("wife\n");
                        }
                      if(weight == 5)
                        {
                         printf("husband\n");
                        }
                      if(weight == 6)
                        {
                         printf("Mother or father\n");
                        }
                      printf(" (weight %d)\n", weight);
              free(adjacentKeys[i]);
              }
           free(adjacentKeys);
           }
                    break;
                    }
                    default:
                    printf("\n*************** INVALID OPTION ENTERED!! **********************");
                    break;

                }

              }
          }
       }

