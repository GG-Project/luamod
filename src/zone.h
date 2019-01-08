#ifndef ZONE_H
#define ZONE_H

#include <stddef.h> // size_t
#include <stdlib.h> // malloc
#include <string.h> // memset

#include <utils.h>

#include <stdlib.h>
#include <stdio.h> //min,max

#define MAX_STRING		256
#define MAX_OSPATH		260

typedef unsigned char byte;

typedef unsigned int	uint;
typedef char		string[MAX_STRING];

#undef true
#undef false

typedef int qboolean;

qboolean Mem_IsAllocatedExt( byte *poolptr, void *data );
void *_Mem_Alloc( byte *poolptr, size_t size, qboolean clear, const char *filename, int fileline );
void _Mem_Free( void *data, const char *filename, int fileline );
void *_Mem_Realloc( byte *poolptr, void *memptr, size_t size, qboolean clear, const char *filename, int fileline );
byte *_Mem_AllocPool( const char *name, const char *filename, int fileline );
void _Mem_FreePool( byte **poolptr, const char *filename, int fileline );
void Mem_CheckHeaderSentinels( void *data, const char *filename, int fileline );
void _Mem_Check( const char *filename, int fileline );
void Mem_PrintStats( void );
void Mem_PrintList( size_t minallocationsize );
void Memory_Init( void );

char *Q_pretifymem( float value, int digitsafterdecimal );
#define Q_memprint( val ) Q_pretifymem( val, 2 )

#define Mem_Malloc( pool, size ) _Mem_Alloc( pool, size, true, __FILE__, __LINE__ )
#define Mem_Calloc( pool, size ) _Mem_Alloc( pool, size, true, __FILE__, __LINE__ )
#define Mem_Realloc( pool, ptr, size ) _Mem_Realloc( pool, ptr, size, true, __FILE__, __LINE__ )
#define Mem_Free( mem ) _Mem_Free( mem, __FILE__, __LINE__ )
#define Mem_AllocPool( name ) _Mem_AllocPool( name, __FILE__, __LINE__ )
#define Mem_FreePool( pool ) _Mem_FreePool( pool, __FILE__, __LINE__ )
#define Mem_EmptyPool( pool ) _Mem_EmptyPool( pool, __FILE__, __LINE__ )
#define Mem_IsAllocated( mem ) Mem_IsAllocatedExt( NULL, mem )
#define Mem_Check() _Mem_Check( __FILE__, __LINE__ )

#endif // ZONE_H
