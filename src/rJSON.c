#include "rJSON.h"

JsonData LoadJSON(const char *Path) {
    JsonData JData;
    
    JData.Root = NULL;
    JData.Subroot = NULL;
    JData.JsonBuffer = NULL;

    // Open the file
    FILE *JFile = fopen(Path, "r");
    if (!JFile) {
        printf("RFW: Failed to open JSON File: %s\n", Path);
        return JData; // Return empty data structure
    } else {
        printf("RFW: Loaded %s Successfully\n", Path);
    }

   
    fseek(JFile, 0, SEEK_END);
    long fileSize = ftell(JFile);
    fseek(JFile, 0, SEEK_SET);

    // Check file size against buffer size
    if (fileSize >= JSONBufferSize) {
        printf("RFW: File size exceeds buffer size\n");
        fclose(JFile);
        return JData;
    }

    // Allocate memory for the JSON buffer
    JData.JsonBuffer = (char *)malloc(fileSize + 1);
    if (!JData.JsonBuffer) {
        printf("RFW: Memory allocation failed\n");
        fclose(JFile);
        return JData;
    }

    // Read the file content into the buffer
    fread(JData.JsonBuffer, 1, fileSize, JFile);
    JData.JsonBuffer[fileSize] = '\0'; 
    fclose(JFile);

    JData.Root = cJSON_Parse(JData.JsonBuffer);
    if (!JData.Root) {
        printf("RFW: Failed to parse JSON\n");
        free(JData.JsonBuffer); 
    }

    return JData;
}

void UnloadJSON(JsonData JData) {
    if (JData.JsonBuffer) free(JData.JsonBuffer);
    if (JData.Root) cJSON_Delete(JData.Root);
}

void JSONSetDefaultRoot(JsonData *JData) {
    if (!JData || !JData->Root) return;
    JData->Subroot = JData->Root;
    JData->StackTop = 0;
    JData->RootStack[JData->StackTop] = JData->Root;
}

void JSONSetRoot(JsonData *JData, const char *RootKey) {
    if (!JData || !JData->Subroot) return;

    if (JData->StackTop + 1 >= JSONRootStack) {
        printf("RFW: Root stack overflow\n");
        return;
    }

    cJSON *Child = cJSON_GetObjectItem(JData->Subroot, RootKey);
    if (Child && cJSON_IsObject(Child)) {
        JData->Subroot = Child;
        JData->StackTop++;
        JData->RootStack[JData->StackTop] = Child;
    } else {
        printf("RFW: Failed to find object key: %s\n", RootKey);
    }
}

void JSONPopRoot(JsonData *JData) {
    if (!JData || JData->StackTop == 0) {
        return;
    }

    JData->StackTop--;
    JData->Subroot = JData->RootStack[JData->StackTop];
}



int JSONFindInteger(JsonData *JData, const char *RootKey) {
    if (!JData || !JData->Subroot) return 0;

    cJSON *Item = cJSON_GetObjectItem(JData->Subroot, RootKey);
    if (Item && cJSON_IsNumber(Item)) {
        return Item->valueint;
    } else {
        printf("RFW: Integer key not found: %s\n", RootKey);
        return 0;
    }
}

float JSONFindFloat(JsonData *JData, const char *RootKey) {
    if (!JData || !JData->Subroot) return 0.0f;

    cJSON *Item = cJSON_GetObjectItem(JData->Subroot, RootKey);
    if (Item && cJSON_IsNumber(Item)) {
        return (float)Item->valuedouble;
    } else {
        printf("RFW: Float key not found: %s\n", RootKey);
        return 0.0f;
    }
}

const char *JSONFindString(JsonData *JData, const char *RootKey) {
    if (!JData || !JData->Subroot) return NULL;

    cJSON *Item = cJSON_GetObjectItem(JData->Subroot, RootKey);
    if (Item && cJSON_IsString(Item)) {
        return Item->valuestring;
    } else {
        printf("RFW: String key not found: %s\n", RootKey);
        return NULL;
    }
}

int JSONFindIntegerInArray(JsonData *JData, const char *RootKey, int Index) {
    if (!JData || !JData->Subroot) return 0;

    cJSON *Array = cJSON_GetObjectItem(JData->Subroot, RootKey);
    if (Array && cJSON_IsArray(Array)) {
        cJSON *Item = cJSON_GetArrayItem(Array, Index);
        if (Item && cJSON_IsNumber(Item)) {
            return Item->valueint;
        } else {
            printf("RFW: Invalid or non-integer item at index %d in array: %s\n", Index, RootKey);
        }
    } else {
        printf("RFW: Array key not found or is not an array: %s\n", RootKey);
    }

    return 0;
}

float JSONFindFloatInArray(JsonData *JData, const char *RootKey, int Index) {
    if (!JData || !JData->Subroot) return 0.0f;

    cJSON *Array = cJSON_GetObjectItem(JData->Subroot, RootKey);
    if (Array && cJSON_IsArray(Array)) {
        cJSON *Item = cJSON_GetArrayItem(Array, Index);
        if (Item && cJSON_IsNumber(Item)) {
            return (float)Item->valuedouble;
        } else {
            printf("RFW: Invalid or non-float item at index %d in array: %s\n", Index, RootKey);
        }
    } else {
        printf("RFW: Array key not found or is not an array: %s\n", RootKey);
    }

    return 0.0f;
}

const char *JSONFindStringInArray(JsonData *JData, const char *RootKey, int Index) {
    if (!JData || !JData->Subroot) return NULL;

    cJSON *Array = cJSON_GetObjectItem(JData->Subroot, RootKey);
    if (Array && cJSON_IsArray(Array)) {
        cJSON *Item = cJSON_GetArrayItem(Array, Index);
        if (Item && cJSON_IsString(Item)) {
            return Item->valuestring;
        } else {
            printf("RFW: Invalid or non-string item at index %d in array: %s\n", Index, RootKey);
        }
    } else {
        printf("RFW: Array key not found or is not an array: %s\n", RootKey);
    }

    return NULL;
}