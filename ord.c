#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ARQUIVO_IMPORTACAO "catalogo.txt"
#define ARQUIVO_REGISTROS  "registros.txt"

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

int readfield (FILE* fHandle, char* string){
	int i = 0;
	char ch;
	ch = fgetc(fHandle);
	while(ch != EOF && ch != '\n' ) {
		if ( ch == ';'){
			string[i] = '|';
		}else{
        	string[i] = ch;
    	}
    	i = i + 1;
        ch = fgetc(fHandle);
    }
    string[i] = '|';
    i = i+1;
	string[i] = '\0';
	return i;
}

void importacao(){
    unsigned short tamanhoString;
    FILE* file;
    FILE* fileEscrita;
	char ch;
	char* buffer;
    file = fopen( ARQUIVO_IMPORTACAO, "r+" );
    if ( !file ){
        printf("\n Não foi possivel abrir arquivo %s. Verifique!", ARQUIVO_IMPORTACAO );
        return;
    }
    fileEscrita = fopen( ARQUIVO_REGISTROS, "w+" );
    if ( !fileEscrita ){
        printf("\n Não foi possivel abrir arquivo %s de escrita. Verifique!", ARQUIVO_REGISTROS );
        return;
    }
	while (readfield(file, buffer) > 1 ){
        tamanhoString = strlen(buffer);
        printf("\n %d ", tamanhoString );
        fwrite(&tamanhoString, sizeof(tamanhoString), 1, fileEscrita);
        fwrite(buffer, tamanhoString, 1, fileEscrita);
	}
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
