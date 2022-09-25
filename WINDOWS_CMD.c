// windows cmd build

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ############ Declaração de Funções Vazias para evitar Erros

void DescobrirPosicaoDoJogador(void);
void ComoJogarTela (void);
void ReiniciarJogo (void);
void TelaDeVitoria (void);
void MoverJogador (void);
void TelaDeDicas (void);
void Verificar (void);

// ############ Declaração de Variáveis

char matrizPrincipal[3][3] = {{"123"},{"456"},{"78 "}};

int posicaoDoJogador[2] = {};

int oJogoAcabou = 0;

int optionMenu = 0;

char optionGame;

// ############ Estatísticas do Jogo

int quantasVezesMoveu = 0;
int quantasVezesReiniciou = 0;

// ############ Declaração de Funções diversas sobre o Funcionamento

void limpar (int howMuch) {
    for (int i=0; i<howMuch; i++) {
        printf ("\n");
    }
}

void InsiraComandoInt (int permitido[]) {

    for (;;) {

        for (int i=0; i<10; i++) {

            if (optionMenu == permitido[i]) {return;}

        }

        limpar(1);
        printf ("[?] Comando Invalido, digite outro comando.");
        limpar(2);

        scanf ("%d",&optionMenu);

    }

}

// ############ Declaração de Funções especificamente do Jogo

void EmbaralharMatriz (char *cobaia, size_t tamanho) {

    if (tamanho > 1) {

        size_t i;
        for (i = 0; i < tamanho - 1; i++) {

            size_t j = i + rand() / (RAND_MAX / (tamanho - i) + 1);
            int t = cobaia[j];
            cobaia[j] = cobaia[i];
            cobaia[i] = t;
        }
    }

    DescobrirPosicaoDoJogador();

    char armazenamento = matrizPrincipal[1][1];
    matrizPrincipal[posicaoDoJogador[0]][posicaoDoJogador[1]] = armazenamento;
    matrizPrincipal[1][1] = ' ';

}


void TraduzirComandoDoJogo (void) {

    char c = optionGame;

    if (c == 'c' || c == 'w' || c == 'W') {optionGame = 'C';} // ↑
    if (c == 'b' || c == 's' || c == 'S') {optionGame = 'B';} // ↓
    if (c == 'e' || c == 'a' || c == 'A') {optionGame = 'E';} // ←
    if (c == 'd' || c == 'D')             {optionGame = 'D';} // →
    if (c == 'v')                         {optionGame = 'V';} // V
    if (c == 'r')                         {optionGame = 'R';} // R

}

void ReconhecerComandoDoJogo (void) {

    TraduzirComandoDoJogo();

    switch (optionGame) {

        case 'V': Verificar(); break;
        case 'R': ReiniciarJogo(); break;
        case 'C': MoverJogador(); break;
        case 'B': MoverJogador(); break;
        case 'E': MoverJogador(); break;
        case 'D': MoverJogador(); break;

        default: break;

    }
}

void ExibirMatriz (void) {

    limpar(45);

    printf ("\t");

    for (int i = 0; i<37; i++) {printf ("||");}

    limpar(2);

    printf ("\t");

    for (int i = 0; i<37; i++) {printf ("__");}

    for (int i = 0; i<3; i++) {

        limpar(3); printf ("\t\t\t  ");

        for (int j = 0; j<3; j++) {

            printf ("\t  %c  ", matrizPrincipal[i][j]);

        }

    }

    limpar(3);

    printf ("\t");

    for (int i = 0; i<37; i++) {printf ("__");}

    limpar(2);

    printf ("\t");

    for (int i = 0; i<37; i++) {printf ("||");}

    limpar(3);

    printf ("\t[  V  ] VERIFICAR");

    limpar(2);

    printf ("\t[  R  ] REINICIAR");

    limpar(5);

    printf ("\t\t\t\t  [ W | C ] Cima\t");
    limpar(3);
    printf ("\t  [ A | E ] Esquerda\t\t\t\t[ D | D ] Direita");
    limpar(3);
    printf ("\t\t\t\t  [ S | B ] Baixo\t");
    limpar(4);

    printf ("");

    scanf ("%c",&optionGame);
    ReconhecerComandoDoJogo();

}

void ReiniciarJogo (void) {

    quantasVezesReiniciou++;

    EmbaralharMatriz(*matrizPrincipal, 9);

}

void DescobrirPosicaoDoJogador (void) {

    for (int i=0; i<3; i++) {

        for (int j=0; j<3; j++) {

            if (matrizPrincipal[i][j] == ' ')
            {posicaoDoJogador[0] = (int)i; posicaoDoJogador[1] = (int)j; break;}

        }
    }
}

void MoverJogador (void) {

    quantasVezesMoveu++;

    DescobrirPosicaoDoJogador();

    char armazenamento;

    switch (optionGame) {

        case 'C':
            armazenamento = matrizPrincipal[posicaoDoJogador[0] - 1][posicaoDoJogador[1]];
            matrizPrincipal[posicaoDoJogador[0] - 1][posicaoDoJogador[1]] = ' ';
            matrizPrincipal[posicaoDoJogador[0]][posicaoDoJogador[1]] = armazenamento;
            break;

        case 'B':
            armazenamento = matrizPrincipal[posicaoDoJogador[0] + 1][posicaoDoJogador[1]];
            matrizPrincipal[posicaoDoJogador[0] + 1][posicaoDoJogador[1]] = ' ';
            matrizPrincipal[posicaoDoJogador[0]][posicaoDoJogador[1]] = armazenamento;
            break;

        case 'E':
            armazenamento = matrizPrincipal[posicaoDoJogador[0]][posicaoDoJogador[1] - 1];
            matrizPrincipal[posicaoDoJogador[0]][posicaoDoJogador[1] - 1] = ' ';
            matrizPrincipal[posicaoDoJogador[0]][posicaoDoJogador[1]] = armazenamento;
            break;

        case 'D':
            armazenamento = matrizPrincipal[posicaoDoJogador[0]][posicaoDoJogador[1] + 1];
            matrizPrincipal[posicaoDoJogador[0]][posicaoDoJogador[1] + 1] = ' ';
            matrizPrincipal[posicaoDoJogador[0]][posicaoDoJogador[1]] = armazenamento;
            break;


    }
}

void Verificar (void) {

    char matrizPerfeita[8][3][3] = {{{"123"},{"456"},{"78 "}}, // → pr ↓
                                    {{" 12"},{"345"},{"678"}}, // → pr ↓ ☆
                                    {{"167"},{"258"},{"34 "}}, // ↓ pr →
                                    {{" 56"},{"147"},{"238"}}, // ↓ pr → ☆
                                    {{"78 "},{"654"},{"123"}}, // → pr ↑
                                    {{"678"},{"543"},{" 12"}}, // → pr ↑ ☆
                                    {{"123"},{"8 4"},{"765"}}, // → va ↓
                                    {{"812"},{"7 3"},{"654"}}, // → va ↓ ☆
    };

    int verificadorDeErros[8] = {0,0,0,0,0,0,0,0};

    for (int m=0; m<8; m++) {

        for (int i=0; i<3; i++) {

            for (int j=0; j<3; j++) {

                if (matrizPrincipal[i][j] == matrizPerfeita[m][i][j]) {} else {verificadorDeErros[m]++;}

            }
        }
    }

    for (int i=0; i<8; i++) {

        if (verificadorDeErros[i] == 0) {oJogoAcabou = 1;}

    }

}

//  ############ Declaração de Funções de Menus

void MenuInicial (void) {
    limpar(45);
    printf ("||| JOGO DE LETRINHAS |||");
    printf ("\n| Feito por Rafael Neuwirth");
    limpar(3);
    printf ("| ADAPTADO PARA WINDOWS CMD \\ CODEBLOCKS");
    limpar(3);
    printf ("\n[DIGITE 1] Iniciar Jogo");
    printf ("\n[DIGITE 2] Como Jogar");
    printf ("\n[DIGITE 3] Dicas");

    limpar(2);

    scanf ("%d",&optionMenu);

    int permitido[] = {1,2,3};
    InsiraComandoInt(permitido);
    if (optionMenu == 1) { /* the game will start automatically */ }
    if (optionMenu == 2) { ComoJogarTela(); }
    if (optionMenu == 3) { TelaDeDicas(); }

}

void ComoJogarTela (void) {

    limpar(45);
    printf ("[!] Regras do Jogo:");
    limpar(3);
    printf ("\n[*] Voce recebera uma matriz composta por nove espacos.");
    printf ("\n[*] Oito serao numeros, um sera um espaco vazio.");
    printf ("\n[*] Voce pode mover para Cima, Baixo, Esquerda e Direita.");
    printf ("\n[*] Seu objetivo se baseia em colocar os numeros na sequencia correta.");
    printf ("\n[*] Voce controla o espaco vazio, se movimentando.");
    limpar(3);
    printf ("[DIGITE 1] Voltar ao Menu Inicial");

    limpar(3);

    scanf ("%d",&optionMenu);

    int permitido[] = {1};
    InsiraComandoInt(permitido);
    MenuInicial();

}

void TelaDeDicas (void) {

    limpar(45);
    printf ("[!] Dicas:");
    limpar(3);
    printf ("\n[*] Voce pode controlar o jogo com C, E, B, D.\n");
    printf ("\n[*] Voce pode controlar o jogo com W, A, S, D, o Padrao dos Jogos.\n");
    printf ("\n[*] Se voce Verificou e nada aconteceu, provavelmente a Ordem não foi aceita.\n");
    printf ("\n[*] Caso tente se mover para um espaco que nao existe, nada ira acontecer.\n");
    printf ("\n[*] Reiniciar o Jogo ira embaralhar a Matriz novamente.\n");
    printf ("\n[*] Voce pode fazer \"Combos de Movimento\", ao inserir por exemplo \"CE\"");
    printf ("\nou \"WA\" (Para Cima, e apos Esquerda) voce ira fazer os dois movimentos");
    printf ("\nem uma unica jogada (P.S: Voce nao pode se mover Diagonalmente).");
    limpar(3);
    printf ("[DIGITE 1] Voltar ao Menu Inicial");

    limpar(3);

    scanf ("%d",&optionMenu);

    int permitido[] = {1,2,3};
    InsiraComandoInt(permitido);
    MenuInicial();

}

void TelaDeAviso (void) {

    limpar(45);
    printf ("\t\t\t\t[!] AVISO [!]");
    limpar(4);
    printf ("\n[*] Por favor, estenda a Tela do Terminal de Comando");
    printf ("\npara a esquerda e para direita, a fim de preencher por");
    printf ("\ninteiro sua tela, evitando problemas com textos cortados.");
    limpar(3);
    printf ("\n[*] Esta Versao esta adaptada para Windows CMD e\\ou Codeblocks,");
    printf ("\npois nao possui acentuacao e tem algumas modificacoes relacionadas");
    printf ("\na posicionamento de caracteres.");

    limpar(4);

    printf ("[ENTER] Entrar no Jogo.");

    limpar(4);

    scanf ("%c",&optionGame);

}

void TelaDeVitoria (void) {

    limpar(45);
    printf ("[+] VITORIA!");
    limpar(2);
    printf ("[+] Voce completou o Jogo!");
    limpar(3);
    printf ("\n[?] Quantidade de Vezes que se Movimentou (TOTAL): %d",quantasVezesMoveu);
    printf ("\n[?] Quantidade de Vezes que Reiniciou a Matriz: %d",quantasVezesReiniciou);
    limpar(4);
    printf ("[ENTER] Finalizar Jogo");
    limpar(2);

    scanf ("%c",&optionGame);
    scanf ("%c",&optionGame);

}

//  ############ JOGO

int main () {

    srand(time(NULL));

    setlocale(LC_ALL, "Portuguese");

    TelaDeAviso();

    MenuInicial();

    EmbaralharMatriz(*matrizPrincipal, 9);

    while (oJogoAcabou == 0) {ExibirMatriz();}

    TelaDeVitoria();
    return 0;

}