
#include "BSTTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include<string.h>
#define STALA 10

int StrCmp( char* s1, char* s2 );
void Visit( TreeItem* p, int linia );
void FindAndInsert( char* x, TreeItem** p, int numer_linii );
int NumberOfLine( ListHead* pierwszy, int linia );
void InOrderToFile( TreeItem* pTree, FILE* fout );

int Letter( char znak );
int Number( char znak );
int isAlpha( char znak );
char* MemoryAllocate();
char* MemoryRealloc( char* pWord, int nSize );
TreeItem* CreateTree( char* x, int numer_linii );
void InsertNumber( TreeItem* p, int numer_linii );


void FindAndInsert( char* x, TreeItem** p, int numer_linii )
{
 
  if( !*p ) // jesli wskaznik *p jest pusty,to tworzymy nowy weze³ drzewa
  {
    *p = CreateTree( x, numer_linii );
    return;
  }
  int zmienna = StrCmp( x, ( *p )->pWord );
   if( zmienna < 0 ) // jesli wartosc  x  mniejsza od wartosci wezla przechodzimy do lewego poddrzewa
    FindAndInsert( x, &( ( *p )->pLeft ), numer_linii );
  else if( zmienna > 0 ) // jesli wieksza  przechodzimy do prawego poddrzewa
    FindAndInsert( x, &( ( *p )->pRight ), numer_linii );
  else
    Visit( *p, numer_linii ); // gdy jest rowna to visit
}

TreeItem* CreateTree( char* x, int numer_linii )
{
  TreeItem* p = ( TreeItem* ) calloc( 1, sizeof( TreeItem ) ); //alokacja  dla nowego wezlaa drzewa

  if( !p )// sprawdzamy 
  {
    printf( "Blad podczas alokacji 1\n" );
    return NULL;
  }

  p->pWord = ( char* ) calloc( strlen( x ) + 1, sizeof( char ) ); // alokacja dla przechowywanego s³owa
  //p ->NodeValue->pWord = ( char* ) calloc( 1, sizeof( x ) ); // alokacja dla przechowywanego s³owa

  if( !p->pWord )
  {
    printf( "Blad podczas alokacji 3\n" );
    return NULL;
  }

 // p->nrlinii = ( ListHead* ) calloc( 1, sizeof( ListHead ) ); // alokacja  dla listy numerow linii
  /*if( !p->nrlinii )
  {
    printf( "Blad podczas alokacji 4\n" );
    return NULL;
  }*/
  InsertNumber( p, numer_linii );
  if( !p->nrlinii.pFirst )
  {
    printf( "Blad podczas alokacji 5\n" );
    return NULL;
  }

  strcpy( p->pWord, x ); // skopiowanie wart s³owa do wezla drzewa
  //( *p )->pLeft = ( *p )->pRight = NULL; // inicjacja wsk na lewe i prawe poddrzewa 
  p->iloscwystapien = 1; // inicjacja licznika  slowa
  return p;
}

// wstawia nowy element z numerem linii do listy numerow linii w wezle 
void InsertNumber( TreeItem* p, int numer_linii )
{
  
  ListItem* v = ( ListItem* ) calloc( 1, sizeof( ListItem ) ); // alokacja  dla pierwszego elementu listy
  if( !v )
  {
    printf( "Blad podczas alokacji 10\n" );
    return;
  }
  v->number = numer_linii;
  if( p->nrlinii.pFirst == NULL )
  {
    p->nrlinii.pFirst = v;
  }
  else
  {
    p->nrlinii.pLast->next = v;
  }
  p->nrlinii.pLast = v;
  /*
  p->nrlinii.pLast = ( p )->nrlinii.pFirst;  // pfirst i plast wskazuja na ten sam element, zrobilem tak bo wypisywalo numery linii w odwrotnej kolejnosci 
  // wstawic pierwszy element do listy z numerem linii ( przekazac nr linii do fukcji )

  if( !p->nrlinii.pFirst )
  {
    printf( "Blad podczas alokacji 5\n" );
    return;
  }
  p->nrlinii.pFirst->number = numer_linii; // inicjalizacja numeru linii w pierwszym elemencie listy
  */
}


int StrCmp( char* s1, char* s2 )
{
  // zaalokowac dynamicznie pamiec na kopie pierwzego stringa( strlen() )
  char* copy1 = ( char* ) malloc( strlen( s1 ) + 1 );
  //zaalokowac dynamicznie pamiec na kopie drugiego stringa
  char* copy2 = ( char* ) malloc( strlen( s2 ) + 1 );
  // wkopiowac pierwszy do kopii - strcpy()
  if( copy1 == NULL || copy2 == NULL )
  {
    printf( "Blad alokacji pamieci\n" );
    return 0; 
  }
  strcpy( copy1, s1 );
  // wkopiowac drugi do kopii
  strcpy( copy2, s2 );


  // przekonwertowac albo do malych albo do duzych liter obie kopie : _strlwr() albo _strupr()
  _strlwr( copy1 );
  _strlwr( copy2 );

  //- porownac i zapamietac wynik - strcmp()
  int res = strcmp( copy1, copy2 );

  //- zwolnic pamiec na obie kopie
  free( copy1 );
  free( copy2 );

  //- zwrocic wynik
  return res;
}


void inOrder( TreeItem* p )
{
  // L Root R
 
 
  if( p )
  {
    inOrder( p->pLeft );
    printf( "Slowo: %s  \n Ilosc wystapien: %d \n", p->pWord, p->iloscwystapien );

    printf( "Numery linii: " );
    ListItem* linia = p->nrlinii.pFirst; // tworzymy  wsk "linia" i ustawiamy go na pierwszy element listy numerow linii

    while( linia )
    {
      printf( "%d ", linia->number );
      linia = linia->next; // wyswietlamy  numer linii i przechodzimy  do kolejnego elementu listy
    }
    printf( "\n\n" );
    inOrder( p->pRight );
  }
}

void Visit( TreeItem* p, int linia  )
{

  p->iloscwystapien = p->iloscwystapien + 1;  // zwiekszamy ilosc wystapien slowa w wezle o 1

  NumberOfLine( &(p->nrlinii), linia ); //dodajemy nr linii do listy numerow linii dla slowa
  // przesylam adres obiektu do funkcji zego go zmienic wewnatrz funkcji 

}

int NumberOfLine( ListHead* list, int linia )
{
  // sprawdzamy czy pusta 
  if( list == NULL )
  {
    return 0;
  }

  // przeszukujemy liste zeby znalezc nr linii 
  //ListItem* temp = list->pLast;
  ListItem* nowy = ( ListItem* ) calloc( 1, sizeof( ListItem ) );
  if( nowy == NULL )
  {
    return 0;
  }
  nowy->number = linia; // przypisanie numeru linii do nowego elementu ListItem

  //sprawdzic zostatnim el listy i ewentualnie dodac do listy !!!
  
    if( list->pLast->number != linia )
    {
      list->pLast->next = nowy;
      list->pLast = nowy;
      // nr linii istnieje
      return 5;
    }
 
  
   // list->pLast->next = nowy;
   // list->pLast = nowy;

  return 1; 
}




int Letter( char znak )
{
  return  ( znak >= 'A' && znak <= 'Z' ) || ( znak >= 'a' && znak <= 'z' ) || ( znak == '_' );
}

int Number( char znak )
{
  return   znak >= '0' && znak  <= '9' ;
}
int isAlpha( char znak )
{
  return Letter( znak ) || Number( znak );
}

// zrobic funkcje
//do readfromfile 
TreeItem* ReadfromFile( FILE* fin )
{
  
  TreeItem* pRoot = NULL;  
  char znak;
  int linijka = 1;  // aktualna linia w pliku
 // char* pWord = ( char* ) calloc( STALA, sizeof( char ) ); 

  while( ( znak = fgetc( fin ) ) != EOF )
  {
    int i = 0;  // aktualna pozycja w tablicy slow
    int size = STALA;  // rozmiar aktualnie zaalokowanej pamieci dla tablicy slow
    if( Letter( znak ) )
    { 
      char* pWord = MemoryAllocate(); // funk do alokacji pam dla slowa 
      if( !pWord )
      {
        printf( "blad alokacji\n" );
      }
    // wedlug zasad identyfikatora
 
      pWord[ i++ ] = znak;


      while( ( znak = fgetc( fin ) ) != EOF && isAlpha( znak ) )
      {

        //while( ( ( znak = fgetc( fin ) ) >= 'a' && znak <= 'z' ) || ( znak >= 'A' && znak <= 'Z' ) || ( znak == '_' ) || ( znak >= '0' && znak <= '9' ) )
        //{
        if( i == ( size - 1 ) )
        {
          // jezeli jest pelny zwiekszamy jego rozmiar
          size += STALA;
          pWord = MemoryRealloc( pWord, size ); // funkcja do realokacji pam 
          //pWord = ( char* ) realloc( pWord, sizeof( char ) * ( size + 1 ) );
        }
          //  formujemy slowo 
        pWord[ i++ ] = znak;
       
      }

      pWord[ i ] = '\0';  // dodajemy znak konca slwoa 


      FindAndInsert( pWord, &pRoot, linijka );  // wyszukujemy i wstawiamy slowo do drzewa
      //i = 0; // dla kolejnego slowa 
      free( pWord );
    }
    if( znak == '\n' )
    {
      // jezeli znak nowej linii to zwiekszamy nr linii i przechodzimy do kolejnej itteracji 
      linijka++;

    }
  }
  
  //fclose( fin );
  return pRoot;  
}


//  do zapisywania zawartosci  drzewa do pliku tekstowego.
void SaveToFile( TreeItem* pTree, FILE* fout )
{
  // otwieramy plik 
  //FILE* fout = fopen( filename, "w" );

  if( fout == NULL ) {
    printf( "B³¹d podczas otwierania pliku do zapisu\n" );
    return;
  }

  InOrderToFile( pTree, fout );  // wywolanie funkcji pomocniczej do zapisu drzewa

  fclose( fout );
}

// do rekurencyjnego zapisywania zawartosci drzewa binarnego do pliku tekstowego
//  zachowana cala struktura drzeawa i inf o slowach i nr linii i ilosci wsystapien  
void InOrderToFile( TreeItem* pTree, FILE* fout ) 
{
  if( pTree == NULL ) {
    return;
  }

  InOrderToFile( pTree->pLeft, fout );  // rek zapisuje lewe poddrzewo
  // zapisujemy inf do pliku 
  fprintf( fout, "Slowo: %s\n Ilosc wystapien : %d\n", pTree->pWord, pTree->iloscwystapien );
  fprintf( fout, "Numery linii: " );

  ListItem* current = pTree->nrlinii.pFirst;// inicjacja wsk current na poczatek listy numerow linii
  while( current ) 
  {
    fprintf( fout, "%d ", current->number );// zapisujemy nr linii do pliku 
    current = current->next; // przesuwamy na nastepny el 
  }
  fprintf( fout, "\n\n" );
  InOrderToFile( pTree->pRight, fout );  // rek zapisuje prawe poddrzewo
}



// alokuje pamiec dla slowa o poczatkowym rozmiarze STALA
// Zwraca wsk do zaalokowanej pamieci lub NULL
char* MemoryAllocate()
{
  int size = STALA;
  // alokuje pam dla slowa o rozmiarze STALA i inicjuje zerami 
  char* pWord = ( char* ) calloc( size, sizeof( char ) );

  if( !pWord )
  {
    printf( "Blad w alokacji\n" );
    return NULL;
  }

  return pWord;
}

// realokuje pamiec dla s³owa na nowy rozmiar nSize
// zwraca wsk do nowo zaalokowanej pamieci lub NULL
char* MemoryRealloc( char* pWord, int nSize )
{
 //realokacja
  char* nWord = ( char* ) realloc( pWord, nSize * sizeof( char ) );

  if( !nWord )
  {
    printf( "Blad podczas realokowania\n" );
    return nWord;
  }

  // jesli  nowy rozmiar (nSize) jest > niz poprzedni (STALA) wypelnia dodatkowe miejsce zaalokowanej pamieci zerami, pozbywamy sie niepotrzebnych danych 
  // jesli  jest mniejszy to nie ma potrzeby wypelniania zerami
  memset( nWord + ( nSize - STALA ), 0, STALA * sizeof( char ) );

  return nWord;
}


void FreeTree( TreeItem* pRoot ) 
{
  if( !pRoot )
  {
    return;
  }

  FreeTree( pRoot->pLeft ); //zwol lewego poddrzewa
  FreeTree( pRoot->pRight );//zwolnienie prawego poddrzewa

  //zwolnienie listy numerow linii
  ListItem* currentLine = pRoot->nrlinii.pFirst;
  ListItem* temp = NULL;
  while( currentLine != NULL )
  {
    temp = currentLine; //zapamietuje pierw stan
    currentLine = currentLine->next; // przesuwamy na nast el 
    free( temp ); 
  }
  
   
  free( pRoot->pWord );//zwalniamy slowo
  free( pRoot );//zwalniamy wezel 
}
