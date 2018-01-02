//#include "stdafx.h" //���������� ��� Visual Studio
#include <iostream>
#include <locale>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <set>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <mmsystem.h>

const int M = 10;
const int N = 12;

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(int x, int y) //������� ������� ��������� �������
{
COORD ord;
ord.X = x;
ord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
}

int turnRandX;
int turnRandY;
int f, k, wr;

void printOutput(char B[][N])
{
for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
				if (B[i][j] == 'v') SetConsoleTextAttribute(console, 10);
                else if (B[i][j] == 'x') 
				{
				SetConsoleTextAttribute(console, 12);
                wr++;
				}
				else if (B[i][j] == '0') SetConsoleTextAttribute(console, 14);
				else if (B[i][j] == '*') SetConsoleTextAttribute(console, 11);
                else SetConsoleTextAttribute(console, 7);
				cout << B[i][j] << " ";
            }
            cout << endl;
        }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned)time(NULL));
	
    char A[N][N];
    char B[N][N];
    char ball = (char)149;

    int x, y, p, q, pos;
    int L, K, i, j;
    int coordx, coordy;
    int turnx, turny;
    
    int shipQ = 0;
	int LshipX;
	int LshipY;
	
	int totalOne = 0;
	int totalTwo = 0;
	
	int total;
    
    vector<int>vec;
	set<pair<int,int>>move;
	set<int>possible = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    string playerOneName, playerTwoName;
    
    PlaySound("greeting.wav", NULL,SND_ASYNC | SND_FILENAME);

    SetConsoleTextAttribute(console, 11);
    cout << "\n*** ���� \"������� ���\" ***" << "\n\n";
    SetConsoleTextAttribute(console, 14);
    cout << "������� ��� ������� ������: ";
    SetConsoleTextAttribute(console, 11);
    getline(cin, playerOneName);
    SetConsoleTextAttribute(console, 14);
    cout << "������� ��� ������� ������: ";
    SetConsoleTextAttribute(console, 11);
    getline(cin, playerTwoName);
    system("cls");
    
    //������ ���� (����������� �� ����)

    SetConsoleTextAttribute(console, 7);

    for (int i = 0; i < 100; i++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if ((i == 0) || (j == 0) || (i == N - 1) || (j == N - 1))
                {
					A[i][j] = '*';
					B[i][j] = '*';
                }
                else
				{
					A[i][j] = '?';
				}
            }
        }
        for (int t1 = 0, t2 = 0; t1 < 4, t2 < 8; t1++, t2 += 2)
        {
            p = 0;
            while (k != (14 - t2))
            {
                pos = 1 + rand() % 2;
                if (pos == 1)
                {
                    x = 1 + rand() % 10;
                    y = 1 + rand() % (7 + t1);
                    k = 0;
                    for (int i = -1; i <= 4 - t1; i++)
                    {
                        if (A[x-1][y+i] == '?')
                            k++;
                        if (A[x+1][y+i] == '?')
                            k++;
                    }
                    if (A[x][y+4-t1] == '?')
                        k++;
                    if (A[x][y-1] == '?')
                        k++;
                    if (k == 14 - t2)
                    {
                        for (int i = 0; i < 4 - t1; i++)
                        {
                            A[x][y+i] = '#';
                        }
                        p++;
                    }
                }
                if (pos == 2)
                {
                    x = 1 + rand() % (7 + t1);
                    y = 1 + rand() % 10;
                    k = 0;
                    for (int i = -1; i <= 4 - t1; i++)
                    {
                        if (A[x+i][y-1] == '?')
                            k++;
                        if (A[x+i][y+1] == '?')
                            k++;
                    }
                    if (A[x-1][y] == '?')
                        k++;
                    if (A[x+4-t1][y] == '?')
                        k++;
                    if (k == 14 - t2)
                    {
                        for (int i = 0; i < 4 - t1; i++)
                        {
                            A[x+i][y] = '#';
                        }
                        p++;
                    }
                }
                k = 0;
                if (p == 1 + t1)
                    break;
            }
        }
        q = 0;
        for (int i = 1; i < N - 1; i++)
        {
            for (int j = 1; j < N - 1; j++)
            {
                if (A[i][j] == '#')
                {
                    q++;
                }
            }
        }
        if (q == 20)
        {
            for (int i = 1; i < N - 1; i++)
            {
                for (int j = 1; j < N - 1; j++)
                {
                    if (A[i][j] == '#')
                    {
                        cout << A[i][j] << " ";
                    }
                    else
                        cout << A[i][j] << " ";
                }
                cout << endl;
            }
            break;
        }
    }
    
    //����� �����������
    
    gotoxy(0, 0); //��������� ������� ������
      
    for (int i = 1; i < N - 1; i++)
    {
    for (int j = 1; j < N - 1; j++)
    {
    B[i][j] = '?';
    cout << B[i][j] << " ";
	}
	cout << "\n";
    }
    
	for (int i = 0; i < 100; i++)
	{
	vec.push_back(i + 1); 
	}
	
	random_shuffle(vec.begin(), vec.end());
      
    int shoot1 = 0;
	int shoot2 = 0;  
	
	for (f = 0; f < 100; f++)
    
    {
    
	if (f % 2 == 0)
	
	{
		moveagain1:
		SetConsoleTextAttribute(console, 12);
		cout << playerOneName << " (�������� ���):\n";
		SetConsoleTextAttribute(console, 10);
		cout << "������: ";
		SetConsoleTextAttribute(console, 11);
		cin >> turnx; 
		SetConsoleTextAttribute(console, 10);
		cout << "�������: ";
		SetConsoleTextAttribute(console, 11);
		cin >> turny;
		
		if ((possible.find(turnx) == possible.end()) || (possible.find(turny) == possible.end())) 
		{
		system("cls");
		printOutput(B); //������ �������� ����������
		gotoxy(0, N);
		SetConsoleTextAttribute(console, 14);
		cout << "������ ��� ����������!" << "\n";
		PlaySound("error.wav", NULL,SND_ASYNC | SND_FILENAME);
		goto moveagain1;
		}
		
		else
		
		{
	
		if (move.find(pair<int, int>(turnx, turny)) != move.end())
        {
        system("cls");
		printOutput(B); //������ �������� ����������
		gotoxy(0, N);
		SetConsoleTextAttribute(console, 14);
		cout << "������ ��� ��� ������! ������ �����!" << "\n";
		PlaySound("error.wav", NULL,SND_ASYNC | SND_FILENAME);
		goto moveagain1;
		}
		else
		{
        move.insert(make_pair(turnx, turny));
        shoot1++;
        }
        
      }
    }
    else
    {
	 moveagain2:
		SetConsoleTextAttribute(console, 12);
		cout << playerTwoName << " (�������� ���):\n";
		SetConsoleTextAttribute(console, 10);
		cout << "������: ";
		SetConsoleTextAttribute(console, 11);
		cin >> turnx; 
		SetConsoleTextAttribute(console, 10);
		cout << "�������: ";
		SetConsoleTextAttribute(console, 11);
		cin >> turny;
		
		if ((possible.find(turnx) == possible.end()) || (possible.find(turny) == possible.end())) 
		{
		system("cls");
		printOutput(B); //������ �������� ����������
		gotoxy(0, N);
		SetConsoleTextAttribute(console, 14);
		cout << "������ ��� ����������!" << "\n";
		PlaySound("error.wav", NULL,SND_ASYNC | SND_FILENAME);
		goto moveagain2;
		}
		
		else
		
		{
	
		if (move.find(pair<int, int>(turnx, turny)) != move.end())
        {
        system("cls");
		printOutput(B); //������ �������� ����������
		gotoxy(0, N);
		SetConsoleTextAttribute(console, 14);
		cout << "������ ��� ��� ������! ������ �����!" << "\n";
		PlaySound("error.wav", NULL,SND_ASYNC | SND_FILENAME);
		goto moveagain2;
		}
		else
		{
        move.insert(make_pair(turnx, turny));
        shoot2++;
        }
        
      }
    }
	
        if (A[turnx][turny] == '#')
        {
            A[turnx][turny] = ball;
            B[turnx][turny] = ball;
            PlaySound("found.wav", NULL,SND_ASYNC | SND_FILENAME);
        }
        else if (A[turnx][turny] == ball)
        {
            A[turnx][turny] = ball;
            B[turnx][turny] = ball;
        }
        else if (A[turnx][turny] == 'x')
        {
            A[turnx][turny] = 'x';
            B[turnx][turny] = 'x';
        }
        else
        {
            A[turnx][turny] = '0';
            B[turnx][turny] = '0';
            PlaySound("miss.wav", NULL,SND_ASYNC | SND_FILENAME);
        }

        //�������������� ������

        for (int K = 4, t = 14; K >= 1, t >= 8; K--, t -= 2)
        {
            L = 1;
            x = N - K;
            y = N - L;
            for (int b = 0; b < y + 1; b++)
            {
                for (int a = 0; a < x + 1; a++)
                {
                    k = 0;
                    for (int i = b; i < L + b; i++)
                    {
                        for (j = a; j < K + a; j++)
                        {
                            if (A[i][j] == ball)
                                k++;
                        }
                    }
                    if (k == L * K)
                    {
                        for (int x = 1; x < N - 1; x++)
                        {
                            for (int y = 1; y < N - 1; y++)
                            {
                                if (((x >= b) && (x < i)) && ((y >= a) && (y < j)))
                                {
                                    coordx = b;
                                    coordy = a;
                                }
                            }
                        }
                        k = 0;
                        for (int i = -1; i <= K; i++)
                        {
                            if (A[coordx-1][coordy+i] == '?' || A[coordx-1][coordy+i] == '0')
                                k++;
                            if (A[coordx+1][coordy+i] == '?' || A[coordx+1][coordy+i] == '0')
                                k++;
                        }
                        if (A[coordx][coordy+K] == '?' || A[coordx][coordy+K] == '0')
                            k++;
                        if (A[coordx][coordy-1] == '?' || A[coordx][coordy-1] == '0')
                            k++;
                        if (k == t)
                        {
                            shipQ++;
                            if (shipQ == M) LshipX = K; 
                            
							if (f % 2 == 0)  totalOne += K;
							else  totalTwo += K;
								
							for (int i = 0; i < K; i++)
                            {
                                A[coordx][coordy+i] = 'x';
                                B[coordx][coordy+i] = 'x';
                            }
                            PlaySound("destroyed.wav", NULL,SND_ASYNC | SND_FILENAME);
                        }
                        break;
                    }
                }
            }
        }

        //������������ ������

        for (int L = 4, t = 14; L >= 1, t >= 8; L--, t -= 2)
        {
            K = 1;
            x = N - K;
            y = N - L;
            for (int b = 0; b < y + 1; b++)
            {
                for (int a = 0; a < x + 1; a++)
                {
                    k = 0;
                    for (i = b; i < L + b; i++)
                    {
                        for (j = a; j < K + a; j++)
                        {
                            if (A[i][j] == ball)
                                k++;
                        }
                    }
                    if (k == L * K)
                    {
                        for (int x = 1; x < N - 1; x++)
                        {
                            for (int y = 1; y < N - 1; y++)
                            {
                                if (((x >= b) && (x < i)) && ((y >= a) && (y < j)))
                                {
                                    coordx = b;
                                    coordy = a;
                                }
                            }
                        }
                        k = 0;
                        for (int i = -1; i <= L; i++)
                        {
                            if (A[coordx+i][coordy-1] == '?' || A[coordx+i][coordy-1] == '0')
                                k++;
                            if (A[coordx+i][coordy+1] == '?' || A[coordx+i][coordy+1] == '0')
                                k++;
                        }
                        if (A[coordx-1][coordy] == '?' || A[coordx-1][coordy] == '0')
                            k++;
                        if (A[coordx+L][coordy] == '?' || A[coordx+L][coordy] == '0')
                            k++;
                        if (k == t)
                        {
                            shipQ++;
                            if (shipQ == M) LshipY = L;
                            
					     	if (f % 2 == 0) totalOne += L;
							else  totalTwo += L;
							
							for (int i = 0; i < L; i++)
                            {
                                A[coordx+i][coordy] = 'x';
                                B[coordx+i][coordy] = 'x';
                            }
                            PlaySound("destroyed.wav", NULL,SND_ASYNC | SND_FILENAME);
                        }
                        break;
                    }
                }
            }
        //Sleep(100); //����� ����� ������
        }
        system("cls");
        wr = 0;
		printOutput(B); //������ �������� ����������
        if (wr == 20)
		{ 
		total = shoot1 + shoot2;
		break;
	    }
    }
    SetConsoleTextAttribute(console, 7);
    
    int etalon = 0;
	for (int i = 1; i < N - 1; i++)
    {
    for (int j = 1; j < N - 1; j++)
    {
    if (A[i][j] == '?') etalon++;
	}
    }
    
    cout << "\n���� ��������!" << "\n";
    //cout << "������������ ��������: " << shipQ << "\n";
	cout << "����� ����� �������: " << total << "/100" << ": " << 100 - total << " = " << etalon << "\n\n";
	
	cout << playerOneName << ":\n";
	//cout << "������� �������: " << shoot1 << "\n";
	cout << "������� ������� ������: " << totalOne << "\n\n";
	
	cout << playerTwoName << ":\n";
	//cout << "������� �������: " << shoot2 << "\n";
	cout << "������� ������� ������: " << totalTwo << "\n\n";
	
	cout << "���� ����:\n\n";
	cout << playerOneName << " ������ ������� " << totalOne / 3 << " ����������!" << "\n";
	cout << playerTwoName << " ������ ������� " << totalTwo / 3 << " ����������!" << "\n"; 
	PlaySound("endofgame.wav", NULL,SND_ASYNC | SND_FILENAME);
	
    system("pause");
    return 0;
}
