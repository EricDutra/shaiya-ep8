#pragma once
#include <cstdint>
#include "include/utils/win32_lean.h"
#include "include/shaiya/SNode.h"

namespace shaiya
{
#pragma pack(push, 1)

    struct SAgent;

    struct SInternetAddress
    {
        uint16_t family;        // 0x00
        uint16_t port;          // 0x02
        uint32_t ip;            // 0x04
        uint8_t unk[8];         // 0x08
    };

    struct SSyncQueueBufferSend
    {
        void* head;             // 0x00
        void* tail;             // 0x04
        uint32_t length;        // 0x08
        CRITICAL_SECTION cs;    // 0x0C
        uint32_t count;         // 0x24
        uint8_t unk[4];         // 0x28
    };

    struct SSyncQueueBuffer
    {
        void* head;             // 0x00
        void* tail;             // 0x04
        CRITICAL_SECTION cs;    // 0x08
        uint32_t count;         // 0x20
        uint8_t unk[4];         // 0x24
    };

    struct SConnectionParam
    {
        SNode node;             // 0x00
        uint8_t unk[8];         // 0x08
        int32_t closeType;      // 0x10
        int32_t closeError;     // 0x14
        uint64_t sendCount;     // 0x18
        uint64_t recvCount;     // 0x20
        uint64_t sendBytes;     // 0x28
        uint64_t recvBytes;     // 0x30
        uint32_t connectTick;   // 0x38
        uint32_t sendProcessing;// 0x3C
        uint8_t unk2[8];        // 0x40
        CRITICAL_SECTION cs;    // 0x48
        uint8_t unk3[8];        // 0x60
    };

    struct SConnection
    {
        void* vftable;               // 0x00
        uint8_t unk[4];              // 0x04
        SConnectionParam param;      // 0x08
        int32_t socket;              // 0x68
        SInternetAddress address;    // 0x6C
        SSyncQueueBuffer sqb;        // 0x7C
        SSyncQueueBufferSend sqbs;   // 0xA0
        SAgent* agent;               // 0xC8
        uint8_t unk2[4];             // 0xCC
    };

#pragma pack(pop)
}