/*
Fa�a um programa que simule um sistema de controle banc�rio, nele deve conter as seguintes a��es;
	Cadastrar Cliente;
	Nome;
	CPF;
	N� Conta;
	Saldo;
	Senha(4 d�gitos , n�meros);
	Modificar Cadastro;	
	Sacar;
	Depositar;
	Transferir(N� conta e CPF);
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
# define  TAMANHO_ARQUIVO  1024
# define  MAX_LINNHAS  2048

// Cria��o da estrutura Cliente
typedef struct Cliente {
	char nome[20];
	char cpf[20];
	int conta;	
	float saldo;
	int senha;
} Cliente;

// M�todo de cadastro de Clientes
void cadastrar() {
	Cliente *cliente;
	cliente = malloc(sizeof(Cliente));
	printf("Informe o nome do cliente: \n");
	scanf("%s", cliente->nome);
	printf("Informe o cpf: \n");
	scanf("%s", cliente->cpf);
	printf("Informe o n�mero da conta: \n");
	scanf("%d", &cliente->conta);
	printf("Informe o saldo inicial: \n");
	scanf("%f.2f", &cliente->saldo);
	printf("Informe o senha de 4 d�gitos: \n");
	scanf("%d", &cliente->senha);
	
	FILE *arq;
	
	arq = fopen("scb.txt", "at"); // Abra um arquivo de texto no modo de acr�scimo para escrever no final do arquivo. fopen() cria o arquivo se ele n�o existir.
	
	if(arq == NULL) {
		printf("Erro ao abrir arquivo");
		return true;
	} else {
		fprintf(arq, "%d ", cliente->conta);
		fprintf(arq, "%d ", cliente->senha);
		fprintf(arq, "%s ", cliente->nome);
		fprintf(arq, "%s ", cliente->cpf);
		fprintf(arq, "%.2f\n", cliente->saldo);
	}   

	fclose(arq);
	
	printf("Dados gravados com sucesso!");	
}

// M�todo de impress�o do banco de dados dos Clientes
void imprimir() {
	FILE* arq;
    char ch;
 
    arq = fopen("scb.txt", "r");	// lendo o arquivo de texto
 
    if (arq == NULL) {
        printf("Erro ao abrir arquivo \n");
        return true;
    }
 
    printf("\nImpress�o do banco de dados dos clientes\n");    
     
    while((ch = getc(arq)) != EOF) {	// final do arquivo - EOF
        printf("%c", ch);
        if (ch == EOF) {
        	break;
    	}
    } 
    printf("\n");
    
    fclose(arq);	
}

// M�todo de substitui��o de arquivo
void copiarConteudo(FILE *file1, FILE *file2) {
	char leitor[TAMANHO_ARQUIVO];
	
	while(fgets(leitor, TAMANHO_ARQUIVO, file1) != NULL)
	
	fputs(leitor, file2);
}

// M�todo de edi��o do cadastro de Clientes
void editar() {

	FILE *arq, *temp;
	
	char nomeArquivo[TAMANHO_ARQUIVO];
	char tempNomeArquivo[TAMANHO_ARQUIVO];
	char buffer[MAX_LINNHAS];
	char substitui[MAX_LINNHAS];
	int linhaSubstituta = 0;
		
	strcpy(tempNomeArquivo, "temp____");
	strcat(tempNomeArquivo, "scb.txt");
	
	printf("N�mero da linha que deseja substituir: ");
	scanf("%d", &linhaSubstituta);
	
	fflush(stdin);
	
	printf("Nova linha: ");
	fgets(substitui, MAX_LINNHAS, stdin);	
		
	arq = fopen("scb.txt", "r");
	temp = fopen("temp.txt", "w");
	
	if (arq == NULL || temp == NULL) {
		printf("Erro ao abrir o arquivo(s).\n");
		return 1;
	}
	
	bool continuaLendo = true;
	
	int linhaAtual = 1;
	
	do {
		fgets(buffer, MAX_LINNHAS, arq);
		
		if (feof(arq)) 
			continuaLendo = false;
		else if (linhaAtual == linhaSubstituta)
		  fputs(substitui, temp);
		else fputs(buffer, temp);
		
		linhaAtual++;
	
	} while (continuaLendo);	
	
	fclose(arq);
	fclose(temp);
	
	FILE *arq1, *arq2;
	arq1 = fopen("scb.txt", "w");
	arq2 = fopen("temp.txt", "r");
	
	copiarConteudo(arq2, arq1);
	
	fclose(arq1);
	fclose(arq2);		
}

// M�todo de c�lculo de dep�sito
void depositar() {
	
	imprimir();
	
	float valorAtual=0, valorDeposito=0;
	
	printf("Informe o valor atual: ");
	scanf("%f", &valorAtual);
	
	printf("Informe o valor de dep�sito: ");
	scanf("%f", &valorDeposito);

	valorAtual = valorAtual + valorDeposito;	
	
	printf("Valor Atualizado: %.2f\n\n", valorAtual);
	
	imprimir();
	editar();
}

// M�todo de c�lculo de c�lculo de saque
void sacar() {
	
	imprimir();
	
	float valorAtual=0, valorSaque=0;
	
	printf("Informe o valor atual: ");
    scanf("%f", &valorAtual);
	
	printf("Informe o valor que deseja sacar: ");
    scanf("%f", &valorSaque);
	
    if (valorSaque <= valorAtual) {       
        
        valorAtual = valorAtual - valorSaque;        
        
    	printf("Valor Atualizado: %.2f\n\n", valorAtual);
    	
    	imprimir();
    	
    	editar();
    } else {
        printf("Saldo Insuficiente!!!!\n\n");
    }    
}

// M�todo de c�lculo de transfer�ncia
void transferir() {
	
	imprimir();
	
	float valorAtual=0, valorTransferir=0;
	int i=0;
	
	printf("Informe o valor atual: ");
    scanf("%f", &valorAtual);
    
    printf("Informe o valor que deseja transferir: ");
    scanf("%f", &valorTransferir);
	
    if (valorTransferir <= valorAtual) {        
        
        valorAtual = valorAtual - valorTransferir;        
        
    	printf("Valor Atualizado: %.2f\n\n", valorAtual);
    	
    	imprimir();  
		
		for(i=0; i<2;i++)
    		editar(); 			   	
    } else {
        printf("Saldo Insuficiente!!!!\n\n");
    }
}

// M�todo de menu
void menu() {
	
	setlocale(LC_ALL, "Portuguese");
	
	int op;
	while(op != 7){
		printf("Informe qual das opera��es deseja realizar\n");
		
		printf("1 - Cadastrar\n");
		printf("2 - Imprimir dados\n");
		printf("3 - Atualizar\n");
		printf("4 - Depositar\n");
		printf("5 - Sacar\n");
		printf("6 - Transferir\n");
		printf("0 - Sair\n");
		printf("Escolha->");
		scanf("%d", &op);
	
		switch(op){
			case 1:
				cadastrar();
				break;
			case 2: 
				imprimir();
				break;
			case 3:
				imprimir();
				editar();
				break;
			case 4:
				depositar();
				break;
			case 5:
				sacar();
				break;
			case 6:
				transferir();
				break;
			case 0:
				exit(true);
				break;
			default:
				printf("Opera��o inv�lida");
		}
	}
}

// M�todo principal
int main(void) {	
	menu();		
	return 0;
}
