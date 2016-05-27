#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ARQUIVO_IMPORTACAO "catalogo.txt"
#define ARQUIVO_REGISTROS  "registros.txt"

int selecionaOpcao(){

    int opcao;
    printf("\n Selecione uma op��o:");
    printf("\n 1 -> Importar");
    printf("\n 2 -> Inser��o");
    printf("\n 3 -> Remo��o");
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

void removeId( char* id){
	FILE* file;
	char idArquivo[3];
	short deslocamento;
	int bytesLidos;
	file = fopen(ARQUIVO_REGISTROS, "r+");
	if( !file ){
		printf( "N�o foi possivel abrir o arquivo %s para remo��o", ARQUIVO_REGISTROS );
		return;
	}
	do{
		fread(&deslocamento, sizeof(short), 1, file);
		bytesLidos = fread(&idArquivo, sizeof(char) * 2, 1, file);
		idArquivo[2] = '\0';
		printf("\n idArquivo : %c", idArquivo[0] );
		printf("\n idArquivo : %c", idArquivo[1] );
		printf("\n sizeof %s",  idArquivo );
		printf("\n deslocamento %d", deslocamento);
		if ( strcmp(id, idArquivo ) ){
			fseek( file, deslocamento - sizeof(char) - sizeof(char), SEEK_CUR); 
		}
	}while( strcmp(id, idArquivo) && bytesLidos != 0 );
		fseek(file, ftell(file), SEEK_SET);
		printf("\n------------%d---------", fputs("|-1", file) );
		fflush(file);
		fclose(file);

}

void remocao(){
	char id[2];
	
	printf("\n Digite id a ser removido:");
	gets(id);
	fflush(stdin);
	
	removeId( id );
		
}
void importacao(){
    unsigned short tamanhoString;
    FILE* file;
    FILE* fileEscrita;
	char ch;
	char* buffer;
    file = fopen( ARQUIVO_IMPORTACAO, "r" );
    if ( !file ){
        printf("\n N�o foi possivel abrir arquivo %s. Verifique!", ARQUIVO_IMPORTACAO );
        return;
    }
    fileEscrita = fopen( ARQUIVO_REGISTROS, "w+" );
    if ( !fileEscrita ){
        printf("\n N�o foi possivel abrir arquivo %s de escrita. Verifique!", ARQUIVO_REGISTROS );
        return;
    }
	while (readfield(file, buffer) > 1 ){
        tamanhoString = strlen(buffer);
        fwrite(&tamanhoString, sizeof(tamanhoString), 1, fileEscrita);
        fwrite(buffer, tamanhoString, 1, fileEscrita);
	}
	
	fclose( file);
	fclose( fileEscrita);
}

void main(){

    int opcao;
    
    opcao = selecionaOpcao();    
    //remocao();
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
                remocao();
                break;
            }
        }
        opcao = selecionaOpcao();
    }

}
