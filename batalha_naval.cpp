#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <new>
#include <string>
#include <time.h>

using namespace std;

struct Tabuleiro{
    char pos[10][10];
};

struct Player{
    string name;
    int score;
};


#ifdef __unix__
    #include <unistd.h>
    #include <stdlib.h>

#elif defined(_WIN32) || defined(WIN32)

   #define OS_Windows

   #include <windows.h>

#endif

struct Colors{
    string BLUE = "\033[34m";
    string RED = "\033[31m";
    string GREEN = "\033[32m";
    string RESET = "\033[0m";
};

void beep(){
    #ifdef OS_Windows
        Beep(523, 500);
        cin.get();
    #else
        system("echo -ne '\007'");
        sleep(0.5);
    #endif

}

void clearScreen(){
    #ifdef OS_Windows
      system("cls");
    #else
      system("clear");
    #endif // OS_Windows

}

void initTab(Tabuleiro *tabuleiro, Tabuleiro *mask){
    for (int line = 0; line < 10; line++){
        for (int column = 0; column < 10; column++){
            tabuleiro->pos[line][column] = 'A';
            mask->pos[line][column] = '*';
        }
    }

}

void showTab(Tabuleiro *tabuleiro, Tabuleiro *mask, string *feedback, Colors *colors){
       cout << *feedback << endl;
       for (int cont = 0; cont < 10; cont++){
        if (cont == 0){
            cout << "    ";
        }
        cout << cont << " ";
       }
       cout << endl;

       for (int cont = 0; cont < 10; cont ++){
          if (cont == 0)
            cout << "    ";
          cout << " |";
       }
       cout << endl;

       for (int line = 0; line < 10; line++){
            cout << line << " - ";
        for (int column=0; column < 10; column++){
            //cout << tabuleiro->pos[line][column]<< " ";
        switch(mask->pos[line][column]){
        case 'A':
            cout << colors->BLUE << mask->pos[line][column] << colors->RESET << " ";
            break;
        case 'P':
            cout << colors->GREEN << mask->pos[line][column] << colors->RESET << " ";
            break;
        default:
            cout << mask->pos[line][column] << " ";
            break;
        }

    }
    cout << endl;
}
}

void putShips(Tabuleiro *tabuleiro){
    int qtd = 10; int aux = 0;
    while (aux < qtd){

        int lineShip = rand() % 10;
        int columnShip = rand() % 10;

        if(tabuleiro->pos[lineShip][columnShip] == 'A'){
            tabuleiro->pos[lineShip][columnShip] = 'P';
            aux++;
        }

    }

}

void verifyShot(Tabuleiro *tabuleiro, int *score, int *line, int *column, string *feedback){
    *feedback = "";
    switch(tabuleiro->pos[*line][*column]){
    case 'P':
        beep();
        *score = *score + 1;
        *feedback = "Você acertou um navio!";
        tabuleiro->pos[*line][*column] = 'X';
    }
    cout << endl << *feedback  << endl;
}

void verifyChoice(int *val){
    while (*val < 0 || *val > 9){
        cout << "Digite um valor válido: ";
        cin >> *val;
    }
}

void showMenu();

void play(Player *player){
    clearScreen();
    Colors *colors = new Colors;
    Tabuleiro *tabuleiro = new Tabuleiro;
    Tabuleiro *mask = new Tabuleiro;
    cout << "Iniciando o jogo, " << player->name << endl;
    sleep(2);
    clearScreen();
    int score = 0; int attempts = 0; int max_attempts = 15;
    int *esc = new int;
    string feedback;

    initTab(tabuleiro, mask);
    putShips(tabuleiro);

    int *line = new int; int *column = new int;
    int state = 1;

    while (state){
        clearScreen();
        showTab(tabuleiro, mask, &feedback, colors);

    if (attempts == max_attempts){
        cout << endl << "Fim de jogo!" << endl;
        cout << "Pontuação: " << score << endl;
        player->score = score;
        int last_score = score;
        break;
    }

    cout << "Score: " << score << endl;
    cout << "Tentativas: " << max_attempts - attempts << endl;

    cout << "Digite uma linha, " << player->name << " [0-9]: ";
    cin >> *line;
    verifyChoice(line);
    cout << "Digite uma coluna[0-9]: ";
    cin >> *column;
    verifyChoice(column);

    verifyShot(tabuleiro, &score, line, column, &feedback);
    attempts++;

    mask->pos[*line][*column] = tabuleiro->pos[*line][*column];
    }

    cout << "Selecione uma opção:" << endl << "1 - Jogar novamente" << endl << "2 - Menu inicial" << endl << "3 - Sair" << endl;

    cin >> *esc;

    switch(*esc){
    case 1:
        play(player);
        break;
    case 2:
        showMenu();
        break;
    case 3:
        break;
    }


}

void showMenu(){
    clearScreen();
    Player *player = new Player;
    cout << "Digite o seu nome: ";
    cin >> player->name;
    int *option = new int;

    cout << "Bem-vindo ao jogo, " << player->name << "!" << endl << "1 - Jogar" << endl << "2 - Sobre" << endl << "3 - Sair" << endl;
    cout << "Escolha uma opção e tecle ENTER:";

    cin >> *option;

    while (*option < 1 || *option > 3){
        cout << "Digite um valor válido!";
        cin >> *option;
    }

    switch(*option){
    case 1:
        //Inicia o jogo
        play(player);
        break;
    case 2:
        cout << "Informações do jogo";
        break;
    case 3:
        cout << "Até mais";
        break;
    }

}

int main(){
    srand ((unsigned)time(NULL));
    setlocale(LC_ALL, "");
    showMenu();


    return 0;
}
