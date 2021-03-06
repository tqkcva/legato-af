/**
 * Implement echo test API in C
 *
 * Copyright (C) Sierra Wireless Inc.
 */

#include "legato.h"
#include "interfaces.h"

#include <string.h>

#define MAX_VALUE_SIZE  257
#define VALUE_ENTRIES   6

typedef struct OutArrayInfo
{
    void* arrayPtr;
    size_t outArraySize;
} OutArrayInfo_t;

LE_MEM_DEFINE_STATIC_POOL(ValuePool, VALUE_ENTRIES, MAX_VALUE_SIZE);
LE_MEM_DEFINE_STATIC_POOL(OutArrayInfoPool, VALUE_ENTRIES, sizeof(OutArrayInfo_t));
LE_MEM_DEFINE_STATIC_POOL(TheStructPool, VALUE_ENTRIES, sizeof(ipcTest_TheStruct_t));
le_mem_PoolRef_t ValuePool;
le_mem_PoolRef_t OutArrayInfoPool;
le_mem_PoolRef_t TheStructPool;


void AsyncServer_EchoSimpleRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    // Weird cast avoids warnings on Ubuntu 14.04
    ipcTest_EchoSimpleRespond(serverCmdPtr,
                              (uint32_t)((size_t)valuePtr));
}

void ipcTest_EchoSimple
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    int32_t InValue
)
{
    // Weird cast avoids warnings on Ubuntu 14.04
    le_event_QueueFunction(AsyncServer_EchoSimpleRespond,
                           serverCmdPtr,
                           (void*)((size_t)InValue));
}

void AsyncServer_EchoSmallEnumRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    ipcTest_EchoSmallEnumRespond(serverCmdPtr,
                                 (ipcTest_SmallEnum_t)((uintptr_t)valuePtr));
}

void ipcTest_EchoSmallEnum
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    ipcTest_SmallEnum_t InValue
)
{
    le_event_QueueFunction(AsyncServer_EchoSmallEnumRespond,
                           serverCmdPtr,
                           (void*)InValue);
}

void AsyncServer_EchoLargeEnumRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    ipcTest_EchoLargeEnumRespond(serverCmdPtr,
                                 *(ipcTest_LargeEnum_t*)valuePtr);
    le_mem_Release(valuePtr);
}


void ipcTest_EchoLargeEnum
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    ipcTest_LargeEnum_t InValue
)
{
    ipcTest_LargeEnum_t* valuePtr = le_mem_AssertAlloc(ValuePool);
    *valuePtr = InValue;

    le_event_QueueFunction(AsyncServer_EchoLargeEnumRespond,
                           serverCmdPtr,
                           valuePtr);
}


void AsyncServer_EchoSmallBitMaskRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    ipcTest_EchoSmallBitMaskRespond(serverCmdPtr,
                                    (ipcTest_SmallBitMask_t)((uintptr_t)valuePtr));
}


void ipcTest_EchoSmallBitMask
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    ipcTest_SmallBitMask_t InValue
)
{
    le_event_QueueFunction(AsyncServer_EchoSmallBitMaskRespond,
                           serverCmdPtr,
                           (void*)((uintptr_t)InValue));
}

void AsyncServer_EchoLargeBitMaskRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    ipcTest_EchoLargeBitMaskRespond(serverCmdPtr,
                                    *(ipcTest_LargeBitMask_t*)valuePtr);
    le_mem_Release(valuePtr);
}


void ipcTest_EchoLargeBitMask
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    ipcTest_LargeBitMask_t InValue
)
{
    ipcTest_LargeBitMask_t* valuePtr = le_mem_AssertAlloc(ValuePool);
    *valuePtr = InValue;

    le_event_QueueFunction(AsyncServer_EchoLargeBitMaskRespond,
                           serverCmdPtr,
                           valuePtr);
}

void AsyncServer_EchoBooleanRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    ipcTest_EchoBooleanRespond(serverCmdPtr, (bool)valuePtr);
}

void ipcTest_EchoBoolean
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    bool InValue
)
{
    le_event_QueueFunction(AsyncServer_EchoBooleanRespond,
                           serverCmdPtr,
                           (void*) InValue);
}


void AsyncServer_EchoResultRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    ipcTest_EchoResultRespond(serverCmdPtr, (le_result_t)((intptr_t) valuePtr));
}

void ipcTest_EchoResult
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    le_result_t InValue
)
{
    le_event_QueueFunction(AsyncServer_EchoResultRespond,
                           serverCmdPtr,
                           (void*) InValue);
}

void AsyncServer_ReturnResultRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    ipcTest_ReturnResultRespond(serverCmdPtr, (le_result_t)((intptr_t) valuePtr));
}


void ipcTest_ReturnResult
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    le_result_t InValue
)
{
    le_event_QueueFunction(AsyncServer_ReturnResultRespond,
                           serverCmdPtr,
                           (void*) InValue);
}


void AsyncServer_EchoOnOffRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    ipcTest_EchoOnOffRespond(serverCmdPtr, (le_onoff_t)((uintptr_t)valuePtr));
}

void ipcTest_EchoOnOff
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    le_onoff_t InValue
)
{
    le_event_QueueFunction(AsyncServer_EchoOnOffRespond,
                           serverCmdPtr,
                           (void*) InValue);
}


void AsyncServer_EchoDoubleRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    ipcTest_EchoDoubleRespond(serverCmdPtr, *(double*)valuePtr);
    le_mem_Release(valuePtr);
}

void ipcTest_EchoDouble
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    double InValue
)
{
    double* valuePtr = le_mem_AssertAlloc(ValuePool);
    *valuePtr = InValue;
    le_event_QueueFunction(AsyncServer_EchoDoubleRespond,
                           serverCmdPtr,
                           (void*) valuePtr);
}

void AsyncServer_EchoReferenceRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    ipcTest_EchoReferenceRespond(serverCmdPtr,
                                 valuePtr);
}


void ipcTest_EchoReference
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    ipcTest_SimpleRef_t InRef
)
{
    le_event_QueueFunction(AsyncServer_EchoReferenceRespond,
                           serverCmdPtr,
                           InRef);
}

void AsyncServer_EchoStringRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    ipcTest_EchoStringRespond(serverCmdPtr,
                              valuePtr);
    le_mem_Release(valuePtr);
}


void ipcTest_EchoString
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    const char* InString,
    size_t OutStringSize
)
{
    // Cap output string size at maximum size of buffer
    if (OutStringSize > MAX_VALUE_SIZE) { OutStringSize = MAX_VALUE_SIZE; }

    char* OutString = le_mem_AssertAlloc(ValuePool);
    strncpy(OutString, InString, OutStringSize);
    OutString[OutStringSize-1] = '\0';
    le_event_QueueFunction(AsyncServer_EchoStringRespond,
                           serverCmdPtr,
                           OutString);
}

void AsyncServer_EchoArrayRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    OutArrayInfo_t* arrayInfoPtr = (OutArrayInfo_t*) valuePtr;
    ipcTest_EchoArrayRespond(serverCmdPtr, (int64_t*) arrayInfoPtr->arrayPtr,
                             arrayInfoPtr->outArraySize);
    le_mem_Release(arrayInfoPtr->arrayPtr);
    le_mem_Release(arrayInfoPtr);
}

void ipcTest_EchoArray
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    const int64_t* InArrayPtr,
    size_t InArraySize,
    size_t OutArraySize
)
{

    char* OutArrayPtr = le_mem_AssertAlloc(ValuePool);
    memcpy(OutArrayPtr, InArrayPtr, InArraySize * sizeof(int64_t));
    OutArrayInfo_t* arrayInfoPtr = le_mem_AssertAlloc(OutArrayInfoPool);
    arrayInfoPtr->arrayPtr = OutArrayPtr;
    arrayInfoPtr->outArraySize = OutArraySize;
    le_event_QueueFunction(AsyncServer_EchoArrayRespond,
                           serverCmdPtr,
                           arrayInfoPtr);
}

void AsyncServer_EchoByteStringRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    OutArrayInfo_t* arrayInfoPtr = (OutArrayInfo_t*) valuePtr;
    ipcTest_EchoByteStringRespond(serverCmdPtr, (uint8_t*) arrayInfoPtr->arrayPtr,
                                  arrayInfoPtr->outArraySize);
    le_mem_Release(arrayInfoPtr->arrayPtr);
    le_mem_Release(arrayInfoPtr);
}

void ipcTest_EchoByteString
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    const uint8_t* InArrayPtr,
    size_t InArraySize,
    size_t OutArraySize
)
{
    char* OutArrayPtr = le_mem_AssertAlloc(ValuePool);
    memcpy(OutArrayPtr, InArrayPtr, InArraySize * sizeof(int64_t));
    OutArrayInfo_t* arrayInfoPtr = le_mem_AssertAlloc(OutArrayInfoPool);
    arrayInfoPtr->arrayPtr = OutArrayPtr;
    arrayInfoPtr->outArraySize = OutArraySize;
    le_event_QueueFunction(AsyncServer_EchoByteStringRespond,
                           serverCmdPtr,
                           arrayInfoPtr);
}

void AsyncServer_EchoStructRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    ipcTest_TheStruct_t* outStructPtr = (ipcTest_TheStruct_t*) valuePtr;
    ipcTest_EchoStructRespond(serverCmdPtr, outStructPtr);
    le_mem_Release(outStructPtr);
}

void ipcTest_EchoStruct
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    const ipcTest_TheStruct_t * LE_NONNULL InStructPtr
)
{
    ipcTest_TheStruct_t* OutStructPtr = le_mem_AssertAlloc(TheStructPool);
    memcpy(OutStructPtr, InStructPtr, sizeof(ipcTest_TheStruct_t));
    le_event_QueueFunction(AsyncServer_EchoStructRespond,
                           serverCmdPtr,
                           OutStructPtr);

}


void AsyncServer_EchoStructArrayRespond
(
    void* serverCmdPtr,
    void* valuePtr
)
{
    OutArrayInfo_t* arrayInfoPtr = (OutArrayInfo_t*) valuePtr;
    ipcTest_EchoStructArrayRespond(serverCmdPtr, arrayInfoPtr->arrayPtr,
                                   arrayInfoPtr->outArraySize);
    le_mem_Release(arrayInfoPtr->arrayPtr);
    le_mem_Release(arrayInfoPtr);
}

void ipcTest_EchoStructArray
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    const ipcTest_TheStruct_t* InStructArrayPtr,
    size_t InStructArraySize,
    size_t OutStructArraySize
)
{
    ipcTest_TheStruct_t* OutArrayPtr = le_mem_AssertAlloc(ValuePool);
    memcpy(OutArrayPtr, InStructArrayPtr, InStructArraySize * sizeof(ipcTest_TheStruct_t));
    OutArrayInfo_t* arrayInfoPtr = le_mem_AssertAlloc(OutArrayInfoPool);
    arrayInfoPtr->arrayPtr = OutArrayPtr;
    arrayInfoPtr->outArraySize = OutStructArraySize;
    le_event_QueueFunction(AsyncServer_EchoStructArrayRespond,
                           serverCmdPtr,
                           arrayInfoPtr);

}

void ipcTest_ExitServer
(
    ipcTest_ServerCmdRef_t serverCmdRef
)
{
    LE_UNUSED(serverCmdRef);
    abort();
}

/**
 * Storage for pointer to Complex event handlers
 */
static ipcTest_EchoComplexHandlerFunc_t EchoEventHandlerComplexPtr = NULL;
static void* EchoComplexEventContextPtr = NULL;
size_t EchoComplexEventRef=1;

ipcTest_EchoComplexEventHandlerRef_t ipcTest_AddEchoComplexEventHandler
(
    ipcTest_EchoComplexHandlerFunc_t handlerPtr,
    void* contextPtr
)
{
    // For simplicity, only allow a single event handler
    if (EchoEventHandlerComplexPtr)
    {
        return NULL;
    }

    EchoEventHandlerComplexPtr = handlerPtr;
    EchoComplexEventContextPtr = contextPtr;

    return (ipcTest_EchoComplexEventHandlerRef_t)EchoComplexEventRef;
}

void ipcTest_RemoveEchoComplexEventHandler
(
    ipcTest_EchoComplexEventHandlerRef_t handlerRef
)
{
    // Remove if this is the current handler.
    if ((size_t)handlerRef == EchoComplexEventRef)
    {
        EchoComplexEventRef += 2;
        EchoEventHandlerComplexPtr = NULL;
        EchoComplexEventContextPtr = NULL;
    }
}

void AsyncServer_EchoTriggerComplexEventRespond
(
    void* serverCmdPtr,
    void* context
)
{
    LE_UNUSED(context);
    ipcTest_EchoTriggerComplexEventRespond(serverCmdPtr);
}


void ipcTest_EchoTriggerComplexEvent
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    int32_t cookie,
    const char* LE_NONNULL cookieString,
    const int16_t* cookieArrayPtr,
    size_t cookieArraySize
)
{
    if (EchoEventHandlerComplexPtr)
    {
        EchoEventHandlerComplexPtr(cookie, cookieString, cookieArrayPtr, cookieArraySize,
                                   EchoComplexEventContextPtr);
    }

    le_event_QueueFunction(AsyncServer_EchoTriggerComplexEventRespond,
                           serverCmdPtr,
                           NULL);
}

/**
 * Storage for pointer to event handlers
 */
static ipcTest_EchoHandlerFunc_t EchoEventHandlerPtr = NULL;
static void* EchoEventContextPtr = NULL;
size_t EchoEventRef=1;

ipcTest_EchoEventHandlerRef_t ipcTest_AddEchoEventHandler
(
    ipcTest_EchoHandlerFunc_t handlerPtr,
    void* contextPtr
)
{
    // For simplicity, only allow a single event handler
    if (EchoEventHandlerPtr)
    {
        return NULL;
    }

    EchoEventHandlerPtr = handlerPtr;
    EchoEventContextPtr = contextPtr;

    return (ipcTest_EchoEventHandlerRef_t)EchoEventRef;
}

void ipcTest_RemoveEchoEventHandler
(
    ipcTest_EchoEventHandlerRef_t handlerRef
)
{
    // Remove if this is the current handler.
    if ((size_t)handlerRef == EchoEventRef)
    {
        EchoEventRef += 2;
        EchoEventHandlerPtr = NULL;
        EchoEventContextPtr = NULL;
    }
}

void AsyncServer_EchoTriggerEventRespond
(
    void* serverCmdPtr,
    void* context
)
{
    LE_UNUSED(context);
    ipcTest_EchoTriggerEventRespond(serverCmdPtr);
}

void ipcTest_EchoTriggerEvent
(
    ipcTest_ServerCmdRef_t serverCmdPtr,
    int32_t cookie
)
{
    if (EchoEventHandlerPtr)
    {
        EchoEventHandlerPtr(cookie, EchoEventContextPtr);
    }
    le_event_QueueFunction(AsyncServer_EchoTriggerEventRespond,
                           serverCmdPtr,
                           NULL);
}

COMPONENT_INIT
{
    ValuePool = le_mem_InitStaticPool(ValuePool, VALUE_ENTRIES, MAX_VALUE_SIZE);
    OutArrayInfoPool = le_mem_InitStaticPool(OutArrayInfoPool, VALUE_ENTRIES,
                                             sizeof(OutArrayInfo_t));
    TheStructPool = le_mem_InitStaticPool(TheStructPool, VALUE_ENTRIES,
                                          sizeof(ipcTest_TheStruct_t));
}
