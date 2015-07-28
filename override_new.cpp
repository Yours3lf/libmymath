#include <malloc.h>
#include <stdio.h>

#define CUSTOM_ALIGNMENT 16

#ifdef _WIN32

void* custom_alloc( size_t s )
{
  void* m = _aligned_malloc( s, CUSTOM_ALIGNMENT );

  return m;
}

void custom_free( void* m )
{
  _aligned_free( m );
}

#else //not win32

void* custom_alloc( size_t s )
{ 
  void* m = 0; 

  if( posix_memalign( &m, MYMATH_ALIGNMENT, s ) ) 
    m = 0; 

  return m; 
} 

void custom_free( void* m )
{ 
  free( p ); 
}

#endif

void* operator new( size_t s )
{
  return custom_alloc( s );
}

void* operator new[]( size_t s )
{
  return custom_alloc( s );
}

void operator delete( void* m )
{
  custom_free( m );
}

void operator delete[]( void* m )
{
  custom_free( m );
}
