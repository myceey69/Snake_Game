// Snake_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver; 
const int width = 25; 
const int height = 15; 
int x, y, fruitX, fruitY, score; 
int tailX[100], tailY[100];
int nTail; 
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir; 
char answer = 'y';
int gameMode; 

void Setup();
void Frame();
void Controls();
void Logic();

int main()
{
    cout << "WELCOME TO THE SNAKE_GAME\n\n";
    cout << "Enter Game Mode ((1)) for Creative or ((2)) for Survival: "; 
        cin >> gameMode; 

    switch (gameMode) {
    case 1:
       while (answer) {
        Setup();
        while (!gameOver)
        {

           Frame();
           Controls();
           Logic();
           Sleep(60); //sleep(10); 
        }
    }
        break; 

    case 2:
            Setup();
            while (!gameOver)
            {

                Frame();
                Controls();
                Logic();
                Sleep(60); //sleep(10); 
            }
            
        break; 
    }

    return 0; 

}


void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;

}

void Frame()
{
    system("cls");
    for (int i{ 0 }; i < width + 2; i++)
        std::cout << "^";
    std::cout << std::endl;

    for (int i{ 0 }; i < height; i++)
    {
        for (int j{ 0 }; j < width; j++)
        {
            if (j == 0)
                std::cout << "^";
            //else
            if (i == y && j == x)
                std::cout << "O";
            else if (i == fruitY && j == fruitX)
                std::cout << "@";
            else {
                bool print = false;
                for (int k{ 0 }; k < nTail; k++)
                {

                    if (tailX[k] == j && tailY[k] == i)
                    {
                        std::cout << "o";
                        print = true;
                    }

                }

                if (!print)
                    std::cout << " ";
            }

            if (j == width - 1)
                std::cout << "^";
        }
        std::cout << std::endl;

    }

    for (int i{ 0 }; i < width + 2; i++)
        std::cout << "^";
    std::cout << std::endl;
    std::cout << "SCORE: " << score << std::endl;


}

void Controls()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;

        case 'w':
            dir = UP;
            break;

        case 's':
            dir = DOWN;
            break;

        case 'q':
            gameOver = true;
            break;
        }
    }

}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i{ 1 }; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;


    }
    switch (dir)
    {

    case LEFT:
        x--;
        break;

    case RIGHT:
        x++;
        break;

    case UP:
        y--;
        break;

    case DOWN:
        y++;
        break;

    default:
        break;
    }

    if (x > width || x < 0 || y > height || y < 0)
        gameOver = true;

    for (int i{ 0 }; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 1;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
