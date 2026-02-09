#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Disciplina
{
  char nomeDisc[30];
  float nota;
  float presenca;
  char situacao[2];
  int periodo;
} Disciplina;

typedef struct Aluno
{
  char nomeAluno[50];
  int matricula;
} Aluno;

// ideia inicial das funcoes
// algumas podem ser removidas ja que estao nas estruturas
//  (ex: adicionar aluno é a mesma coisa de adicionar um elemento na lista)
Aluno *buscarAluno(int matricula);
void cadastrarAluno();
void cadastrarDisciplina();
void removerAluno();
void listarAlunos();
void exibirHistorico();
void atualizarDisciplina();

#endif
