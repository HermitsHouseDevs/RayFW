/*

- RFW JSON Module -

This Addition adds Easy Json Functionality to RayFW. 


- Hermits House 

*/
#pragma once

#ifndef RJSON_H
#define RJSON_H

#include <stdio.h>
#include <stdlib.h>

#include "external/cJSON/cJSON.h"

// Definitions 
#define JSONBufferSize 3000
#define JSONRootStack 16

// Data Structures 
typedef struct JsonData {
    cJSON *Root;
    cJSON *Subroot;
    char *JsonBuffer;

    cJSON *RootStack[JSONRootStack];
    int StackTop;
} JsonData;

// File IO
JsonData LoadJSON(const char *Path);
void UnloadJSON(JsonData JData);

// Root Manipulation
void JSONSetDefaultRoot(JsonData *JData);
void JSONSetRoot(JsonData *JData, const char *RootKey);
void JSONPopRoot(JsonData *JData);

// Data IO
int JSONFindInteger(JsonData *JData, const char *RootKey);
float JSONFindFloat(JsonData *JData, const char *RootKey);
const char *JSONFindString(JsonData *JData, const char *RootKey);
int JSONFindIntegerInArray(JsonData *JData, const char *RootKey, int Index);
float JSONFindFloatInArray(JsonData *JData, const char *RootKey, int Index);
const char *JSONFindStringInArray(JsonData *JData, const char *RootKey, int Index);

#endif
