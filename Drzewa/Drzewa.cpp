//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"BSTTree.h"

int main( int argc, char* argv[] )
{
  if( argc != 3 ) 
  {
    printf( "Usage: %s <data_file>\n", argv[ 0 ] );
    return -8;
  }

  /*
  TreeItem* p = NULL;
  char* slowo = ( char* ) malloc( 10 * sizeof( char ) );
  strcpy( slowo, "alamakota" );
  FindAndInsert( slowo, &p, 7 );

  char* slowo1 = ( char* ) malloc( 10 * sizeof( char ) );
  strcpy( slowo1, "alama" );
  FindAndInsert( slowo1, &p, 5 );

  char* slowo2 = ( char* ) malloc( 10 * sizeof( char ) );
  strcpy( slowo2, "aLa" );
  FindAndInsert( slowo2, &p, 5 );

  char* slowo3 = ( char* ) malloc( 10 * sizeof( char ) );
  strcpy( slowo3, "kot" );
  FindAndInsert( slowo3, &p, 5 );

  char* slowo4 = ( char* ) malloc( 10 * sizeof( char ) );
  strcpy( slowo4, "ala" );
  FindAndInsert( slowo4, &p, 5 );
  printf( "\n" );
  */
  FILE* fin = fopen( argv[1], "r");
  if( fin == NULL )
  {
    printf( "Blad podczas otwierania pliku: %s\n", argv[ 1 ] );
    return -2;
  }

 TreeItem* obiekt = ReadfromFile( fin );

  //preOrder( pRoot );
  //printf( "\n\n" );
 //inOrder( p );
  inOrder( obiekt );
  FILE* plik = NULL;
  plik = fopen( argv[ 2 ], "w" );
  if( plik == NULL )
  {
    printf( "Blad otwirania pliku\n" );
    return -3;
  }
  SaveToFile( obiekt, plik );
  
  //zwolnic pamiec
  //obiekt = FreeTree( obiekt );
 // fclose( fin );
  FreeTree( obiekt );
 
  printf( "\n\n" );
  return 0;
}