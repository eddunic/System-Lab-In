/**
                           Início do Projeto: 23/09/2017
                         CONTROLE DE ACESSO AO LABORATÓRIO
              Projeto de LPED- Lógica de Programacão e Estrutura de Dados
                                     ANO: 2017
        Componentes: Bianca Ângelo, Daniela Ferreira, Eduardo Neves e Marcos Felipe.
*/

/**BIBLIOTECAS*/
#include <stdio.h> /**Funções de entrada e saída*/
#include <stdlib.h> ///Padrão
#include <windows.h> ///Hora e gotoxy
#include <ctype.h> ///Manipulação de caracteres
#include <string.h> ///Manipulação de strings
#include <conio.h>

#define QTDE 50  ///Caracteres de cada string do cadastro

/**Protótipos das funções*/
void principio(); /**Opta por administrador ou usuário comum*/
void opcoes_principio();
void senha_admin(); ///Janela que pede cadastro de senha do administrador
void login_admin();
void edite_sen_admin(); ///Altera senha do administrador
void login_user();
void menu_user(); ///Menu de usuário comum
void opcoes_menu_user();
void menu_principal(); /**MENU: Tela inicial - Tela 1.0*/
void opcoes_menu_principal();
void menu_cadastro(); /**MENU: Tela Cadastro - Tela 1.1*/
void opcoes_menu_cadastro(); /**Função p/ opção selecionada na TELA 1.0*/
void inclusao(); /**Inclusão de Conta*/
int verifica_conta(); /**Caso tenha contas iguais na inclusão*/
int verifica_usuario(); /**Caso tenha usuários iguais na inclusão*/
void delay(int); ///Desacelera o tempo para imprimir
void consulta(); /**Mostra contas existentes*/
void exclusao(); /**Exclui conta**/
void alteracao(); /**Altera dados*/
void menu_entrada_saida(); /**MENU: Tela Entrada e Saída*/
void entrada_saida();
void menu_estatisticas_acesso(); /**MENU: Tela Estatísticas - Tela 1.3*/
void registros_uso();
void exclui_entrada_saida();
void meus_dados();
///Protótipos das Funções Moldes dos MENUS
void abertura_carregamento(); /**Tela de entrada*/
void molde_tempo(); //Para data e hora
void molde1(); //Tela 0.0 (Menor)
void molde2(); //Tela 1.0
void molde3(); //Menu inclusao
void linha_cima_dialogo(int xi, int l, int q, int xf); //Molde caixa de diálogo
void linha_baixo_dialogo(int xi, int l, int q, int xf);
void laterais_dialogo(int xi, int l, int q, int xf);
void data_hora(); //Falta atualizar!!
void area_trabalho(); //Limite TELA
void computador(); //Detalhe - PC no canto direito
void preenche_linha_superior(int xi, int l, int q, int xf); //Preenche a linha superior
void preenche_linha_inferior(int xi, int l, int q, int xf); //Preenche a linha inferior
void preenche_laterais(int xi, int l, int q, int xf);
void mensagem(int exibe); //Janelinha de aviso
void suporte_pc();
void limpa_parte_tela(int xi, int li, int q, int r);
void preenche_lateral_linha_fina (int c, int l, int q);
void preenche_linha_fina_horizontal(int l, int c, int q);

void gotoxy(int x, int y) { ///Função para posicionar o cursor
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x-1,y-1});
}

void SetColor(char ForgC) { ///Altera cor de caractere
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

typedef struct{ /**Estrutura para guardar os dados do usuário*/
    char conta[QTDE], senha[QTDE], usuario[QTDE];
    char finalidade[QTDE];
    int hora_entrada, hora_saida, min_entrada, min_saida;
    int dia, mes, ano;
    }atual;

/**Variáveis Globais*/
char arquivo[] = "Contas.txt";
FILE *arq_inclusao;

char password[QTDE]; //Senha do admin
FILE *senha; //Guarda senha do admin
char pass[] = "Senha_admin.txt";

FILE *presenca;
char present[] = "Presenca_de_senha.txt";
char senhaounao; //Auxilia na verificação para voltar ao menu anterior correspondente ao tipo de usuário

//Registros de Entrada e Saída
FILE *registro_uso;
char temps[] = "Registros_de_entrada_e_saida.txt";

char nome_da_conta[QTDE];


int main(void) {
    SetConsoleTitle("System Lab In (SLIN)");
    system("COLOR F0");
    abertura_carregamento();
    principio();
    return 0;
}

void abertura_carregamento() {
    system("cls");
    area_trabalho();
    computador();
    int vindo = 55, c = 46, j = 46, x11 = 32, t = 55, l = 37, lc = 30, k = 21;
	char str[100] = "System Lab In", str2[100] = "SLIN";
	int x1 = 32, y1 = 15; /**Mensagem central*/
	int x2 = 28, y2 = 17; /**Quadradinho carrega debaixo da mensagem central*/
	int x3 = 20, y3 = 9; /** linha de cima e baixo*/
	int x4 = 20, y4 = 10; /**linha esquerda e direita*/
	int c1 = 85, l1 = 6; /**Coordenadas computadorzinho*/
	int a; /**Contador*/

	/**Cantos do quadrado maior*/
	gotoxy(20, 9); /**Canto superior esquerdo*/
	printf("%c", 201);
    gotoxy(56, 9); /**Canto superior direito*/
    printf("%c", 187);

    gotoxy(20, 22); /**Canto inferior esquerdo*/ /**32*/
	printf("%c", 200);
    gotoxy(56, 22); /**Canto inferior direito*/
    printf("%c", 188);

	gotoxy(x1, y1); /**Posiciona em:*/
	for(a = 1; a <= 72; a++) { /**80 chega até o final os símbolos, se diminuir o de cima e o de baixo não completam*/
		if(a - 1 < 20) { /** <26*/
			gotoxy(x1, y1);
			if(a - 1 != 18) {
                printf("%c", str[a - 1]);   /**Mensagem central*/
                gotoxy(x1 + 4, y1 + 1);
                printf("%c", str2[ a - 1]);
            }
            x1++;
		}
		if(a - 1 < 42) {
			gotoxy(x2, y2);
			if(a % 2 == 0) {
				printf("%c ", 254); /**Quadradinho embaixo da frase central*/
				x2++;
			}
		}

		/**Caixinha Central*/
		if(a < 15) { /**1 parte em cima*/
			gotoxy(x3 + 1, y3);
			printf("%c", 205); /**Cima*/
		}

		if(a == 1) { /**Cantos e centrinho caixinha 2*/
            gotoxy(29, y3);
            printf("%c", 185);
            gotoxy(29, y3 - 1);
            printf("%c", 201);
            gotoxy(29, y3 + 1);
            printf("%c", 200);

            gotoxy(47, y3);
            printf("%c", 204);
            gotoxy(47, y3 - 1);
            printf("%c", 187);
            gotoxy(47, y3 + 1);
            printf("%c", 188);
        }

		if(a < 17) {
            gotoxy(x2 + 2, y3 + 1); /**Caixinha central 2 - em baixo esq p/ dir*/
            printf("%c", 205);
		}

        if(a < 12) {
            gotoxy(lc++, y3 - 1); /**Caixinha central 1 - em cima - direita p/ esquerda*/
            printf("%c", 205);
        }

        if(a < 8) {
            gotoxy(j--, y3 - 1); /**Caixinha central 2 - em cima direita para esquerda*/
            printf("%c", 205);
        }

        if(a < 9) {
            gotoxy(c--, y3 + 1); /**Embaixo direita p/ esquerda*/
            printf("%c", 205);
        }

        /**Título*/
        if(a - 1 < 13) { /** <26*/
			gotoxy(x11, y3);
			if(a - 1 != 18) {
                printf("%c", str[a - 1]);
            }
            x11++;
		}

        /**Quadrado grande*/
		if(a < 8) {
			gotoxy(x3 + 1, 22); /**Em cima vindo da esquerda*/
			printf("%c", 205);
			x3++;
		}
		if(a < 9) {
			gotoxy(vindo--, y3); /**Cima direita p/ esquerda*/
			printf("%c",205);
		}

        if (a < 20) {
            gotoxy(t--, 22);
            printf("%c", 205);  /**Embaixo vindo da direita  2*/
        }

        if (a < 19) {
            gotoxy(k++, 22);
            printf("%c", 205);  /**Embaixo vindo da esquerda  2*/
        }

		if(a < 13) {
			gotoxy(x4, y4);
			printf("%c", 186); /**Esquerda*/
			gotoxy(56, y4);
			printf("%c", 186); /**Direita*/
			y4++;
		}
        /**Quadrado grande final*/
    Sleep(70);
    }
    system("cls");
}

void principio() {
    molde1();
    gotoxy(36, 9);
    printf("LOGIN");
    gotoxy(32, 13);
    printf("ADMINISTRADOR");
    gotoxy(32, 16);
    printf("USU%cRIO", 181);
    gotoxy(32, 19);
    printf("SAIR");

    opcoes_principio();
}

void opcoes_principio() {
    int x = 30, y = 13;
    int escolha = 0;
    char opcao;
    while(opcao != 13) {
        if(opcao != 27) {
            gotoxy(x, y);
            printf("%c", 175);
            opcao = getch();
            if(opcao == 72) {
                if(y > 13) {
                    gotoxy(x, y);
                    printf(" ");
                    y -= 3;
                    gotoxy(x, y);
                    printf("%c", 175);
                    if(y == 13)
                        escolha = 1;
                    else
                        if(y == 16)
                            escolha = 2;
                        else
                            escolha = 3;
                }
            }else
                if(opcao == 80) {
                    if(y < 19) {
                        gotoxy(x, y);
                        printf(" ");
                        y += 3;
                        gotoxy(x, y);
                        printf("%c", 175);
                        if(y == 19)
                            escolha = 3;
                        else
                            if(y == 16)
                                escolha = 2;
                            else
                                escolha = 1;
                    }
                }else{
                    if(y == 13)
                        escolha = 1;
                }
        }else{
            system("cls");
            exit(0);
        }
    }

    if(escolha == 1) {
        senha = fopen(pass, "rb");
        if(senha == NULL || password[0] == NULL) {
            presenca = fopen(present, "rb");
            if(presenca == NULL) {
                fclose(presenca);
                fclose(senha);
                senha_admin();
            }else{
                fclose(presenca);
                fclose(senha);
                login_admin();
            }
        }else{
            fclose(senha);
            login_admin();
        }
    }
    if(escolha == 2) {
        login_user();
    }
    if(escolha == 3) {
        system("cls");
        exit(0);
    }
}

void senha_admin() {
    volta:
    system("cls");
    char c, pass_copy[QTDE], resp;
    int i = 0;
    preenche_lateral_linha_fina(76, 4, 25);
    preenche_lateral_linha_fina(82, 4, 25);
    preenche_linha_superior(1, 1, 89, 91);
    preenche_laterais(1, 2, 31, 91);
    preenche_linha_inferior(1, 32, 89, 91);
    gotoxy(76, 6);
    printf("%c%c%c%c%c%c%c", 195, 196, 196, 196, 196, 196, 180);
    gotoxy(76, 12);
    printf("%c%c%c%c%c%c%c", 195, 196, 196, 196, 196, 196, 180);
    gotoxy(76, 22);
    printf("%c%c%c%c%c%c%c", 195, 196, 196, 196, 196, 196, 180);
    preenche_linha_fina_horizontal(4, 28, 84);
    preenche_linha_superior( 8, 4, 55, 64);
    preenche_laterais(8, 5, 1, 64);
    preenche_linha_inferior(8, 6, 55, 64);
    volta1:
    gotoxy(10, 5);
    printf("Digite uma senha para o root: ");
    do{
        c = getch(); //Pausa para receber
        if(isprint(c)) { //Analisa se o valor da variável c é imprimível
            password[i] = c;
            i++;
            printf("*");
        }else
            if(c == 8 && i) {   //8 é o caractere BackSpace na tabela ASCII
                password[i] = '\0';
                i--;
                printf("\b \b");    //Apaga o caractere backspace digitado,  && i analisa se i é diferente de 0
            }
    }while(c != 13);             //13 é o valor de ENTER na tabela ASCII
    password[i] = '\0';
    if(password[0] <= '0') {
        gotoxy(40, 5);
        SetColor(4);
        printf("Campo Obrigat%crio", 162);
        delay(25);
        limpa_parte_tela(37, 5, 27, 38);
        SetColor(0);
        goto volta1;
    }
    fflush(stdin);
    i = 0;
    volta2:
    preenche_lateral_linha_fina(16, 7, 3);
    preenche_lateral_linha_fina(56, 7, 3);
    preenche_linha_superior( 8, 9, 55, 64);
    preenche_laterais(8, 10, 1, 64);
    preenche_linha_inferior(8, 11, 55, 64);
    gotoxy(10, 10);
    printf("Confirme a senha: ");
    do{
        c = getch(); //Pausa para receber
        if(isprint(c)) { //Analisa se o valor da variável c é imprimível
            pass_copy[i] = c;
            i++;
            printf("*");
        }else
            if(c == 8 && i) {   //8 é o caractere BackSpace na tabela ASCII
                pass_copy[i] = '\0';
                i--;
                printf("\b \b");    //Apaga o caractere backspace digitado,  && i analisa se i é diferente de 0
            }
    }while(c != 13);             //13 é o valor de ENTER na tabela ASCII
    pass_copy[i] = '\0';
    if(pass_copy[0] <= '0') {
        SetColor(4);
        printf("Campo Obrigat%crio", 162);
        delay(25);
        limpa_parte_tela(27, 10, 27, 28);
        SetColor(0);
        goto volta2;
    }
    senha = fopen(pass, "w");
    if(strcmp(pass_copy, password) == 0) {
        fputs(password, senha); //Especial para 1 elemento
        fclose(senha);
        preenche_lateral_linha_fina(33, 12, 6);
        preenche_lateral_linha_fina(39, 12, 6);
        preenche_linha_superior(26, 18, 19, 46);
        preenche_laterais(26, 19, 1, 46);
        preenche_linha_inferior(26, 20, 19, 46);
        gotoxy(28, 19);
        printf("Senha confirmada!");
        senhaounao = '1';
        presenca = fopen(present, "w");
        fputc(senhaounao, presenca);
        fclose(presenca);
        mensagem(4);
        getch();
        menu_principal();
    }else{
        preenche_lateral_linha_fina(16, 12, 4);
        gotoxy(16, 16);
        printf("%c", 195);
        gotoxy(16, 17);
        printf("%c", 192);

        gotoxy(18, 16);
        printf("Senhas desiguais");
        gotoxy(18, 17);
        printf("Ainda deseja adicionar uma senha? [S/N]: ");
        scanf("%c", &resp);
        if(resp == 'S' || resp == 's') {
            fclose(senha);
            goto volta;
        }else{
            password[0] = NULL;
            fclose(senha);
            principio();
        }
    }
}

void login_admin() {
    char key[QTDE], c;
    int i = 0;
    volta:
    molde1();
    gotoxy(32, 9);
    printf("ADMINISTRADOR");
    gotoxy(22, 15);
    printf("Digite sua senha: ");
    gotoxy(24, 17);
    do{
        c = getch(); //Pausa para receber
        if(isprint(c)) { //Analisa se o valor da variável c é imprimivel
            key[i] = c;
            i++;
            printf("*");
        }else
            if(c == 8 && i) {   //8 é o caractere BackSpace na tabela ASCII
                key[i] = '\0';
                i--;
                printf("\b \b");    //Apaga o caractere backspace digitado,  && i analisa se i é diferente de 0
            }
    }while(c != 13);             //13 é o valor de ENTER na tabela ASCII
    key[i] = '\0';
    senha = fopen(pass, "r");
    rewind(senha);
    while(fscanf(senha, "%s", password) != EOF) { //Comando para fputs
        if(strcmp(password, key) == 0) {
            fclose(senha);
            senhaounao = '1'; //Usado para voltar da consulta ao menu correpondente
            menu_principal();
        }else{
            fclose(senha);
            limpa_parte_tela(22, 17, 34, 22);
            gotoxy(31, 17);
            SetColor(4);
            printf("Senha incorreta");
            SetColor(0);
            getch();
            principio();
        }
    }
}

void edite_sen_admin() {
    char chave[QTDE], c, chave_confirma[QTDE];
    int i;
    system("cls");
    area_trabalho();
    i = 0;
    preenche_linha_superior(33, 1, 25, 59);
    preenche_laterais(33, 2, 1, 59);
    preenche_linha_inferior(33, 3, 25, 59);
    gotoxy(35, 2);
    printf("EDI%c%cO DE SENHA DO ROOT", 128, 199);
    gotoxy(7, 5);
    printf("%c", 195);
    preenche_linha_fina_horizontal(8, 5, 77);
    printf("%c", 180);
    gotoxy(7, 25);
    printf("%c", 195);
    preenche_linha_fina_horizontal(8, 25, 77);
    printf("%c", 180);
    preenche_lateral_linha_fina(4, 8, 15);
    preenche_lateral_linha_fina(10, 8, 15);
    gotoxy(4, 12);
    printf("%c%c%c%c%c%c%c", 195, 196, 196, 196, 196, 196, 180);
    gotoxy(4, 18);
    printf("%c%c%c%c%c%c%c", 195, 196, 196, 196, 196, 196, 180);
    preenche_lateral_linha_fina(81, 8, 15);
    preenche_lateral_linha_fina(87, 8, 15);
    gotoxy(81, 12);
    printf("%c%c%c%c%c%c%c", 195, 196, 196, 196, 196, 196, 180);
    gotoxy(81, 18);
    printf("%c%c%c%c%c%c%c", 195, 196, 196, 196, 196, 196, 180);
    preenche_linha_superior(24, 11, 40, 65);
    preenche_laterais(24, 12, 1, 65);
    preenche_linha_inferior(24, 13, 40, 65);
    gotoxy(25, 12);
    printf("Digite a senha atual: ");
    setbuf(stdin, NULL);
    do{
        c = getch();
        if(isprint(c)) {
            chave[i] = c;
            i++;
            printf("*");
        }else
            if(c == 8 && i) {
                chave[i] = '\0';
                i--;
                printf("\b \b");
            }
    }while(c != 13);
    chave[i] = '\0';
    if(chave[0] <= '0') {
        menu_principal();
    }
    senha = fopen(pass, "r");
    rewind(senha);
    while(fscanf(senha, "%s", password) != EOF) { //Comando para fputs
        if(strcmp(password, chave) == 0) {
            fclose(senha);
            i = 0;
            volta2:
            preenche_lateral_linha_fina(28, 14, 2);
            preenche_lateral_linha_fina(32, 14, 2);
            preenche_linha_superior(24, 15, 40, 65);
            preenche_laterais(24, 16, 1, 65);
            preenche_linha_inferior(24, 17, 40, 65);

            gotoxy(25, 16);
            printf("Digite a nova senha: ");
            do{
                c = getch();
                if(isprint(c)) {
                    chave[i] = c;
                    i++;
                    printf("*");
                }else
                    if(c == 8 && i) {
                        chave[i] = '\0';
                        i--;
                        printf("\b \b");
                    }
            }while(c != 13);
            chave[i] = '\0';
            if(chave[0] <= '0') {
                gotoxy(46, 16);
                SetColor(4);
                printf("Campo Obrigat%crio", 162);
                delay(25);
                SetColor(0);
                limpa_parte_tela(46, 16, 18, 46);
                goto volta2;
            }
            volta3:
            i = 0;
            limpa_parte_tela(24, 17, 42, 14);
            preenche_laterais(24, 17, 1, 65);
            preenche_linha_inferior(24, 18, 40, 65);
            gotoxy(25, 17);
            printf("Confirme a nova senha: ");

            do{
                c = getch();
                if(isprint(c)) {
                    chave_confirma[i] = c;
                    i++;
                    printf("*");
                }else
                    if(c == 8 && i) {
                        chave_confirma[i] = '\0';
                        i--;
                        printf("\b \b");
                    }
            }while(c != 13);
            chave_confirma[i] = '\0';
            if(chave_confirma[0] <= '0') {
                SetColor(4);
                printf("Campo Obrigat%crio", 162);
                SetColor(0);
                getch();
                goto volta3;
            }
            if(strcmp(chave, chave_confirma) == 0) {
                senha = fopen(pass, "w");
                strcpy(password, chave);
                fputs(password, senha);
                fclose(senha);
                limpa_parte_tela(24, 15, 42, 24);
                limpa_parte_tela(24, 16, 42, 24);
                limpa_parte_tela(24, 17, 42, 24);
                limpa_parte_tela(24, 18, 42, 24);

                preenche_linha_superior(24, 15, 17, 42);
                preenche_laterais(24, 16, 1, 42);
                preenche_linha_inferior(24, 17, 17, 42);

                gotoxy(25, 16);
                printf("Senha Atualizada!");
                gotoxy(1, 1);
                delay(75);
                menu_principal();
            }else{
                limpa_parte_tela(24, 15, 42, 24);
                limpa_parte_tela(24, 16, 42, 24);
                limpa_parte_tela(24, 17, 42, 24);
                limpa_parte_tela(24, 18, 42, 24);
                preenche_linha_superior(24, 15, 17, 42);
                preenche_laterais(24, 16, 1, 42);
                preenche_linha_inferior(24, 17, 17, 42);
                gotoxy(25, 16);
                printf("Senhas desiguais");
                gotoxy(1, 1);
                delay(75);
                menu_principal();
            }
        }else{
            fclose(senha);
            limpa_parte_tela(47, 12, 18, 47);
            gotoxy(47, 12);
            SetColor(4);
            printf("Senha Incorreta");
            delay(25);
            SetColor(0);
            delay(80);
            menu_principal();
        }
    }
}

void login_user() {
    atual reg;
    char pass[QTDE], count[QTDE], c;
    int i = 0;
    molde1();
    gotoxy(35, 9);
    printf("USU%cRIO", 181);
    arq_inclusao = fopen(arquivo, "rb");
    if(arq_inclusao == NULL) {
        fclose(arq_inclusao);
        mensagem(3);
        getch();
        principio();
    }
    gotoxy(22, 14);
    printf("Digite sua conta: ");
    gets(count);
    while(fread(&reg, sizeof(atual), 1, arq_inclusao) == 1) {
        if(strcmp(count, reg.conta) == 0) {
            fflush(stdin);
            gotoxy(22, 17);
            printf("Digite sua senha: ");
            do{
                c = getch(); //Pausa para receber
                if(isprint(c)) { //Analisa se o valor da variável c é imprimivel
                    pass[i] = c;
                    i++;
                    printf("*");
                }else
                    if( c == 8 && i) {   //8 é o caractere BackSpace na tabela ASCII
                        pass[i] = '\0';
                        i--;
                        printf("\b \b");    //Apaga o caractere backspace digitado,  && i analisa se i é diferente de 0
                    }
            }while(c != 13);             //13 é o valor de ENTER na tabela ASCII
            pass[i] = '\0';
            if(strcmp(pass, reg.senha) == 0) {
                senhaounao = 0;
                strcpy(nome_da_conta, count);
                menu_user();
            }else{
                gotoxy(31, 19);
                SetColor(4);
                printf("Senha Inv%clida", 160);
                SetColor(0);
                getch();
                principio();
            }
        }
    }
    gotoxy(31, 16);
    SetColor(4);
    printf("Conta Inv%clida", 160);
    SetColor(0);
    getch();
    principio();
}

void menu_user() {
    molde1();
    gotoxy(35,9);
    printf("USU%cRIO", 181);
    gotoxy(29, 13);
    printf("ENTRADA/SA%cDA", 214); //consulta - meus dados
    gotoxy(29, 16);
    printf("ESTAT%cSTICAS DE ACESSO", 214);
    gotoxy(29, 19);
    printf("FINALIZAR");

    opcoes_menu_user();
}

void opcoes_menu_user() {
    int x = 26, y = 13;
    int escolha = 0;
    char opcao;
    while(opcao != 13) {
        if(opcao != 27) {
            gotoxy(x, y);
            printf("%c", 175);
            opcao = getch();
            if(opcao == 72) {
                if(y > 13) {
                    gotoxy(x, y);
                    printf(" ");
                    y -= 3;
                    gotoxy(x, y);
                    printf("%c", 175);
                    if(y == 13)
                        escolha = 1;
                    else
                        if(y == 16)
                            escolha = 2;
                        else
                            if(y == 19)
                                escolha = 3;
                }
            }else
                if(opcao == 80) {
                    if(y < 19) {
                        gotoxy(x, y);
                        printf(" ");
                        y += 3;
                        gotoxy(x, y);
                        printf("%c", 175);
                        if(y == 19)
                            escolha = 3;
                        else
                            if(y == 16)
                                escolha = 2;
                            else
                                if(y == 13)
                                    escolha = 1;
                    }
                }else{
                    if(y == 13)
                        escolha = 1;
                }
        }else{
            system("cls");
            principio();
        }
    }

    if(escolha == 1) {
        meus_dados();
    }
    if(escolha == 2) {
        menu_estatisticas_acesso();
    }
    if (escolha == 3){
        system("cls");
        exit (0);
    }
}

void menu_principal() { ///Interface
    molde1();
    gotoxy(35,9);
    printf("CONTAS");
    gotoxy(28, 12);
    printf("DADOS");
    gotoxy(28, 14);
    printf("ENTRADA/SA%cDA", 214);
    gotoxy(28, 16);
    printf("ESTAT%cSTICAS DE ACESSO", 214);
    gotoxy(28, 18);
    printf("EDI%c%cO DE SENHA", 128, 199);
    gotoxy(28, 20);
    printf("FINALIZAR");

    opcoes_menu_principal();
}

void opcoes_menu_principal() { ///Especial para seta
    int x = 26, y = 12;
    int escolha = 0;
    char opcao;
    while(opcao != 13) {
        if(opcao != 27) {
            gotoxy(x, y);
            printf("%c", 175);
            opcao = getch();
            if(opcao == 72) {
                if(y > 12) {
                    gotoxy(x, y);
                    printf(" ");
                    y -= 2;
                    gotoxy(x, y);
                    printf("%c", 175);
                    if(y == 12)
                        escolha = 1;
                    else
                        if(y == 14)
                            escolha = 2;
                        else
                            if(y == 16)
                                escolha = 3;
                            else
                                if(y == 18)
                                    escolha = 4;
                                else
                                    if(y == 20)
                                        escolha = 5;
                }
            }else
                if(opcao == 80) {
                    if(y < 20) {
                        gotoxy(x, y);
                        printf(" ");
                        y += 2;
                        gotoxy(x, y);
                        printf("%c", 175);
                        if(y == 20)
                            escolha = 5;
                        else
                            if(y == 18)
                                escolha = 4;
                            else
                                if(y == 16)
                                    escolha = 3;
                                else
                                    if(y == 14)
                                        escolha = 2;
                                    else
                                        if(y == 12)
                                            escolha = 1;
                    }
                }else{
                    if(y == 12)
                        escolha = 1;
                }
        }else{
            system("cls");
            principio();
        }
    }

    if(escolha == 1) {
        menu_cadastro();
    }
    if(escolha == 2) {
        menu_entrada_saida();
    }
    if(escolha == 3) {
        menu_estatisticas_acesso();
    }
    if(escolha == 4) {
        edite_sen_admin();
    }
    if(escolha == 5) {
        system("cls");
        exit(0);
    }
}

void menu_cadastro() {
    system("cls");
    molde3();
    gotoxy(30, 7);
    printf("CADASTRO DE CONTA");
    gotoxy(34, 10);
    printf("INCLUS%cO", 199);
    gotoxy(34, 12);
    printf("ALTERA%c%cO", 128,199);
    gotoxy(34, 14);
    printf("CONSULTA");
    gotoxy(34, 16);
    printf("EXCLUS%cO",199);
    gotoxy(34, 18);
    printf("RETORNAR");

    opcoes_menu_cadastro();
}

void opcoes_menu_cadastro() {
    int x = 32, y = 10;
    int escolha = 0;
    char opcao;
    while(opcao != 13) {
        if(opcao != 27){
            gotoxy(x, y);
            printf("%c", 175);
            opcao = getch();
            if(opcao == 72) {
                if(y > 10) {
                    gotoxy(x, y);
                    printf(" ");
                    y -= 2;
                    gotoxy(x, y);
                    printf("%c", 175);
                    if(y == 10)
                        escolha = 1;
                    else
                        if(y == 12)
                            escolha = 2;
                        else
                            if(y == 14)
                            escolha = 3;
                            else
                                if(y == 16)
                                    escolha = 4;
                                else
                                    escolha = 0;
                }
            }else
                if(opcao == 80) {
                    if(y < 18) {
                        gotoxy(x, y);
                        printf(" ");
                        y += 2;
                        gotoxy(x, y);
                        printf("%c", 175);
                        if(y == 16)
                            escolha = 4;
                        else
                            if(y == 14)
                                escolha = 3;
                            else
                                if(y == 12)
                                    escolha = 2;
                                else
                                    if(y == 10)
                                        escolha = 1;
                                    else
                                        escolha = 0;
                    }
                }else{
                    if(y == 10)
                        escolha = 1;
                }
        }else{
            menu_principal();
        }
    }

    switch(escolha) {
        case 1:
                inclusao(0);
                break;
        case 2:
                alteracao(0);
                break;
        case 3:
                consulta(0);
                break;
        case 4:
                exclusao(0);
                break;
        default:
                menu_principal(0);
        }
}

void inclusao() {
    atual REG;
    int verific; //Verificador de conta e usuário
    char c; //Formulador de asterisco
    int i = 0; //Contador para geração de asteriscos
    int posicao = 0;
    char resp;
    char count[QTDE], user[QTDE]; //Para armazenar última conta; Último usuário
    do{
        volta_conta:
        fflush(arq_inclusao);
        system("cls");
        molde2();
        gotoxy(32,12);
        printf("INCLUS%cO DE CONTA", 199);
        gotoxy(22, 14);
        printf("Deseja incluir uma nova conta ? [S/N]  ");
        scanf("%s", &resp);
        if(resp == 'n' || resp == 'N') {
            fflush(stdin);
            menu_cadastro();
        }
        fflush(arq_inclusao);
        limpa_parte_tela(22, 14, 40, 22);
        fflush(stdin);
        gotoxy(22, 14);
        printf("Conta: ");
        arq_inclusao = fopen(arquivo, "ab"); //Abre o arquivo
        fflush(stdin);
        gets(REG.conta);
        if(REG.conta[0] <= '0') {
            gotoxy(29, 14);
            SetColor(4);
            printf("Campo Obrigat%crio", 162);
            SetColor(0);
            getch();
            goto volta_conta;
        }
        fflush(stdin);
        strcpy(count, REG.conta);
        verific = verifica_conta(count);
        if(verific == 0) {
            mensagem(1);
            getch(); //Para
            goto volta_conta;
        }
        gotoxy(22,16);
        printf("Senha: ");
        do{
            c = getch(); //Pausa para receber
            if(isprint(c)) { //Analisa se o valor da variável c é imprimivel
                REG.senha[i] = c;
                i++;
                printf("*");
            }else
                if(c == 8 && i) {   //8 é o caractere BackSpace na tabela ASCII
                    REG.senha[i] = '\0';
                    i--;
                    printf("\b \b");    //Apaga o caractere backspace digitado,  && i analisa se i é diferente de 0
                }
        }while(c != 13);             //13 é o valor de ENTER na tabela ASCII
        REG.senha[i] = '\0';
        if(REG.senha[0] <= '0') {
            gotoxy(29, 16);
            SetColor(4);
            printf("Campo Obrigat%crio", 162);
            SetColor(0);
            getch();
            goto volta_conta;
        }
        volta_usuario:
        gotoxy(22, 18);
        printf("Usu%crio(a): ", 160);
        fflush(stdin);
        gets(REG.usuario);
        if(REG.usuario[0] <= '0') {
            gotoxy(34, 18);
            SetColor(4);
            printf("Campo Obrigat%crio", 162);
            SetColor(0);
            getch();
            limpa_parte_tela(34, 18, 27, 34);
            goto volta_usuario;
        }
        fflush(stdin);
        strcpy(user, REG.usuario);
        verific = verifica_usuario(user);
        if(verific == 0) {
            limpa_parte_tela(34, 18, 10, 34);
            mensagem(2);
            SetColor(0);
            goto volta_usuario;
        }
        gotoxy(26, 20);
        printf("CONFIRMA INCLUS%cO ? [S/N] ", 199);
        scanf("%c", &c);
        if ((c == 'S')||(c =='s')) {
            fflush(stdin);
            fwrite(&REG, sizeof(atual), 1, arq_inclusao); //Escreve no arquivo
            fclose(arq_inclusao); //Fecha o arquivo
            fflush(stdin);
            mensagem(13);
            mensagem(4);
            getch(); //Pausa
            system("cls");
        }else{
            REG.conta[posicao] = ""; //Zera posição
            REG.senha[posicao] = "";
            REG.usuario[posicao] = "";
            fclose(arq_inclusao); //Fecha o arquivo
            fflush(stdin);
            system("cls");
            menu_cadastro();
        }
        posicao++;
    }while(c == 'N'|| c == 'n');
    menu_cadastro();
}

int verifica_conta(char count[]) {
    atual REG;
    FILE *arq_conta;
    arq_conta = fopen(arquivo, "rb");
    if(arq_conta == NULL) {
        fclose(arq_conta);
        fflush(stdin);
        return 1;
    }
    while(fread(&REG, sizeof(atual), 1, arq_conta) == 1) {
        if(!strcmp(strlwr(count), strlwr(REG.conta))) {
            fclose(arq_conta);
            fflush(stdin);
            return 0;
        }
    }
    rewind(arq_conta);
    fclose(arq_conta);
    fflush(stdin);

    return 1;
}

int verifica_usuario(char user[]) {
    atual REG;
    FILE *arq_usuario;
    arq_usuario = fopen(arquivo, "rb");
    if(arq_usuario == NULL) {
        fclose(arq_usuario);
        fflush(stdin);
        return 1;
    }
    while(fread(&REG, sizeof(atual), 1, arq_usuario) == 1) {
        if(strcmp(strlwr(user), strlwr(REG.usuario)) == 0) {
            fclose(arq_usuario);
            fflush(stdin);
            return 0;
        }
    }
    rewind(arq_usuario);
    fclose(arq_usuario);
    fflush(stdin);

    return 1;
}

void delay(int x) {
    int i;
    for(i = 0; i < (10050000 * x); i++);
}

void consulta() {
    system("cls");
    atual REGISTER;
    int x = 0, i, i2 = 0;
    char pass[QTDE], c;
    computador();
    //caixa título contas
    gotoxy(28, 5); //cima
    preenche_linha_superior(29, 5, 16, 46);
    gotoxy(28, 7); // baixo
    preenche_linha_inferior(29, 7, 16, 46);
    preenche_laterais(29, 6, 1, 29);
    gotoxy(46, 6); //direita
    printf("%c", 204);
    gotoxy(35, 6);
    printf("CONTAS");
    delay(2);
    for(x = 47; x < 59; x++) {
        gotoxy( x, 6);
        printf("%c", 196);
    }
    gotoxy(59, 6);
    printf("%c", 194);
    gotoxy(60, 6);
    printf("%c", 191);
    FILE *arq_consulta = fopen(arquivo, "rb");
    fflush(arq_consulta);
    if(arq_consulta == NULL) {
        setbuf(stdin, NULL);
        fclose(arq_consulta);
        laterais_dialogo(59, 7, 7, 60);
        gotoxy(59,14);
        printf("%c",192);
        gotoxy(60, 14);
        printf("%c",217);
        mensagem(3);
        mensagem(4);
        getch();
        menu_cadastro();
    }else{
        x = 8;
        while(fread(&REGISTER, sizeof(atual), 1, arq_consulta) == 1) {
            //EXIBE DADOS
            setbuf(stdin, NULL);
            preenche_linha_superior(18, x, 40, 58);
            gotoxy(20, x+1);
            printf("Conta: %s", REGISTER.conta);
            gotoxy(20, x+2);
            printf("Usu%crio: %s", 160, REGISTER.usuario);
            preenche_linha_inferior (18, x+3, 40, 58);
            preenche_laterais(18, x+1, 2, 58);
            laterais_dialogo(59, 7, x - 3, 60);
            x = x + 4;
            delay(1);
        }
    }
    fclose(arq_consulta);
    mensagem(4);
    setbuf(stdin, NULL);
    getch();
    if(senhaounao == '1') {
        menu_cadastro();
    }else{
        menu_user();
    }
}

void exclusao() {
    atual Cpy; //Muda nome da estrutura
    char resp; //Resposta
    char nome[QTDE], sen[QTDE];
    int c, i = 0, exibe = 0;
    FILE *copia; //Arquivo
    FILE *copy_registro;
    system("cls");
    computador();
    arq_inclusao = fopen(arquivo, "rb"); //Abre arquivo original
    if(arq_inclusao == NULL){
        fclose(arq_inclusao);
        mensagem(3);
        mensagem(4);
        getch();
        menu_cadastro();
    } else{
    preenche_linha_superior(16, 7, 43, 59);
    gotoxy(21, 8);
    printf("Informe a conta que deseja excluir"); //Solicita a conta a ser excluída
    preenche_linha_inferior (16, 9, 43, 59);
    preenche_laterais(16, 8, 1, 59);
    gotoxy(38, 10);
    printf("%c", 179);
    gotoxy(38, 11);
    printf("%c", 179);
    gotoxy(38, 12);
    printf("%c", 179);
    preenche_linha_superior (16, 13, 43, 59); //local solicita nome
    preenche_linha_inferior (16, 15, 43, 59);
    preenche_laterais(16, 14, 1, 59);
    gotoxy(21, 14);
    printf("Nome: ");
    setbuf(stdin, NULL);
    gets(nome); //Conta a ser excluída
    while(fread(&Cpy, sizeof(atual), 1, arq_inclusao) == 1) { //Percorre o arquivo
        if(strcmp(nome, Cpy.conta) == 0) { //Compara conta fornecida com a conta que está no arquivo
            delay(2);
            gotoxy(38, 16);
            printf("%c", 179);
            gotoxy(38, 17);
            printf("%c", 179);
            gotoxy(38, 18);
            printf("%c", 179);
            gotoxy(38, 19);
            printf("%c%c%c ", 195, 196, 196);
            delay(1);
            gotoxy(42, 19);
            printf("Conta: %s", Cpy.conta);//Exibe dados dessa conta
            gotoxy(38, 20);
            printf("%c", 179);
            gotoxy(38, 21);
            printf("%c%c%c ", 192, 196, 196);
            delay(1);
            gotoxy(42, 21);
            printf("Usu%crio(a): %s", 160, Cpy.usuario);
            setbuf(stdin, NULL);
            delay(1);
            preenche_linha_superior(13, 23, 51, 64);
            SetColor(4);
            gotoxy(14, 24);
            printf("Tem certeza que deseja apagar esta conta? [S/N]: ");
            preenche_linha_inferior (13, 25, 51, 64);
            preenche_laterais(13, 24, 1, 64);
            gotoxy(63, 24);
            setbuf(stdin, NULL);
            scanf("%c", &resp);
            SetColor(0);
            if(resp == 'S' || resp == 's') { //Se sim:
                volta:
                system("cls");
                data_hora();
                molde3();
                computador();
                gotoxy(29, 10);
                printf ("DADOS PARA EXCLUS%cO", 199);
                linha_cima_dialogo(19, 12, 38, 57);
                linha_baixo_dialogo(19, 15, 38, 57);
                laterais_dialogo(19, 13, 2, 57);
                gotoxy(21, 13);
                printf ("Conta: %s", Cpy.conta);
                gotoxy(21, 14);
                printf("Usu%crio(a): %s", 160, Cpy.usuario); //Solicita a senha
                gotoxy(25, 17);
                printf("Senha: ");
                do{
                    c = getch();
                    if(isprint(c)) {    //Analisa se o valor da variável c é imprimivel
                        sen[i] = c;
                        i++;
                        printf("*");
                }else
                    if(c == 8 && i) {
                        sen[i] = '\0';
                        i--;
                        printf("\b \b");    //Apaga o caractere backspace digitado
                    }
                }while(c != 13);
                sen[i] = '\0';
                setbuf(stdin, NULL);
                if(strcmp(sen, Cpy.senha) == 0) { //Faz comparação de senha
                    copia = fopen("copia_arq.txt", "ab"); //Abre arquivo copia
                    rewind(arq_inclusao); //Volta pro início do arquivo original
                    while(fread(&Cpy, sizeof(atual), 1, arq_inclusao) == 1) { //Percorre o arquivo
                        if(strcmp(nome, Cpy.conta) != 0) { //Onde tiver essa conta
                            fwrite(&Cpy, sizeof(atual), 1, copia); //Escreve no arquivo tudo que for diferente dessa conta
                        }
                    }
                    fclose(arq_inclusao); //Fecha arquivo original
                    fclose(copia); //Fecha arquivo copia
                    unlink(arquivo); //Ao invés de remove
                    rename("copia_arq.txt", arquivo); //Renomeia
                    registro_uso = fopen(temps, "rb");
                    copy_registro = fopen("copia_reg.txt", "ab");
                    rewind(registro_uso);
                    while(fread(&Cpy, sizeof(atual), 1, registro_uso) == 1) {
                        if(strcmp(nome, Cpy.conta) != 0) {
                            fwrite(&Cpy, sizeof(atual), 1, copy_registro);
                        }
                    }
                    fclose(registro_uso);
                    fclose(copy_registro);
                    unlink(temps);
                    rename("copia_reg.txt", "Registros_de_entrada_e_saida.txt");
                    preenche_linha_superior (20, 21, 23, 43);
                    gotoxy(22, 22);
                    printf("Exclus%co conclu%cda!", 198, 161);
                    preenche_linha_inferior(20, 23, 23, 43);
                    preenche_laterais(20, 22, 1, 43);
                    getch();
                    menu_cadastro();
                    }else{ //Se não digitar senha correta
                        mensagem(5);
                        gotoxy(31, 18);
                        printf("Senha incorreta");
                        gotoxy(15, 22);
                        printf("Ainda deseja excluir? [S/N]: ");
                        scanf("%c", &resp);
                        if(resp == 's' || resp == 'S') {
                            system("cls");
                            goto volta; //Volta e pede a senha de novo
                        }else
                        menu_cadastro();
                        getch();
                        setbuf(stdin, NULL);
                    }
            }else
            menu_cadastro();
        }
    }
    }
    if(exibe == 0){
        fflush(stdin);
        mensagem(9);
        delay(1);
        mensagem(6);
        delay(1);
        getch();
        menu_cadastro();
    }
    fclose(arq_inclusao); //Fecha arquivo original
    getch();
} //Fim da função exclusão

void alteracao() {
    atual cpy;
    char nome[QTDE], sen[QTDE]; //Conta e senha
    char resp;
    int op, c, i = 0;
    FILE *copy;
    arq_inclusao = fopen(arquivo, "rb");
    existe:
    system("cls");
    computador();
    if(arq_inclusao == NULL) {
        fclose(arq_inclusao);
        mensagem(3);
        mensagem(4);
        getch();
        menu_cadastro();
    }else{
        preenche_linha_superior (8, 10,45, 53);
        gotoxy(10, 11);
        printf("Informe o nome da conta que deseja alterar");
        preenche_linha_inferior (8, 12, 45, 53);
        preenche_laterais(8, 11, 1, 53);
        gotoxy(10, 13),
        printf("%c  %c", 179, 179);
        gotoxy(10, 14);
        printf("%c  %c", 179, 179);
        preenche_linha_superior (8, 15, 34, 42);
        preenche_linha_inferior(8, 17, 34, 42);
        preenche_laterais(8, 16, 1, 42);
        gotoxy(10, 16);
        printf("Nome:  ");
        setbuf(stdin, NULL);
        gets(nome);
        if(nome[0] <= '0') {
            menu_principal();
        }
        while(fread(&cpy, sizeof(atual), 1, arq_inclusao) == 1) {
            if(strcmp(nome, cpy.conta) == 0 ) {
                gotoxy(10, 18);
                printf("%c  %c", 179, 179);
                gotoxy(10, 19);
                printf("%c  %c", 179, 179);
                gotoxy(10, 20);
                printf("%c", 179);
                gotoxy(10, 21);
                printf("%c", 179);
                gotoxy(10, 22);
                printf("%c", 179);
                gotoxy(10, 23);
                printf("%c", 179);
                gotoxy(10, 24);
                printf("%c  %c", 179, 179);
                preenche_linha_superior(12, 20, 26, 38);
                gotoxy(14, 21);
                printf("Conta: %s", cpy.conta);
                gotoxy(14, 22);
                printf("Usu%crio: %s", 160, cpy.usuario);
                preenche_linha_inferior(12, 23, 26, 38);
                preenche_laterais(12, 21, 2, 38);
                gotoxy(39, 25);
                printf("%c", 186);
                gotoxy(39, 26);
                printf("%c", 186);
                preenche_linha_superior (8, 25, 54, 62);
                preenche_linha_inferior (8, 27, 54, 62);
                preenche_laterais(8, 26, 1, 62);
                SetColor(4);
                gotoxy(10,26);
                printf("Tem certeza que deseja alterar esta conta? [S/N]:  ");
                setbuf(stdin, NULL);
                scanf("%c", &resp);
                SetColor(0);
                if(resp == 'S' || resp == 's') {
                    volta:
                    system("cls");
                    area_trabalho();
                    computador();
                    gotoxy(15, 9);
                    printf("DIGITE A SENHA PARA ALTERA%c%cO:  ", 128, 199);
                    do{
                        c = getch();
                        if(isprint(c)) {    //Analisa se o valor da variável c é imprimivel
                            sen[i] = c;
                            i++;
                            printf("*");
                    }else
                        if(c == 8 && i) {
                            sen[i] = '\0';
                            i--;
                            printf("\b \b");    //Apaga o caractere backspace digitado
                        }
                    }while(c != 13);
                    sen[i] = '\0';
                    setbuf(stdin, NULL);
                    if(strcmp(sen, cpy.senha) == 0) {
                        copy = fopen("copia.txt", "ab");
                        rewind(arq_inclusao);
                        while(fread(&cpy, sizeof(atual), 1, arq_inclusao) == 1) {
                            if(strcmp(nome, cpy.conta) == 0 ) {
                                system("cls");
                                area_trabalho();
                                computador();
                                gotoxy(4, 5);
                                printf("1 - Conta");
                                gotoxy(4, 6);
                                printf("2 - Senha");
                                gotoxy(4, 7);
                                printf("3 - Usu%crio", 160);
                                gotoxy(19, 5);
                                printf("%c", 179);
                                gotoxy(19, 6);
                                printf("%c", 179);
                                gotoxy(19, 7);
                                printf("%c", 179);
                                gotoxy(21, 6);
                                printf("Escolha o que deseja alterar:");
                                gotoxy(52, 6);
                                do{
                                    fflush(stdin);
                                    scanf("%d", &op);
                                }while(op < 1 && op > 3);
                                switch(op) {
                                    case 1:
                                        preenche_linha_superior (21, 14, 40, 61);
                                        gotoxy(22, 15);
                                        printf("Novo nome da conta: ");
                                        preenche_linha_inferior (21, 16, 40, 61);
                                        preenche_laterais(21, 15, 1, 61);
                                        gotoxy(41, 15);
                                        fflush(stdin);
                                        gets(cpy.conta);
                                        break;
                                    case 2:
                                        preenche_linha_superior (21, 14, 40, 61);
                                        gotoxy(22, 15);
                                        printf("Nova senha da conta: ");
                                        preenche_linha_inferior(21, 16, 40, 61);
                                        preenche_laterais(21, 15, 1, 61);
                                        gotoxy(42, 15);
                                        fflush(stdin);
                                        gets(cpy.senha);
                                        break;
                                    case 3:
                                        preenche_linha_superior(21, 14, 40, 61);
                                        gotoxy(22, 15);
                                        printf("Novo usu%crio da conta: ", 160);
                                        preenche_linha_inferior (21, 16, 40, 61);
                                        preenche_laterais(21, 15, 1, 61);
                                        gotoxy(45, 15);
                                        fflush(stdin);
                                        gets(cpy.usuario);
                                        break;
                                }
                            }
                            fwrite(&cpy, sizeof(atual), 1, copy);
                        }
                    }else{
                        area_trabalho();
                        computador();
                        SetColor(4);
                        gotoxy(15, 11);
                        printf("Senha incorreta");
                        gotoxy(15, 12);
                        printf("Ainda deseja fazer a altera%c%co? [S/N]: ", 135, 198);
                        setbuf(stdin,NULL);
                        scanf("%c", &resp);
                        SetColor(0);
                        if(resp == 's' || resp == 'S') {
                            system("cls");
                            goto volta;
                        }else
                            menu_cadastro();
                    }
                }else
                    menu_cadastro();
            }
        }
    }
    fclose(arq_inclusao);
    fclose(copy);
    unlink(arquivo);
    rename("copia.txt", "contas.txt");
    system("cls");
    mensagem(10);
    getch();
    menu_cadastro();
}

void menu_estatisticas_acesso() {
    atual uso;
    int hours;
    int v[24];
    int y = 11;
    int i;
    int quantos = 0;
    int x = 12, x2=12;
    int a = 0;
    int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0, a7 = 0, a8 = 0, a9 = 0, a10 =0;
    int a11 = 0, a12 = 0, a13 = 0, a14 = 0, a15 = 0, a16 = 0, a17 = 0, a18 = 0, a19 = 0, a20 = 0;
    int a21 = 0, a22 = 0, a23 = 0, a0 = 0;
    system("cls");
    computador();
    char copia_conta[QTDE];
    preenche_linha_superior(27, 5, 20, 48);
    preenche_linha_inferior(27, 7, 20, 48);
    preenche_laterais(27, 6, 1, 48);
    gotoxy(29, 6);
    printf("MAPA DE UTILIZA%c%cO", 128, 199);
    gotoxy(18, 9);
    printf("HOR%cRIO", 181);
    preenche_linha_superior(16, 8, 10, 26);
    preenche_linha_inferior(16, 10, 10, 26);
    preenche_laterais(16, 9, 1, 48);
    preenche_linha_superior(27, 8, 20, 48);
    preenche_linha_inferior(27, 10, 20, 48);
    gotoxy(29, 9);
    printf("QUANTIDADE DE USO");
    preenche_linha_superior(62, 16, 14, 76);
    gotoxy(65, 17);
    printf("USO TOTAL");
    preenche_linha_inferior(62, 18, 14, 76);
    preenche_laterais(62, 17, 1, 76);
    preenche_linha_superior(55,17, 6, 61);
    gotoxy(61, 17);
    printf("%c", 185);
    preenche_linha_inferior(55, 23, 27, 83);
    preenche_laterais(55, 18, 5, 83);
    preenche_linha_superior(77, 17, 5, 83);
    gotoxy(77, 17);
    printf("%c", 204);
    linha_cima_dialogo(62, 19, 14, 76);
    laterais_dialogo(62, 20, 2, 76);
    linha_baixo_dialogo(62, 22, 14, 76);
    registro_uso = fopen(temps, "rb");
    if(registro_uso == NULL){
        fclose(registro_uso);
        mensagem(3);
        mensagem(4);
        getch();
        principio();
    }
    while(fread(&uso, sizeof(uso), 1, registro_uso) == 1) {
        setbuf(stdin, NULL);
            if (uso.hora_entrada == 0 ||  uso.hora_saida == 0){
                a0 = a0 +1;
                a++;
            }
            if (uso.hora_entrada == 1 ||  uso.hora_saida == 1){
                a1 = a1+ 1;
                a++;
            }
            if (uso.hora_entrada ==2 ||  uso.hora_saida == 2){
                a2 = a2+ 1;
                a++;
            }
            if (uso.hora_entrada ==3 ||  uso.hora_saida == 3){
                a3 = a3+ 1;
                a++;
            }
            if (uso.hora_entrada ==4||  uso.hora_saida == 4){
                a4 = a4+ 1;
                a++;
            }
            if (uso.hora_entrada == 5||  uso.hora_saida == 5){
                a5 = a5+ 1;
                a++;
            }
            if (uso.hora_entrada == 6||  uso.hora_saida == 6){
                a6 = a6+ 1;
                a++;
            }
            if (uso.hora_entrada == 7||  uso.hora_saida == 7){
                a7 = a7+ 1;
                a++;
            }
            if (uso.hora_entrada == 8||  uso.hora_saida == 8){
                a8 = a8+ 1;
                a++;
            }
            if (uso.hora_entrada == 9 ||  uso.hora_saida == 9){
                a9 = a9+ 1;
                a++;
            }
            if (uso.hora_entrada == 10||  uso.hora_saida == 10){
                a10 = a10 + 1;
                a++;
            }
            if (uso.hora_entrada == 11||  uso.hora_saida == 11){
                a11 = a11+ 1;
                a++;
            }
            if (uso.hora_entrada == 12 ||  uso.hora_saida == 12){
                a12 = a12+ 1;
                a++;
            }
            if (uso.hora_entrada == 13 ||  uso.hora_saida == 13){
                a13 = a13+ 1;
                a++;
            }
            if (uso.hora_entrada == 14||  uso.hora_saida == 14){
                a14 = a14+ 1;
                a++;
            }
            if (uso.hora_entrada == 15 ||  uso.hora_saida == 15){
                a15 = a15+ 1;
                a++;
            }
            if (uso.hora_entrada == 16 ||  uso.hora_saida == 16){
                a16 = a16+ 1;
                a++;
            }
            if (uso.hora_entrada == 17 ||  uso.hora_saida == 17){
                a17 = a17+ 1;
                a++;
            }
            if (uso.hora_entrada == 18 ||  uso.hora_saida == 18){
                a18 = a18+ 1;
                a++;
            }
            if (uso.hora_entrada == 19 ||  uso.hora_saida == 19){
                a19 = a19+ 1;
                a++;
            }
            if (uso.hora_entrada == 20||  uso.hora_saida == 20){
                a20 = a20+ 1;
                a++;
            }
            if (uso.hora_entrada == 21 ||  uso.hora_saida == 21){
                a21 = a21+ 1;
                a++;
            }
            if (uso.hora_entrada == 22 ||  uso.hora_saida == 22){
                a22 = a22+ 1;
                a++;
            }
            if (uso.hora_entrada == 23 ||  uso.hora_saida == 23){
                a23 = a23+ 1;
                a++;
            }
    }
    if (a0 > 0){
        quantos++;
        v [0] = 00;
        }else v [0] = 100;
    if (a1 > 0){
        quantos++;
        v[1] = 01;
        }else v [1] = 100;
    if (a2 > 0){
        quantos++;
        v [2] = 02;
        }else v [2] = 100;
    if (a3 > 0){
        quantos++;
        v [3] = 03;
        }else v [3] = 100;
    if (a4 > 0){
        quantos++;
        v [4] = 04;
        }else v [4] = 100;
    if (a5 > 0){
        quantos++;
        v [5] = 05;
        }else v [5] = 100;
    if (a6 > 0){
        quantos++;
        v [6] = 06;
        }else v [6] = 100;
    if (a7 > 0){
        quantos++;
        v [7] = 07;
        }else v [7] = 100;
    if (a8 > 0){
        quantos++;
        v [8] = 8;
        }else v [8] = 100;
    if (a9 > 0){
        quantos++;
        v [9] = 9;
        }else v [9] = 100;
    if (a10 > 0){
        quantos++;
        v [10] = 10;
        }else v [10] = 100;
    if (a11 > 0){
        quantos++;
        v [11] = 11;
        }else v [11] = 100;
    if (a12 > 0){
        quantos++;
        v [12] = 12;
        }else v [12] = 100;
    if (a13 > 0){
        quantos++;
        v [13] = 13;
        }else v [13] = 100;
    if (a14 > 0){
        quantos++;
        v [14] = 14;
        }else v [14] = 100;
    if (a15 > 0){
        quantos++;
        v [15] = 15;
        }else v [15] = 100;
    if (a16 > 0){
        quantos++;
        v [16] = 16;
        }else v [16] = 100;
    if (a17 > 0){
        quantos++;
        v [17] = 17;
        }else v [17] = 100;
    if (a18 > 0){
        quantos++;
        v [18] = 18;
        }else v [18] = 100;
    if (a19 > 0){
        quantos++;
        v [19] = 19;
        }else v [19] = 100;
    if (a20 > 0){
        quantos++;
        v [20] = 20;
        }else v [20] = 100;
    if (a21 > 0){
        quantos++;
        v [21] = 21;
        }else v [21] = 100;
    if (a22 > 0){
        quantos++;
        v [22] = 22;
        }else v [22] = 100;
    if (a23 > 0){
        quantos++;
        v [23] = 23;
        }else v [23] = 100;
    if (quantos > 0){
        for (i=0; i < 24; i++){ //p/ hora
                if(v[i] < 100){
                    if(v[i] >= 10){
                        gotoxy(19, x);
                        printf("%d:00", v[i]);
                    } else {
                        gotoxy(19, x);
                        printf("0%d:00", v[i]);
                    }
                    x+=3;
                }
        }
        x2=12;
        for(i = 0; i < 1; i++){
            if(a0 > 0) {
                gotoxy(36, x2);
                printf("%d", a0);
                x2+=3;
            }
            if (a1 > 0){
                gotoxy(36, x2);
                printf("%d", a1);
                x2+=3;
            }
            if (a2 > 0){
                gotoxy(36, x2);
                printf("%d", a2);
                x2+=3;
            }
            if (a3 > 0){
                gotoxy(36, x2);
                printf("%d", a3);
                x2+=3;
            }
            if (a4 > 0){
                gotoxy(36, x2);
                printf("%d", a4);
                x2+=3;
            }
            if (a5 > 0){
                gotoxy(36, x2);
                printf("%d", a5);
                x2+=3;
            }
            if (a6 > 0){
                gotoxy(36, x2);
                printf("%d", a6);
                x2+=3;
            }
            if (a7 > 0){
                gotoxy(36, x2);
                printf("%d", a7);
                x2+=3;
            }
            if (a8 > 0){
                gotoxy(36, x2);
                printf("%d", a8);
                x2+=3;
            }
            if (a9 > 0){
                gotoxy(36, x2);
                printf("%d", a9);
                x2+=3;
            }
            if (a10 > 0){
                gotoxy(36, x2);
                printf("%d", a10);
                x2+=3;
            }
            if (a11 > 0){
                gotoxy(36, x2);
                printf("%d", a11);
                x2+=3;
            }
            if (a12 > 0){
                gotoxy(36, x2);
                printf("%d", a12);
                x2+=3;
            }
            if (a13 > 0){
                gotoxy(36, x2);
                printf("%d", a13);
                x2+=3;
            }
            if (a14 > 0){
                gotoxy(36, x2);
                printf("%d", a14);
                x2+=3;
            }
            if (a15 > 0){
                gotoxy(36, x2);
                printf("%d", a15);
                x2+=3;
            }
            if (a16 > 0){
                gotoxy(36, x2);
                printf("%d", a16);
                x2+=3;
            }
            if (a17 > 0){
                gotoxy(36, x2);
                printf("%d", a17);
                x2+=3;
            }
            if (a18 > 0){
                gotoxy(36, x2);
                printf("%d", a18);
                x2+=3;
            }
            if (a19 > 0){
                gotoxy(36, x2);
                printf("%d", a19);
                x2+=3;
            }
            if (a20 > 0){
                gotoxy(36, x2);
                printf("%d", a20);
                x2+=3;
            }
            if (a21 > 0){
                gotoxy(36, x2);
                printf("%d", a21);
                x2+=3;
            }
            if (a22 > 0){
                gotoxy(36, x2);
                printf("%d", a22);
                x2+=3;
            }
            if (a23 > 0){
                gotoxy(36, x2);
                printf("%d", a23);
                x2+=3;
            }
        }
        gotoxy(66, 21);
        printf("EM %d h", quantos);
        gotoxy(69, 20);
        printf("%d", a);
        for (hours = 0; hours < quantos; hours++){
            linha_cima_dialogo(16, y, 9, 26);
            linha_cima_dialogo(27, y, 21, 48);
            laterais_dialogo(16, y +1, 1, 48); // ambos
            linha_baixo_dialogo(16, y + 2, 9, 26);
            linha_baixo_dialogo(27, y+2, 21, 48);
            y +=3;
        }
    }
    fclose(registro_uso);
    getch();
    menu_principal();
}

void menu_entrada_saida(){
    int x = 29, y = 12;
    int escolha = 0;
    char opcao;
    system("cls");
    area_trabalho();
    computador();
    preenche_linha_superior(31, 8, 13, 44);
    preenche_linha_inferior(31, 10, 13, 44);
    preenche_laterais(31, 9, 1, 44);
    preenche_linha_superior(26, 9, 3, 30);
    preenche_laterais(26, 10, 8, 49);
    preenche_linha_inferior(26, 18, 22, 49);
    preenche_linha_superior(45, 9, 3, 49);
    gotoxy(33,9);
    printf("USO DO LAB", 214);
    gotoxy(31, 12);
    printf("NOVO REGISTRO"); //consulta
    gotoxy(31, 14);
    printf("ENTRADAS/SA%cDAS", 214); //estatisticas de acesso
    gotoxy(31, 16);
    printf("EXCLUIR REGISTRO");
    while(opcao != 13) {
        if(opcao != 27) {
            gotoxy(x, y);
            printf("%c", 175);
            opcao = getch();
            if(opcao == 72) {
                if(y > 12) {
                    gotoxy(x, y);
                    printf(" ");
                    y -= 2;
                    gotoxy(x, y);
                    printf("%c", 175);
                    if(y == 12)
                        escolha = 1;
                    else
                        if(y == 14)
                            escolha = 2;
                        else
                            escolha = 3;
                }
            }else
                if(opcao == 80) {
                    if(y < 16) {
                        gotoxy(x, y);
                        printf(" ");
                        y += 2;
                        gotoxy(x, y);
                        printf("%c", 175);
                        if(y == 16)
                            escolha = 3;
                        else
                            if(y == 14)
                                escolha = 2;
                            else
                                escolha = 1;
                    }
                }else{
                    if(y == 12)
                        escolha = 1;
                }
        }else{
            system("cls");
            menu_principal();
        }
    }
    if(escolha == 1) {
        entrada_saida();
    }
    if(escolha == 2) {
        registros_uso();
    }
    if(escolha == 3) {
        exclui_entrada_saida();
    }
}

void entrada_saida(){
    atual uso; //Muda nome da struct
    int posicao = 0;
    char counta[QTDE], r, aux_dia = 0, aux_mes = 0;
    arq_inclusao = fopen(arquivo, "rb");
    if(arq_inclusao == NULL) {
        fclose(arq_inclusao);
        system("cls");
        preenche_linha_superior(20, 7, 40, 60);
        preenche_linha_inferior(20, 33, 40, 60);
        preenche_laterais(20, 8, 25, 60);
        gotoxy(27, 9);
        printf("REGISTRO DE ENTRADA E SA%cDA", 214);
        mensagem(3);
        mensagem(4);
        getch();
        menu_principal();
    } else {
    do{
        system("cls");
        computador();
        preenche_linha_superior(20, 7, 40, 60);
        preenche_linha_inferior(20, 33, 40, 60);
        preenche_laterais(20, 8, 25, 60);
        gotoxy(27, 9);
        printf("REGISTRO DE ENTRADA E SA%cDA", 214);
        volta_conta:
        gotoxy(24, 12);
        printf("Conta: ");
        setbuf(stdin, NULL);
        gets(counta);
        if(counta[0] <= '0') {
            gotoxy(31, 12);
            SetColor(4);
            printf("Campo Obrigat%crio", 162);
            SetColor(0);
            delay(50);
            limpa_parte_tela(30, 12, 30, 30);
            goto volta_conta;
        }
        while(fread(&uso, sizeof(atual), 1, arq_inclusao) == 1) { //Percorre o arquivo
            if(strcmp(strlwr(counta), strlwr(uso.conta)) == 0) { //Compara conta fornecida com a conta que está no arquivo
                gotoxy(24, 14);
                printf("Usu%crio: %s", 160, uso.usuario);
                finalidade_vazia:
                gotoxy(24, 16);
                printf("Finalidade: ");
                setbuf(stdin, NULL);
                gets(uso.finalidade);
                if(uso.finalidade[0] <= '0') {
                    gotoxy(36, 16);
                    SetColor(4);
                    printf("Campo Obrigat%crio", 162);
                    SetColor(0);
                    delay(50);
                    limpa_parte_tela(36, 16, 24, 36);
                    goto finalidade_vazia;
                }
                data_igual:
                gotoxy(37, 18);
                printf("HOR%cRIO", 181);
                gotoxy(29, 20);
                printf("ENTRADA");
                hora_entrada_invalida:
                gotoxy(24,21);
                printf("HORA: ");
                setbuf(stdin, NULL);
                scanf("%d",&uso.hora_entrada);
                if(uso.hora_entrada > 23 || uso.hora_entrada < 0){
                    mensagem(11);
                    limpa_parte_tela(30, 21, 30, 30);
                    delay(95);
                    limpa_parte_tela(1, 8, 12, 30);
                    limpa_parte_tela(1, 9, 12, 30);
                    limpa_parte_tela(1, 10, 12, 30);
                    limpa_parte_tela(1, 11, 12, 30);
                    limpa_parte_tela(1, 12, 12, 30);
                    limpa_parte_tela(1, 13, 12, 30);
                    limpa_parte_tela(1, 14, 12, 30);
                    limpa_parte_tela(1, 15, 12, 30);
                    goto hora_entrada_invalida;
                }
                min_entrada_invalido:
                gotoxy(24, 22);
                printf("MINUTOS: ");
                setbuf(stdin, NULL);
                scanf("%d", &uso.min_entrada);
                if(uso.min_entrada > 59 || uso.min_entrada < 0){
                    mensagem(11);
                    limpa_parte_tela(33, 22, 27, 33);
                    delay(95);
                    limpa_parte_tela(1, 8, 12, 33);
                    limpa_parte_tela(1, 9, 12, 33);
                    limpa_parte_tela(1, 10, 12, 33);
                    limpa_parte_tela(1, 11, 12, 33);
                    limpa_parte_tela(1, 12, 12, 33);
                    limpa_parte_tela(1, 13, 12, 33);
                    limpa_parte_tela(1, 14, 12, 33);
                    limpa_parte_tela(1, 15, 12, 33);
                    goto min_entrada_invalido;
                }
                SetColor(1);
                if(uso.hora_entrada >= 10){
                        gotoxy(38, 20);
                        printf("%d h", uso.hora_entrada);
                } else {
                        gotoxy(38, 20);
                        printf("0%d h", uso.hora_entrada);
                }

                if(uso.min_entrada >= 10){
                        gotoxy(43, 20);
                        printf("%d min.", uso.min_entrada);
                } else {
                        gotoxy(43, 20);
                        printf("0%d min.", uso.min_entrada);
                }
                SetColor(0);
                limpa_parte_tela(22, 21, 37, 29);
                limpa_parte_tela(22, 22, 37, 29);
                gotoxy(29, 22);
                printf("SA%cDA", 214);
                hora_saida_invalida:
                gotoxy(24,23);
                printf("HORA: ");
                setbuf(stdin, NULL);
                scanf("%d", &uso.hora_saida);
                if(uso.hora_saida > 23 || uso.hora_saida < 0 || uso.hora_saida < uso.hora_entrada){
                    mensagem(11);
                    limpa_parte_tela(30, 23, 30, 30);
                    delay(95);
                    limpa_parte_tela(1, 8, 12, 30);
                    limpa_parte_tela(1, 9, 12, 30);
                    limpa_parte_tela(1, 10, 12, 30);
                    limpa_parte_tela(1, 11, 12, 30);
                    limpa_parte_tela(1, 12, 12, 30);
                    limpa_parte_tela(1, 13, 12, 30);
                    limpa_parte_tela(1, 14, 12, 30);
                    limpa_parte_tela(1, 15, 12, 30);
                    goto hora_saida_invalida;
                }
                min_saida_invalido:
                gotoxy(24, 24);
                printf("MINUTOS: ");
                setbuf(stdin, NULL);
                scanf("%d", &uso.min_saida);
                if(uso.min_saida > 59 || uso.min_saida < 0){
                    h_min_iguais:
                    mensagem(11);
                    limpa_parte_tela(33, 24, 27, 33);
                    delay(95);
                    limpa_parte_tela(1, 8, 12, 30);
                    limpa_parte_tela(1, 9, 12, 30);
                    limpa_parte_tela(1, 10, 12, 30);
                    limpa_parte_tela(1, 11, 12, 30);
                    limpa_parte_tela(1, 12, 12, 30);
                    limpa_parte_tela(1, 13, 12, 30);
                    limpa_parte_tela(1, 14, 12, 30);
                    limpa_parte_tela(1, 15, 12, 30);
                    goto min_saida_invalido;
                }else{
                    if(uso.hora_saida == uso.hora_entrada){
                        if(uso.min_entrada == uso.min_saida || uso.min_saida < uso.min_entrada){
                            goto h_min_iguais;
                      }
                    }
                }
                SetColor(1);
                if(uso.hora_saida >= 10){
                        gotoxy(35, 22);
                        printf("%d h", uso.hora_saida);
                } else {
                        gotoxy(35, 22);
                        printf("0%d h", uso.hora_saida);
                }

                if(uso.min_saida >= 10){
                        gotoxy(40, 22);
                        printf("%d min.", uso.min_saida);
                } else {
                        gotoxy(40, 22);
                        printf("0%d min.", uso.min_saida);
                }
                SetColor(0);
                limpa_parte_tela(22, 23, 37, 29);
                limpa_parte_tela(22, 24, 37, 29);
                gotoxy(29, 24);;
                printf("DATA");
                dia_invalido:
                gotoxy(24, 25);
                printf("DIA ");
                setbuf(stdin, NULL);
                scanf("%d", &uso.dia);
                if(uso.dia > 31 || uso.dia <= 0){
                    mensagem(11);
                    limpa_parte_tela(28, 25, 27, 28);
                    delay(95);
                    limpa_parte_tela(1, 8, 12, 30);
                    limpa_parte_tela(1, 9, 12, 30);
                    limpa_parte_tela(1, 10, 12, 30);
                    limpa_parte_tela(1, 11, 12, 30);
                    limpa_parte_tela(1, 12, 12, 30);
                    limpa_parte_tela(1, 13, 12, 30);
                    limpa_parte_tela(1, 14, 12, 30);
                    limpa_parte_tela(1, 15, 12, 30);
                    aux_dia = uso.dia;
                    goto dia_invalido;
                }
                mes_invalido:
                gotoxy(24, 26);
                printf("M%cS ", 210);
                setbuf(stdin, NULL);
                scanf("%d", &uso.mes);
                if(uso.mes > 12 || uso.mes <= 0){
                    mensagem(11);
                    limpa_parte_tela(28, 26, 27, 28);
                    delay(95);
                    limpa_parte_tela(1, 8, 12, 30);
                    limpa_parte_tela(1, 9, 12, 30);
                    limpa_parte_tela(1, 10, 12, 30);
                    limpa_parte_tela(1, 11, 12, 30);
                    limpa_parte_tela(1, 12, 12, 30);
                    limpa_parte_tela(1, 13, 12, 30);
                    limpa_parte_tela(1, 14, 12, 30);
                    limpa_parte_tela(1, 15, 12, 30);
                    aux_mes = uso.mes;
                    goto mes_invalido;
                }
                uso.ano = 2017;
                SetColor(1);
                if(uso.dia >= 10){
                        gotoxy(35, 24);
                        printf("%d /", uso.dia);
                } else {
                        gotoxy(34, 24);
                        printf("0%d /", uso.dia);
                }

                if(uso.mes >= 10){
                        gotoxy(39, 24);
                        printf("%d / %d", uso.mes, uso.ano);
                } else {
                        gotoxy(39, 24);
                        printf("0%d / %d", uso.mes, uso.ano);
                }
                SetColor(0);
                limpa_parte_tela(22, 25, 37, 29);
                limpa_parte_tela(22, 26, 37, 29);

                /*registro_uso = fopen(temps, "rb");
                while(fread(&uso, sizeof(atual), 1, registro_uso) == 1){
                    if(strcmp(strlwr(counta), strlwr(uso.conta)) == 0){
                        if(aux_dia == uso.dia && aux_mes == uso.mes){
                            mensagem(14);
                            goto data_igual;
                        }
                    }
                }
                fclose(registro_uso);*/

                gotoxy(26, 26);
                printf("CONFIRMA REGISTRO ? [S/N] ");
                fflush(stdin);
                scanf("%c", &r);
                fflush(stdin);
                if(r == 'S' || r == 's') {
                    registro_uso = fopen(temps, "ab");
                    fwrite(&uso, sizeof(atual), 1, registro_uso);
                    fclose(registro_uso);
                    fclose(arq_inclusao);
                    fflush(stdin);
                    mensagem(7);
                    getch(); //Pausa
                    system("cls");
                    menu_principal();
                }else{
                    registro_uso = fopen("uso.txt", "ab");
                    rewind(arq_inclusao);
                    while(fread(&uso, sizeof(atual), 1, arq_inclusao) == 1) {
                        if(strcmp(strlwr(counta), strlwr(uso.conta)) == 0) {
                            fclose(arq_inclusao); //Fecha o arquivo
                            fclose(registro_uso);
                            fflush(stdin);
                            mensagem(4);
                            getch();
                            system("cls");
                            menu_principal();
                        }
                    }
                }
                posicao++;
            }
        }
    }while(r == 'N' || r == 'n');
    menu_principal();
    }
}

void exclui_entrada_saida() {
    int cont = 0, hora1, hora2, yd = 14;
    char count[QTDE], resp;
    FILE *copia;
    char copy[] = "copia_registro.txt";
    system("cls");
    atual uso;
    computador();
    registro_uso = fopen(temps, "rb");
    if(registro_uso == NULL) {
        fclose(registro_uso);
        mensagem(12);
        getch();
        menu_entrada_saida();
    }
    preenche_linha_superior(25, 8, 23, 48);
    preenche_linha_inferior(25, 10, 23, 48);
    preenche_laterais(25, 9, 1, 48);
    gotoxy(27, 9);
    printf("EXCLUS%cO DE REGISTRO", 199);
    linha_cima_dialogo(23, 11, 40, 63);
    linha_baixo_dialogo(23, 13, 40, 63);
    laterais_dialogo(23, 12, 1, 63);
    gotoxy(25, 12);
    printf("Digite a conta: ");
    setbuf(stdin, NULL);
    gets(count);
    while(fread(&uso, sizeof(atual), 1, registro_uso) == 1) {
        if(strcmp(count, uso.conta) == 0) {
            gotoxy(25, yd);
            printf("Conta: %s", uso.conta);
            gotoxy(25, yd+1);
            printf("Usu%crio: %s", 160, uso.usuario);
        }
    }
    rewind(registro_uso);
    while(fread(&uso, sizeof(atual), 1, registro_uso) == 1) {
        if(strcmp(count, uso.conta) == 0) {
            gotoxy(25, yd+3);
            printf("Finalidade: %s", uso.finalidade);
            gotoxy(25, yd+4);
            printf("Hor%crio de entrada: ", 160);
            if(uso.hora_entrada >= 10){
                gotoxy(47, yd+4);
                printf("%d h", uso.hora_entrada);
            } else {
                gotoxy(46, yd+4);
                printf("0%d h", uso.hora_entrada);
            }
            if(uso.min_entrada >= 10){
                gotoxy(51, yd+4);
                printf("%d min", uso.min_entrada);
            } else {
                gotoxy(51, yd+4);
                printf("0%d min", uso.min_entrada);
            }
            gotoxy(25, yd+5);
            printf("Hor%crio de sa%cda: ", 160, 161);
            if(uso.hora_saida >= 10){
                gotoxy(47, yd+5);
                printf("%d h", uso.hora_saida);
            } else {
                gotoxy(46, yd+5);
                printf("0%d h", uso.hora_saida);
            }
            if(uso.hora_saida >= 10){
                gotoxy(51, yd+5);
                printf("%d min", uso.min_saida);
            } else {
                gotoxy(51, yd+5);
                printf("0%d min", uso.min_saida);
            }
            yd+= 4;
            cont += 1;
        }
    }
    yd-= 4;
    if(cont > 1) {
        gotoxy(30, yd+7);
        printf("Digite o hor%crio que deseja apagar", 160);
        fflush(stdin);
        gotoxy(25, yd+ 9);
        printf("Hora de Entrada: ");
        fflush(stdin);
        scanf("%d", &hora1);
        fflush(stdin);
        gotoxy(25, yd+10);
        printf("Hora de Sa%cda: ", 161);
        fflush(stdin);
        scanf("%d", &hora2);
        fflush(stdin);
        gotoxy(30, yd+11);
        printf("Apagar o registro digitado? [S/N]  ");
        scanf("%c", &resp);
        if(resp == 's' || resp == 'S') {
            copia = fopen(copy, "ab");
            rewind(registro_uso);
            while(fread(&uso, sizeof(atual), 1, registro_uso) == 1) {
                if(hora1 != uso.hora_entrada && hora2 != uso.hora_saida) {
                    fwrite(&uso, sizeof(atual), 1, copia);
                }
            }
            fclose(registro_uso);
            fclose(copia);
            unlink(temps);
            rename(copy, temps);
            SetColor(4);
            limpa_parte_tela(28, 14, 19, 28);
            limpa_parte_tela(28, 15, 19, 28);
            limpa_parte_tela(28, 16, 19, 28);
            preenche_linha_superior(28, 14, 21, 49);
            preenche_laterais(28, 15, 1, 49);
            preenche_linha_inferior(28, 16, 21, 49);
            gotoxy(30, 15);
            printf("Exclus%co Conclu%cda", 198, 161);
            SetColor(0);
            mensagem(4);
            getch();
            menu_entrada_saida();
            }else{
                fclose(registro_uso);
                menu_entrada_saida();
            }
    }else{
        gotoxy(25, yd+7);
        printf("Apagar Registro? [S/N]  ");
        scanf("%c", &resp);
        if(resp == 's' || resp == 'S') {
            copia = fopen(copy, "ab");
            rewind(registro_uso);
            while(fread(&uso, sizeof(atual), 1, registro_uso) == 1) {
                if(strcmp(count, uso.conta) != 0) {
                    fwrite(&uso, sizeof(atual), 1, copia);
                }
            }
            fclose(registro_uso);
            fclose(copia);
            unlink(temps);
            rename(copy, temps);
            SetColor(4);
            limpa_parte_tela(28, 14, 19, 28);
            limpa_parte_tela(28, 15, 19, 28);
            limpa_parte_tela(28, 16, 19, 28);
            preenche_linha_superior(28, 14, 21, 49);
            preenche_laterais(28, 15, 1, 49);
            preenche_linha_inferior(28, 16, 21, 49);
            gotoxy(30, 15);
            printf("Exclus%co Conclu%cda", 198, 161);
            SetColor(0);
            mensagem(4);
            getch();
            menu_entrada_saida();
        }else
            fclose(registro_uso);
            menu_entrada_saida();
        }
}

void meus_dados() {
    system("cls");
    area_trabalho();
    atual uso;
    int y = 5;
    registro_uso = fopen(temps, "rb");
    if(registro_uso == NULL) {
        fclose(registro_uso);
        mensagem(12);
        getch();
        menu_user();
    }else{
        preenche_linha_superior(40, 2, 20, 61);
        preenche_laterais(40, 3, 4, 61);
        preenche_linha_inferior(40, 7, 20, 61);
        gotoxy(46, 3);
        printf("REGISTROS");
        while(fread(&uso, sizeof(atual), 1, registro_uso) == 1) {
            if(strcmp(nome_da_conta, uso.conta) == 0){
                gotoxy(41, y);
                printf("Conta: %s", uso.conta);
                gotoxy(41, y+1);
                printf("Usu%crio: %s", 160, uso.usuario);
            }
        }
        rewind(registro_uso);
        while(fread(&uso, sizeof(atual), 1, registro_uso) == 1){
            if(strcmp(nome_da_conta, uso.conta) == 0) {
                preenche_lateral_linha_fina(47, y + 2, 2);
                preenche_lateral_linha_fina(53, y + 2, 2);
                preenche_linha_inferior(40, 7, 20, 61);
                preenche_linha_superior(33, y + 4, 34, 68);
                preenche_laterais(33, y + 5, 4, 68);
                preenche_linha_inferior(33, y + 9, 34, 68);
                gotoxy(34, y+5);
                printf("Finalidade: %s", uso.finalidade);
                gotoxy(34, y+6);
                printf("Data: ");
                if(uso.dia >= 10){
                        gotoxy(41, y+6);
                        printf("%d /", uso.dia);
                } else {
                        gotoxy(40, y+6);
                        printf("0%d /", uso.dia);
                }

                if(uso.mes >= 10){
                        gotoxy(46, y+6);
                        printf("%d / %d", uso.mes, uso.ano);
                } else {
                        gotoxy(46, y+6);
                        printf("0%d / %d", uso.mes, uso.ano);
                }
                gotoxy(34, y+7);
                printf("Hora de Entrada: ");
                if(uso.hora_entrada >= 10){
                        gotoxy(52, y+7);
                        printf("%d h", uso.hora_entrada);
                } else {
                        gotoxy(51, y+7);
                        printf("0%d h", uso.hora_entrada);
                }

                if(uso.min_entrada >= 10){
                        gotoxy(56, y+7);
                        printf("%d min.", uso.min_entrada);
                } else {
                        gotoxy(56, y+7);
                        printf("0%d min.", uso.min_entrada);
                }
                gotoxy(34, y+8);
                printf("Hora de Sa%cda: ", 161);
                if(uso.hora_saida >= 10){
                        gotoxy(51, y+8);
                        printf("%d h", uso.hora_saida);
                } else {
                        gotoxy(50, y+8);
                        printf("0%d h", uso.hora_saida);
                }

                if(uso.min_saida >= 10){
                        gotoxy(55, y+8);
                        printf("%d min.", uso.min_saida);
                } else {
                        gotoxy(55, y+8);
                        printf("0%d min.", uso.min_saida);
                }
                gotoxy(34, y+9);
                y += 8;
            }
        }
        fclose(registro_uso);
        mensagem(4);
        getch();
        menu_user();
    }
}
void registros_uso(){
    atual uso;
    int x = 11;
    registro_uso = fopen(temps, "rb");
    if(registro_uso == NULL) {
       fclose(registro_uso);
       system("cls");
       preenche_linha_superior(20, 7, 40, 60);
       preenche_linha_inferior(20, 33, 40, 60);
       preenche_laterais(20, 8, 25, 60);
       gotoxy(27, 9);
       printf("REGISTRO DE ENTRADA E SA%cDA", 214);
       mensagem(12);
       mensagem(4);
       getch();
       menu_entrada_saida();
    }else{
        system("cls");
        computador();
        gotoxy(30, 7);
        printf("REGISTROS");
        preenche_linha_superior(28, 6, 11, 40);
        preenche_linha_inferior(28, 8, 11, 40);
        preenche_laterais(28, 7, 1, 40);
        while(fread(&uso, sizeof(uso), 1, registro_uso) == 1) {
            setbuf(stdin, NULL);
            preenche_linha_superior(18, x, 40, 58);
            gotoxy(20, x+1);
            printf("Conta: %s", uso.conta);
            gotoxy(20, x+2);
            printf("Usu%crio: %s", 160, uso.usuario);
            gotoxy(20, x+3);
            printf("Finalidade: %s", uso.finalidade);
            gotoxy(20, x+4);
            printf("Data: ");
            if(uso.dia >= 10){
                gotoxy(27, x+4);
                printf("%d /", uso.dia);
            } else {
                gotoxy(26, x+4);
                printf("0%d /", uso.dia);
            }
            if(uso.mes >= 10){
                gotoxy(32, x+4);
                printf("%d / %d", uso.mes, uso.ano);
            } else {
                gotoxy(32, x+4);
                printf("0%d / %d", uso.mes, uso.ano);
            }
            gotoxy(20, x+5);
            printf("Hor%crio de entrada: ", 160);
            if(uso.hora_entrada >= 10){
                gotoxy(41, x+5);
                printf("%d h", uso.hora_entrada);
            } else {
                gotoxy(40, x+5);
                printf("0%d h", uso.hora_entrada);
            }
            if(uso.min_entrada >= 10){
                gotoxy(46, x+5);
                printf("%d min", uso.min_entrada);
            } else {
                gotoxy(46, x+5);
                printf("0%d min", uso.min_entrada);
            }
            gotoxy(20, x+6);
            printf("Hor%crio de sa%cda: ", 160, 161);
            if(uso.hora_saida >= 10){
                gotoxy(41, x+6);
                printf("%d h", uso.hora_saida);
            } else {
                gotoxy(40, x+6);
                printf("0%d h", uso.hora_saida);
            }
            if(uso.min_saida >= 10){
                gotoxy(46, x+6);
                printf("%d min", uso.min_saida);
            } else {
                gotoxy(46, x+6);
                printf("0%d min", uso.min_saida);
            }
            preenche_linha_inferior (18, x+7, 40, 58);
            preenche_laterais(18, x+1, 6, 58);
            x = x + 8;
            gotoxy(1, 29);
        }
    }
    fclose(registro_uso);
    mensagem(4);
    setbuf(stdin, NULL);
    getch();
    menu_entrada_saida();
}

void area_trabalho(){
    int x = 2, li = 2, i;
    //cantos
    gotoxy(1,1); //superior esquerdo
    printf("%c", 201);
    gotoxy(1,32); //inferior esquerdo
    printf("%c", 200);
    gotoxy(90,1); //superior direito
    printf("%c", 187);
    gotoxy(90,32); //inferior direito
    printf("%c", 188);

    for(i=0;i<30;i++){
        gotoxy(1,li); //esq.
        printf("%c", 179);
        gotoxy(90, li); //direita
        printf("%c", 179);
        li++;
    }
    for(i=0;i<88;i++){
        gotoxy(x,1); //cima
        printf("%c", 194);
        gotoxy(x,32); //baixo
        printf("%c", 193);
        x++;
    }
    gotoxy(1, 32);
}

void molde1(){
    system("cls");
    area_trabalho();
    //Molde
    int c=48; //posicao depois da cx. de titulo
	int x3=21; // linha de cima e baixo
	int y4=10; //linha esquerda e direita
    //Caixa de titulo
    int lc=30; //linha de baixo e cima
	int i; //contador
	//Cantos Molde
	gotoxy(20,9); //superior esquerdo
	printf("%c", 201);
    gotoxy(56,9); //superior direito
    printf("%c", 187);
    gotoxy(20,22); //inferior esquerdo
	printf("%c", 200);
    gotoxy(56,22); //inferior direito
    printf("%c", 188);
    //Cantos e laterais caixinha titulo
    gotoxy(29,9); //centro esquerdo
    printf("%c",185);
    gotoxy(29,8);  //cima
    printf("%c",201);
    gotoxy(29,10); //baixo
    printf("%c",200);
    gotoxy(47,9); //centro direito
    printf("%c",204);
    gotoxy(47,8); //cima
    printf("%c",187);
    gotoxy(47,10); //baixo
    printf("%c",188);
    //Molde
    for(i=1; i<13; i++){
        gotoxy(20,y4);
        printf("%c",186); //esquerda
        gotoxy(56,y4);
        printf("%c",186); //direita
        y4++;
        if(i<9){
            gotoxy(c, 9); //cima _ direita
            printf("%c",205);
            c++;
            gotoxy(x3,9);
			printf("%c",205); //cima _ esquerda
			x3++;
        }
    }
    //Caixa de titulo
    for(i=1;i<18; i++){
        gotoxy(lc,10); //embaixo
        printf("%c",205);
        gotoxy(lc++,8); //em cima
        printf("%c",205);
    }
    x3=21;
    for(i=1; i<36;i++){
        gotoxy(x3,22); //embaixo
        printf("%c",205);
        x3++;
    }
    computador();
	gotoxy(1,32);
}

void molde2(){
    system("cls");
    area_trabalho();
    //Molde
    int c=50; //posicao depois da cx. de titulo
	int x3=17; // linha de cima e baixo
	int y4=10; //linha esquerda e direita
        //Caixa de titulo
    int lc=32; //linha de baixo e cima
	int i; //contador
	//Cantos Molde
	gotoxy(16,9); //superior esquerdo
	printf("%c", 201);
    gotoxy(63,9); //superior direito
    printf("%c", 187);
    gotoxy(16,22); //inferior esquerdo
	printf("%c", 200);
    gotoxy(63,22); //inferior direito
    printf("%c", 188);
    //Cantos e laterais caixinha titulo
    gotoxy(31,9); //centro esquerdo
    printf("%c",185);
    gotoxy(31,8);  //cima
    printf("%c",201);
    gotoxy(31,10); //baixo
    printf("%c",200);
    gotoxy(49,9); //centro direito
    printf("%c",204);
    gotoxy(49,8); //cima
    printf("%c",187);
    gotoxy(49,10); //baixo
    printf("%c",188);
    //Molde
    for(i=1; i<13; i++){
        gotoxy(16,y4);
        printf("%c",186); //esquerda
        gotoxy(63,y4);
        printf("%c",186); //direita
        y4++;
    }
    for(i=1;i<20;i++){
        if(i<14){
            gotoxy(c,9); //cima _ direita
            printf("%c",205);
            c++;
        }
        if(i<15){
            gotoxy(x3,9);
			printf("%c",205); //cima vindo da esquerda
			x3++;
        }
    }
    //Título
    gotoxy(34, 9);
    printf("System Lab In");
    //Caixa de título
    for(i=1;i<18; i++){
        gotoxy(lc,10); //em baixo
        printf("%c",205);
        gotoxy(lc++,8); //em cima
        printf("%c",205);
    }
    x3=17;
    for(i=1; i<47;i++){
        gotoxy(x3,22); //em baixo
        printf("%c",205);
        x3++;
    }
    computador();
	gotoxy(1,32); //Posiciona o cursor para depois da tela
}

void molde3(){
    system("cls");
    area_trabalho();
    //Molde
    int c=48; //posicao depois da cx. de titulo
	int x3=18; // linha de cima e baixo
	int y4=8; //linha esquerda e direita
	    //Caixa de titulo
    int lc=30; //linha de baixo e cima
	int i; //contador
    int a;
	//Cantos Molde
	gotoxy(17,7); //superior esquerdo
	printf("%c", 201);
    gotoxy(59,7); //superior direito
    printf("%c", 187);
    gotoxy(17,20); //inferior esquerdo
	printf("%c", 200);
    gotoxy(59,20); //inferior direito
    printf("%c", 188);
    //Cantos e laterais caixinha titulo
    gotoxy(29,7); //centro esquerdo
    printf("%c",185);
    gotoxy(29,6);  //cima
    printf("%c",201);
    gotoxy(29,8); //baixo
    printf("%c",200);
    gotoxy(47,7); //centro direito
    printf("%c",204);
    gotoxy(47,6); //cima
    printf("%c",187);
    gotoxy(47,8); //baixo
    printf("%c",188);
    //Molde
    for(i=1; i<13; i++){
        gotoxy(17,y4);
        printf("%c",186); //esquerda
        gotoxy(59,y4);
        printf("%c",186); //direita
        y4++;
        if(i<12){
            gotoxy(c, 7); //cima _ direita
            printf("%c",203);
            c++;
            gotoxy(x3,7);
			printf("%c",203); //cima vindo da esquerda
			x3++;
        }
    }
    //Titulo
    gotoxy(32, 7);
    printf("System Lab In");
    //Caixa de titulo
    for(i=1;i<18; i++){
        gotoxy(lc,8); //em baixo
        printf("%c",205);
        gotoxy(lc++,6); //em cima
        printf("%c",203);
    }
    x3=18;
    for(i=1; i<42;i++){
        gotoxy(x3,20); //em baixo
        printf("%c",202);
        x3++;
    }
    computador();
	gotoxy(1,32); //Posiciona o cursor para depois da tela
}

void computador(){
    int c1=71, c2=72, l2=8, j=79; //cima direita
    int i;
    //Cantos
    gotoxy(71,7); //superior esquerdo
    printf("%c", 218);
    gotoxy(71,11); //inferior esquerdo
    printf("%c", 192);
    gotoxy(82,7); //superior direito
    printf("%c", 191);
    gotoxy(82,11); //inferior direito
    printf("%c", 217);
    //lados tela
    gotoxy(73,9);
    printf("%c", 186);
    gotoxy(80,9);
    printf("%c", 186);
    for(i=1; i<11; i++){
        gotoxy(c2,7);
        printf("%c",196); //cima - tela
        if(i<7){
            if(i<4){
            gotoxy(c2,11);
            printf("%c",205); //baixo esq.- tela
            gotoxy(j,11);
            printf("%c",205); j++; //baixo direita - tela
            }
            gotoxy(c2+2,10);
            printf("%c",205); //baixo SLIN
            gotoxy(c2+2,8); //cima SLIN
            printf("%c",205);
        }
        c2++;
        if(i<4){
            gotoxy(82,l2);
            printf("%c",186); //direita
            gotoxy(c1,l2);
            printf("%c",186); //esquerda
            l2++;
    }
    //apoio pc
    gotoxy(78,11);
    printf("%c",201);
    gotoxy(75,11);
    printf("%c",187);
    gotoxy(78,12);
    printf("%c",202);
    gotoxy(75,12);
    printf("%c",202);
    gotoxy(76,12);
    printf("%c",205);
    gotoxy(77,12);
    printf("%c",205);
    gotoxy(73,10); //SLIN inferior esquerdo
    printf("%c",200);
    gotoxy(80,8); //superior direito
    printf("%c",187);
    gotoxy(73,8);
    printf("%c", 201); //superior esq.
    gotoxy(80,10); //inferior dir.
    printf("%c",188);
    gotoxy(75,9);
    printf("SLIN");
    Sleep(75);
    }
    data_hora();
    suporte_pc();
    gotoxy(1,22);
}

void suporte_pc(){
    preenche_linha_superior(72, 12, 2, 74);
    gotoxy(74, 12);
    printf("%c", 205);
    preenche_linha_superior(79, 12, 4, 84);
    gotoxy(79, 12);
    printf("%c", 205);
    gotoxy(82, 12);
    printf("%c", 203);
    preenche_linha_superior(70, 13, 14, 84);
    gotoxy(84, 13);
    printf("%c", 188);
    gotoxy(73, 13);
    printf("%c", 202);
    preenche_linha_superior(69, 14, 14, 84);
    gotoxy(83, 14);
    printf("%c", 202);
    gotoxy(76, 14);
    printf("%c", 202);
    gotoxy(80, 14);
    printf("%c", 203);
    gotoxy(71, 14);
    printf("%c", 203);
    gotoxy(86, 14);
    printf("%c", 188);
    gotoxy(86, 13);
    printf("%c", 201);
    gotoxy(87, 13);
    printf("%c", 188);
    gotoxy(88, 11);
    printf("%c", 201);
    gotoxy(88, 12);
    printf("%c", 188);
    gotoxy(89, 11);
    printf("%c", 188);
    gotoxy(89, 10);
    printf("%c", 201);
    gotoxy(87, 12);
    printf("%c", 201);
    preenche_linha_inferior(69, 15, 15, 85);
    gotoxy(74, 15);
    printf("%c", 203);
    preenche_linha_inferior(74, 16, 8, 83);
    gotoxy(85, 14);
    printf("%c", 201);
    gotoxy(83, 15);
    printf("%c", 201);
    gotoxy(80, 16);
    printf("%c", 202);
    gotoxy(76, 16);
    printf("%c", 203);
}

void molde_tempo(){ //molde de data e hora
    //Laterais
    preenche_laterais(2, 3, 1, 21); //esquerda e direita DATA
    preenche_laterais(55, 3, 1, 69); //esquerda e direita HORA
    //cima e baixo DATA
    preenche_linha_superior(2, 2, 18, 21);
    preenche_linha_inferior(2, 4, 18, 21);
    //cima e baixo HORA
    preenche_linha_superior(55, 2, 13, 69);
    preenche_linha_inferior(55, 4, 13, 69);
}

void linha_cima_dialogo(int xi, int l, int q, int xf){ //caixa de dialogo explicativo
    int i;
    gotoxy(xi, l); //canto superior esquerdo
    printf("%c", 218);
    for (i=0; i < q; i++){
        xi++;
        gotoxy(xi , l);
        printf ("%c", 196);
    }
    gotoxy(xf, l); //canto superior direito
    printf("%c", 191);
}

void linha_baixo_dialogo(int xi, int l, int q, int xf){
    int i;
    gotoxy(xi, l); //canto inferior esquerdo
    printf("%c", 192);
    for (i=0; i < q; i++){
        xi++;
        gotoxy(xi , l);
        printf ("%c", 196);
    }
    gotoxy(xf, l); //canto inferior direito
    printf("%c", 217);
}

void laterais_dialogo(int xi, int l, int q, int xf){
    int i;
    for(i=0; i< q; i++){
        gotoxy(xi, l);
        printf("%c", 179);
        gotoxy(xf, l);
        printf("%c", 179);
        l++;
    }
}

void data_hora(){ //Data e hora atualizadas
    int tempo;
        molde_tempo();
        gotoxy(4,3);
        printf("DATA:");
        gotoxy(10,3);
        system("date/t");
        gotoxy(57,3);
        printf("HORA:");
        gotoxy(63,3);
        system("time/t");
}

void preenche_linha_superior(int xi, int l, int q, int xf) {
    int i;
    gotoxy(xi, l);
    printf("%c", 201);
    for(i = 0; i < q; i++) {
        xi++;
        gotoxy(xi, l);
        printf("%c", 205);
    }
    gotoxy(xf,l);
    printf("%c", 187);
}

void preenche_linha_inferior(int xi, int l, int q, int xf) {
    int i;
    //canto inferior esquerdo
    gotoxy(xi, l);
    printf("%c", 200);
    for(i = 0; i < q; i++) {
        xi++;
        gotoxy(xi, l);
        printf("%c", 205);
    }
    //canto inferior direito
    gotoxy(xf, l);
    printf("%c", 188);
}

void preenche_laterais (int xi, int l, int q, int xf) {
    int i;
    for(i=0; i< q; i++) {
        gotoxy(xi, l);
        printf("%c", 186);
        gotoxy(xf, l);
        printf("%c", 186);
        l++;
    }
}

void mensagem(int exibe) {
    switch (exibe) {
        case 1:
            SetColor(4);
            linha_cima_dialogo(17, 16, 45, 62);
            linha_baixo_dialogo(17, 18, 45, 62);
            laterais_dialogo(17, 17, 1, 62);
            gotoxy(30, 17);
            printf("Conta j%c cadastrada", 160);
            linha_cima_dialogo(2, 8, 12, 14);
            linha_baixo_dialogo(2, 13, 12, 14);
            laterais_dialogo(2, 9, 4, 14);
            gotoxy(4, 9);
            printf("Pressione");
            gotoxy(4, 10);
            printf("enter para");
            gotoxy(5, 11);
            printf("incluir");
            gotoxy(4,12);
            printf("nova conta");
            gotoxy(1, 25);
            SetColor(0);
            break;
        case 2:
            SetColor(4);
            limpa_parte_tela(2, 8, 14, 16);
            limpa_parte_tela(2, 9, 14, 16);
            limpa_parte_tela(2, 10, 14, 16);
            limpa_parte_tela(2, 11, 14, 16);
            limpa_parte_tela(2, 12, 14, 16);
            linha_cima_dialogo(2, 8, 12, 14);
            linha_baixo_dialogo(2, 12, 12, 14);
            laterais_dialogo(2, 9, 3, 14);
            gotoxy(5, 9);
            SetColor(4);
            printf("Usu%crio", 160);
            gotoxy(7, 10);
            printf("j%c", 160);
            gotoxy(4, 11);
            printf("existente");
            delay(100);
            limpa_parte_tela(2, 8, 14, 16);
            limpa_parte_tela(2, 9, 14, 16);
            limpa_parte_tela(2, 10, 14, 16);
            limpa_parte_tela(2, 11, 14, 16);
            limpa_parte_tela(2, 12, 14, 16);
            SetColor(0);
            break;
        case 3:
            SetColor(4);
            preenche_linha_superior(24, 11, 27, 52);
            preenche_linha_inferior(24, 13, 27, 52);
            preenche_laterais(24, 12, 1, 52);
            gotoxy(26,12);
            printf("N%co h%c contas cadastradas", 198, 160);
            SetColor(0);
            break;
        case 4:
            SetColor(5);
            limpa_parte_tela(2, 12, 12, 14);
            limpa_parte_tela(2, 13, 12, 14);
            limpa_parte_tela(2, 14, 12, 14);
            limpa_parte_tela(2, 15, 12, 14);
            linha_cima_dialogo(2, 12, 12, 14);
            linha_baixo_dialogo(2, 15, 12, 14);
            laterais_dialogo(2, 13, 2, 14);
            gotoxy(4, 13);
            printf("Pressione");
            gotoxy(6, 14);
            printf("enter");
            SetColor(0);
            break;
        case 5:
            SetColor(4);
            limpa_parte_tela(2, 8, 12, 14);
            limpa_parte_tela(2, 9, 12, 14);
            limpa_parte_tela(2, 10, 12, 14);
            limpa_parte_tela(2, 11, 12, 14);
            limpa_parte_tela(2, 12, 12, 14);
            limpa_parte_tela(2, 13, 12, 14);
            limpa_parte_tela(2, 14, 12, 14);
            limpa_parte_tela(2, 15, 12, 14);
            limpa_parte_tela(2, 16, 12, 14);
            linha_cima_dialogo(2, 8, 13, 15);
            linha_baixo_dialogo(2, 16, 13, 15);
            laterais_dialogo(2, 9, 7, 15);
            gotoxy(3, 9);
            printf("Voc%c digitou", 136);
            gotoxy(3, 10);
            printf("a senha");
            gotoxy(3, 11);
            printf("incorreta,");
            gotoxy(3, 12);
            printf("pressione");
            gotoxy(3, 13);
            printf("enter para");
            gotoxy(3, 14);
            printf("tentar");
            gotoxy(3, 15);
            printf("novamente");
            SetColor(0);
            break;
        case 6:
            SetColor(4);
            limpa_parte_tela(2, 20, 12, 14);
            limpa_parte_tela(2, 21, 12, 14);
            limpa_parte_tela(2, 22, 12, 14);
            limpa_parte_tela(2, 23, 12, 14);
            limpa_parte_tela(2, 24, 12, 14);
            limpa_parte_tela(2, 25, 12, 14);
            limpa_parte_tela(2, 26, 12, 14);
            limpa_parte_tela(2, 27, 12, 14);
            limpa_parte_tela(2, 28, 12, 14);
            linha_cima_dialogo(2, 20, 13, 15);
            linha_baixo_dialogo(2, 28, 13, 15);
            laterais_dialogo(2, 21, 7, 15);
            gotoxy(3, 21);
            printf("Voc%c n%co", 136, 198);
            gotoxy(3, 22);
            printf("pode fazer");
            gotoxy(3, 23);
            printf("isso,");
            gotoxy(3, 24);
            printf("pressione");
            gotoxy(3, 25);
            printf("enter para");
            gotoxy(3, 26);
            printf("tentar");
            gotoxy(3, 27);
            printf("novamente");
            SetColor(0);
            break;
        case 7:
            SetColor(2);
            preenche_linha_superior(26, 30, 27, 53);
            preenche_linha_inferior(26, 32, 27, 53);
            preenche_laterais(26, 31, 1, 53);
            gotoxy(31, 31);
            printf("Hor%crio registrado", 160);
            SetColor(0);
            break;
        case 8:
            SetColor(4);
            preenche_linha_superior(24, 11, 27, 52);
            preenche_linha_inferior(24, 13, 27, 52);
            preenche_laterais(24, 12, 1, 52);
            gotoxy(26,12);
            printf("Erro no arquivo");
            SetColor(0);
            break;
        case 9:
            SetColor(4);
            preenche_linha_superior(24, 20, 27, 52);
            preenche_linha_inferior(24, 22, 27, 52);
            preenche_laterais(24, 21, 1, 52);
            gotoxy(26,21);
            printf ("Conta n%co cadastrada.", 198);
            SetColor(0);
            break;
        case 10:
            SetColor(2);
            preenche_linha_superior(10, 10, 26, 36);
            gotoxy(12, 11);
            printf("Altera%c%ces registradas!", 135, 228);
            preenche_linha_inferior(10, 12, 26, 36);
            preenche_laterais(10, 11, 1, 36);
            SetColor(0);
            break;
        case 11:
            SetColor(4);
            limpa_parte_tela(2, 8, 12, 12);
            limpa_parte_tela(2, 9, 12, 12);
            limpa_parte_tela(2, 10, 12, 12);
            limpa_parte_tela(2, 11, 12, 12);
            limpa_parte_tela(2, 12, 12, 12);
            limpa_parte_tela(2, 13, 12, 12);
            limpa_parte_tela(2, 14, 12, 12);
            limpa_parte_tela(2, 15, 12, 12);
            linha_cima_dialogo(2, 8, 10, 12);
            linha_baixo_dialogo(2, 15, 10, 12);
            laterais_dialogo(2, 9, 6, 12);
            gotoxy(5, 9);
            printf("Voc%c", 136);
            gotoxy(3, 10);
            printf("forneceu");
            gotoxy(5, 11);
            printf("dados");
            gotoxy(3, 12);
            printf("inv%clidos", 160);
            gotoxy(5, 13);
            printf("tente");
            gotoxy(3, 14);
            printf("novamente");
            SetColor(0);
            break;
        case 12:
            SetColor(4);
            preenche_linha_superior(24, 11, 27, 52);
            preenche_linha_inferior(24, 13, 27, 52);
            preenche_laterais(24, 12, 1, 52);
            gotoxy(27,12);
            printf("N%co h%c registros salvos", 198, 160);
            SetColor(0);
            break;
        case 13:
            SetColor(2);
            limpa_parte_tela(16, 14, 47, 16);
            limpa_parte_tela(16, 15, 47, 16);
            limpa_parte_tela(16, 16, 47, 30);
            preenche_linha_superior(16, 14, 47, 63);
            preenche_linha_inferior(16, 16, 47, 63);
            preenche_laterais(16, 15, 1, 63);
            gotoxy(30, 15);
            printf("Cadastro efetuado.");
            SetColor(0);
            break;
        }
}

void limpa_parte_tela(int xi, int li, int q, int r) {
    int i;
    for(i=0; i < q; i++){
        gotoxy(xi, li);
        printf(" ");
        xi++;
    }
    gotoxy(r, li);
}

void preenche_lateral_linha_fina (int c, int l, int q) {
    int i;
    for(i=0; i< q; i++) {
        gotoxy(c, l);
        printf("%c", 179);
        l++;
    }
}

void preenche_linha_fina_horizontal(int l, int c, int q){
    int i;
    gotoxy(l, c);
    for(i = 0; i < q; i++){
        printf("%c", 196);
    }
}
