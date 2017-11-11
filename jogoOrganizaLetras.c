#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int geraLetra(int dificuldade) { //Funcao que retorna o codigo ASCII de uma letra aleatoria de acordo com a dificuldade

	int letra=0;
	
	if (dificuldade == 1) {
		
		letra = (65 + rand()%6); 
		
	} else if (dificuldade == 2) {
		
		letra = (65 + rand()%16);
		
	} else {
		
		letra = (65 + rand()%26); 
		
	}
	
	
	return letra;
}

int verificaValidadePosicaoAnterior(int vet[], int letra, int posicao) { //Funcao para verificar se existe algum valor anterior que seja maior que a letra gerada
	int validade=1;
	int j;
	
	if (posicao == 1) {
		
		if (vet[posicao-1] > letra) 
			validade = 0;
		
	} else {
		
		for (j=0; j<posicao-1; j++) {  //Passa por todos os valores anteriores a posicao selecionada
	
			if (vet[j] > letra) {  //Verifica se em alguma posição anterior há uma letra "maior" que a letra gerada
	
				validade = 0;
		
			}
			
		}	
		
	}
	
	return validade;
}

int verificaValidadePosicaoSuperior(int vet[], int letra, int posicao) { //Funcao para verificar se existe algum valor após a posição selecionada que seja menor que a letra gerada
	
	int validade=1;
	int j;
	
	for (j=9; j>posicao-1; j--){ //Passa por todos os valores posteriores a posicao selecionada
		
		if ( (vet[j] != 0) && (vet[j] < letra) ) {  //Verifica se em alguma posição, apos a posicao selecionada, há uma letra "menor" que a letra gerada
	
			validade = 0; 
		
		}
		
	}
	
	return validade;
	
}

void mostraVetor(int vet[]) { //Funcao para mostrar o estado atual do vetor
	
	int j;
	
	printf("estado do vetor: \n\n{");
		
		for (j=0;j<10;j++){
			
			printf("%c ", vet[j]);
			
		}
			
	printf("}\n 1 2 3 4 5 6 7 8 9 10 \n");
	
}

int verificaPerda(int vet[], int letra) { //Funcao para verificar se usuario perdeu se nao tem mais jogadas possiveis
	int i, j=0, cont=0, fim, vetPosicao[10];
	
	for (i=0;i<10;i++) { //Verifica quais posicoes estao vazias
		
		if (vet[i] == 0) {
			
			vetPosicao[j] = i+1; 
			
			j++;  
			
		}
		
	}
	
	for (i=0; i<j; i++) { //Verifica se há alguma posicao que ainda pode ser ocupada
		
		if ((verificaValidadePosicaoAnterior(vet, letra, vetPosicao[i]) == 1) && (verificaValidadePosicaoSuperior(vet, letra, vetPosicao[i]) == 1)) {
		
			fim = 0;
			break;
		
		} else {
	
			fim = 1;	
		
		}
		
	}

	return fim;
	
}

int verificaGanho(int vet[]) { //Funcao que verifica se usuario ganhou se todas posições do vetor estao preenchidas
	
	int fim=1, i;
	
	for (i=0;i<10;i++) {
		
		if (vet[i] == 0) {
			
			fim = 0;
			
		}
		
	}
	
	return fim;
	
}

int main() {
	
	int vetor[10], i, pos, letraGerada, nivel;
	
	printf("selecione um nivel de dificuldade (1-facil, 2-medio, 3-dificil): ");
	scanf("%d", &nivel);
	
	while ( (nivel < 1) || (nivel > 3) ) {
		printf("nivel invalido. informe novamente um nivel de dificuldade (1-facil, 2-medio, 3-dificil): ");
		scanf("%d", &nivel);
	}
	
	for (i=0;i<10;i++) { //seta todos os valores do vetor pra 0
		vetor[i] = 0;
	}
	
	for (i=0;i<10;i++) {
		
		printf("---------Rodada %d----------\n", i+1);
		
		srand(time(NULL)); //Funcao usada pra nao repetir os numeros gerados aleatoriamente
		letraGerada = geraLetra(nivel);
		
		printf("letra gerada = %c\n", letraGerada);
		mostraVetor(vetor);
		
		if (verificaGanho(vetor) == 1) {
			printf("\n---------VOCE GANHOU----------!\n");
			return 0;
		}
		
		if (verificaPerda(vetor, letraGerada) == 1) {
			printf("\n-------VOCE PERDEU-------\n");
			return 0;
		}
		
		printf("posicao que deseja colocar a letra: ");
		scanf("%d", &pos);
		
		while ((vetor[pos-1] != 0) || (pos > 10) || (pos < 0)) {
			
			printf("posicao invalida. informe outra posicao: ");
			scanf("%d", &pos);
			
		}
						
		if ((verificaValidadePosicaoAnterior(vetor, letraGerada, pos) == 1) && (verificaValidadePosicaoSuperior(vetor, letraGerada, pos) == 1)) {	 
			
			vetor[pos-1] = letraGerada;
				
		} else {
			
			printf("posicao invalida. informe outra posicao: ");
			scanf("%d", &pos);
			
			while ( (verificaValidadePosicaoAnterior(vetor, letraGerada, pos) == 0) || (verificaValidadePosicaoAnterior(vetor, letraGerada, pos) == 0) ) {
				
				printf("posicao invalida. informe outra posicao: ");
				scanf("%d", &pos);
				
			}
			
			vetor[pos-1] = letraGerada;
			
		}	
			
	}
	
	return 0;
}
