// Библиотеки
#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>
#include <random>

using namespace std;

// Прототипы
void display();
void XStep();
void OStep();
void PCStep();
char FindWinner();
void PvE();
void PvP();
void Help();
void EndGame();
char CheckArgs(string input);
bool CheckInput(char input);
void RunString(string str, int time);
int Counter(char symbol);

// Глобальные переменные
string Hello = "Добро пожаловать в игру Tic-Tac-Toe!\n\n";
string Menu = "Меню игры\n1) PvE (Против компьютера)\n2) PvP (Против человека)\n3) Как играть?\n4) Выйти из игры";
string helps[] = {
    "Помощь по игре",
    "Крестики-Нолики - это логическая игра между двумя противниками на квадратном поле 3x3 клетки",
    "Игра рассчитана на двоих человек – один играет за крестики, другой за нолики.",
    "Игрок, играющий за Крестики имеет право первоочередного хода.",
    "Игроки ходят поочереди.",
    "Выигрывает тот игрок, кто соберёт связку из 3 идущих подряд одиннаковых символов"
};

char Board[9] = {
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' '
};

// Main
int main()
{
    setlocale(LC_ALL, "Russian");
    RunString(Hello, 50);
    RunString(Menu, 10);
    string chooose;

    while (true) {
        cout << "\n> ";
        getline(cin, chooose);
        int selected;
        char s = CheckArgs(chooose);
        if (CheckInput(s)) {
            selected = s - '0';
        }
        else {
            selected = 0;
        }
        switch (selected) {
            case 1:
                system("cls");
                PvE();
                break;
            case 2:
                system("cls");
                PvP();
                break;
            case 3:
                system("cls");
                Help();
            case 4:
                exit(0);
            default:
                cout << "Выбранного пункта [" << selected << "] нет в меню!\nПопробуйте ещё раз!" << endl;
        }
    }
    return 0;
}


// Функции
char CheckArgs(string input) {
    /*
        Функция позволяет вводить только 1 символ как аргумент

        Args:
        -----
        `input` - str:
            Строка, которую нужно проверить

        Example:
        --------
        getline(cin, input);
        char s = CheckArgs(input);
    */
    int MaxLenArgs = 1;
    if (input.length() == 1) {
        return (char)input.at(0);
    } else if (input.length() > 1) {
        return (char)input.at(0);
    }
}


void RunString(string str, int time) {
    /*
        Функция позволяет создать "Бегущую строку"

        Args:
        -----
        string str:
            Строка, которую нужно "пробежать"
        double time:
            Время (млсек) печатания символа

        Example:
        --------
        string greet = "Hello World!";
        RunString(greet, 20);
    */
    for (int i = 0; i <= str.length() - 1; i++) {
        cout << str[i];
        Sleep(time);
    }
}


void display() {
    /*
    Функция отображения всего игрового поля
    */

    system("cls");
    cout << "     |     |     " << endl;
    cout << "  " << Board[0] << "  |  " << Board[1] << "  |  " << Board[2] << "  " << endl;
    cout << "____1|____2|____3" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << Board[3] << "  |  " << Board[4] << "  |  " << Board[5] << "  " << endl;
    cout << "____4|____5|____6" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << Board[6] << "  |  " << Board[7] << "  |  " << Board[8] << "  " << endl;
    cout << "    7|    8|    9" << endl;
};


bool CheckInput(char input) {
    /*
    Функция проверки символа на число
    */
    if (!isalpha(input)) {
        return true;
    }
    else {
        return false;
    }
}


void XStep() {
    /*
    Функция "ходьбы" игрока с символом 'X'
    */

    string xStepChoose;
    while (true) {
        cout << "Клетка под номером: ";
        getline(cin, xStepChoose);
        int choice;
        char s = CheckArgs(xStepChoose);
        if (CheckInput(s)) {
            choice = s - '0';
            choice--;
            if (choice < 0 || choice > 8) {
                system("cls");
                display();
                cout << "Введите, пожалуйста, корректное число от 1 до 9" << endl;
            }
            else if (Board[choice] != ' ') {
                system("cls");
                display();
                cout << "Клетка [" << choice << "] уже занята\nИспользуйте другую" << endl;
            }
            else {
                Board[choice] = 'X';
                break;
            }
        }
    }
};


void OStep() {
    /*
    Функция "ходьбы" игрока с символом 'O'
    */

    string oStepChoose;
    while (true) {
        cout << "Клетка под номером: ";
        getline(cin, oStepChoose);
        int choice;
        char s = CheckArgs(oStepChoose);
        if (CheckInput(s)) {
            choice = s - '0';
            choice--;
            if (choice < 0 || choice > 8) {
                system("cls");
                display();
                cout << "Введите, пожалуйста, корректное число от 1 до 9" << endl;
            }
            else if (Board[choice] != ' ') {
                system("cls");
                display();
                cout << "Клетка [" << choice << "] уже занята\nИспользуйте другую" << endl;
            }
            else {
                Board[choice] = 'O';
                break;
            }
        }
    }
};


void PCStep() {
    /*
    Функция "ходьбы" Бота
    */

    srand(time(0));
    int RandInt;
    do {
        RandInt = rand() % 9;
    } while (Board[RandInt] != ' ');
    Board[RandInt] = 'O';
}


int Counter(char symbol) {
    /*
    Функция подсчёта
        - считает кол-во определённых символов на поле

    Args:
    -----
    symbol char - Искомый символ

    Returns:
    --------
    count int - Количество искомого символа на поле
    */

    int count = 0;
    for (int i = 0; i < 9; i++) {
        if (Board[i] == symbol) {
            count += 1;
        }
    };
    return count;
}


void PvE() {
    /*
    Функция организации игры PvE (Player vs Enviroment)
    */

    system("cls");
    cout << "Крестики-Нолики: Режим PvE" << endl;
    string Player;
    cout << "Введите свой никнейм: ";
    cin >> Player;
    while (true) {
        system("cls");
        display();
        if (Counter('X') == Counter('O')) {
            cout << "Ход игрока: " << Player << endl;
            XStep();
        }
        else {
            PCStep();
        }
        char WinnerInGame = FindWinner();
        if (WinnerInGame == 'X') {
            system("cls");
            display();
            cout << "\nИгрок " << Player << " выйграл Компьютер" << endl;
            Sleep(5000);
            EndGame();
            break;
        }
        else if (WinnerInGame == 'O') {
            system("cls");
            display();
            cout << "\nКомпьютер выйграл игрока " << Player << endl;
            Sleep(5000);
            EndGame();
            break;
        }
        else if (WinnerInGame == 'D') {
            system("cls");
            display();
            cout << "\nИгра закончилась ничьёй!" << endl;
            Sleep(5000);
            EndGame();
            break;
        }
    };
}


void EndGame() {
    /*
    Функция конца игры
        - очищает игровое поле
    */

    for (int i = 0; i < 9; i++) {
        Board[i] = ' ';
    }
    system("cls");
    RunString(Menu, 10);
}


void PvP() {
    /*
    Функция организации игры PvP (Player vs Player)
    */

    cout << "Крестики-Нолики: Режим PvP" << endl;
    string Player1, Player2;
    cout << "Игрок 1, введите свой никнейм: ";
    cin >> Player1;
    cout << "Игрок 2, введите свой никнейм: ";
    cin >> Player2;

    while (true) {
        system("cls");
        display();
        if (Counter('X') == Counter('O')) {
            cout << "Ход игрока: " << Player1 << endl;
            XStep();
        }
        else {
            cout << "Ход игрока: " << Player2 << endl;
            OStep();
        }
        char WinnerInGame = FindWinner();
        if (WinnerInGame == 'X') {
            system("cls");
            display();
            cout << "\nИгрок " << Player1 << " выйграл игрока " << Player2 << endl;
            Sleep(5000);
            EndGame();
            break;
        }
        else if (WinnerInGame == 'O') {
            system("cls");
            display();
            cout << "\nИгрок " << Player2 << " выйграл игрока " << Player1 << endl;
            Sleep(5000);
            EndGame();
            break;
        }
        else if (WinnerInGame == 'D') {
            system("cls");
            display();
            cout << "\nИгра закончилась ничьёй!" << endl;
            Sleep(5000);
            EndGame();
            break;
        }
    };
}


char FindWinner() {
    /*
    Функция определения исхода игры

    Returns:
    --------
    char = 'X' // or 'O' or 'D')
        'X' - победа Крестиков
        'O' - победа Ноликов
        'D' - ничья
    
    */

    // Horizontal`s
    if (Board[0] == Board[1] && Board[1] == Board[2] && Board[0] != ' ') {
        return Board[0];
    }
    if (Board[3] == Board[4] && Board[4] == Board[5] && Board[3] != ' ') {
        return Board[3];
    }
    if (Board[6] == Board[7] && Board[7] == Board[8] && Board[6] != ' ') {
        return Board[6];
    }

    // Vetical`s
    if (Board[0] == Board[3] && Board[3] == Board[6] && Board[0] != ' ') {
        return Board[0];
    }
    if (Board[1] == Board[4] && Board[4] == Board[7] && Board[1] != ' ') {
        return Board[1];
    }
    if (Board[2] == Board[5] && Board[5] == Board[8] && Board[2] != ' ') {
        return Board[2];
    }
    // Diagonal`s
    if (Board[0] == Board[4] && Board[4] == Board[8] && Board[0] != ' ') {
        return Board[0];
    }
    if (Board[2] == Board[4] && Board[4] == Board[6] && Board[2] != ' ') {
        return Board[2];
    }

    if (Counter(' ') < 1) {
        return 'D';
    }
}


void Help() {
    system("cls");
    for (int i = 0; i < 6; i++) {
        cout << helps[i] << endl;
    }
    Sleep(25000);
}