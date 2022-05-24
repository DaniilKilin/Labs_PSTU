#pragma once
#pragma once
#include <vector>
#include <glut.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <cmath>
#include <queue>
using namespace std;

const int maximumVerts = 10;//максимальное число вершин
extern int WinW;//ширина и высота окна
extern int WinH;
struct vertCoord //структура координат вершин
{
	int x, y;
};

class Graph
{
private:
	vector<int> vertList;
	int adjMatrix[maximumVerts][maximumVerts];
public:
	Graph();
	~Graph();

	bool IsEmpty(); // Проверка на пустоту
	bool IsFull(); // Проверка на заполненность 
	int GetVertexElement(int i) { return vertList[i]; }
	vector<int> GetVertList() { return  vertList; }
	int GetAdjMatrixElement(int i, int j) { return adjMatrix[i][j]; }
	int GetAmountEdges(); // Количество рёбр 
	int GetAmountVerts() { return vertList.size(); } // Количество вершин
	int GetVertPos(const int& v);
	void InsertVertex(const int& v); // Добавление вершины
	void InsertEdge(const int& v, const int& v2, int w); // Добавление ребра
	void PrintGraph(); // Вывод матрицы смежности
	void DeleteVertex(); // Удаление вершины
	void DeleteEdge(const int& v1, const int& v2); // Удаление ребра
	void drawGraph(); // Вывод графа
};

extern Graph graph;
int** TransMatrix(); //создается матрица, заменяя 0 на -1
int* Find_Min(int* l, int n);//поиск минимального элемента в строке матрицы
void Print(int** m);//вывод текущей матрицы
int** Reduct_Matrix(int** m); //редукция матрицы
int** b_and_b(int** m); // Метод ветвей и границ
void comy();//вывод результата решения задачи Коммивояжера
bool Cheking(int** matrix); // Проверка на возможность решения задачи
int Circle_Check(int x, int y);
void drawCircle(int x, int y, int R); 
void drawThisCircle(int x, int y, int R);
void drawText(int nom, int x1, int y1); // Отрисовка текста
void drawLine(int text, int x0, int y0, int x1, int y1); // Отрисовка линий между вершинами
void drawVertex(int n); // Отрисовка вершины
void button_1();
void button_2();
void button_3();
void button_4();
void button_5();
void button_6();
void makeGraph();
void setCoords(int i, int n); 
void Move(int x, int y); // Передвижение вершин
void Click(int button, int state, int x, int y);
void reshape(int w, int h); // Изменение размеров окна
void display(); // Вывод на экран


