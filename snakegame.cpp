#include <iostream> // kninica iostream
#include <conio.h> // kninica conio.h (conInputOutput.h)
#include <windows.h> //kninica windows.h vïaka ktorej môme hru spomali

using namespace std;

bool gameOver; // premenná gameOver bude boolean
const int width = 20; // premenná width bude const integer (const = nedá sa zamieòa)
const int height = 20; // premenná height bude const integer
int x, y, fruitX, fruitY, score; // premenné x, y, fruitX, fruitY a score budú integer
int tailX[100], tailY[100]; // premenní tailX a tailY budú integer, s maximálnou hodnotou 100
int nTail; // premenná nTail bude integer, d¾ka chvostu hadíka
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN}; // enumeraèná premenná eDirection ktorá má hodnoty STOP = 0, LEFT, RIGHT, UP a DWON
eDirecton dir; //premenná dir (direction)

void Setup() // funkcia Setup
{
    gameOver = false; // gameOver nastavíme na False
    dir = STOP; // dir nadobudne hodnotu STOP aby hadík na zaèiatku hry stál na mieste
    x = width / 2; // x nadobudne hodnotu 10 (polovica width)
    y = height / 2; // y nadobudne hodnotu 10 (polovica height)
    fruitX = rand() % width; // x-ova pozicia ovocia ktoré sa náhodne spawne na hracej ploche
    fruitY = rand() % height; //y-ova pozicia ovocia ktoré sa náhodne spawne na hracej ploche
    score = 0; // defaultné skóre je 0
}

void Draw() //funkcia Draw
{
    system("cls"); // konzola sa vyèistí pred zapnutím hry
    for (int i = 0; i < width+2; i++) // vykreslíme hornú stranu mapy
        cout << "#"; //strana bude vykreslená ###
    cout << endl; //vykres¾ovanie sa posunie o riadok nišie
 
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0) // ak premenná j == 0, vykreslí nám # na ¾avı okraj hracej ploche
                cout << "#"; // vykreslí nám ###
            if (i == y && j == x) // ak i == y spolu aj j == x, vykreslí nám hlavu hada
                cout << "O"; // vykreslí nám O (Hlava hada)
            else if (i == fruitY && j == fruitX) //ak i == fruitY spolu aj j == fruitX, vykreslí nám ovocie
                cout << "F"; // vykresli nám F (Fruit)
            else
            {
                bool print = false; // premenná print ktorá bude boolean s hodnotou false
                for (int k = 0; k < nTail; k++) // loop v ktorom premenná k bude ma dåku chvostu
                {
                    if (tailX[k] == j && tailY[k] == i) // ak dåka chvosta X sa zhoduje so súradnicou j a zároveò dåka chvosta Y sa zhoduje so súradnicou i
                    {
                        cout << "o"; // vykreslíme chvost ako o
                        print = true; // print sa zmení na true ak sa vykreslí chvost hadíka
                    }
                }
                if (!print) // ak print ostane false
                    cout << " "; // vykreslí sa prázdnota
            }
                 
 
            if (j == width - 1) // ak premenná j == width - 1 (19), vykreslí # na pravı okraj hracej plochy
                cout << "#"; // vykreslí nám ###
        }
        cout << endl; //kreslenie prejde na ïalší riadok
    }
 
    for (int i = 0; i < width+2; i++) // vykreslíme dolnú stranu mapy
        cout << "#"; // strana bude vykreslená ###
    cout << endl; // vykres¾ovanie prejde o riadok nišie
    cout << "Score:" << score << endl; // na obrazovke nám to printne momentálne skóre
}

void Input()
{
    if (_kbhit()) // ak je stlaèená klávesa (kbhit = KeyBoardHIT)
    {
        switch (_getch()) // switch case (getch nám vráti boolean hodnotu pod¾a toho, èi sme stlaèili klávesu)
        {
        case 'a': // ak sme stlaèili a
            dir = LEFT; // hadik pôjde do¾ava, premenne dir sa zmení hodnota
            break; // case sa "breakne", èie hadik pôjde stále v¾avo
            
        case 'd': // ak sme stlaèili d
            dir = RIGHT; // hadik pôjde doprava, premenne dir sa zmení hodnota
            break; // case sa "breakne", èize hadik pôjde stále vpravo
            
        case 'w': //ak sme stlaèili w
            dir = UP; // hadik pôjde hore, premenne dir sa zmení hodnota
            break; // case sa "breakne", èize hadik pôjde stále hore
            
        case 's': // ak sme stlaèili s
            dir = DOWN; // hadik pôjde dole, premenne dir sa zmení hodnota
            break; // case sa "breakne", èie hadik pôjde stále dole
            
        case 'x': // ak sme stlaèili x
            gameOver = true; // hra sa skonèí
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0]; // premenná prevX, ktorá obsahuje minulú hodnotu X súradnice zaèiatku chvosta
    int prevY = tailY[0]; // premenná prevY, ktorá obsahuje minulú hodnotu Y súradnice zaèiatku chvosta
    int prev2X, prev2Y; // premenné prev2X, prev2Y, ktoré sú integer
    tailX[0] = x; // nastavíme aby prvá èas chvostu sledovala ssúradnicu X (hlavu hada)
    tailY[0] = y; // nastavíme aby prvá èas chvostu sledovala ssúradnicu Y (hlavu hada)
    for (int i = 1; i < nTail; i++) // loop na zväèšovanie chvostu hadíka
    {
        prev2X = tailX[i]; // prev2X bude ma hodnotu momentálnej súradnice X zaèiatku chvosta
        prev2Y = tailY[i]; // prev2Y nude ma hodnotu momentálnej súradnice Y zaèiatku chvosta
        tailX[i] = prevX; // zmeníme pôvodnu hodnotu na prevX
        tailY[i] = prevY; // zmeníme pôvodnu hodnotu na prevY
        prevX = prev2X; // aktualizujeme prevX na prev2X
        prevY = prev2Y; // aktualizujeme prevY na prev2Y
    }
    switch (dir) // zmeníme premennú dir
    {
    case LEFT: // ak hadik pôjde v¾avo
        x--; // hadikove súradnice sa zmenia 
        break;
        
    case RIGHT: // ak hadik pôjde vpravo
        x++; //hadikove súradnice sa zmenia
        break;
        
    case UP: // ak hadik pôjde hore
        y--; // hadikove súradnice sa zmenia
        break;
        
    case DOWN: // ak hadik pôjde dole
        y++; // hadikove súradnice sa zmenia
        break;
        
    default: // niè sa nestane (xd)
        break;
    }
    
    if (x >= width) x = 0; else if (x < 0) x = width - 1; // ak x bude viac ako šírka (20), x sa presunie na 0, a naopak
    if (y >= height) y = 0; else if (y < 0) y = height - 1; // ak y bude viac ako vıška (20), y sa presunie na 0, a naopak
 
    for (int i = 0; i < nTail; i++) // loop ktorı prejde kadú èast chvostu
        if (tailX[i] == x && tailY[i] == y) // ak sa hlava hadíka nabúra s hociakou èasou chvostu
            gameOver = true; // hra skonèi
 
    if (x == fruitX && y == fruitY) // ak súradnica hlavy hada je totoná so súradnicou ovocia (ak hadik zje jedlo)
    {
        score += 10; // skóre sa zvıši o 10
        fruitX = rand() % width; // x-ova pozicia ovocia ktoré sa náhodne spawne na hracej ploche
    	fruitY = rand() % height; //y-ova pozicia ovocia ktoré sa náhodne spawne na hracej ploche
        nTail++; // chvost sa zväèší o 1
    }
}
int main() // hlavná hra
{
    Setup(); // povoláme funkciu Setup
    while (!gameOver) // pokia¾ neni koniec hry
    {
        Draw(); // povoláme funkcie Draw(), Input(), Logic()
        Input();
        Logic();
        Sleep(10); // spoma¾uje hru
    }
    return 0;
}
