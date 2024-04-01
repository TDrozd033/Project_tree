#pragma once
//#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
typedef struct tagListItem
{
  int number;           // nr linii
  tagListItem* next;  // wsk na nastepny el listy

} ListItem;

typedef struct 
{
  ListItem* pFirst;   // wsk na pierwszy element listy
  ListItem* pLast;    // na ostatni

} ListHead;


typedef struct tagTreeItem
{
  int iloscwystapien;
  char* pWord;
  ListHead nrlinii;
  tagTreeItem* pLeft;    
  tagTreeItem* pRight;    

} TreeItem;

  void inOrder( TreeItem* p );
//void postOrder( TreeItem* p );
//void preOrder( TreeItem* p );
  TreeItem* ReadfromFile(  FILE* fin );

  void SaveToFile( TreeItem* pTree,  FILE* fout );

   void FreeTree( TreeItem* pRoot );

   