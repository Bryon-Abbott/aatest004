// Manage messages
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "response.h"
#include "aamsg.h"



char* aaResponseMessage(AA_Response r) 
{
    cJSON *root;

    root=cJSON_CreateObject();                              //  Create root data object 
    cJSON_AddNumberToObject(root,"ResCode", r.aaRespCode);  //  Add key value pair for Code
    cJSON_AddStringToObject(root,"ResDesc", r.aaRespDesc);  //  Add key value pair for Desc

    char *out = cJSON_PrintUnformatted(root);   //  take json Convert form to string 

    // Free memory   
    cJSON_Delete(root);  
    // free(out);        
    return out; 
}

char* aaRegisterMessage(char *ma)
{
    cJSON *root;
    cJSON *data;

    root=cJSON_CreateObject();                           //  Create root data object 
    cJSON_AddStringToObject(root,"Action", "Register");  //  Add key value pair for Code
    
    data=cJSON_CreateObject(); 
    cJSON_AddItemToObject(root, "Data", data); 

    cJSON_AddStringToObject(data,"Loc", "AbbottHouse");  //  Add key value pair for Code
    cJSON_AddStringToObject(data,"SubLoc", "Office");  //  Add key value pair for Code
    cJSON_AddStringToObject(data,"Ctrl", "C001");  //  Add key value pair for Code
    cJSON_AddStringToObject(data,"Dev", "D001");  //  Add key value pair for Code
    cJSON_AddStringToObject(data,"Type", "Led");  //  Add key value pair for Code
    cJSON_AddStringToObject(data,"Mac", ma);  //  Add key value pair for Code

    char *out = cJSON_PrintUnformatted(root);   //  take json Convert form to string 

    //  Free memory   
    cJSON_Delete(root);  
    //cJSON_Delete(data);  
    // free(out);        
    return out; 
}
char* aaHeartbeatMessage(void)
{
    cJSON *root;
 
    root=cJSON_CreateObject();                           //  Create root data object 
    cJSON_AddStringToObject(root,"Action", "Heartbeat");  //  Add key value pair for Code

    char *out = cJSON_PrintUnformatted(root);   //  take json Convert form to string 

    //  Free memory   
    cJSON_Delete(root);  
    //cJSON_Delete(data);  
    // free(out);        
    return out; 
}