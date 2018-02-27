#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>

enum menu
{
	cadAluno = 1, cadProfessor, cadDisciplina, matricularAluno, alocarProfessor, cancelarAluno, cancelarProfessor, imprimirAluno, imprimirProfessor, imprimirDisciplina, sair
};
typedef struct {
	int ra;
	char nome[100];
	int disciplinas[20];
}aluno;

typedef struct {
	int rg;
	char nome[100];
	int disciplinas[20];
}professor;

typedef struct {
	int cod;
	char nome[100];
}disciplina;

aluno buscarAluno(int ra, int tamanho, aluno *alunos); //busca um aluno atravez do ra
int existeAluno(int ra, int tamanho, aluno *alunos);
void imprimeAlunos(int tamanho, aluno *alunos);

professor buscarProfessor(int rg, int tamanho, professor *professores); //busca um professor atravez do rg
int existeProfessor(int rg, int tamanho, professor *professores);
void imprimeProfessores(int tamanho, professor *professores);

disciplina buscarDisciplina(int cod, int tamanho, disciplina *disciplinas); //busca uma disciplina atravez do cod
int existeDisciplina(int cod, int tamanho, disciplina *disciplinas);
void imprimeDisciplinas(int tamanho, disciplina *disciplinas);

void main() {
	//variaveis globais
	aluno alunos[100];
	professor professores[100];
	disciplina disciplinas[100];
	int indiceAluno = 0, indiceProf = 0, indiceDis = 0;

	int opcao, i, qtd,
		qtdAluno, raAtual,
		qtdProf, rgAtual,
		qtdDis, codAtual;

	do {
		printf("Digite:\n");
		printf("%d) Cadastrar Aluno.\n", cadAluno);
		printf("%d) Cadastrar Professor.\n", cadProfessor);
		printf("%d) Cadastrar Disciplina.\n", cadDisciplina);
		printf("%d) Matricular aluno(s).\n", matricularAluno);
		printf("%d) Alocar professor(es).\n", alocarProfessor);
		printf("%d) Cancelar  matricula.\n", cancelarAluno);
		printf("%d) Cancelar  alocacao.\n", cancelarProfessor);
		printf("%d) Imprimir  Aluno.\n", imprimirAluno);
		printf("%d) Imprimir  Professor.\n", imprimirProfessor);
		printf("%d) Imprimir  Disciplina.\n", imprimirDisciplina);
		printf("%d) Sair.\n", sair);
		scanf("%d", &opcao);

		switch (opcao)
		{
		case cadAluno:
			printf("Digite quantos alunos serao cadastrados:\n");
			scanf("%d", &qtd);
			for (i = 0; i < qtd; i++) {
				printf("Digite o ra do aluno\n");
				scanf("%d", &raAtual);
				if (existeAluno(raAtual, indiceAluno, alunos) == 0) {
					alunos[indiceAluno].ra = raAtual;
					printf("Digite o nome do aluno\n");
					scanf("%s", alunos[indiceAluno].nome);

					printf("Aluno cadastrado com sucesso!\n");

					indiceAluno++;
				}
				else {
					printf("Aluno ja cadastrado!\n");
					i--;
				}
			}

			break;
		case cadProfessor:
			printf("Digite quantos professores serao cadastrados:\n");
			scanf("%d", &qtd);
			for (i = 0; i < qtd; i++) {
				printf("Digite o rg do professor\n");
				scanf("%d", &rgAtual);
				if (existeProfessor(rgAtual, indiceProf, professores) == 0) {
					professores[indiceProf].rg = rgAtual;
					printf("Digite o nome do professor\n");
					scanf("%s", professores[indiceProf].nome);

					printf("Professor cadastrado com sucesso!\n");

					indiceProf++;
				}
				else {
					printf("Professor ja cadastrado!\n");
					i--;
				}
			}

			break;
		case cadDisciplina:
			printf("Digite quantas disciplinas serao cadastrados:\n");
			scanf("%d", &qtd);
			for (i = 0; i < qtd; i++) {
				printf("Digite o cod da disciplina\n");
				scanf("%d", &codAtual);
				if (existeDisciplina(codAtual, indiceDis, disciplinas) == 0) {
					disciplinas[indiceDis].cod = codAtual;
					printf("Digite o nome da disciplina\n");
					scanf("%s", disciplinas[indiceDis].nome);

					printf("Disciplina cadastrada com sucesso!\n");

					indiceDis++;
				}
				else {
					printf("Disciplina ja cadastrado!\n");
					i--;
				}
			}

			break;
		case matricularAluno:
			break;
		case alocarProfessor:
			break;
		case cancelarAluno:
			break;
		case cancelarProfessor:
			break;
		case imprimirAluno:
			imprimeAlunos(indiceAluno, alunos);
			break;
		case imprimirProfessor:
			imprimeProfessores(indiceProf, professores);
			break;
		case imprimirDisciplina:
			imprimeDisciplinas(indiceDis, disciplinas);
			break;
		case sair:
			break;
		default:
			printf("Opcao Invalida!\n");
			break;
		}
	} while (opcao != sair);
	system("pause");

}

int existeAluno(int ra, int tamanho, aluno *alunos) {
	int j;
	for (j = 0; j < tamanho; j++) {
		if (alunos[j].ra == ra) {
			return 1; //true
		}
	}
	return 0; //false

}

aluno buscarAluno(int ra, int tamanho, aluno *alunos) {
	int j;
	for (j = 0; j < tamanho; j++) {
		if (alunos[j].ra == ra) {
			return alunos[j];
		}
	}
}

void imprimeAlunos(int tamanho, aluno *alunos) {
	int j;
	printf("RA        NOME\n");
	for (j = 0; j < tamanho; j++) {
		printf("%d         %s\n", alunos[j].ra, alunos[j].nome);
	}
}
int existeProfessor(int rg, int tamanho, professor *professores) {
	int j;
	for (j = 0; j < tamanho; j++) {
		if (professores[j].rg == rg) {
			return 1; //true
		}
	}
	return 0; //false

}

professor buscarProfessor(int rg, int tamanho, professor *professores) {
	int j;
	for (j = 0; j < tamanho; j++) {
		if (professores[j].rg == rg) {
			return professores[j];
		}
	}
}

void imprimeProfessores(int tamanho, professor *professores) {
	int j;
	printf("RG        NOME\n");
	for (j = 0; j < tamanho; j++) {
		printf("%d         %s\n", professores[j].rg, professores[j].nome);
	}
}

int existeDisciplina(int cod, int tamanho, disciplina *disciplinas) {
	int j;
	for (j = 0; j < tamanho; j++) {
		if (disciplinas[j].cod == cod) {
			return 1; //true
		}
	}
	return 0; //false

}

disciplina buscarDisciplina(int cod, int tamanho, disciplina *disciplinas) {
	int j;
	for (j = 0; j < tamanho; j++) {
		if (disciplinas[j].cod == cod) {
			return disciplinas[j];
		}
	}
}

void imprimeDisciplinas(int tamanho, disciplina *disciplinas) {
	int j;
	printf("COD       NOME\n");
	for (j = 0; j < tamanho; j++) {
		printf("%d         %s\n", disciplinas[j].cod, disciplinas[j].nome);
	}
}