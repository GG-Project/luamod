#pragma once
#include <extdll.h>
#include <meta_api.h>

/*
        void            (*pfnMessageBegin)                      (int msg_dest, int msg_type, const float *pOrigin, edict_t *ed);
        void            (*pfnMessageEnd)                        (void);
        void            (*pfnWriteByte)                         (int iValue);
        void            (*pfnWriteChar)                         (int iValue);
        void            (*pfnWriteShort)                        (int iValue);
        void            (*pfnWriteLong)                         (int iValue);
        void            (*pfnWriteAngle)                        (float flValue);
        void            (*pfnWriteCoord)                        (float flValue);
        void            (*pfnWriteString)                       (const char *sz);
        void            (*pfnWriteEntity)                       (int iValue);
*/

void pfnMessageBegin(int msg_dest, int msg_type, const float *pOrigin, edict_t *pEntity);
void pfnMessageEnd(void);
void pfnWriteByte(int iValue);
void pfnWriteChar(int iValue);
void pfnWriteShort(int iValue);
void pfnWriteLong(int iValue);
void pfnWriteAngle(float iValue);
void pfnWriteCoord(float iValue);
void pfnWriteString(const char* Value);
void pfnWriteEntity(int iValue);
