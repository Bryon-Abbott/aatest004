// Manage messages
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "response.h"
#include "aamsg.h"

char* jsonResponseMessage(AA_Response r) 
{
    cJSON *root;
    cJSON *arry;

    root=cJSON_CreateObject();                              //  Create root data object 
    cJSON_AddNumberToObject(root,"ResCode", r.aaRespCode);  //  Add key value pair for Code
    cJSON_AddStringToObject(root,"ResDesc", r.aaRespDesc);  //  Add key value pair for Desc

    char *out = cJSON_PrintUnformatted(root);   //  take json Convert form to string 

    //  Free memory   
    // cJSON_Delete(root);  
    // free(out);        
    return out; 
}