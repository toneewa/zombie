#include <cstdio>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
using namespace std;

bool zmbexist(vector<vector<int> >& sqarep, int posx, int posy);
int nrzombies(vector<vector<int> >& plain);
void display(vector<vector<int> >& terain);
bool movezombies(vector<vector<int> >& plain);
bool smartmovezombies(vector<vector<int> >& plain);
bool play(int nrz, int nrholes, vector<vector <int> >& plain);

int main()
{
    srand(time(NULL));
    vector<vector<int> > vectx;
    //initialise the vector
    vectx.resize(10);
    for (int i = 0; i < 10; i++)
    {
        vectx[i].resize(10, 0);
    }

    //convention : hole number is 3 , zombie number is 2, and human number is 1;
    //ask for nr of houls
    int nrholes;
    cout << "number of holes(0 for random) : ";
    cin >> nrholes;
    //if type 0 , then the nr of houls is generated automaticaly
    if (!nrholes)
    {
        nrholes = (rand() % 9) + 1;
    }

    //place the houls

    for (int i = 0; i < nrholes;)
    {
        int xhol = rand() % 10;
        int yhol = rand() % 10;
        if (vectx.at(xhol).at(yhol) == 0)
        {
            vectx.at(xhol).at(yhol) = 3;
            i++;
        }

    }

    //ask for nr of zombies
    int nrzombies;
    cout << "number of zombies(0 for random) : ";
    cin >> nrzombies;
    //if nr is 0, then is generated automaticaly
    if (!nrzombies)
    {
        nrzombies = (rand() % 9) + 1;
    }
    for (int i = 0; i < nrzombies;)
    {
        int xhol = rand() % 10;
        int yhol = rand() % 10;
        if (vectx.at(xhol).at(yhol) == 0)
        {
            vectx.at(xhol).at(yhol) = 2;
            i++;
        }
    }

    cout << "now we place the man";
    for (;;)
    {
        int xhol = rand() % 10;
        int yhol = rand() % 10;
        if (vectx.at(xhol).at(yhol) == 0)
        {
            vectx.at(xhol).at(yhol) = 1;
            break;
        }
    }
    display(vectx);
    play(nrzombies, nrholes, vectx);
    cin.ignore(255, '\n');
    return 0;
}

bool zmbexist(vector<vector<int> >& sqarep, int posx, int posy)
{
    if (sqarep[posx][posy] == 2)
        return true;
    else
        return false;

}
int nrzombies(vector<vector<int> >& plain)
{
    int nrzmb = 0;
    for (size_t i = 0; i < plain.size(); i++)
        for (size_t j = 0; j < plain[i].size(); j++)
        {
            if (plain[i][j] == 2)
                nrzmb++;
        }
    return nrzmb;
}
void display(vector<vector<int> >& terain)
{

    system("cls");
    cout << endl;
    for (size_t i = 0; i < terain.size(); i++)
    {
        for (size_t j = 0; j < terain[i].size(); j++)
        {
            switch (terain[i][j])
            {
            case -1:
                cout << " D ";
                break;
            case 0:
                cout << " * ";
                break;
            case 1:
                cout << " M ";
                break;
            case 2:
                cout << " Z ";
                break;
            case 3:
                cout << " G ";
                break;
            default:
                cout << " E ";
                break;
            }
        }
        cout << endl;
    }

    // Sleep(5000);
}
bool movezombies(vector<vector<int> >& plain)
{
    bool dead, zombiemove;
    for (size_t i = 0; i < plain.size(); i++)
    {
        for (size_t j = 0; j < plain[i].size(); j++)
        {
            //make sure that all the zombie moves

            if (plain[i][j] == 2)
            {
                zombiemove = false;
                while (!zombiemove)
                {
                    int rndmove = rand() % 4 + 1;
                    cout << rndmove << "\n";
                    // Sleep(1000);
                    cout << "now move zombie \n";
                    //move up if is possible

                    if (rndmove == 1)
                    {
                        cout << "move up \n";
                        if (i > 1)
                        {
                            if (plain[i - 1][j] == 3)
                            {
                                plain[i][j] = 0;
                                zombiemove = true;
                                //  break;
                            }
                            else if (plain[i - 1][j] == 1)
                            {
                                dead = true;
                                //return true;
                                zombiemove = true;

                            }
                            else if (plain[i - 1][j] == 0)
                            {
                                plain[i][j] = 0;
                                plain[i - 1][j] = 5;
                                zombiemove = true;
                                //break;

                            }
                        }
                    }
                    //move down if is possible
                    if (rndmove == 2)
                    {
                        cout << "move down \n";
                        if (i < 9)
                        {
                            if (plain[i + 1][j] == 3)
                            {
                                plain[i][j] = 0;
                                zombiemove = true;
                                //break;
                            }
                            else if (plain[i + 1][j] == 1)
                            {
                                dead = true;
                                //return true;
                                zombiemove = true;
                                //break;
                            }
                            else if (plain[i + 1][j] == 0)
                            {
                                plain[i][j] = 0;
                                plain[i + 1][j] = 5;
                                zombiemove = true;
                                //break;

                            }
                        }
                    }
                    //move left if is possible
                    if (rndmove == 3)
                    {
                        cout << "move left \n";
                        if (j > 1)
                        {
                            if (plain[i][j - 1] == 3)
                            {
                                plain[i][j] = 0;
                                zombiemove = true;
                                //break;
                            }
                            else if (plain[i][j - 1] == 1)
                            {
                                dead = true;
                                zombiemove = true;
                                //return true;
                            }
                            else if (plain[i][j - 1] == 0)
                            {
                                plain[i][j] = 0;
                                plain[i][j - 1] = 5;
                                zombiemove = true;
                                //  break;
                            }
                        }
                    }
                    //move left if is possible
                    if (rndmove == 4)
                    {
                        cout << "move right \n";
                        if (j < 9)
                        {
                            if (plain[i][j + 1] == 3)
                            {
                                plain[i][j] = 0;
                                zombiemove = true;
                                //break;
                            }

                            else if (plain[i][j + 1] == 1)
                            {
                                dead = true;
                                //  return true;
                                zombiemove = true;
                            }
                            else if (plain[i][j + 1] == 0)
                            {
                                plain[i][j] = 0;
                                plain[i][j + 1] = 5;
                                zombiemove = true;
                                //  break;
                            }
                        }
                    }
                }//end while
            }
        }
    }
    //}
    for (size_t i = 0; i < plain.size(); i++)
    {
        for (size_t j = 0; j < plain[i].size(); j++)
        {
            if (plain[i][j] == 5)
                plain[i][j] = 2;
        }
    }
    return false;
}
bool movehuman(vector<vector<int> >& plain)
{
    char move;
    bool dead;
    bool pmove = false;
    int x = 0, y = 0;
    for (size_t i = 0; i < plain.size(); i++)
        for (size_t j = 0; j < plain[i].size(); j++)
        {
            if ((plain[i][j]) == 1)
            {
                x == i;
                y == j;
            }

        }

    while (!pmove)
    {
        system("cls");
        display(plain);
        cout << "move human (2=down,8=up,4=left,6=right): ";
        cin >> move;
        cout << move;
        if (move == 52)
        {
            if (y > 0)
            {
                if ((plain[x][y - 1] == 3) || (plain[x][y - 1] == 2))
                {
                    cout << "is mort acuma2";
                    Sleep(2000);
                    dead = true;
                    //  return dead;
                }
                plain[x][y] = 0;
                plain[x][y - 1] = 1;
                y--;
                pmove = true;
            }

        }

        if (move == 54)
        {
            if (y < 9)
            {
                if ((plain[x][y + 1] == 3) || (plain[x][y + 1] == 2))
                {
                    return true;
                }
                plain[x][y] = 0;
                plain[x][y + 1] = 1;
                y++;
                pmove = true; 
            }

        }
        if (move == 56)
        {
            if (x > 0)
            {
                if ((plain[x - 1][y] == 3) || (plain[x - 1][y] == 2))
                {
                    return true;
                }
                plain[x][y] = 0;
                plain[x - 1][y] = 1;
                x--;
                pmove = true;
            }

        }

        if (move == 50)
        {
            if (x < 9)
            {
                if ((plain[x + 1][y] == 3) || (plain[x + 1][y] == 2))
                {
                    return true;
                }
                plain[x][y] = 0;
                plain[x + 1][y] = 1;
                x++;
                pmove = true;
            }

        }
    }
    return dead;
}
bool smartmovezombies(vector<vector<int> >& plain)
{

    size_t x = 0;
    size_t y = 0;

    //get human position

    for (size_t i = 0; i < plain.size(); i++)
    {
        for (size_t j = 0; j < plain[i].size(); j++)
        {
            if (plain[i][j] == 1)
            {
                x = i;
                y = j;
                break;
            }
        }
    }
    //for everyzombie possition calculate how to get closer to human quickly
    for (size_t i = 0; i < plain.size(); i++)
        for (size_t j = 0; j < plain[i].size(); j++)
        {
            if (plain[i][j] == 2)
            {

                if ((i > x) && (j > y))
                {
                    if (i - x > j - y)
                        if (plain[i - 1][j] == 2)
                            plain[i][j] = 0;
                        else
                        {
                            if (i > 1)
                            {
                                plain[i][j] = 0;
                                plain[i - 1][j] = 5;
                            }
                        }

                    else
                    {
                        if (plain[i][j - 1] == 2)
                            plain[i][j] = 0;
                        else
                        {
                            if (j > 1)
                            {
                                plain[i][j] = 0;
                                plain[i][j - 1] = 5;
                            }
                        }

                    }

                }

                if ((i < x) && (j < y))
                {
                    if (i - x > j - y)
                        if (plain[i + 1][j] == 2)
                            plain[i][j] = 0;
                        else
                        {
                            if (i < 10)
                            {
                                plain[i][j] = 0;
                                plain[i + 1][j] = 5;
                            }
                        }

                    else
                    {
                        if (plain[i][j + 1] == 2)
                            plain[i][j] = 0;
                        else
                        {
                            if (j < 10)
                            {
                                plain[i][j] = 0;
                                plain[i][j + 1] = 5;
                            }
                        }

                    }

                }

                if ((i < x) && (j > y))
                {
                    if (i - x > j - y)
                        if (plain[i + 1][j] == 2)
                            plain[i][j] = 0;
                        else
                        {
                            if (i < 10)
                            {
                                plain[i][j] = 0;
                                plain[i + 1][j] = 5;
                            }
                        }

                    else
                    {
                        if (plain[i][j - 1] == 2)
                            plain[i][j] = 0;
                        else
                        {
                            if (j > 1)
                            {
                                plain[i][j] = 0;
                                plain[i][j - 1] = 5;
                            }
                        }

                    }

                }

                if ((i > x) && (j < y))
                {
                    if (i - x > j - y)
                        if (plain[i - 1][j] == 2)
                            plain[i][j] = 0;
                        else
                        {
                            if (i > 1)
                            {
                                plain[i][j] = 0;
                                plain[i - 1][j] = 5;
                            }
                        }

                    else
                    {
                        if (plain[i][j + 1] == 2)
                            plain[i][j] = 0;
                        else
                        {
                            if (j > 1)
                            {
                                plain[i][j] = 0;
                                plain[i][j + 1] = 5;
                            }
                        }

                    }

                }

                if ((plain[i - 1][j] == 1) || (plain[i + 1][j] == 1) || (plain[i][j + 1] == 1) || (plain[i][j - 1] == 1))
                {
                    return true;
                }
            }

        }
    for (size_t i = 0; i < plain.size(); i++)
        for (size_t j = 0; j < plain[i].size(); j++)
        {
            if (plain[i][j] == 5)
                plain[i][j] = 2;

        }
    return false;

}
bool play(int nrz, int nrholes, vector<vector<int> >& plain)
{
    bool dead, endgame;
    endgame = false;
    dead = false;
    while (true)
    {
        endgame = smartmovezombies(plain);
        dead = movehuman(plain);
        nrz = nrzombies(plain);
        if (dead = true)
        {
            cout << "human dead";
            exit(1);
        }
        if (nrz == 0)
        {
            cout << "human win";
            exit(1);
        }
    }
    return true;
}
