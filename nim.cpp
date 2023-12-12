#include <iostream>
#include <vector>
#include <time.h>
#include <windows.h>
#include <conio.h>

using namespace std;

bool end_game(vector<int> pole, int kuch);
vector<int> bot_step(vector<int> pole, int kuch);
void print(vector<int>, int k);
int nim_sum(vector<int> vec);

int main()
{
    int kuch, step, pile_index, stones;
    cout << "Введите количество кучек\t";
    cin >> kuch;
    cout << "Выберите кто ходит первым (1 - Вы; 0 - Компьютер)\t";
    cin >> step;
    vector<int> pole = {};

    srand(time(0));

    for (int i = 0; i < kuch; i++)
    {
        pole.push_back((rand() % (kuch) + 1) * 2);
    }

    print(pole, 1);

    while (end_game(pole, kuch) == false)
    {
        if (step == 1)
        {
            Sleep(1000);
            cout << "Ваш ход:\n";
            cout << "Выберите кучку\t";
            cin >> pile_index;
            pile_index -= 1;
            while ((pile_index < 0) or (pile_index > kuch) or (pole[pile_index] == 0))
            {
                cout << "Введите корректное значение!\n";
                cin >> pile_index;
                pile_index -= 1;
            }
            cout << "Выберите количество камней\t";
            cin >> stones;
            while ((stones < 0) or (stones > pole[pile_index]))
            {
                cout << "Введите корректное значение!\n";
                cin >> stones;
                cout << endl;
            }

            pole[pile_index] -= stones;

            step -= 1;
        }
        else
        {
            Sleep(1000);
            cout << "Ход Компьютера\n";
            int kuch_index = bot_step(pole, kuch)[0];
            int num_to_remove = bot_step(pole, kuch)[1];

            pole[kuch_index] -= num_to_remove;

            step += 1;
        }
        if (step == 1)
        {
            print(pole, 4);
        }
        else
        {
            print(pole, 1);
        }
    }

    if (step == 0)
    {
        cout << "Вы поберили!";
    }
    else
    {
        cout << "Вы проиграли(";
    }
    getch();
    return 0;
}

bool end_game(vector<int> pole, int kuch)
{
    int sum = 0;
    for (int i = 0; i < kuch; i++)
    {
        sum += pole[i];
    }
    if (sum == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

vector<int> bot_step(vector<int> pole, int kuch)
{
    int xor_sum = nim_sum(pole);

    for (int pile_index = 0; pile_index < kuch; pile_index++)
    {
        for (int j = 1; j < pole[pile_index] + 1; j++)
        {
            vector<int> temp = pole;
            temp[pile_index] = pole[pile_index] - j;
            if (nim_sum(temp) == 0)
            {
                return {pile_index, j};
            }
        }
    }

    int pile_index = rand() % kuch;
    while (pole[pile_index] == 0)
    {
        pile_index = rand() % kuch;
    }
    int pile_size = pole[pile_index];
    int num_to_remove = rand() % (pile_size) + 1;
    return {pile_index, num_to_remove};
}

void print(vector<int> vec, int k)
{
    Sleep(k * 600);
    cout << "___________________________________________________" << endl;
    for (int i = 0; i < vec.capacity(); i++)
    {
        cout << i + 1 << "-ая кучка " << vec[i] << endl;
    }
    cout << "___________________________________________________" << endl;
}

int nim_sum(vector<int> vec)
{
    int xor_sum = 0;
    for (int i = 0; i < vec.capacity(); i++)
    {
        xor_sum = xor_sum ^ vec[i];
    }

    return xor_sum;
}