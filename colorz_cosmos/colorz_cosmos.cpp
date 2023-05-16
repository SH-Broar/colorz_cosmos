#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <random>
#include <chrono>
#include <string>
#include <iomanip>

using namespace std;

long long xsize = 100;
long long ysize = 30;

long long speedation = 30;
long long frequency = 42;

long long cosmos = 0;
long long currmaxcosmos = 0;
long long maxcosmos = 0;
long long maxtotalcosmos = 0;
long long totalcosmos = 0;
long long ticks = 0;

int printType = 0;

string cons{};

struct Cell
{
    long long n;
    char p;
    int type;
    vector<bool> vec;

    Cell()
    {
        n = 1;
        p = '1';
        type = 1;
        vec.resize(4);
    }

    void init(int i)
    {
        n = i;
        p = i+'0';
        fill(vec.begin(), vec.end(), false);
    }

    void set(int nn, vector<bool>& v)
    {
        n = nn;
        vec = v;
    }

    const int& operator=(const int& i)
    {
        n = i;
        return n;
    }

    const int& operator+=(const int& i)
    {
        n += i;
        return n;
    }

    bool operator!=(const Cell& i)
    {
        return n != i.n;
    }

    bool operator ==(const int& i)
    {
        return n == i;
    }

    int vectorNums()
    {
        int i = 0;
        for (auto b : vec)
            if (b) i++;
        return i;
    }
};

vector<vector<Cell>> panel;
vector<vector<Cell>> printpanel;
vector<vector<Cell>> tmppanel;
default_random_engine dre;
uniform_int_distribution<int> uid;

void gotoxy(short x, short y)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y });
}

void pulser(long long i, long long j)
{
    if (printpanel[i][j].n)
    {
        cosmos++;
        int c = tmppanel[i][j].n;
        if (c > maxcosmos)
        {
            maxcosmos = c;
        }
        if (c > currmaxcosmos)
        {
            currmaxcosmos = c;
        }
        const auto& vv = tmppanel[i][j].vec;
        if (i > 0 && vv[0])
        {
            tmppanel[i - 1][j] += c;
            tmppanel[i - 1][j].vec[0] = true;
        }
        if (j > 0 && vv[1])
        {
            tmppanel[i][j - 1] += c;
            tmppanel[i][j - 1].vec[1] = true;
        }
        if (i < xsize - 1 && vv[2])
        {
            tmppanel[i + 1][j] += c;
            tmppanel[i + 1][j].vec[2] = true;
        }
        if (j < ysize - 1 && vv[3])
        {
            tmppanel[i][j + 1] += c;
            tmppanel[i][j + 1].vec[3] = true;
        }

        tmppanel[i][j].n = 0;
        fill(tmppanel[i][j].vec.begin(), tmppanel[i][j].vec.end(), false);
    }
}

int main()
{
    SetConsoleTitle(TEXT("numeric cosmos"));
    cout << "select 0 (default) / 1(custom) / 2(fullsize radiate) : ";
    int selection;
    cin >> selection;

    if (selection == 1)
    {
        cout << "xsize : ";
        cin >> xsize;
        cout << "ysize : ";
        cin >> ysize;
        cout << "speedation : ";
        cin >> speedation;
        cout << "frequency : ";
        cin >> frequency;
        cout << "printType : ";
        cin >> printType;
    }
    else if (selection == 2)
    {
        SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
        xsize = 238;
        ysize = 66;
        
        cout << "speedation : ";
        cin >> speedation;
        cout << "frequency : ";
        cin >> frequency;
        cout << "printType : ";
        cin >> printType;
    }

    panel.resize(xsize);
    printpanel.resize(xsize);
    tmppanel.resize(xsize);
    for (int i = 0; i < xsize; ++i)
    {
        panel[i].resize(ysize);
        printpanel[i].resize(ysize);
        tmppanel[i].resize(ysize);
    }

    if (!(selection == 2))
    {
        cons = "mode con lines=";
        if (xsize < 90)
            cons += to_string(ysize + 2);
        else
            cons += to_string(ysize + 1);
        cons += " cols=";
        cons += to_string(xsize);
        system(cons.c_str());
    }

    dre.seed(std::chrono::system_clock::now().time_since_epoch().count());

    for (int i = 0; i < xsize; ++i)
    {
        for (int j = 0; j < ysize; ++j)
        {
            panel[i][j].init(1);
            printpanel[i][j].init(0);
        }
    }

    cosmos = 0;
    currmaxcosmos = 0;
    totalcosmos = 0;

    long long counter = 0;

    while (true)
    {
        for (long long i = 0; i < xsize; ++i)
        {
            for (long long j = 0; j < ysize; ++j)
            {
                if (panel[i][j] != printpanel[i][j])
                {
                    gotoxy(i, j);

                    panel[i][j] = printpanel[i][j].n;

                   
                    if (printType == 1)
                    {
                        if (panel[i][j].n <= 0)
                            panel[i][j].p = '.';
                        else if (panel[i][j].n < 10)
                            panel[i][j].p = panel[i][j].n + '0';
                        else if (panel[i][j].n <= 10 + 26)
                            panel[i][j].p = 'a' + panel[i][j].n - 10;
                        else if (panel[i][j].n <= 10 + 26 + 260)
                            panel[i][j].p = 'A' + (panel[i][j].n - 36)/10;
                        else
                            panel[i][j].p = '*';
                    }
                    else if (printType == 0)
                    {
                        if (panel[i][j].n <= 0)
                            panel[i][j].p = '.';
                        else if (panel[i][j].n < 10)
                            panel[i][j].p = panel[i][j].n + '0';
                        else
                            panel[i][j].p = '9';
                    }

                    totalcosmos += printpanel[i][j].n * printpanel[i][j].vectorNums();

                    cout << panel[i][j].p;

                }
            }
        }
        if (totalcosmos > maxtotalcosmos)
            maxtotalcosmos = totalcosmos;

        gotoxy(0, ysize);

        string xx{};
        xx.resize(xsize, ' ');
        cout << xx;

        gotoxy(0, ysize);
        cout << "C : " << cosmos << " / M : " << maxcosmos << " / CM : " << currmaxcosmos << " / T : " << maxtotalcosmos << " / CT : " << totalcosmos << " / Ticks : " << ticks;

        counter++;
        ticks++;
        SleepEx(speedation, true);

        cosmos = 0;
        currmaxcosmos = 0;
        totalcosmos = 0;

        tmppanel = printpanel;
        for (long long i = 0; i < xsize; ++i)
        {
            for (long long j = 0; j < ysize; ++j)
            {
                pulser(i, j);
            }
        }
        printpanel = tmppanel;

        if (counter >= uid(dre) % frequency)
        {
            counter = 0;
            int rx = uid(dre) % xsize;
            int ry = uid(dre) % ysize;
            vector < bool > vv;
            vv.resize(4);
            fill(vv.begin(), vv.end(), true);

            printpanel[rx][ry].set(1, vv);
        }
    }
}