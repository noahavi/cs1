#include <stdlib.h>
#include <stdio.h>
#include "LonelyPartyArray.h"








LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length){
    if( (num_fragments>0)&&(fragment_length>0) ){
        LonelyPartyArray *createdArray;
        createdArray = (LonelyPartyArray *)malloc( sizeof(LonelyPartyArray) );
        if(createdArray==NULL){
            return NULL;
        }
        createdArray->fragment_length = fragment_length;
        createdArray->num_fragments = num_fragments;
        createdArray->num_active_fragments = 0;
        createdArray->size = 0;
        createdArray->fragments = (int ** )calloc(num_fragments,sizeof(int *));
        if(createdArray->fragments==NULL){
            free(createdArray);
            return NULL;
        }
        createdArray->fragment_sizes = (int*)calloc(num_fragments,sizeof(int));
        if(createdArray->fragment_sizes == NULL){
            free(createdArray->fragments);
            free(createdArray);
            return NULL;
        }
        printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n",createdArray->size,createdArray->num_fragments);
        return createdArray;
    }else{
        return NULL;
    }
}
//Function 2:
LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party){
    if(party!=NULL){
        if(party->fragment_sizes!=NULL){
            free(party->fragment_sizes);
        }
        if(party->fragments!=NULL){
            free(party->fragments);
        }
        printf("-> The LonelyPartyArray has returned to the void.\n");
        free(party);
    }
    return NULL;
}
//Function 3:
int set(LonelyPartyArray *party, int index, int key){
    if(party!=NULL)
    {
        int fragment_num = index/party->fragment_length;
        int index_in_fragment = index%party->fragment_length;
        if( (index>=0) && ( index<= ( party->num_fragments*party->fragment_length-1 )))
        {
            if(party->fragments[fragment_num]==NULL)
            {
                party->fragments[fragment_num] = (int *)calloc(party->fragment_length,sizeof(int));
                if(party->fragments[fragment_num]==NULL)
                {
                    return LPA_FAILURE;
                }
                int i;
                for(i=0;i<party->fragment_length;++i)
                {
                    party->fragments[fragment_num][i]=UNUSED;
                }
                party->fragments[fragment_num][index_in_fragment] = key;
                //updating the LPA variables
                party->num_active_fragments = party->num_active_fragments+1;
                printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n",fragment_num,party->fragment_length,party->fragment_length*fragment_num,(((party->fragment_length*fragment_num)+party->fragment_length)-1));
            }
            else
            {
                party->fragments[fragment_num][index_in_fragment] = key;
            }
            //updating LPA variables
            party->size = party->size+1;
            party->fragment_sizes[fragment_num] = party->fragment_sizes[fragment_num]+1;
        }
        else
        {
            printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d,offset: %d)\n",index,fragment_num,index_in_fragment);
            return LPA_FAILURE;
        }
    }
    else
    {
        printf("-> Bloop! NULL pointer detected in set().\n");
        return LPA_FAILURE;
    }
}
//Function 4
int get(LonelyPartyArray *party, int index){
    if(party!=NULL){
        int fragment_num = index/party->fragment_length;
        int index_in_fragment = index%party->fragment_length;
        if( (index>=0) && ( index<= ( party->num_fragments*party->fragment_length-1 ) ) )
        {
           if(party->fragments[fragment_num]==NULL)
           {
               return UNUSED;
           }
           else
           {
               return party->fragments[fragment_num][index_in_fragment];
           }
        }
        else
        {
            printf("-> Bloop! Invalid access in get(). (index:%d, fragment: %d, offset: %d)\n",index,fragment_num,index_in_fragment);
            return LPA_FAILURE;
        }
    }
    else
    {
        printf("> Bloop! NULL pointer detected in get().\n");
        return LPA_FAILURE;
    }
}