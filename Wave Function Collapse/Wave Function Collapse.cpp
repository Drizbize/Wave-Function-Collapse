#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>

const int MAP_SIZE_X = 100;
const int MAP_SIZE_Y = 50;
const int COUNT_OF_WATER = 10;

enum Color
{
    Green = 10,
    Blue = 9,
    Yellow = 14,
    White = 7
};

void RenderMap(char** &map, HANDLE &hConsole)
{
    int previous = Color::White;
    for (int y = 0; y < MAP_SIZE_Y; y++)
    {
        for (int x = 0; x < MAP_SIZE_X; x++)
        {
            if (map[y][x] == 'L' && previous != Color::Green)
            {
                SetConsoleTextAttribute(hConsole, Color::Green);
                previous = Color::Green;
            }
            else if (map[y][x] == 'C' && previous != Color::Yellow)
            {
                SetConsoleTextAttribute(hConsole, Color::Yellow);
                previous = Color::Yellow;
            }
            else if (map[y][x] == 'S' && previous != Color::Blue)
            {
                SetConsoleTextAttribute(hConsole, Color::Blue);
                previous = Color::Blue;
            }
            std::cout << map[y][x];
        }
        std::cout << "\n";
    }
    SetConsoleTextAttribute(hConsole, Color::White);
}

void RerenderMap(char** &map)
{
    for (int y = 0; y < MAP_SIZE_Y; y++)
    {
        for (int x = 0; x < MAP_SIZE_X; x++)
        {
            if (map[y][x] == 'S')
            {
                bool isWater = true;
                if (y != 0)
                {
                    if (map[y - 1][x] == 'S')
                    {
                        isWater = false;
                    }
                }
                else if (y != MAP_SIZE_Y)
                {
                    if (map[y + 1][x] == 'S')
                    {
                        isWater = false;
                    }
                }

                if (isWater)
                {
                    int size = 0;
                    if (y != 0)
                    {
                        if (map[y - 1][x] == 'L')
                        {
                            map[y - 1][x] = 'C';
                        }
                    }

                    for (int Y = y; Y < MAP_SIZE_Y; Y++)
                    {
                        map[Y][x] = 'S';
                        for (int i = 1; i <= size; i++)
                        {
                            map[Y][x + i] = 'S';
                            map[Y][x - i] = 'S';
                        }

                        if (map[Y][x + size + 1] == 'L')
                        {
                            map[Y][x + size + 1] = 'C';
                        }

                        if (map[Y][x - size - 1] == 'L')
                        {
                            map[Y][x - size - 1] = 'C';
                        }
                        size++;
                    }
                }
            }
        }
    }
}

int main()
{
    srand(time(0));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    char** map = new char* [MAP_SIZE_Y];
    for (int i = 0; i < MAP_SIZE_Y; i++)
    {
        map[i] = new char[MAP_SIZE_X];
    }

    for (int y = 0; y < MAP_SIZE_Y; y++)
    {
        for (int x = 0; x < MAP_SIZE_X; x++)
        {
            map[y][x] = 'L';
        }
    }

    int CountOfSpawnedWater = 0;
    while (CountOfSpawnedWater < COUNT_OF_WATER)
    {
        int RandX = rand() % (MAP_SIZE_X);
        int RandY = rand() % (MAP_SIZE_Y);
        if (map[RandY][RandX] != 'S')
        {
            map[RandY][RandX] = 'S';
            CountOfSpawnedWater++;

            RerenderMap(map);
        }
    }

    RenderMap(map, hConsole);
    
    return 0;
}
