#pragma once
#include "include/utils/win32_lean.h"
#include "include/shaiya/SNode.h"

#pragma pack(push, 1)
struct Sentinel
{
    SNode* tail;
    SNode* head;
};

template<class T>
struct SSyncList
{
    Sentinel sentinel;    //0x00
    CRITICAL_SECTION cs;  //0x08
    UINT32 count;         //0x20
    T* last;              //0x24
    T* first;             //0x28
    // 0x2C
};
#pragma pack(pop)