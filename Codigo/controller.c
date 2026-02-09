#ifndef ALUNO_H
#define ALUNO_H

#include "linkedlist.h"

// estrutura que representa uma disciplina
typedef struct
{
  char nomeDisc[30];
  float nota;
  float presenca;
  char situacao[2];
  int periodo;
} Disciplina;

//
// Estrutura de um aluno
typedef struct Aluno
{
  char nome[100];
  int matricula;

} Aluno;

#endif
