#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define INVALID_CHAR '#'
#define NUM_MOBS 5
#define NUM_ARMAS 5
#define MAX_ARMAS 5
#define QNT_CURA 20

typedef enum {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY,
    LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
} COLORS;

static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;

void textcolor (int color) {
	__FOREGROUND = color;
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), color + (__BACKGROUND << 4));
}

struct atributo {
	int agi_P, for_P, int_P, car_P, hp_P;
};

struct atributo_Mob {

	int dano_Mob,hp_Mob;

};

struct arma {

	char nome[50];
	int id;
	int dano;
	int defesa;
	float peso;

};

struct inventario {

	int moedas;
	int espaco;
	int hp_Pocoes;
	struct arma armas[MAX_ARMAS];

};

struct personagem_Principal {
	char classe[30];
	char genero[10];
	char nome[30];
	char raca[30];
	struct atributo *atributos;
	struct inventario invent;
};

struct mob {

	char nome[30];
	char raca[30];
	char classe [30];
	struct atributo_Mob atributos;

};


char le_Valida_Duplo_Char(char carac1, char caract2);
char mostrar_Sair();
int batalha_Mob(struct personagem_Principal *perso_Prin,struct mob mobs[],int pos_inventario);
int le_Valida_Num_MM(int num_Minimo,int num_Maximo);
int leValida_Troca_Arma(struct personagem_Principal *perso_Prin, int pos_inventario);
int ponto_Controle(struct personagem_Principal *perso_Prin, int num_Finalizacoes, int pos_inventario, int finalizarCapitulo, int checkPoint );
int selecao_Seta(int num_Finalizacoes);
int tutorial(struct personagem_Principal *perso_Prin, struct mob mobs[], struct arma armas_Todas[],int *pos_inventario);
void armazena_Armas_Inventario(struct personagem_Principal* perso_Prin,struct arma armas_Todas[],int *pos_inventario, int pos_Vetor);
void como_Jogar();
void continua_Save(struct personagem_Principal *perso_Prin, int *num_Finalizacoes, int *pos_inventario, int *finalizarCapitulo, int *checkPoint  );
void cria_Personagem(struct personagem_Principal* perso_Prin, int num_Finalizacoes);
void flashback_Historia(int num_Flash);
void gotoxy(int x, int y);
void informacoes();
void inicia_Historia();
void le_Valida_Classe(struct personagem_Principal *perso_Prin, int num_Finalizacoes, int *num_Classe);
void le_Valida_Escolha_Atributo(char *escolha_Atributo);
void le_Valida_Genero(struct personagem_Principal *perso_Prin);
void le_Valida_Nome(struct personagem_Principal *perso_Prin);
void le_Valida_Tecla_Dado(char *tecla_dado);
void limpa_Tela();
void mostra_ASCII_Classe();
void mostra_Erro(int num_Erro);
void mostra_Hps(struct personagem_Principal *perso_Prin,struct mob mobs[], int numMob);
void mostra_Inimigo(int num_Inimigo);
void mostra_Janela(int cor);
void mostra_Menu();
void mostra_Seguir(char seguirGo);
void mostrar_Menu_Classes(int num_Finalizacoes);
void mostrar_Menu_Classes_Extra(int num_Finalizacoes);
void preenche_Armas(struct arma armas_Todas[]);
void preenche_Atributo(struct personagem_Principal *perso_Prin, int num_Classe);
void preenche_Classe(struct personagem_Principal *perso_Prin, int *num_Classe);
void preencher_Mob(struct mob mobs[]);
void realiza_Espacamento(struct personagem_Principal *perso_Prin, int num_Espaco);
void realizaSave(struct personagem_Principal *perso_Prin, int num_Finalizacoes, int pos_inventario, int finalizarCapitulo, int checkPoint);
void recompensa_batalha(struct personagem_Principal *perso_Prin);
void reproduz_Texto_Narrador(int num_texto);
void set_Dimensions();
void you_Died();
void creditos();

int main () {

	int tecla, flag_Tecla = 0, finalizarCapitulo = 0, finalizar_Jogo = 0, num_Finalizacoes = 0, pos_inventario = 0, volta_Menu = 0, flag_volta = 0 , checkPoint = 0;
	struct personagem_Principal perso_Prin;
	struct mob mobs[NUM_MOBS];
	struct arma armas_Todas[MAX_ARMAS];
	struct atributo atributosAux;
	int id[MAX_ARMAS];

	char seguirGo = 'Y';
	char escolha_saida = 'N';

	num_Finalizacoes = 0;
	preenche_Armas(armas_Todas);

	perso_Prin.atributos = &atributosAux;

	srand(time(NULL));

	do {
		//	printf("%d",checkPoint);
		
		escolha_saida = 'N';
		set_Dimensions();
		mostra_Menu(1);

		if(flag_Tecla == 0) {
			tecla = selecao_Seta(num_Finalizacoes);
		} else {
			flag_Tecla = 1;
		}

		



		switch(tecla) {

			case 1: // New Game - Começa

				if(finalizarCapitulo == 0) {
					cria_Personagem(&perso_Prin, num_Finalizacoes);
					preencher_Mob(mobs);
					Sleep(2000);

					inicia_Historia();

					finalizarCapitulo = finalizarCapitulo + tutorial(&perso_Prin,mobs,armas_Todas,&pos_inventario);

					//Finalizar == 1;

					if(finalizarCapitulo == 1 || flag_volta == 0) {
						volta_Menu = 0;
						volta_Menu = ponto_Controle(&perso_Prin, num_Finalizacoes, pos_inventario, finalizarCapitulo, checkPoint );//CheackPoint
						//ponto_Controle == 1;
						//Voltar Menu == 1 Se exit no checkpoint;
						//Voltar Menu == 0 Se continue no checkpoint;
						if(volta_Menu == 0) {
							flag_volta = 1;
						}
					}


					//Finalizar == 1;

					if(finalizarCapitulo == 1 || flag_volta == 1) {
						system("cls");

						printf(" Just after the fight %s falls to the ground and faints.\n",perso_Prin.nome);
						printf(" For a few seconds he sees that he is being charged, but then faints again.\n");
						printf(" When she finally wakes up, I realize she's in a room under a bed.\n");
						printf(" With a lot of effort tries to get up.\n");
						printf(" Woman:. Don't make too much effort you should rest.\n");

						printf("\n 'You have two options, go with the woman or go it alone' \n");
						printf(" Go with the woman ('Y'/'N')? \n >");
						fflush(stdin);
						seguirGo = le_Valida_Duplo_Char('Y','N');

						mostra_Seguir(seguirGo);
						num_Finalizacoes++;
					}
				}

				break;

			case 2: // Continue - Continuar?

				//ERRO -> Ta chegando como num_Finalizacoes = 0.
				//Metodo correto finalizarCapitulo == 0;

				if(finalizarCapitulo == 0) {
					system("cls");
					printf(" You do not have a save to continue, starting a new game. . .\n");
					Sleep(1500);
				} else {
					tecla = 1;
					continua_Save(&perso_Prin, &num_Finalizacoes, &pos_inventario, &finalizarCapitulo, &checkPoint);
					flag_Tecla = 1;
				}

				break;
			case 3: // Informations - Informações
				system("cls");
				//printf(" %d ",tecla);
				set_Dimensions();
				informacoes();
				getchar();
				break;
			case 4: // How To Play - Como Jogar
				system("cls");
				textcolor(RED);
				como_Jogar();
				textcolor(WHITE);
				getchar();
				break;
			case 5: // Exit - Sair
				system("cls");
				escolha_saida = mostrar_Sair();
				break;
		}

	} while(escolha_saida != 'Y');

	free(perso_Prin.atributos);
	return 0;
}

void preenche_Armas(struct arma armas_Todas[]) {

	int pos_Id = 0;
	int dano, id;
	char move_Ponteiro, nome_Arma[30];
	float peso;

	FILE *pont_armas;
	pont_armas = fopen("armas.txt","r");

	if(pont_armas == NULL) {
		mostra_Erro(1);
		exit(1);
	}

	do {

		fscanf(pont_armas,"%[^\n]",armas_Todas[pos_Id].nome);
		fscanf(pont_armas,"%d",&armas_Todas[pos_Id].id);
		fscanf(pont_armas,"%d",&armas_Todas[pos_Id].dano);
		fscanf(pont_armas,"%d",&armas_Todas[pos_Id].defesa);
		fscanf(pont_armas,"%f",&armas_Todas[pos_Id].peso);
		fseek(pont_armas,sizeof(char)+1, SEEK_CUR);

		pos_Id++;
	} while(pos_Id < NUM_ARMAS);

	fclose(pont_armas);
}

void cria_Personagem(struct personagem_Principal* perso_Prin, int num_Finalizacoes) {

	char mostra_Classe[100];
	int num_Classe;
	FILE *pont_Classe;

	strcpy(perso_Prin->raca,"Humano");

	limpa_Tela();
	printf(" Create your character \n");
	printf(" Name: ");
	le_Valida_Nome(perso_Prin);

	limpa_Tela();
	printf(" Name: %s \n",perso_Prin->nome);
	printf(" Gender ('M'/'W'): ");
	le_Valida_Genero(perso_Prin);

	limpa_Tela();
	printf(" Name: %s \n",perso_Prin->nome);
	printf(" Gender: %s \n",perso_Prin->genero);
	printf(" Race: %s \n",perso_Prin->raca);
	mostrar_Menu_Classes(num_Finalizacoes);
	printf(" Class: ");
	le_Valida_Classe(perso_Prin, num_Finalizacoes, &num_Classe);

	perso_Prin->atributos = NULL;

	preenche_Atributo(perso_Prin,num_Classe);

	limpa_Tela();
	printf(" Name:   %s \n",perso_Prin->nome);
	printf(" Gender: %s \n",perso_Prin->genero);
	printf(" Race:   %s \n",perso_Prin->raca);
	printf(" Class:  %s \n\n",perso_Prin->classe);

	printf(" Health Points = %d\n\n",perso_Prin->atributos->hp_P);
	printf(" Agility       = %d \t Carism       = %d \n",perso_Prin->atributos->agi_P, perso_Prin->atributos->car_P);
	printf(" Force         = %d \t Intelligence = %d \n\n",perso_Prin->atributos->for_P, perso_Prin->atributos->int_P);

	perso_Prin->invent.espaco = 0;
	perso_Prin->invent.hp_Pocoes = 0;
	perso_Prin->invent.moedas = 0;

	/*
	//mostra_ASCII_Classe(); ainda nao pronto

	// Lembrar de colocar um time antes do jogo começar
	*/
}

void gotoxy(int x, int y) {
	COORD p= {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void mostra_Janela(int cor) {
	int pos_Pixel;

	if(cor == 1)
		textcolor(DARKGRAY);
	else if(cor == 2)
		textcolor(BROWN);

	gotoxy(0,0);
	printf("%c",201); // Canto superior esquerdo
	gotoxy(0,34);
	printf("%c",200); // Canto inferior esquerdo
	gotoxy(119,0);
	printf("%c",187); // Canto superior direito
	gotoxy(119,34);
	printf("%c",188); // Canto inferior direito

	for(pos_Pixel = 1; pos_Pixel < 34; pos_Pixel++) {
		gotoxy(0,pos_Pixel);
		printf("%c",186); // Linha Vertical Superior
		gotoxy(119,pos_Pixel);
		printf("%c",186); // Linha Vertical Inferior
	}

	for(pos_Pixel = 1; pos_Pixel < 119; pos_Pixel++) {
		gotoxy(pos_Pixel,0);
		printf("%c",205); // Linha Horizontal Superior
		gotoxy(pos_Pixel,34);
		printf("%c",205); // Linha Horizontal Inferior
	}

	textcolor(WHITE);
}

void mostra_Menu() {
	char frase_Menu[100];
	FILE *pont_Menu;
	
	textcolor(LIGHTBLUE);
	char saigo[] = {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xBB,0x20,0xDB,0xDB,0xDB,0xDB,0xDB,0xBB,0x20,0xDB,0xDB,0xBB,0x20,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xBB,0x20,0x20,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xBB,0x20,0x20,0x20,0x20,0x20,0xDB,0xDB,0xDB,0xBB,0x20,0x20,0x20,0xDB,0xDB,0xBB,0x20,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xBB,0x20,0x20,0x20,0x20,0x20,0xDB,0xDB,0xBB,0x20,0x20,0xDB,0xDB,0xBB,0xDB,0xDB,0xBB,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xBB,0x20,0x20,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xBB,0x20,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xDB,0xDB,0xC9,0xCD,0xCD,0xCD,0xCD,0xBC,0xDB,0xDB,0xC9,0xCD,0xCD,0xDB,0xDB,0xBB,0xDB,0xDB,0xBA,0xDB,0xDB,0xC9,0xCD,0xCD,0xCD,0xCD,0xBC,0x20,0xDB,0xDB,0xC9,0xCD,0xCD,0xCD,0xDB,0xDB,0xBB,0x20,0x20,0x20,0x20,0xDB,0xDB,0xDB,0xDB,0xBB,0x20,0x20,0xDB,0xDB,0xBA,0xDB,0xDB,0xC9,0xCD,0xCD,0xCD,0xDB,0xDB,0xBB,0x20,0x20,0x20,0x20,0xDB,0xDB,0xBA,0x20,0xDB,0xDB,0xC9,0xBC,0xDB,0xDB,0xBA,0xDB,0xDB,0xC9,0xCD,0xCD,0xDB,0xDB,0xBB,0xDB,0xDB,0xC9,0xCD,0xCD,0xCD,0xDB,0xDB,0xBB,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xBB,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xBA,0xDB,0xDB,0xBA,0xDB,0xDB,0xBA,0x20,0x20,0xDB,0xDB,0xDB,0xBB,0xDB,0xDB,0xBA,0x20,0x20,0x20,0xDB,0xDB,0xBA,0x20,0x20,0x20,0x20,0xDB,0xDB,0xC9,0xDB,0xDB,0xBB,0x20,0xDB,0xDB,0xBA,0xDB,0xDB,0xBA,0x20,0x20,0x20,0xDB,0xDB,0xBA,0x20,0x20,0x20,0x20,0xDB,0xDB,0xDB,0xDB,0xDB,0xC9,0xBC,0x20,0xDB,0xDB,0xBA,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xC9,0xBC,0xDB,0xDB,0xBA,0x20,0x20,0x20,0xDB,0xDB,0xBA,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xC8,0xCD,0xCD,0xCD,0xCD,0xDB,0xDB,0xBA,0xDB,0xDB,0xC9,0xCD,0xCD,0xDB,0xDB,0xBA,0xDB,0xDB,0xBA,0xDB,0xDB,0xBA,0x20,0x20,0x20,0xDB,0xDB,0xBA,0xDB,0xDB,0xBA,0x20,0x20,0x20,0xDB,0xDB,0xBA,0x20,0x20,0x20,0x20,0xDB,0xDB,0xBA,0xC8,0xDB,0xDB,0xBB,0xDB,0xDB,0xBA,0xDB,0xDB,0xBA,0x20,0x20,0x20,0xDB,0xDB,0xBA,0x20,0x20,0x20,0x20,0xDB,0xDB,0xC9,0xCD,0xDB,0xDB,0xBB,0x20,0xDB,0xDB,0xBA,0xDB,0xDB,0xC9,0xCD,0xCD,0xDB,0xDB,0xBB,0xDB,0xDB,0xBA,0x20,0x20,0x20,0xDB,0xDB,0xBA,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xBA,0xDB,0xDB,0xBA,0x20,0x20,0xDB,0xDB,0xBA,0xDB,0xDB,0xBA,0xC8,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xC9,0xBC,0xC8,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xC9,0xBC,0x20,0x20,0x20,0x20,0xDB,0xDB,0xBA,0x20,0xC8,0xDB,0xDB,0xDB,0xDB,0xBA,0xC8,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xC9,0xBC,0x20,0x20,0x20,0x20,0xDB,0xDB,0xBA,0x20,0x20,0xDB,0xDB,0xBB,0xDB,0xDB,0xBA,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xC9,0xBC,0xC8,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xC9,0xBC,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xC8,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xBC,0xC8,0xCD,0xBC,0x20,0x20,0xC8,0xCD,0xBC,0xC8,0xCD,0xBC,0x20,0xC8,0xCD,0xCD,0xCD,0xCD,0xCD,0xBC,0x20,0x20,0xC8,0xCD,0xCD,0xCD,0xCD,0xCD,0xBC,0x20,0x20,0x20,0x20,0x20,0xC8,0xCD,0xBC,0x20,0x20,0xC8,0xCD,0xCD,0xCD,0xBC,0x20,0xC8,0xCD,0xCD,0xCD,0xCD,0xCD,0xBC,0x20,0x20,0x20,0x20,0x20,0xC8,0xCD,0xBC,0x20,0x20,0xC8,0xCD,0xBC,0xC8,0xCD,0xBC,0xC8,0xCD,0xCD,0xCD,0xCD,0xCD,0xBC,0x20,0x20,0xC8,0xCD,0xCD,0xCD,0xCD,0xCD,0xBC,0x20};
	
	
		
	system("cls");
	pont_Menu = fopen("menu2.txt","r");

	printf("\n\n\n\n\n%s",saigo);
	printf("\n\n\n\n\n\n\n\n");	

	if(pont_Menu == NULL) {
		mostra_Erro(1);
		exit(1);
	} else {
		while(fgets(frase_Menu,100,pont_Menu) != NULL)
			printf("%s",frase_Menu);
	}
	fclose(pont_Menu);
	mostra_Janela(1);
}

int selecao_Seta(int num_Finalizacoes) {
	char tecla = 'H';
	int pos_Y = 20, tecla_Saida = 1;

// Seta Cima -> H = 72
// Seta Baixo-> P = 80

	textcolor(LIGHTGRAY );
	gotoxy(43,20);
	printf("%c%c%c%c%c",185,175,175,175,175); // Espada da Seleção
	gotoxy(119,34);

	do {

		fflush(stdin);
		tecla = toupper(getch());

		gotoxy(43,20);
		printf("      ");
		gotoxy(43,22);
		printf("      ");
		gotoxy(43,24);
		printf("      ");
		gotoxy(43,26);
		printf("      ");
		gotoxy(43,28);
		printf("      ");

		switch(tecla) {

			case 'H':
				pos_Y -= 2;

				if(pos_Y < 20)
					pos_Y = 28;

				tecla_Saida--;

				if(tecla_Saida == 0)
					tecla_Saida = 5;

				gotoxy(43,pos_Y);
				printf("%c%c%c%c%c",185,175,175,175,175); // Espada da Seleção

				break;
			case 'P':
				pos_Y += 2;

				if(pos_Y > 28)
					pos_Y = 20;

				tecla_Saida++;

				if(tecla_Saida == 6)
					tecla_Saida = 1;

				gotoxy(43,pos_Y);
				printf("%c%c%c%c%c",185,175,175,175,175); // Espada da Seleção

				break;

			default:
				gotoxy(43,pos_Y);
				printf("%c%c%c%c%c",185,175,175,175,175); // Espada da Seleção
		}

		gotoxy(119,34);


		// 13 e /n significa 'Enter'
	} while(tecla != 13);

	textcolor(WHITE);

	return tecla_Saida;
}

void mostra_Erro(int num_Erro) {
	fflush(stdin);
	switch(num_Erro) {
		case 1:
			printf(" ERROR 001: A file referring to the information to be executed was not opened, closing program . . . \n");
			break;
		case 2:
			printf(" ERROR 002: Invalid Name! \n");
			printf(" Enter name again: ");
			break;
		case 3:
			printf(" ERROR 003: Invalid Gender! \n");
			printf(" Enter gender again: ");
			break;
		case 4:
			printf(" ERROR 004: Invalid Class! \n");
			printf(" Enter class again: ");
			break;
		case 5:
			printf(" ERROR 005: Invalid attribute character! \n");
			printf(" Enter character again: ");
			break;
		case 6:
			printf(" ERROR 006: Invalid character! \n");
			printf(" Enter character again: ");
			break;
		case 7:
			printf(" ERROR 007: Memory allocation was not effective, closing program . . . \n");
			break;
		case 8:
			printf(" ERROR 008: Invalid number for selection! \n");
			printf(" Enter number for selection: ");
			break;
		case 9:
			printf(" ERROR 009: Invalid number for indication ! \n");
			printf(" Enter number for indication: ");
			break;
	}

}

void limpa_Tela() {
	system("cls");
	printf("\n");
}

void mostra_ASCII_Classe() {

//	pont_Classe = fopen("classe.txt","r");
//	fclose(pont_Classe);

}

void le_Valida_Nome(struct personagem_Principal *perso_Prin) {
	int pos_Nome, tamanho_Nome, tamanho_Max = 29, valid;

	do {
		if(!valid)
			mostra_Erro(2);
		valid = 1;

		fflush(stdin);
		gets(perso_Prin->nome);
		fflush(stdin);

		tamanho_Nome = strlen(perso_Prin->nome);

		if(tamanho_Max > tamanho_Nome && tamanho_Nome != 0) {
			for(pos_Nome = 0; pos_Nome < tamanho_Nome; pos_Nome++)
				if(!isalpha(perso_Prin->nome[pos_Nome]) && perso_Prin->nome[pos_Nome] != ' ')
					valid = 0;
		} else
			valid = 0;

	} while(!valid);
}

void le_Valida_Genero(struct personagem_Principal *perso_Prin) {
	char genero;

	do {
		scanf("%c",&genero);
		genero = toupper(genero);

		if(genero != 'M' && genero != 'W')
			mostra_Erro(3);

	} while(genero != 'M' && genero != 'W');

	if(genero == 'M')
		strcpy(perso_Prin->genero,"Man");
	else
		strcpy(perso_Prin->genero,"Woman");
}

void le_Valida_Classe(struct personagem_Principal *perso_Prin, int num_Finalizacoes, int *num_Classe) {

	do {
		scanf(" %d",num_Classe);

		if(*num_Classe < 1 || *num_Classe > (num_Finalizacoes + 1) * 5)
			mostra_Erro(4);

	} while(*num_Classe < 1 || *num_Classe > (num_Finalizacoes + 1) * 5);

	preenche_Classe(perso_Prin, num_Classe);

}

void preenche_Classe(struct personagem_Principal *perso_Prin, int *num_Classe) {

	switch(*num_Classe) {
		case 1:
			strcpy(perso_Prin->classe,"Warrior");
			break;
		case 2:
			strcpy(perso_Prin->classe,"Archer");
			break;
		case 3:
			strcpy(perso_Prin->classe,"Mage");
			break;
		case 4:
			strcpy(perso_Prin->classe,"Thief");
			break;
		case 5:
			strcpy(perso_Prin->classe,"Farmer");
			break;
		case 6:
			strcpy(perso_Prin->classe,"Paladin");
			break;
		case 7:
			strcpy(perso_Prin->classe,"Berserk");
			break;
		case 8:
			strcpy(perso_Prin->classe,"Priest");
			break;
		case 9:
			strcpy(perso_Prin->classe,"Druid");
			break;
		case 10:
			strcpy(perso_Prin->classe,"Merchant");
			break;
		case 11:
			strcpy(perso_Prin->classe,"Necromancer");
			break;
		case 12:
			strcpy(perso_Prin->classe,"Assasin");
			break;
		case 13:
			strcpy(perso_Prin->classe,"Guardian");
			break;
		case 14:
			strcpy(perso_Prin->classe,"Dark Knight");
			break;
		case 15:
			strcpy(perso_Prin->classe,"Dragon");
			break;
	}

}

void set_Dimensions() {
	system("MODE con cols=121 lines=36");
}

void informacoes () {

	FILE *arq;
	char palavra[100];
	char id_Classe[15][30] = {"Warrior.txt","Archer.txt","Mage.txt","Thief.txt","Farmer.txt",
	                          "Paladin.txt","Berserk.txt","Priest.txt","Druid.txt","Merchant.txt",
	                          "Necromancer.txt","Assasin.txt","Guardian.txt","Dark Knight.txt","Dragon.txt"
	                         };
	int pos_Classe = 0;

	do {

		system("cls");
		arq = fopen(id_Classe[pos_Classe],"r");

		if(arq == NULL) {
			mostra_Erro(1);
			exit(1);
		} else {
			while(fgets(palavra,100,arq) != NULL)
				printf(" %s",palavra);
		}
		getchar();
		fclose(arq);

		pos_Classe++;

	} while(pos_Classe < 15);

}

void mostrar_Menu_Classes(int num_Finalizacoes) {
	printf("-------------- Classes --------------\n");

	if(num_Finalizacoes == 0)
		mostrar_Menu_Classes_Extra(num_Finalizacoes);
	else if(num_Finalizacoes == 1)
		mostrar_Menu_Classes_Extra(num_Finalizacoes);
	else
		mostrar_Menu_Classes_Extra(num_Finalizacoes);

}

void mostrar_Menu_Classes_Extra(int num_Finalizacoes) {

	switch(num_Finalizacoes) {
		case 0:
			printf(" 01) Warrior   02) Archer      03) Mage    \n");
			printf(" +2 FOR.       +2 AGI.         +2 INT.     \n");
			printf(" -1 INT.       -2 FOR.         -1 FOR.     \n");
			printf(" -1 AGI.                       -1 AGI.     \n");

			printf("\n");
			printf(" 04) Thief     05) Farmer     \n");
			printf(" +2 AGI.       +2 AGI.        \n");
			printf(" -2 FOR.       +2 FOR.        \n");
			printf("               +2 INT.        \n");
			printf("               -4 CAR.        \n");
			break;
		case 1:
			printf(" 01) Warrior   02) Archer      03) Mage     \n");
			printf(" +2 FOR.       +2 AGI.         +2 INT.      \n");
			printf(" -1 INT.       -2 FOR.         -1 FOR.      \n");
			printf(" -1 AGI.                       -1 AGI.      \n");

			printf("\n");
			printf(" 04) Thief     05) Farmer       06) Paladin \n");
			printf(" +2 AGI.       +2 AGI.          +1 INT.     \n");
			printf(" -2 FOR.       +2 FOR.          +1 FOR.     \n");
			printf("               +2 INT.          +1 CAR.     \n");
			printf("               -4 CAR.          -3 AGI.     \n");

			printf("\n");
			printf(" 07) Berserk   08) Priest       09) Druid   \n");
			printf(" +3 FOR.       +1 INT.          +1 INT.     \n");
			printf(" -3 INT.       +2 CAR.          +2 AGI.     \n");
			printf("               +3 FOR.          -2 FOR.     \n");
			printf("                                -1 CAR.     \n");

			printf("\n");
			printf(" 10) Merchant  \n");
			printf(" +3 CAR.       \n");
			printf(" +1 INT.       \n");
			printf(" -2 FOR.       \n");
			printf(" -2 AGI.       \n");


			break;
		default:
			printf(" 01) Warrior   02) Archer      03) Mage     \n");
			printf(" +2 FOR.       +2 AGI.         +2 INT.      \n");
			printf(" -1 INT.       -2 FOR.         -1 FOR.      \n");
			printf(" -1 AGI.                       -1 AGI.      \n");

			printf("\n");
			printf(" 04) Thief     05) Farmer       06) Paladin \n");
			printf(" +2 AGI.       +2 AGI.          +1 INT.     \n");
			printf(" -2 FOR.       +2 FOR.          +1 FOR.     \n");
			printf("               +2 INT.          +1 CAR.     \n");
			printf("               -4 CAR.          -3 AGI.     \n");

			printf("\n");
			printf(" 07) Berserk   08) Priest       09) Druid   \n");
			printf(" +3 FOR.       +1 INT.          +1 INT.     \n");
			printf(" -3 INT.       +2 CAR.          +2 AGI.     \n");
			printf("               -3 FOR.          -2 FOR.     \n");
			printf("                                -1 CAR.     \n");

			printf("\n");
			printf(" 10) Merchant  11) Necromancer  12) Assasin \n");
			printf(" +3 CAR.       +5 INT.          +5 AGI.     \n");
			printf(" +1 INT.       -3 FOR.          -3 FOR.     \n");
			printf(" -2 FOR.       -1 AGI.          -2 CAR.     \n");
			printf(" -2 AGI.       -1 CAR.                      \n");

			printf("\n");
			printf(" 13) Guardian  14) Dark Knigh  15) Dragon   \n");
			printf(" +5 FOR.       +3 FOR.          +4 FOR.     \n");
			printf(" -4 AGI.       +2 AGI.          +1 AGI.     \n");
			printf(" -1 INT.       -2 INT.          -1 INT.     \n");
			printf("               -3 CAR.          -4 CAR.     \n");
	}

}

void le_Valida_Escolha_Atributo(char *escolha_Atributo) {

	do {
		fflush(stdin);
		scanf(" %c",escolha_Atributo);

		*escolha_Atributo = toupper(*escolha_Atributo);

		if(*escolha_Atributo != 'A' && *escolha_Atributo != 'F' && *escolha_Atributo != 'C' && *escolha_Atributo != 'I' )
			mostra_Erro(5);

	} while(*escolha_Atributo != 'A' && *escolha_Atributo != 'F' && *escolha_Atributo != 'C' && *escolha_Atributo != 'I' );


}

void preenche_Atributo(struct personagem_Principal *perso_Prin, int num_Classe) {
	int pontos_Iniciais = 5;
	int pontos_Aux = 5;
	char escolha_Atributo;
	void preenche_Atributo(struct personagem_Principal *perso_Prin, int num_Classe);

	if(perso_Prin->atributos == NULL) {
		perso_Prin->atributos = malloc(sizeof(struct atributo));
	} else {
		mostra_Erro(7);
		exit(1);
	}

	switch(num_Classe) {

		case 1:
			perso_Prin->atributos->for_P = pontos_Aux + 2;
			perso_Prin->atributos->agi_P = pontos_Aux - 1;
			perso_Prin->atributos->int_P = pontos_Aux - 1;
			perso_Prin->atributos->car_P = pontos_Aux;
			perso_Prin->atributos->hp_P = pontos_Aux + 95;
			break;
		case 2:
			perso_Prin->atributos->for_P = pontos_Aux - 2;
			perso_Prin->atributos->agi_P = pontos_Aux + 2;
			perso_Prin->atributos->int_P = pontos_Aux;
			perso_Prin->atributos->car_P = pontos_Aux;
			perso_Prin->atributos->hp_P = pontos_Aux + 65;
			break;
		case 3:
			perso_Prin->atributos->for_P = pontos_Aux - 1;
			perso_Prin->atributos->agi_P = pontos_Aux - 1;
			perso_Prin->atributos->int_P = pontos_Aux + 2;
			perso_Prin->atributos->car_P = pontos_Aux;
			perso_Prin->atributos->hp_P = pontos_Aux + 45;
			break;
		case 4:
			perso_Prin->atributos->for_P = pontos_Aux - 2;
			perso_Prin->atributos->agi_P = pontos_Aux + 2;
			perso_Prin->atributos->int_P = pontos_Aux;
			perso_Prin->atributos->car_P = pontos_Aux;
			perso_Prin->atributos->hp_P = pontos_Aux + 65;
			break;
		case 5:
			perso_Prin->atributos->for_P = pontos_Aux + 2;
			perso_Prin->atributos->agi_P = pontos_Aux + 2;
			perso_Prin->atributos->int_P = pontos_Aux + 2;
			perso_Prin->atributos->car_P = pontos_Aux - 4;
			perso_Prin->atributos->hp_P = pontos_Aux + 45;
			break;
		case 6:
			perso_Prin->atributos->for_P = pontos_Aux + 1;
			perso_Prin->atributos->agi_P = pontos_Aux - 3;
			perso_Prin->atributos->int_P = pontos_Aux + 1;
			perso_Prin->atributos->car_P = pontos_Aux + 1;
			perso_Prin->atributos->hp_P = pontos_Aux + 100;
			break;
		case 7:
			perso_Prin->atributos->for_P = pontos_Aux + 3;
			perso_Prin->atributos->agi_P = pontos_Aux ;
			perso_Prin->atributos->int_P = pontos_Aux - 3;
			perso_Prin->atributos->car_P = pontos_Aux;
			perso_Prin->atributos->hp_P = pontos_Aux + 75;
			break;
		case 8:
			perso_Prin->atributos->for_P = pontos_Aux - 3;
			perso_Prin->atributos->agi_P = pontos_Aux ;
			perso_Prin->atributos->int_P = pontos_Aux + 1;
			perso_Prin->atributos->car_P = pontos_Aux + 2;
			perso_Prin->atributos->hp_P = pontos_Aux + 55;
			break;
		case 9:
			perso_Prin->atributos->for_P = pontos_Aux - 2;
			perso_Prin->atributos->agi_P = pontos_Aux + 2;
			perso_Prin->atributos->int_P = pontos_Aux + 1;
			perso_Prin->atributos->car_P = pontos_Aux - 1;
			perso_Prin->atributos->hp_P = pontos_Aux + 75;
			break;
		case 10:
			perso_Prin->atributos->for_P = pontos_Aux - 2;
			perso_Prin->atributos->agi_P = pontos_Aux - 2;
			perso_Prin->atributos->int_P = pontos_Aux + 1;
			perso_Prin->atributos->car_P = pontos_Aux + 3;
			perso_Prin->atributos->hp_P = pontos_Aux + 45;
			break;
		case 11:
			perso_Prin->atributos->for_P = pontos_Aux - 3;
			perso_Prin->atributos->agi_P = pontos_Aux - 1;
			perso_Prin->atributos->int_P = pontos_Aux + 5;
			perso_Prin->atributos->car_P = pontos_Aux - 1;
			perso_Prin->atributos->hp_P = pontos_Aux + 85;
			break;
		case 12:
			perso_Prin->atributos->for_P = pontos_Aux - 3;
			perso_Prin->atributos->agi_P = pontos_Aux + 5;
			perso_Prin->atributos->int_P = pontos_Aux;
			perso_Prin->atributos->car_P = pontos_Aux - 2;
			perso_Prin->atributos->hp_P = pontos_Aux + 85;
			break;
		case 13:
			perso_Prin->atributos->for_P = pontos_Aux + 5;
			perso_Prin->atributos->agi_P = pontos_Aux - 4;
			perso_Prin->atributos->int_P = pontos_Aux - 1;
			perso_Prin->atributos->car_P = pontos_Aux;
			perso_Prin->atributos->hp_P = pontos_Aux + 175;
			break;
		case 14:
			perso_Prin->atributos->for_P = pontos_Aux + 3;
			perso_Prin->atributos->agi_P = pontos_Aux + 2;
			perso_Prin->atributos->int_P = pontos_Aux - 2;
			perso_Prin->atributos->car_P = pontos_Aux - 3;
			perso_Prin->atributos->hp_P = pontos_Aux + 155;
			break;
		case 15:
			perso_Prin->atributos->for_P = pontos_Aux + 4;
			perso_Prin->atributos->agi_P = pontos_Aux + 1;
			perso_Prin->atributos->int_P = pontos_Aux - 1;
			perso_Prin->atributos->car_P = pontos_Aux - 4;
			perso_Prin->atributos->hp_P = pontos_Aux + 145;
			break;
	}




	while(pontos_Iniciais != 0) {

		limpa_Tela();
		printf(" ------- Informations -------\n");
		printf(" Name: %s \n",perso_Prin->nome);
		printf(" Gender: %s \n",perso_Prin->genero);
		printf(" Race: %s \n",perso_Prin->raca);
		printf(" Class: %s \n",perso_Prin->classe);
		printf(" ------- Skill Points -------\n");
		printf(" Total Points %d\n",pontos_Iniciais);

		printf(" A - Agility      (Agi.) = %d\n",perso_Prin->atributos->agi_P);
		printf(" F - Force        (For.) = %d\n",perso_Prin->atributos->for_P);
		printf(" C - Carism       (Car.) = %d\n",perso_Prin->atributos->car_P);
		printf(" I - Intelligence (Int.) = %d\n",perso_Prin->atributos->int_P);

		printf(" Enter a character to represent the skill you want to add +1.\n");
		printf(" %c ",175);

		le_Valida_Escolha_Atributo(&escolha_Atributo);

		switch(escolha_Atributo) {

			case 'A':
				perso_Prin->atributos->agi_P++;
				break;
			case 'C':
				perso_Prin->atributos->car_P++;
				break;
			case 'F':
				perso_Prin->atributos->for_P++;
				break;
			case 'I':
				perso_Prin->atributos->int_P++;
				break;
		}
		pontos_Iniciais--;
	}
}

void inicia_Historia() {
	int num_Flash;

	for(num_Flash = 1; num_Flash <= 3; num_Flash++) {
		flashback_Historia(num_Flash);
		Sleep(1000);
	}

// Abre  Arquivo pontos aleatorios
	system("COLOR F0");
	system("COLOR 0F");
	system("COLOR F0");
	system("COLOR 0F");
// fecha Arquivo pontos aleatorios

}

void flashback_Historia(int num_Back) {
	limpa_Tela();

	char str_Flash[100];
	char nome_Flash[10] = {"asciiLuta"};
	char numero_Flash[2] = {num_Back + '0'};

	strcat(nome_Flash,numero_Flash);
	strcat(nome_Flash,".txt");

	FILE *pont_Flash;
	pont_Flash = fopen(nome_Flash,"r");


	if(pont_Flash == NULL) {
		mostra_Erro(1);
		exit(1);
	} else {
		while(fgets(str_Flash,100,pont_Flash) != NULL)
			printf("%s",str_Flash);
	}


	fclose(pont_Flash);
}

int tutorial(struct personagem_Principal *perso_Prin, struct mob mobs[], struct arma armas_Todas[],int *pos_inventario) {

	FILE *pont_sword;
	FILE *pont_yn;

	char escolha_Sword;
	int finalizar;
	char str_sword[100],str_yn[100];

	system("cls");

	pont_sword = fopen("asciiOldSword.txt","r");
	pont_yn = fopen("Y_ou_N.txt","r");

    reproduz_Texto_Narrador(1);
    reproduz_Texto_Narrador(2);

	printf("\n");

	printf(" Get the sword? ");

	printf("\n");

	if(pont_yn == NULL) {
		mostra_Erro(1);
		exit(1);
	} else {
		while(fgets(str_yn,100,pont_yn) != NULL)
			printf("%s",str_yn);
	}

	fflush(stdin);

	printf("\n\n\n\n\n\n");

	if(pont_sword == NULL) {
		mostra_Erro(1);
		exit(1);
	} else {
		while(fgets(str_sword,100,pont_sword) != NULL)
			printf("%s",str_sword);
	}

	printf("\n");

	escolha_Sword = le_Valida_Duplo_Char('Y', 'N');

	armazena_Armas_Inventario(perso_Prin, armas_Todas, pos_inventario, 0);

	if(escolha_Sword == 'Y')
		armazena_Armas_Inventario(perso_Prin, armas_Todas, pos_inventario, 2);

	finalizar = batalha_Mob(perso_Prin, mobs, *pos_inventario);

	fclose(pont_sword);
	fclose(pont_yn);

	return finalizar;
}

void armazena_Armas_Inventario(struct personagem_Principal* perso_Prin,struct arma armas_Todas[],int *pos_inventario, int pos_Vetor) {

	strcpy(perso_Prin->invent.armas[*pos_inventario].nome,armas_Todas[pos_Vetor].nome);
	perso_Prin->invent.armas[*pos_inventario].id = armas_Todas[pos_Vetor].id;
	perso_Prin->invent.armas[*pos_inventario].dano = armas_Todas[pos_Vetor].dano;
	perso_Prin->invent.armas[*pos_inventario].defesa = armas_Todas[pos_Vetor].defesa;
	perso_Prin->invent.armas[*pos_inventario].peso = armas_Todas[pos_Vetor].peso;

	*pos_inventario = *pos_inventario + 1;
}

char le_Valida_Duplo_Char(char carac1, char caract2) {
	char caracter;

	do {
		//scanf("%c",&caracter);
		caracter = getch();
		fflush(stdin);
		caracter = toupper(caracter);
		if(caracter != carac1 && caracter != caract2)
			mostra_Erro(6);

	} while(caracter != carac1 && caracter != caract2);

	return caracter;
}

void reproduz_Texto_Narrador(int num_texto) {

	char caracter;
	int num_Invalid = 0;
	FILE *pont_Narrador;

	pont_Narrador = fopen("fala_Narrador.txt","r");

	if(pont_Narrador == NULL) {
		mostra_Erro(1);
		exit(1);
	}

	do {
		fscanf(pont_Narrador,"%c",&caracter);

		if(caracter == INVALID_CHAR)
			num_Invalid++;

		if (num_Invalid == num_texto && caracter != INVALID_CHAR) {
			printf("%c",caracter);
			Sleep(50);
		}

	} while(num_Invalid <= num_texto);

	fclose(pont_Narrador);

}

void preencher_Mob(struct mob mobs[]) {

	int id_Mob = 0;
	int multiplicador = 2;//Mudar para numero randomico

	while(id_Mob != NUM_MOBS) {

		switch(id_Mob) {
			case 0:
				strcpy(mobs[id_Mob].nome,"???");
				strcpy(mobs[id_Mob].raca,"Orc");
				strcpy(mobs[id_Mob].classe,"Warrior");
				mobs[id_Mob].atributos.dano_Mob = 5;
				mobs[id_Mob].atributos.hp_Mob = 110;
				break;
			case 1:
				strcpy(mobs[id_Mob].nome,"MOB01");
				strcpy(mobs[id_Mob].raca,"RACA01");
				mobs[id_Mob].atributos.dano_Mob = 2;
				mobs[id_Mob].atributos.hp_Mob = 2;
				break;
			case 2:
				strcpy(mobs[id_Mob].nome,"MOB02");
				strcpy(mobs[id_Mob].raca,"RACA02");
				mobs[id_Mob].atributos.dano_Mob = 3;
				mobs[id_Mob].atributos.hp_Mob = 3;
				break;
			case 3:
				strcpy(mobs[id_Mob].nome,"MOB03");
				strcpy(mobs[id_Mob].raca,"RACA03");
				mobs[id_Mob].atributos.dano_Mob = 4;
				mobs[id_Mob].atributos.hp_Mob = 4;
				break;
			case 4:
				strcpy(mobs[id_Mob].nome,"MOB04");
				strcpy(mobs[id_Mob].raca,"RACA04");
				mobs[id_Mob].atributos.dano_Mob = 5;
				mobs[id_Mob].atributos.hp_Mob = 5;
				break;
			case 5:
				strcpy(mobs[id_Mob].nome,"MOB05");
				strcpy(mobs[id_Mob].raca,"RACA05");
				mobs[id_Mob].atributos.dano_Mob = 6;
				mobs[id_Mob].atributos.hp_Mob = 6;
				break;

		}
		id_Mob++;
	}
}

int le_Valida_Num_MM(int num_Minimo,int num_Maximo) {
	int num_Aux;

	do {
		scanf("%d",&num_Aux);

		if(num_Aux < num_Minimo || num_Aux > num_Maximo)
			mostra_Erro(8);

	} while(num_Aux < num_Minimo || num_Aux > num_Maximo);

	return num_Aux;
}

int batalha_Mob(struct personagem_Principal *perso_Prin,struct mob mobs[],int pos_inventario) {

	int acao, d6, d6_Mob;
	int id_Mob = 0, flag = 0 , vitoria_Pacifica = 0, cont_Arma = 0, armaAtual = pos_inventario - 1;
	int dano_Total_P, dano_Total_M,defesa_Total;
	int finalizar = 1;
	int vitoria = 0;
	int flag_Leve = 0;
	int derrota = 0;
	char tecla_dado;
	char str_asciiDado[100];

	FILE *pont_asciiDado;


	system("cls");

	reproduz_Texto_Narrador(3);

	acao = menu_Batalha(perso_Prin,mobs);

	do {
		dano_Total_P = 0;
		dano_Total_M = 0;
		defesa_Total = 0;
		flag_Leve = 0;

		if(flag) {
			system("cls");
			printf("\n Dice: %d \n",d6 );
			acao = menu_Batalha(perso_Prin,mobs);
		}

		if(acao == 1 || acao == 2) {
			pont_asciiDado = fopen("asciiDado.txt","r");

			printf(" Note: The die is used to influence your actions, throw it to get a bonus.\n");
			printf(" Press to roll the dice to determine the attribute multiplier:\n ");

			if(pont_asciiDado == NULL) {
				mostra_Erro(1);
				exit(1);
			} else {
				while(fgets(str_asciiDado,100,pont_asciiDado) != NULL)
					printf("\t%s",str_asciiDado);
			}

			le_Valida_Tecla_Dado(&tecla_dado);

			fclose(pont_asciiDado);
			d6 = (rand() % 5) + 1;
			limpa_Tela();
		}

		switch(acao) {
			case 1://Ataque Leve / Rapido

				//Dano total do ataque leve
				dano_Total_P =  ((perso_Prin->invent.armas[armaAtual].dano * d6) + (perso_Prin->atributos->agi_P / 5)) / 2;

				//Retirando a vida do mob ataque leve
				flag_Leve = 1;
				if(flag_Leve == 1)
					mobs[id_Mob].atributos.hp_Mob = mobs[id_Mob].atributos.hp_Mob - dano_Total_P;

				break;
			case 2://Ataque Forte/ Lento

				//Dano Total do ataque pesado
				dano_Total_P = (perso_Prin->invent.armas[armaAtual].dano * d6) + (perso_Prin->atributos->for_P / 5);

				//Retirando vida do mob ataque pesado
				mobs[id_Mob].atributos.hp_Mob = mobs[id_Mob].atributos.hp_Mob - dano_Total_P;

				break;
			case 3://Defesa
				system("cls");
				defesa_Total =  ((perso_Prin->invent.armas[armaAtual].defesa * d6)/5) + (perso_Prin->atributos->for_P / 5);
				defesa_Total = defesa_Total/2;
				vitoria_Pacifica = vitoria_Pacifica + 1;
				break;
			case 4://  Troca arma
				system("cls");

				printf("\n  Weapons: \n");
				for(cont_Arma = 0; cont_Arma < pos_inventario; cont_Arma++) {

					printf("\n  %d) %s \n",cont_Arma + 1, perso_Prin->invent.armas[cont_Arma].nome);
					printf("  Identification: %d \n",perso_Prin->invent.armas[cont_Arma].id);
					printf("  Damage: %d \n",perso_Prin->invent.armas[cont_Arma].dano);
					printf("  Defense: %d \n",perso_Prin->invent.armas[cont_Arma].defesa);
					printf("  Weight: %.1f \n",perso_Prin->invent.armas[cont_Arma].peso);

				}

				printf("Enter indication to change weapon: ");
				armaAtual = leValida_Troca_Arma(perso_Prin, pos_inventario);

				//	mostra_Janela(2);

				getchar();
				getchar();
				break;
			case 5: // Poção

				perso_Prin->atributos->hp_P = perso_Prin->atributos->hp_P + QNT_CURA;
				perso_Prin->invent.hp_Pocoes --;

				break;
		}

		//Dano Total do MOB
		d6_Mob = (rand() % 5) + 1;
		dano_Total_M = mobs[id_Mob].atributos.dano_Mob * d6_Mob;

		//Descontando no HP personagem

		if(acao != 3) {

			perso_Prin->atributos->hp_P = perso_Prin->atributos->hp_P - dano_Total_M;

		} else {
			dano_Total_M = dano_Total_M - defesa_Total;
			perso_Prin->atributos->hp_P = perso_Prin->atributos->hp_P - dano_Total_M;
		}

		if(flag_Leve == 1 && perso_Prin->atributos->hp_P < 0 && mobs[id_Mob].atributos.hp_Mob < 0) {
			printf("\nAtacou primeiro\n");
		} else if(flag_Leve == 0 && perso_Prin->atributos->hp_P < 0 && mobs[id_Mob].atributos.hp_Mob < 0) {
			printf("Atacou depois\n");
		}

		flag = 1;

		if(perso_Prin->atributos->hp_P > 0 && mobs[id_Mob].atributos.hp_Mob < 0) {
			vitoria = 1;
		} else if (vitoria_Pacifica >= 8) {
			vitoria = 1;
		} else if(perso_Prin->atributos->hp_P < 0 && mobs[id_Mob].atributos.hp_Mob > 0) {
			derrota = 1;
		}


	} while(vitoria != 1 && derrota != 1);//Vida mob ou personagem > 0

	limpa_Tela();

	//Mensagens de vitoria / derrota ou pacifista
	if(vitoria == 1 && vitoria_Pacifica < 8) {
		printf(" 'Uma vitoria limpa' ('Eu deixei seu humano imundo')\n");
	} else if(derrota == 1 && vitoria_Pacifica < 8) {
		printf(" 'Fraco demais , pobre humano' \n");
	} else if(vitoria_Pacifica >= 8) {
		printf(" Vitoria pacifica\n");
	}

	Sleep(3000);

	system("cls");


	if(vitoria == 1) {

		if(perso_Prin->atributos->int_P >= 7) {
			if(perso_Prin->invent.hp_Pocoes < 9)
				perso_Prin->invent.hp_Pocoes = perso_Prin->invent.hp_Pocoes + 2;
			else
				perso_Prin->invent.hp_Pocoes = perso_Prin->invent.hp_Pocoes = 0;
		} else {
			if(perso_Prin->invent.hp_Pocoes < 9)
				perso_Prin->invent.hp_Pocoes = 1;
			else
				perso_Prin->invent.hp_Pocoes = perso_Prin->invent.hp_Pocoes = 0;
		}

		if(perso_Prin->atributos->car_P >= 7) {
			perso_Prin->invent.moedas = perso_Prin->invent.moedas + 20;
		} else {
			perso_Prin->invent.moedas = 10;
		}

		recompensa_batalha(perso_Prin);

	} else if (vitoria == 0) {
		you_Died();
		finalizar = 0;
	}

	printf("\n");

	//Voltar para o tutorial ou inicio e colocar a opção de salvar dados.


	return finalizar;
}

void you_Died() {
	char inserir_Frase[] = {0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xDB,0xDB,0x20,0x20,0x20,0xDB,0xDB,0xB2,0x20,0xB1,0xDB,0xDB,0xDB,0xDB,0xDB,0x20,0x20,0x20,0xDB,0x20,0x20,0x20,0x20,0xDB,0xDB,0x20,0x20,0x20,0x20,0xB2,0xDB,0xDB,0xDB,0xDB,0xDB,0xDC,0x20,0x20,0xDB,0xDB,0xB2,0xB2,0xDB,0xDB,0xDB,0xDB,0xDB,0x20,0xB2,0xDB,0xDB,0xDB,0xDB,0xDB,0xDC,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB1,0xDB,0xDB,0x20,0x20,0xDB,0xDB,0xB1,0xB1,0xDB,0xDB,0xB1,0x20,0x20,0xDB,0xDB,0xB1,0x20,0xDB,0xDB,0x20,0x20,0xB2,0xDB,0xDB,0xB1,0x20,0x20,0x20,0xB1,0xDB,0xDB,0xDF,0x20,0xDB,0xDB,0x20,0xB2,0xDB,0xDB,0xB1,0xB2,0xDB,0x20,0x20,0x20,0xDF,0x20,0xB1,0xDB,0xDB,0xDF,0x20,0xDB,0xDB,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB1,0xDB,0xDB,0x20,0xDB,0xDB,0xB0,0xB1,0xDB,0xDB,0xB0,0x20,0x20,0xDB,0xDB,0xB1,0xB2,0xDB,0xDB,0x20,0x20,0xB1,0xDB,0xDB,0xB0,0x20,0x20,0x20,0xB0,0xDB,0xDB,0x20,0x20,0x20,0xDB,0x20,0xB1,0xDB,0xDB,0xB1,0xB1,0xDB,0xDB,0xDB,0x20,0x20,0x20,0xB0,0xDB,0xDB,0x20,0x20,0x20,0xDB,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0xDB,0xDB,0xB2,0xB0,0xB1,0xDB,0xDB,0x20,0x20,0x20,0xDB,0xDB,0xB0,0xB2,0xB2,0xDB,0x20,0x20,0xB0,0xDB,0xDB,0xB0,0x20,0x20,0x20,0xB0,0xB2,0xDB,0xDC,0x20,0x20,0x20,0xDB,0xB0,0xDB,0xDB,0xB0,0xB1,0xB2,0xDB,0x20,0x20,0xDC,0x20,0xB0,0xB2,0xDB,0xDC,0x20,0x20,0x20,0xDB,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0xDB,0xDB,0xB1,0xB2,0xB0,0xB0,0x20,0xDB,0xDB,0xDB,0xDB,0xB2,0xB1,0xB0,0xB1,0xB1,0xDB,0xDB,0xDB,0xDB,0xDB,0xB2,0x20,0x20,0x20,0x20,0xB0,0xB1,0xDB,0xDB,0xDB,0xDB,0xB2,0x20,0xB0,0xDB,0xDB,0xB0,0xB0,0xB1,0xDB,0xDB,0xDB,0xDB,0xB1,0xB0,0xB1,0xDB,0xDB,0xDB,0xDB,0xB2,0x20,0x20,0x20,0x20,0x20,0xDB,0xDB,0xB2,0x20,0x20,0x20,0x20,0x20,0xDB,0xDB,0xB2,0x20,0x20,0x20,0x20,0x20,0xDB,0xDB,0xB2,0x20,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xDB,0xDB,0xB1,0xB1,0xB1,0x20,0xB0,0x20,0xB1,0xB0,0xB1,0xB0,0xB1,0xB0,0x20,0xB0,0xB1,0xB2,0xB1,0x20,0xB1,0x20,0xB1,0x20,0x20,0x20,0x20,0x20,0xB1,0xB1,0xB2,0x20,0x20,0xB1,0x20,0xB0,0xB2,0x20,0x20,0xB0,0xB0,0x20,0xB1,0xB0,0x20,0xB0,0x20,0xB1,0xB1,0xB2,0x20,0x20,0xB1,0x20,0x20,0x20,0x20,0x20,0xB1,0xB2,0xB1,0x20,0x20,0x20,0x20,0x20,0xB1,0xB2,0xB1,0x20,0x20,0x20,0x20,0x20,0xB1,0xB2,0xB1,0x20,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xDB,0xDB,0x20,0xB0,0xB1,0xB0,0x20,0x20,0x20,0xB0,0x20,0xB1,0x20,0xB1,0xB0,0x20,0xB0,0xB0,0xB1,0xB0,0x20,0xB0,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0xB1,0x20,0x20,0xB1,0x20,0x20,0xB1,0x20,0xB0,0x20,0xB0,0x20,0xB0,0x20,0x20,0xB0,0x20,0xB0,0x20,0xB1,0x20,0x20,0xB1,0x20,0x20,0x20,0x20,0x20,0xB0,0xB1,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0xB1,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0xB1,0x20,0x20,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB1,0x20,0xB1,0x20,0xB0,0xB0,0x20,0x20,0xB0,0x20,0xB0,0x20,0xB0,0x20,0xB1,0x20,0x20,0x20,0xB0,0xB0,0xB0,0x20,0xB0,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0xB0,0x20,0x20,0xB0,0x20,0x20,0xB1,0x20,0xB0,0x20,0x20,0x20,0xB0,0x20,0x20,0x20,0x20,0xB0,0x20,0xB0,0x20,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0x20,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0xB0,0x20,0x20,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0x20,0x20};

	textcolor(RED);
	printf("\n\n\n\n\n%s",inserir_Frase);
	Sleep(3000);
	textcolor(WHITE);

}

void realiza_Espacamento(struct personagem_Principal *perso_Prin, int num_Espaco) {

	int espaco = 82, cont;

	switch(num_Espaco) {
		case 1:
			for(cont = 0; cont < espaco - strlen(perso_Prin->nome); cont++)
				printf(" ");
			break;
		case 2:
			for(cont = 0; cont < espaco - strlen(perso_Prin->classe); cont++)
				printf(" ");
			break;
		case 3:
			for(cont = 0; cont < espaco - strlen(perso_Prin->raca); cont++)
				printf(" ");
			break;
		case 4:
			for(cont = 0; cont < espaco; cont++)
				printf(" ");
			break;
	}
}

void mostra_Hps(struct personagem_Principal *perso_Prin,struct mob mobs[], int numMob) {

	printf(" Name: %s",perso_Prin->nome);
	realiza_Espacamento(perso_Prin,1);
	printf("  Name: %s\n",mobs[numMob].nome);

	printf(" Class: %s",perso_Prin->classe);
	realiza_Espacamento(perso_Prin,2);
	printf(" Class: %s\n",mobs[numMob].classe);

	printf(" HP: %4.d",perso_Prin->atributos->hp_P);
	realiza_Espacamento(perso_Prin,4);
	printf("HP: %4.d\n", mobs[numMob].atributos.hp_Mob);
}


int menu_Batalha(struct personagem_Principal *perso_Prin,struct mob mobs[]) {
	int  num_Selecao, num_Acao_1, num_Acao_2, qtde_Pocoes;

	qtde_Pocoes = perso_Prin->invent.hp_Pocoes;

	do {
		mostra_Hps(perso_Prin,mobs,0);
		mostra_Inimigo(1);
		printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191);
		printf("%c1)    ATTACK      %c",179, 179);
		printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217);
		printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191);
		printf("%c2)DEFENSE (SHIELD)%c",179, 179);
		printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217);
		printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191);
		printf("%c3)   INVENTORY    %c",179, 179);
		printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217);

		printf(" Enter number: ");
		num_Selecao = le_Valida_Num_MM(1,3);

		switch(num_Selecao) {
			case 1:
				limpa_Tela();
				mostra_Hps(perso_Prin,mobs,0);
				mostra_Inimigo(1);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191);
				printf("%c11) QUICK ATTACK  %c",179, 179);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191);
				printf("%c12) HEAVY ATTACK  %c",179, 179);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191);
				printf("%c13) BACK          %c",179, 179);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217);

				printf(" Enter number: ");
				num_Acao_1 = le_Valida_Num_MM(11,13);
				break;
			case 2:
				limpa_Tela();
				mostra_Hps(perso_Prin,mobs,0);
				mostra_Inimigo(1);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191);
				printf("%c21)MAXIMUM DEFENSE%c",179, 179);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191);
				printf("%c22) BACK          %c",179, 179);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217);

				printf(" Enter number: ");
				num_Acao_1 = le_Valida_Num_MM(21,22);
				break;
			case 3:
				limpa_Tela();
				mostra_Hps(perso_Prin,mobs,0);
				mostra_Inimigo(1);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191);
				printf("%c31) CHANGE WEAPON %c",179, 179);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191);
				printf("%c32) POTIONS  x%d   %c",179, qtde_Pocoes ,179);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191);
				printf("%c33) BACK          %c",179, 179);
				printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 192, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 217);

				printf(" Enter number: ");
				num_Acao_1 = le_Valida_Num_MM(31,33);
				break;
		}

		switch(num_Acao_1) {
			case 11:
				num_Acao_2 = 1;
				break;
			case 12:
				num_Acao_2 = 2;
				break;
			case 13:
				num_Acao_2 = 0;
				break;
			case 21:
				num_Acao_2 = 3;
				break;
			case 22:
				num_Acao_2 = 0;
				break;
			case 31:
				num_Acao_2 = 4;
				break;
			case 32:
				if(perso_Prin->invent.hp_Pocoes  == 0) {
					printf("\n No Potions ...");
					Sleep(1000);
					num_Acao_2 = 0;
				}
				num_Acao_2 = 5;
				break;
			case 33:
				num_Acao_2 = 0;
				break;
		}

		if(num_Acao_2 == 0) {
			system("cls");
		}

	} while(num_Acao_2 == 0);



	return num_Acao_2;
}

void mostra_Inimigo(int num_Inimigo) {

	char str_Inimigo[100];
	char nome_Inimigo[10] = {"inimigo"};
	char numero_Char[2] = {num_Inimigo + '0'};

	strcat(nome_Inimigo,numero_Char);
	strcat(nome_Inimigo,".txt");

	FILE *pont_Inimigo;
	pont_Inimigo = fopen(nome_Inimigo,"r");


	if(pont_Inimigo == NULL) {
		mostra_Erro(1);
		exit(1);
	} else {
		while(fgets(str_Inimigo,100,pont_Inimigo) != NULL)
			printf("%s",str_Inimigo);
	}


	fclose(pont_Inimigo);
}

void le_Valida_Tecla_Dado(char *tecla_dado) {

	do {

		fflush(stdin);
		//scanf("%c",tecla_dado);
		*tecla_dado = getch();
		fflush(stdin);
		*tecla_dado = toupper(*tecla_dado);

		if(*tecla_dado != 'D')
			mostra_Erro(6);

	} while(*tecla_dado != 'D');

}

int leValida_Troca_Arma(struct personagem_Principal *perso_Prin, int pos_inventario) {
	int arma_troca, cont, flag = 0;

	do {
		scanf("%d",&arma_troca);

		for(cont = 0; cont < pos_inventario; cont++) {
			if(arma_troca == perso_Prin->invent.armas[cont].id) {
				flag = 1;
			}
		}
		if(!flag)
			mostra_Erro(9);

	} while(!flag);
	if(arma_troca == 2)
		arma_troca =1;

	return arma_troca;
}

int ponto_Controle(struct personagem_Principal *perso_Prin, int num_Finalizacoes, int pos_inventario, int finalizarCapitulo, int checkPoint ) {
	int acao_Controle, volta_Menu;
	char frase_Controle[100];
	FILE *pont_Controle;

	do {
		system("cls");
		pont_Controle = fopen("checkpoint.txt","r");

		if(pont_Controle == NULL) {
			mostra_Erro(1);
			exit(1);
		} else {
			while(fgets(frase_Controle,100,pont_Controle) != NULL)
				printf("%s",frase_Controle);
		}

		fclose(pont_Controle);

		printf("\n\n 1) Save \n");
		//printf("\n 2) Continue \n");
		printf("\n 2) Continue \n\n %c",175);
	//	printf("\n 3) Exit to menu \n\n %c",175);
		acao_Controle = le_Valida_Num_MM(1, 3);

		switch(acao_Controle) {
			case 1: 
				realizaSave(perso_Prin,num_Finalizacoes,pos_inventario,finalizarCapitulo,checkPoint);
				break;
			case 2:
				volta_Menu = 0;
				break;
			case 3:
				volta_Menu = 1;
				break;
		}
	} while(acao_Controle == 1);

	return volta_Menu;
}

void realizaSave(struct personagem_Principal *perso_Prin, int num_Finalizacoes, int pos_inventario, int finalizarCapitulo , int checkPoint) {
	FILE *pont_Save;
	
	checkPoint++;

	pont_Save = fopen("save.txt","w");

	if(pont_Save == NULL) {
		mostra_Erro(1);
		exit(1);
	}

	fprintf(pont_Save,"%s",perso_Prin->classe);
	fprintf(pont_Save,"\n");
	fprintf(pont_Save,"%s",perso_Prin->genero);
	fprintf(pont_Save,"\n");
	fprintf(pont_Save,"%s",perso_Prin->nome);
	fprintf(pont_Save,"\n");
	fprintf(pont_Save,"%s",perso_Prin->raca);
	fprintf(pont_Save,"\n");

	fprintf(pont_Save,"%d",perso_Prin->atributos->agi_P);
	fprintf(pont_Save,"\n");
	fprintf(pont_Save,"%d",perso_Prin->atributos->car_P);
	fprintf(pont_Save,"\n");
	fprintf(pont_Save,"%d",perso_Prin->atributos->for_P);
	fprintf(pont_Save,"\n");
	fprintf(pont_Save,"%d",perso_Prin->atributos->hp_P);
	fprintf(pont_Save,"\n");
	fprintf(pont_Save,"%d",perso_Prin->atributos->int_P);
	fprintf(pont_Save,"\n");

	//fprintf(pont_Save,"%d",perso_Prin->invent.armas.);
	fprintf(pont_Save,"%d",perso_Prin->invent.espaco);
	fprintf(pont_Save,"\n");
	fprintf(pont_Save,"%d",perso_Prin->invent.hp_Pocoes);
	fprintf(pont_Save,"\n");
	fprintf(pont_Save,"%d",perso_Prin->invent.moedas);
	fprintf(pont_Save,"\n");

	fprintf(pont_Save,"%d",num_Finalizacoes);
	fprintf(pont_Save,"\n");
	fprintf(pont_Save,"%d",pos_inventario);
	fprintf(pont_Save,"\n");
	fprintf(pont_Save,"%d",finalizarCapitulo);
	fprintf(pont_Save,"\n");
	fprintf(pont_Save,"%d",checkPoint);
	fprintf(pont_Save,"\n");
}

void como_Jogar() {

	FILE *pont_rule;
	char str_rule[100];

	pont_rule = fopen("HowToPlay.txt","r");

	if(pont_rule == NULL) {
		mostra_Erro(1);
		exit(1);
	} else {
		while(fgets(str_rule,100,pont_rule) != NULL)
			printf("%s",str_rule);
	}

}

void recompensa_batalha(struct personagem_Principal *perso_Prin) {

	FILE *pont_rec_atb;
	FILE *pont_recom;
	char frase_atributo[100];
	char frase_recompensa[100];
	int add_agi = 0, add_for = 0, add_int = 0, add_car = 0; // Pode se multiplicar aqui pelo num mob;

	if(perso_Prin->atributos->int_P >= 7) {
		if(perso_Prin->invent.hp_Pocoes < 9)
			perso_Prin->invent.hp_Pocoes = perso_Prin->invent.hp_Pocoes + 2;
		else
			perso_Prin->invent.hp_Pocoes = perso_Prin->invent.hp_Pocoes = 0;
	} else {
		if(perso_Prin->invent.hp_Pocoes < 9)
			perso_Prin->invent.hp_Pocoes = 1;
		else
			perso_Prin->invent.hp_Pocoes = perso_Prin->invent.hp_Pocoes = 0;
	}

	if(perso_Prin->atributos->car_P >= 7) {
		perso_Prin->invent.moedas = perso_Prin->invent.moedas + 20;
	} else {
		perso_Prin->invent.moedas = 10;
	}

	//O vezes 7 posteriormente em outros mobs pode receber o numero do contador do mob para multiplicar para receber os atributos
	if(perso_Prin->atributos->agi_P > 7) {
		add_agi = add_agi + 1;
		perso_Prin->atributos->agi_P = perso_Prin->atributos->agi_P + add_agi;
	}

	if(perso_Prin->atributos->for_P > 7) {
		add_for = add_for + 1;
		perso_Prin->atributos->for_P = perso_Prin->atributos->for_P + add_for;
	}

	if(perso_Prin->atributos->int_P > 7) {
		add_int = add_int + 1;
		perso_Prin->atributos->int_P = perso_Prin->atributos->int_P + add_int;
	}

	if(perso_Prin->atributos->car_P > 7) {
		add_car = add_car + 1;
		perso_Prin->atributos->car_P = perso_Prin->atributos->car_P + add_car;
	}


	pont_rec_atb = fopen("recompensaAtributos.txt","r");

	if(pont_rec_atb == NULL) {
		mostra_Erro(1);
		exit(1);
	} else {
		while(fgets(frase_atributo,100,pont_rec_atb) != NULL)
			printf("%s",frase_atributo);
	}

	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");


	printf("  + %d Force \n",add_for);
	printf("  + %d Agility \n",add_agi);
	printf("  + %d Intelligence \n",add_int);
	printf("  + %d Charisma \n",add_car);

	Sleep(5000);
	fclose(pont_rec_atb);

	system("cls");

	pont_recom = fopen("recompensa.txt","r");

	if(pont_recom == NULL) {
		mostra_Erro(1);
		exit(1);
	} else {
		while(fgets(frase_recompensa,100,pont_recom) != NULL)
			printf("%s",frase_recompensa);
	}


	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");

	printf("  %4.d HP Potions. \n",perso_Prin->invent.hp_Pocoes);
	printf("  %4.d P&M.        \n",perso_Prin->invent.moedas);

	Sleep(5000);
	fclose(pont_rec_atb);

}

void continua_Save(struct personagem_Principal *perso_Prin, int *num_Finalizacoes, int *pos_inventario, int *finalizarCapitulo, int *checkPoint ) {
	FILE *pont_Save;

	pont_Save = fopen("save.txt","r");

	if(pont_Save == NULL) {
		mostra_Erro(1);
		exit(1);
	}

	fgets(perso_Prin->classe,30,pont_Save);
	fgets(perso_Prin->genero,10,pont_Save);
	fgets(perso_Prin->nome,30,pont_Save);
	fgets(perso_Prin->raca,30,pont_Save);

	fscanf(pont_Save,"%d",&perso_Prin->atributos->agi_P);
	fscanf(pont_Save,"%d",&perso_Prin->atributos->car_P);
	fscanf(pont_Save,"%d",&perso_Prin->atributos->for_P);
	fscanf(pont_Save,"%d",&perso_Prin->atributos->hp_P);
	fscanf(pont_Save,"%d",&perso_Prin->atributos->int_P);

	//fprintf(pont_Save,"%d",perso_Prin->invent.armas.);
	fscanf(pont_Save,"%d",&perso_Prin->invent.espaco);
	fscanf(pont_Save,"%d",&perso_Prin->invent.hp_Pocoes);
	fscanf(pont_Save,"%d",&perso_Prin->invent.moedas);

	fscanf(pont_Save,"%d",&(*num_Finalizacoes));
	fscanf(pont_Save,"%d",&(*pos_inventario));
	fscanf(pont_Save,"%d",&(*finalizarCapitulo));
	fscanf(pont_Save,"%d",&(*checkPoint));

}

void mostra_Seguir(char seguirGo) {
	system("cls");

	if(seguirGo == 'Y') {
		printf("  You spend your last energies to get to the unknown woman's house, even so close to death when you arrive ");
		printf(" you feel better trying to rest. . .");
		Sleep(5000);
		creditos();
	} else {
		printf("  The unknown woman leaves, and you don't stop bleeding, there is only one end to this journey.\n");
		you_Died();
		Sleep(5000);
		system("cls");
		printf("\n\n\n\n");
		printf("END THE GAME SORRY\n");
		Sleep(2000);
		exit(1);
	}

}

char mostrar_Sair() {

	FILE *pont_sair1 , *pont_yn;
	char str_sair1[100] , str_yn[100];
	char escolha;


	pont_sair1 = fopen("asciiSair1.txt","r");
	pont_yn = fopen("Y_ou_N.txt","r");

	do {

		if(pont_sair1 == NULL) {
			mostra_Erro(1);
			exit(1);
		} else {
			while(fgets(str_sair1,100,pont_sair1) != NULL)
				printf("%s",str_sair1);
		}

		printf("\n\n\n\n");

		if(pont_yn == NULL) {
			mostra_Erro(1);
			exit(1);
		} else {
			while(fgets(str_yn,100,pont_yn) != NULL)
				printf("%s",str_yn);
		}


		//Lendo e validando o numero
		do {
			//scanf("%c",&caracter);
			escolha = getch();
			fflush(stdin);
			escolha = toupper(escolha);
			if(escolha != 'Y' && escolha != 'N') {

				printf("\n\n");
				mostra_Erro(6);
			}
		} while(escolha != 'Y' && escolha != 'N');


	} while(escolha != 'Y' && escolha != 'N');

	fclose(pont_sair1);
	fclose(pont_yn);

	return escolha;

}

void creditos() {
	system("cls");

	printf(" - Um oferecimento - \n");
	Sleep(3000);
	printf(" - Vai ter continuacao com mais de um MOB prometo...\n");
	Sleep(3000);
	printf(" - 777 funcoes \n");
	Sleep(3000);
	printf(" - Exagero de validacao \n");
	Sleep(3000);
	printf(" - Muito Ascii \n");
	Sleep(3000);
	printf(" - Muito Mesmo!!!!\n");
	Sleep(3000);
	system("cls");

	printf(" - PROGRAMADORES E O RESTO TODO -\n");
	printf(" - MATHEUS DE SOUSA MATOS\n");
	printf(" - PHILIPPE DE PAULA VENANCIO\n");

	Sleep(3000);

	exit(1);

}
