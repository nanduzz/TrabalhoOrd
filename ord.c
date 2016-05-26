#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ARQUIVO_IMPORTACAO "catalogo.txt"
#define ARQUIVO_REGISTROS  "registros.txt"

typedef struct Aluno{
    int id;
    char* autor;
    char* titulo;
    char* curso;
    char* tipo;
}Aluno;


int selecionaOpcao(){

    int opcao;
    printf("\n Selecione uma opção:");
    printf("\n 1 -> Importar");
    printf("\n 2 -> Inserção");
    printf("\n 3 -> Remoção");
    printf("\n 0 -> Sair\n ");

    scanf( "%d", &opcao);
    fflush(stdin);
    return opcao;

}

void le(FILE* fHandle){

	char buffer[512];
	char* field;

	fread(buffer, 1, 64, fHandle);

	field = strtok(buffer,"|");
	while(field!=NULL){
		printf("%s \n", field);
		field = strtok(NULL, "|");
	}
}

void importacao(){

    FILE* file;
	int i = 0;
	int iCampo = 0;
	int iString = 0;
	char ch;
	char* string;
    char alunos[100][5][1000];
    file = fopen( ARQUIVO_IMPORTACAO, "r+" );
    if ( !file ){
        printf("\n Não foi possivel abrir arquivo %s. Verifique!", ARQUIVO_IMPORTACAO );
        return;
    }

	ch = fgetc(file);
    alunos[i][iCampo];
	while(ch != EOF ) {
        //novo registro
	    if( ch == '\n'){
            i++;
            iCampo = 0;
            iString = 0;
            ch = fgetc(file);
            continue;
	    }
        //le registro
	    while( ch != '\n' ){
            if ( ch == ';'){
                iCampo++;
                iString = 0;
                ch = fgetc(file);
                continue;
            }
            alunos[i][iCampo][iString] = ch;
            iString++;
            ch = fgetc(file);
	    }

    }

    for( int n = 0; n < 100; n++){
        printf( "\n");
        for( int j = 0; j < 5; j++){
            printf("\n-->%s", alunos[n][j] );
        }
        printf( "\n");
    }
    printf( " \n\n %d ", i );
}

void main(){

    int opcao;

    opcao = selecionaOpcao();
    while( opcao != 0){
        switch(opcao){
            case 1 : {
                importacao();
                break;
            }
            case 2 : {
                printf("\n inserindo");
                break;
            }

            case 3 : {
                printf( "\n Remoção");
                break;
            }
        }
        opcao = selecionaOpcao();
    }

}
