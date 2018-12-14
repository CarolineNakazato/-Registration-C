#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>

enum menu
{
	cadAluno = 1, cadProfessor, cadDisciplina, matricularAluno, alocarProfessor, cancelarAluno, cancelarProfessor, imprimirAluno, imprimirProfessor, imprimirDisciplina, imprimirDiscAluno, imprimirAlunoDisc, imprimirDiscProf, imprimirProfDisc, sair
};
typedef struct {
	int ra;
	char nome[100];
	int disciplinas[20];
	int qtdDisci;
}aluno;

typedef struct {
	int rg;
	char nome[100];
	int disciplinas[20];
	int qtdDisci;
}professor;

typedef struct {
	int cod;
	char nome[100];
}disciplina;

int buscarAluno(int ra, int tamanho, aluno *alunos); //busca um aluno atravez do ra
int existeAluno(int ra, int tamanho, aluno *alunos);
void imprimeAlunos(int tamanho, aluno *alunos);
int existeMatricula(int cod, int posAluno, aluno *alunos);

int buscarProfessor(int rg, int tamanho, professor *professores); //busca um professor atravez do rg
int existeProfessor(int rg, int tamanho, professor *professores);
void imprimeProfessores(int tamanho, professor *professores);
int existeAlocacao(int cod, int tamanho, professor *professores);

disciplina buscarDisciplina(int cod, int tamanho, disciplina *disciplinas); //busca uma disciplina atravez do cod
int existeDisciplina(int cod, int tamanho, disciplina *disciplinas);
void imprimeDisciplinas(int tamanho, disciplina *disciplinas);

void matricularAlunos(int posAluno, aluno *alunos, int tamanho, int *grupoDisciplinas);
int cursando(aluno alunoAtual);
void alocarProfessores(int posProf, professor *professores, int qtdDis, int *grupoDisciplinas);

void imprimirDisciplinasDeAluno(int posAluno, aluno *alunos);
void imprimirAlunosPorDisciplina(int codAtual, int tamanho, aluno *alunos);

void imprimirDisciplinasDeProf(int posProf, professor *professores);
void imprimirProfPorDisciplina(int codAtual, int tamanho, professor *professores);

void cancelarDisciplina(int tamanho, aluno *alunos, int qtdDis, int *grupoDisciplinas);
void excluiDoVetor(int posAluno, int posDisc, aluno *alunos);

void cancelarDisciplina2(int tamanho, professor *professores, int qtdDis, int *grupoDisciplinas);
void excluiDoVetor2(int posProf, int posDisc, professor *professores);

int existeNoVetor(int tamanho, int *vetor, int valorAtual);


void main() {
	//variaveis globais
	aluno alunos[100];
	professor professores[100];
	disciplina disciplinas[100];
	int indiceAluno = 0, indiceProf = 0, indiceDis = 0;

	int opcao, i, qtd,
		qtdAluno = 0, raAtual, grupoAlunos[20],
		qtdProf = 0, rgAtual, grupoProfessores[20],
		qtdDis = 0, codAtual, grupoDisciplina[20];

	do {
		printf("Digite:\n");
		printf("%d) Cadastrar Aluno.\n", cadAluno);
		printf("%d) Cadastrar Professor.\n", cadProfessor);
		printf("%d) Cadastrar Disciplina.\n", cadDisciplina);
		printf("%d) Matricular aluno(s).\n", matricularAluno);
		printf("%d) Alocar professor(es).\n", alocarProfessor);
		printf("%d) Cancelar  Matricula.\n", cancelarAluno);
		printf("%d) Cancelar  Alocacao.\n", cancelarProfessor);
		printf("%d) Imprimir  Aluno.\n", imprimirAluno);
		printf("%d) Imprimir  Professor.\n", imprimirProfessor);
		printf("%d) Imprimir  Disciplina.\n", imprimirDisciplina);
		printf("%d) Imprimir  Disciplina de um aluno desejado.\n", imprimirDiscAluno);
		printf("%d) Imprimir  Aluno de uma disciplina desejada.\n", imprimirAlunoDisc);
		printf("%d) Imprimir  Disciplina de um professor desejado.\n", imprimirDiscProf);
		printf("%d) Imprimir  Professor de uma disciplina desejada.\n", imprimirProfDisc);
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
					alunos[indiceAluno].qtdDisci = 0;
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
					professores[indiceProf].qtdDisci = 0;
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

			if ((indiceAluno && indiceDis) == 0) {
				printf("Aluno e/ou disciplna nao cadastrado\n");
				printf("Cadastre pelo menos um em cada categoria para poder realizar a matricula\n");
			}
			else {
				do
			{
				printf("Digite quantas disciplinas serao matriculadas:\n");
				scanf("%d", &qtdDis);
			} while (qtdDis>20);

			imprimeDisciplinas(indiceDis, disciplinas);

			for (i = 0; i < qtdDis; i++) {
				printf("Digite codigo da disciplina:\n");
				scanf("%d", &codAtual);
				if (existeDisciplina(codAtual, indiceDis, disciplinas) == 1) {
					if (existeNoVetor(i, grupoDisciplina, codAtual) == 0) {
						grupoDisciplina[i] = codAtual;
					}
					else {
						printf("Disciplina ja esta no grupo\n");
						i--;
					}
				}
				else {
					printf("Disciplina nao cadastrado!\n");
					i--;
				}
			}


			printf("Digite quantos alunos serao matriculados:\n");
			scanf("%d", &qtd);
			imprimeAlunos(indiceAluno, alunos);
			for (i = 0; i < qtd; i++) {
				printf("Digite ra do aluno:\n");
				scanf("%d", &raAtual);
				if (existeAluno(raAtual, indiceAluno, alunos) == 1) {
					matricularAlunos(buscarAluno(raAtual, indiceAluno, alunos), alunos, qtdDis, grupoDisciplina);
				}
				else {
					printf("Aluno nao cadastrado!\n");
					i--;
				}
			}
			}

			break;
		case alocarProfessor:
			if ((indiceProf && indiceDis) == 0) {
				printf("Professor e/ou disciplna nao cadastrado\n");
				printf("Cadastre pelo menos um em cada categoria para poder realizar a alocacao\n");
			}
			else {
			do
			{
				printf("Digite quantas disciplinas serao alocadas:\n");
				scanf("%d", &qtdDis);
			} while (qtdDis>20);

			imprimeDisciplinas(indiceDis, disciplinas);

			for (i = 0; i < qtdDis; i++) {
				printf("Digite codigo da disciplina:\n");
				scanf("%d", &codAtual);
				if (existeDisciplina(codAtual, indiceDis, disciplinas) == 1) {
					if ((existeNoVetor(i, grupoDisciplina, codAtual) == 0)) {
						grupoDisciplina[i] = codAtual;
					}
					else {
						printf("Disciplina ja esta no grupo\n");
						i--;
					}
				}
				else {
					printf("Disciplina nao cadastrado!\n");
					i--;
				}
			}


			printf("Digite quantos professores serao alocados:\n");
			scanf("%d", &qtd);
			imprimeProfessores(indiceProf, professores);
			for (i = 0; i < qtd; i++) {
				printf("Digite rg do professor:\n");
				scanf("%d", &rgAtual);
				if (existeProfessor(rgAtual, indiceProf, professores) == 1) {
					alocarProfessores(buscarProfessor(rgAtual, indiceProf, professores), professores, qtdDis, grupoDisciplina);
				}
				else {
					printf("Professores nao cadastrado!\n");
					i--;
				}
				}
			}



			break;
		case cancelarAluno:
			if ((indiceAluno && indiceDis) == 0) {
				printf("Sem matricula para cancelamento\n");
			}
			else {
				do
				{
					printf("Digite quantas disciplinas serao desmatriculadas:\n");
					scanf("%d", &qtdDis);
				} while (qtdDis > 20);

				imprimeDisciplinas(indiceDis, disciplinas);

				for (i = 0; i < qtdDis; i++) {
					printf("Digite codigo da disciplina:\n");
					scanf("%d", &codAtual);
					if (existeDisciplina(codAtual, indiceDis, disciplinas) == 1) {
						grupoDisciplina[i] = codAtual;
					}
					else {
						printf("Disciplina nao cadastrado!\n");
						i--;
					}
				}


				printf("Digite quantos alunos serao desmatriculados:\n");
				scanf("%d", &qtd);
				imprimeAlunos(indiceAluno, alunos);
				for (i = 0; i < qtd; i++) {
					printf("Digite ra do aluno:\n");
					scanf("%d", &raAtual);
					if (existeAluno(raAtual, indiceAluno, alunos) == 1) {
						cancelarDisciplina(buscarAluno(raAtual, indiceAluno, alunos), alunos, qtdDis, grupoDisciplina);
					}
					else {
						printf("Aluno nao cadastrado!\n");
						i--;
					}
				}
			}
	

			break;
		case cancelarProfessor:
			do
			{
				printf("Digite quantas disciplinas serao desalocadas:\n");
				scanf("%d", &qtdDis);
			} while (qtdDis>20);

			imprimeDisciplinas(indiceDis, disciplinas);

			for (i = 0; i < qtdDis; i++) {
				printf("Digite codigo da disciplina:\n");
				scanf("%d", &codAtual);
				if (existeDisciplina(codAtual, indiceDis, disciplinas) == 1) {
					grupoDisciplina[i] = codAtual;
				}
				else {
					printf("Disciplina nao cadastrado!\n");
					i--;
				}
			}

			printf("Digite quantos professores serao desalocados:\n");
			scanf("%d", &qtd);
			imprimeProfessores(indiceProf, professores);
			for (i = 0; i < qtd; i++) {
				printf("Digite rg do professor:\n");
				scanf("%d", &rgAtual);
				if (existeProfessor(rgAtual, indiceProf, professores) == 1) {
					cancelarDisciplina2(buscarProfessor(rgAtual, indiceProf, professores), professores, qtdDis, grupoDisciplina);
				}
				else {
					printf("Professor nao cadastrado!\n");
					i--;
				}
			}
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
		case imprimirDiscAluno:
			printf("Digite ra do aluno:\n");
			scanf("%d", &raAtual);

			if (existeAluno(raAtual, indiceAluno, alunos) == 1) {
				imprimirDisciplinasDeAluno(buscarAluno(raAtual, indiceAluno, alunos), alunos);
			}
			else {
				printf("Aluno nao cadastrado!\n");
			}

			break;
		case imprimirAlunoDisc:
			printf("Digite codigo da disciplina:\n");
			scanf("%d", &codAtual);
			if (existeDisciplina(codAtual, indiceDis, disciplinas) == 1) {
				imprimirAlunosPorDisciplina(codAtual, indiceAluno, alunos);
			}
			else {
				printf("Disciplina nao cadastrada!\n");
			}
			break;
		case imprimirDiscProf:
			printf("Digite rg do professor:\n");
			scanf("%d", &rgAtual);
			if (existeProfessor(rgAtual, indiceProf, professores) == 1) {
				imprimirDisciplinasDeProf(buscarProfessor(rgAtual, indiceProf, professores), professores);
			}
			else {
				printf("Professor nao cadastrado!\n");
			}
			break;
		case imprimirProfDisc:
			printf("Digite codigo da disciplina:\n");
			scanf("%d", &codAtual);
			if (existeDisciplina(codAtual, indiceDis, disciplinas) == 1) {
				imprimirProfPorDisciplina(codAtual, indiceProf, professores);
			}
			else {
				printf("Disciplina nao cadastrada!\n");
			}
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

int buscarAluno(int ra, int tamanho, aluno *alunos) {
	int j;
	for (j = 0; j < tamanho; j++) {
		if (alunos[j].ra == ra) {
			return j;
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

int existeMatricula(int cod, int posAluno, aluno *alunos) {
	int k;
	for (k = 0; k < alunos[posAluno].qtdDisci; k++) {
		if (alunos[posAluno].disciplinas[k] == cod) {
			return 1;// true existe
		}
	}
	return 0;
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

int buscarProfessor(int rg, int tamanho, professor *professores) {
	int j;
	for (j = 0; j < tamanho; j++) {
		if (professores[j].rg == rg) {
			return j;
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

int existeAlocacao(int cod, int tamanho, professor *professores) {
	int k;
	for (k = 0; k < professores[tamanho].qtdDisci; k++) {
		if (professores[tamanho].disciplinas[k] == cod) {
			return 1;// true existe
		}
	}
	return 0;
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

int cursando(aluno alunoAtual) {
	int j, cursos = 0;
	for (j = 0; j < 20; j++) {
		if (alunoAtual.disciplinas[j] != NULL) {
			cursos++;
		}
	}
	return cursos;
}
void matricularAlunos(int posAluno, aluno *alunos, int qtdDis, int *grupoDisciplinas) {
	int j, k = 0, materias, l = 0;
	materias = alunos[posAluno].qtdDisci;
	if (materias >= 20) {
		printf("Este aluno ja esta cadastrado em muitas disiciplinas!\n");
	}
	else {
		if (materias == 0) {
			for (j = 0; j < qtdDis; j++) {
				alunos[posAluno].disciplinas[j] = grupoDisciplinas[l];
				alunos[posAluno].qtdDisci++;
				l++;
				}
		}
		else {
			for (j = materias - 1; j < 20; j++) {
				if (l >= qtdDis) {
					j = 20;
				}
				else {
					if (existeMatricula(grupoDisciplinas[l], posAluno, alunos) == 0) {
						alunos[posAluno].disciplinas[j] = grupoDisciplinas[l];
						alunos[posAluno].qtdDisci++;
						//k++;
						j--;
					}
					l++;
				}
			}
			//for (j = k; j < qtdDis; j++) {
			//printf("Este aluno ja esta cadastrado em muitas disiciplinas!\n");
			//	printf("Nao foi possivel cadastrarlo na disciplina %d!\n", grupoDisciplinas[j]);
			//}
		}

	}
}

void imprimirDisciplinasDeAluno(int posAluno, aluno *alunos) {
	int j;
	printf("--------------Disciplinas---------------\n");
	if (alunos[posAluno].qtdDisci > 0) {
		for (j = 0; j < alunos[posAluno].qtdDisci; j++) {
			printf("%d\n", alunos[posAluno].disciplinas[j]);
		}
	}
	else {
		printf("Este aluno nao esta cadastrado em nenhuma disciplina!\n");
	}

}
void imprimirAlunosPorDisciplina(int codAtual, int tamanho, aluno *alunos) {
	int j, k;
	printf("--------------Alunos---------------\n");
	for (j = 0; j < tamanho; j++) {
		if (alunos[j].qtdDisci != 0) {
			for (k = 0; k < alunos[j].qtdDisci; k++) {
				if (alunos[j].disciplinas[k] == codAtual) {
					printf("%d\n", alunos[j].ra);
				}
			}
		}
	}
}
void excluiDoVetor(int posAluno, int posDisc, aluno *alunos) {
	int j;
	if (alunos[posAluno].qtdDisci == 1) {
		alunos[posAluno].disciplinas[posDisc] = 0;
	}
	else {
		for (j = posDisc; j < alunos[posAluno].qtdDisci; j++) {

			if (j == (alunos[posAluno].qtdDisci - 1)) {
				alunos[posAluno].disciplinas[j] = 0;
			}
			else {
				alunos[posAluno].disciplinas[j] = alunos[posAluno].disciplinas[j + 1];
			}
		}

	}

	alunos[posAluno].qtdDisci--;
}
void cancelarDisciplina(int posAluno, aluno *alunos, int qtdDis, int *grupoDisciplinas) {
	int j, k, l;
	for (l = 0; l < qtdDis; l++) {
		if (alunos[posAluno].qtdDisci != 0) {
			for (k = 0; k < alunos[posAluno].qtdDisci; k++) {
				if (alunos[posAluno].disciplinas[k] == grupoDisciplinas[l]) {
					excluiDoVetor(posAluno, k, alunos);
				}
			}
		}
	}
}

void cancelarDisciplina2(int posProf, professor *professores, int qtdDis, int *grupoDisciplinas) {
	int j, k, l;
	for (l = 0; l < qtdDis; l++) {
		if (professores[posProf].qtdDisci != 0) {
			for (k = 0; k < professores[posProf].qtdDisci; k++) {
				if (professores[posProf].disciplinas[k] == grupoDisciplinas[l]) {
					excluiDoVetor2(posProf, k, professores);
				}
			}
		}
	}
}

void alocarProfessores(int posProf, professor *professores, int qtdDis, int *grupoDisciplinas) {
	int j, k = 0, materias, l = 0;
	materias = professores[posProf].qtdDisci;
	printf("%d", materias);
	if (materias >= 20) {
		printf("Este professor ja esta cadastrado em muitas disiciplinas!\n");
	}
	else {
		if (materias == 0) {
			for (j = 0; j < qtdDis; j++) {
				professores[posProf].disciplinas[j] = grupoDisciplinas[j];
				professores[posProf].qtdDisci++;
				//l++;
			}

		}
		else {
			for (j = (materias - 1); j < 20; j++) {
				if (l >= qtdDis) {
					j = 20;
				}
				else {
					if (existeAlocacao(grupoDisciplinas[l], posProf, professores) == 0) {
						professores[posProf].disciplinas[j] = grupoDisciplinas[l];
						professores[posProf].qtdDisci++;
						//k++;
						j--;
					}
					l++;
				}
			}
			//for (j = k; j < qtdDis; j++) {
			//printf("Este aluno ja esta cadastrado em muitas disiciplinas!\n");
			//	printf("Nao foi possivel cadastrarlo na disciplina %d!\n", grupoDisciplinas[j]);
			//}
		}

	}
}

void imprimirDisciplinasDeProf(int posProf, professor *professores) {
	int j;
	printf("--------------Disciplinas---------------\n");
	if (professores[posProf].qtdDisci > 0) {
		for (j = 0; j < professores[posProf].qtdDisci; j++) {
			printf("%d\n", professores[posProf].disciplinas[j]);
		}
	}
	else {
		printf("Este professor nao esta cadastrado em nenhuma disciplina!\n");
	}

}
void imprimirProfPorDisciplina(int codAtual, int tamanho, professor *professores) {
	int j, k;
	printf("--------------Professores---------------\n");
	for (j = 0; j < tamanho; j++) {
		if (professores[j].qtdDisci > 0) {
			for (k = 0; k < professores[j].qtdDisci; k++) {
				if (professores[j].disciplinas[k] == codAtual) {
					printf("%d\n", professores[j].rg);
				}
			}
		}
	}
}

void excluiDoVetor2(int posProf, int posDisc, professor *professores) {
	int j;
	if (professores[posProf].qtdDisci == 1) {
		professores[posProf].disciplinas[posDisc] = 0;
	}
	else {
		for (j = posDisc; j < professores[posProf].qtdDisci; j++) {

			if (j == (professores[posProf].qtdDisci - 1)) {
				professores[posProf].disciplinas[j] = 0;
			}
			else {
				professores[posProf].disciplinas[j] = professores[posProf].disciplinas[j + 1];
			}
		}

	}

	professores[posProf].qtdDisci--;
}

int existeNoVetor(int tamanho, int *vetor, int valorAtual) {
	int i;
	for (i = 0; i < tamanho; i++) {
		if (vetor[i] == valorAtual) {
			return 1;
		}
	}
	return 0;
}
