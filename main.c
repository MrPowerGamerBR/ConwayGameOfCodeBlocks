#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int MAX_X = 50; // tamanho x
int MAX_Y = 50; // tamanho y
int geracao = 0; // geração atual

int main(int argc, char *argv[]) {
	int tabela[100][100]; // tabela da geração "passada"
	int nextGen[100][100]; // tabela da geração processada

	limparMundo(tabela);
	
	// REQ01
	while (0 == 0) { // Ficar preso em um loop infinito, para caso o usuário coloque uma opção errada
		clrscr(); // Limpar tela
		char ch = ' ';

		printf("CONWAY'S JOGO DA VIDA\n\n");
		printf("\n(C)onfigurar");
		printf("\n(J)ogar");
		printf("\n(S)air");

		printf("\n\nForneca a opcao...\n");
		scanf(" %c", &ch);

		clrscr();

		if (ch == 'c' || ch == 'C') { // Caso seja C, mostre a configuração
			mostrarConfig(tabela);
		}
		if (ch == 'j' || ch == 'J') { // Caso seja J, saia do loop e entre no jogo
			break;
		}
		if (ch == 's' || ch == 'S') { // Caso seja S, retorne e saia do programa
			return;
		}
	}

	// Variáveis de inicialização
	int autoGen = 0;
	int delayTimer = 0;
	bool simularNextGen = true;

	while (0 == 0) {
		clrscr();

		printf("GERACAO %d\n", geracao);
		copiarTabelaParaNextGen(tabela, nextGen);
		if (geracao != 0 && simularNextGen) {
			processarJogo(tabela, nextGen);
		}
		simularNextGen = true;

		mostrarNextGen(nextGen);
		copiarNextGenParaTabela(tabela, nextGen);

		// REQ07
		if (autoGen != 0) {
			sleep(1);
			autoGen--;
		} else {
			// REQ10
			char ch = _getch();
			printf("%c", ch);
			if (ch == 's' || ch == 'S') {
				FILE *f = fopen("kkeaemen.txt", "w");
				if (f == NULL)
				{
				    printf("Erro ao abrir o arquivo\n");
				    exit(1);
				}

				fprintf(f, "%d;%d;%d\n", MAX_X, MAX_Y, geracao);
				int auxX = 0;
				while (100 > auxX) {
					int auxY = 0;
					while (100 > auxY) {
						if (tabela[auxX][auxY] == 1) {
							fprintf(f, "1");
						} else {
							fprintf(f, "0");
						}

						auxY++;
					}
					fprintf(f, "\n");
					auxX++;
				}
				fclose(f);
				simularNextGen = false;
				continue;
			}
			// REQ05 & REQ06
			if (ch == 'j' || ch == 'J') {
				// jooj
				clrscr();
				printf("Quantas vezes você deseja simular automaticamente as gerações?\n");
				scanf(" %d", &autoGen);
				printf("Quantos segundos de delay?\n");
				scanf(" %d", &delayTimer);
			}
			if (ch == 'c' || ch == 'C') {
				carregarMundo(tabela, false);
				continue;
			}
			if (ch == 'p' || ch == 'P') {
				clrscr();
				printf("Escolha um padrão para ser carregado, ao escolher um padrão o seu jogo será DELETADO\n\nSair: -1\nLimpar Mundo: 0\nBlinker: 1\nToad: 2\nGlider: 3\n");
				int option = 0;
				scanf(" %d", &option);

				if (option == -1) {
					simularNextGen = false;
					continue;
				}
				
				limparMundo(tabela);

				if (option == 0) {
					simularNextGen = false;
					continue;
				}
				
				if (option == 1) {
					tabela[1][0] = 1;
					tabela[1][1] = 1;
					tabela[1][2] = 1;
				}
				if (option == 2) {
					tabela[1][1] = 1;
					tabela[1][2] = 1;
					tabela[1][3] = 1;
					tabela[2][0] = 1;
					tabela[2][1] = 1;
					tabela[2][2] = 1;
				}

				if (option == 3) {
					tabela[0][0] = 1;
					tabela[1][1] = 1;
					tabela[1][2] = 1;
					tabela[2][1] = 1;
					tabela[2][0] = 1;
				}

				simularNextGen = false;
				continue;
			}
		}

		geracao++;
	}
	// printf(".X");

	return 0;
}

void processarJogo(int tabela[100][100], int nextGen[100][100]) { // Processa a próxima geração
	int auxX = 0;
	while (MAX_X > auxX) {
		int auxY = 0;
		while (MAX_Y > auxY) {
			int vizinhos = pegarVizinhosDaPosicao(auxX, auxY, tabela, MAX_X, MAX_Y);

			if (tabela[auxX][auxY] == 1) {
				if (2 > vizinhos) {
	
					nextGen[auxX][auxY] = 0;
					} else if (vizinhos > 3) {
						nextGen[auxX][auxY] = 0;
					} else {
						nextGen[auxX][auxY] = 1;
					}
				} else {
					if (vizinhos == 3) {
						nextGen[auxX][auxY] = 1;
				}
			}
			auxY++;
		}
		auxX++;
	}
}

void copiarTabelaParaNextGen(int tabela[100][100], int nextGen[100][100]) {
	int auxX = 0;
	while (MAX_X > auxX) {
		int auxY = 0;
		while (MAX_Y > auxY) {
			nextGen[auxX][auxY] = tabela[auxX][auxY];
			auxY++;
		}
		auxX++;
	}
}

void copiarNextGenParaTabela(int tabela[100][100], int nextGen[100][100]) {
	int auxX = 0;
	while (MAX_X > auxX) {
		int auxY = 0;
		while (MAX_Y > auxY) {
			tabela[auxX][auxY] = nextGen[auxX][auxY];
			auxY++;
		}
		auxX++;
	}
}

int pegarNumeroDeGenteViva(int nextGen[100][100]) {
	int auxX = 0;
	int i = 0;
	while (100 > auxX) {
		int auxY = 0;
		while (100 > auxY) {
			if (nextGen[auxX][auxY] == 1) {
				i++;
			}
			auxY++;
		}
		auxX++;
	}
	return i;
}

void mostrarNextGen(int nextGen[100][100]) {
	int auxX = 0;
	while (MAX_X > auxX) {
		int auxY = 0;
		while (MAX_Y > auxY) {
			if (nextGen[auxX][auxY] == 0) {
				printf(" ", nextGen[auxX][auxY]);
			} else {
				// printf("â˜º", nextGen[auxX][auxY]);
				printf("\xDB");
				// printf("");
			}
			auxY++;
		}
		int div = MAX_X / 2;
		printf(" \263 ");
		if (auxX == div - 2) {
			printf("Numero de celulas vivas: %d", pegarNumeroDeGenteViva(nextGen));
		}
		
		if (auxX == div) {
			printf("Para escolher um padrao, aperte P");
		}
		if (auxX == div + 1) {
			printf("Para salvar, aperte S");
		}
		if (auxX == div + 2) {
			printf("Para carregar, aperte C");
		}
		if (auxX == div + 3) {
			printf("Para avançar, aperte A");
		}
		if (auxX == div + 3) {
			printf("Para simular automaticamente, aperte J");
		}
		printf("\n");
		auxX++;
	}
}

void mostrarConfig(int tabela[100][100]) {
	char ch = ' ';

	printf("\n(A)lterar tamanho do mundo");
	printf("\n(S)elecionar seres vivos");
	printf("\n(L)impar células do mundo");
	printf("\n(C)arregar um jogo salvo");
	printf("\n(V)oltar");

	printf("\n\nForneca a opcao...\n");
	scanf(" %c", &ch);

	clrscr();

	if (ch == 'a' || ch == 'A') {
		pegarTamanhoDoMundo();
	}
	if (ch == 's' || ch == 'S') {
		selecionarSeresVivos(tabela);
	}
	if (ch == 'l' || ch == 'L') {
		limparMundo(tabela);
	}
	if (ch == 'c' || ch == 'C') {
		carregarMundo(tabela, true);
	}
	if (ch == 'y' || ch == 'Y') { // Debugging, apenas para gerar uma tabela aleatória
		{
			int auxX = 0;
			while (MAX_X > auxX) {
				int auxY = 0;
				while (MAX_Y > auxY) {
					tabela[auxX][auxY] = 0;
					int r = rand() % 3;
					if (r == 2) {
						tabela[auxX][auxY] = 1;
					}
					printf("%d %d\n", auxX, auxY);
					auxY++;
				}
				auxX++;
			}
		}
		// return;
	}
	if (ch == 'v' || ch == 'V') {
		return;
	}
}

// REQ03
void limparMundo(int tabela[100][100]) {
	int auxX = 0;
	while (100 > auxX) {
		int auxY = 0;
		while (100 > auxY) {
			tabela[auxX][auxY] = 0;
			auxY++;
		}
		auxX++;
	}
	clrscr();
	printf("Tabela limpada!\n");
}

void carregarMundo(int tabela[100][100], bool preVisualizacao) {
	char *nomeArq = "kkeaemen.txt";
	FILE *arq;
  	char linha[100];
  	char *result;

  	int i;
  	// Abre um arquivo TEXTO para LEITURA
  	arq = fopen(nomeArq, "rt");
  	if (arq == NULL)  // Se houve erro na abertura
  	{
    	printf("Problemas na abertura do arquivo: %s\n", nomeArq);
     	return;
 	}
  	i = 0;

  	bool isHeader = true;
  	int yAtual = 0;

  	while (!feof(arq)) {
		// Lê uma linha (inclusive com o '\n')
      	result = fgets(linha, 102, arq);

      	if (result) {
      		if (isHeader) {
      			char *aux;
      			char *eptr;

      			aux = strtok(result, ";");
      			MAX_X = strtol(aux, &eptr, 10);
      			aux = strtok(NULL, ";");
      			MAX_Y = strtol(aux, &eptr, 10);
      			aux = strtok(NULL, ";");
      			geracao = strtol(aux, (char **)NULL, 10);
      			isHeader = false;
			} else {
				int idx = 0;


				for (idx = 0; 100 > idx; idx++) {
					char c = linha[idx];
					if (c == '0') {
						tabela[yAtual][idx] = 0;
					} else {
						tabela[yAtual][idx] = 1;
					}
				}

				yAtual++;
			}
        }
		i++;
  	}
  	if (preVisualizacao) {
	  	printf("PRÉ-VISUALIZAÇÃO DO JOGO CARREGADO\n");
	  	mostrarNextGen(tabela);
	  	printf("Aperte qualquer tecla para continuar...");
	  	getch();
 	}
  	fclose(arq);
}

void pegarTamanhoDoMundo() {
	printf("Tamanho...\n");
	int tamanho = 0;
	scanf("%d", &tamanho);
	if (50 > tamanho || tamanho > 100) {
		printf("O tamanho deve ser entre 50 e 100!\n");
		pegarTamanhoDoMundo();
		return;
	}
	MAX_X = tamanho;
	MAX_Y = tamanho;
}

void selecionarSeresVivos(int tabela[100][100]) {
	while (0 == 0) {
		int x = 0;
		int y = 0;
		printf("Insira coordenadas para o nascimento do ser vivo\nCaso você queria sair, insira -1 -1\n");
		scanf("%d %d", &x, &y);

		if (x == -1 && y == -1) {
			return;
		}

		tabela[y][x] = 1;

		printf("A posição %d %d foi marcada como um ser vivo!\n", x, y, tabela[y][x]);
	}
}

int pegarVizinhosDaPosicao(int x, int y, int tabela[100][100], int maxX, int maxY) {
	int vizinhos = 0;

	int topX = -1;
	int topY = -1;
	int bottomX = 1;
	int bottomY = 1;

	if (0 >= x) {
		topX = 0;
	}
	if (0 >= y) {
		topY = 0;
	}
	if (x >= maxX - 1) {
		bottomX = 0;
	}
	if (y >= maxY - 1) {
		bottomY = 0;
	}

	int auxX = topX;
	while (bottomX >= auxX) {
		int auxY = topY;
		while (bottomY >= auxY) {
			int newX = x + auxX;
			int newY = y + auxY;
			if (x != newX || y != newY) {
				if (tabela[x + auxX][y + auxY] == 1) {
					vizinhos++;
				}
			}
			auxY++;
		}
		auxX++;
	}
	return vizinhos;
}

void clrscr()
{
    system("@cls||clear");
}
