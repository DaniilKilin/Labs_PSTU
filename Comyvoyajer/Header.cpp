#include "Header.h"
using namespace std;


vector<pair<int, int>> pathParts;
vector<int> fullWay;
int R;

int Moving_Vertex;//перемещаемая вершина
int CursorX;//позиция курсора 
int CursorY;//позиция курсора 
bool* Vert_ON = new bool[maximumVerts]; //курсор в зоне круга
bool MovingMode = false; //перемещены ли вершины
bool Vert_Move = false; //отвечает за перемещение вершин 
vertCoord vertC[maximumVerts + 1];//координаты вершин
Graph graph;

int WinW = 1000; // Длина 1000
int WinH = 800; // Высота 800
Graph::Graph()
{
	for (int i = 0; i < maximumVerts; i++)
	{
		Vert_ON[i] = false;
		for (int j = 0; j < maximumVerts; j++)
			adjMatrix[i][j] = 0;
	}
}

Graph::~Graph()
{ }

int Graph::GetVertPos(const int& vertex)
{
	for (size_t i = 0; i < vertList.size(); i++)
	{
		if (vertList[i] == vertex)
			return i;
	}
	return -1;
}

bool Graph::IsEmpty() // Проверка на пустоту
{
	if (vertList.size() != 0)
		return false;
	else
		return true;
}

bool Graph::IsFull() // Проверка на полную заполненность 
{
	return (vertList.size() == maximumVerts);
}

void Graph::InsertVertex(const int& vertex) // Добавление вершины
{
	if (!IsFull())
		vertList.push_back(vertex);
	else
	{
		cout << "Граф заполнен. Невозможно добавить вершину " << endl;
		return;
	}
}

void Graph::InsertEdge(const int& vertex1, const int& vertex2, int weight) // Добавление ребра
{
	if (weight < 1)
	{
		cout << "\nВеличина веса некорректна записана\n";
		return;
	}
	if (GetVertPos(vertex1) != (-1) && GetVertPos(vertex2) != (-1))	//если вершины есть в графе
	{
		int vertPos1 = GetVertPos(vertex1);	//находим позиции вершин
		int vertPos2 = GetVertPos(vertex2);
		if (adjMatrix[vertPos1][vertPos2] != 0 && adjMatrix[vertPos2][vertPos1] != 0)//если между ними уже есть ребро
		{
			cout << "Ребро уже существует" << endl;
			return;
		}
		else											//иначе добавляем ребро
		{
			adjMatrix[vertPos1][vertPos2] = weight;
			adjMatrix[vertPos2][vertPos1] = weight;
		}
	}
	else
	{
		cout << "Одной из них вершин нет в графе " << endl;
		return;
	}
}

void Graph::PrintGraph() // Вывод матрицы смежности
{
	if (!IsEmpty())
	{
		cout << "Матрица смежности графа: " << endl;
		for (int i = 0; i < vertList.size(); i++)
		{
			cout << vertList[i] << " ";
			for (int j = 0; j < vertList.size(); j++)
				cout << setw(4) << adjMatrix[i][j];
			cout << endl;
		}
	}
	else
		cout << "Граф пуст " << endl;
}

void Graph::DeleteVertex()  // Удаление вершины
{
	if (IsEmpty())
	{
		cout << "\nГраф пуст\n";
		return;
	}
	int n = vertList.size();
	for (int j = 0; j < n; j++)
	{
		adjMatrix[n - 1][j] = 0;
		adjMatrix[j][n - 1] = 0;
	}

	vertList.pop_back();
}

void Graph::DeleteEdge(const int& vertex1, const int& vertex2) // Удаление ребра
{
	if (GetVertPos(vertex1) != (-1) && GetVertPos(vertex2) != (-1))	//если вершины есть в графе
	{
		int vertPos1 = GetVertPos(vertex1);							//находим позиции вершин
		int vertPos2 = GetVertPos(vertex2);
		if (adjMatrix[vertPos1][vertPos2] == 0 && adjMatrix[vertPos2][vertPos1] == 0)//если между ними уже есть ребро
		{
			cout << "Ребра нет" << endl;
			return;
		}
		else														//иначе добавляем ребро
		{
			adjMatrix[vertPos1][vertPos2] = 0;
			adjMatrix[vertPos2][vertPos1] = 0;
		}
	}
	else
	{
		cout << "Обеих вершин (или одной из них) нет в графе " << endl;
		return;
	}
}

int Graph::GetAmountEdges() // Количество рёбер
{
	int edges = 0;
	for (int i = 0; i < vertList.size(); i++)
		for (int j = 0; j < vertList.size(); j++)
			if (adjMatrix[i][j] > 0)
				edges++;
	return edges;
}

void Graph::drawGraph() // Рисует граф
{
	int n = graph.GetAmountVerts(); // Кол-во вершин
	for (int i = 0; i < n; i++)
	{
		if (!MovingMode)
			setCoords(i, n); //Функция для задания координат вершинам
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int a = adjMatrix[i][j];
			if (a != 0) //Проверка на наличие дороги
				drawLine(a, vertC[i].x, vertC[i].y, vertC[j].x, vertC[j].y); //Функция отрисовки линий, соединяющих две вершины
			if (a == adjMatrix[j][i] && a != 0)
				drawLine(a, vertC[j].x, vertC[j].y, vertC[i].x, vertC[i].y);//Функция отрисовки линий, соединяющих две вершины
		}
	}
	drawVertex(n); // Отрисовка вершины
	glutPostRedisplay();
}

void button_1()
{
	// Кнопка отвечающая за удаление ребра
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2i(850, 500);
	glVertex2i(850, 600);
	glVertex2i(1000, 600);
	glVertex2i(1000, 500);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(850, 500);
	glVertex2i(850, 600);
	glVertex2i(1000, 600);
	glVertex2i(1000, 500);
	glEnd();
	string name = "-Edge";
	glRasterPos2i(862, 545);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, name[i]);
}

void button_2()
{
	// Кнопка отвечающая за добавление ребра
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2i(850,400);
	glVertex2i(850,500);
	glVertex2i(1000,500);
	glVertex2i(1000,400);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(850, 400);
	glVertex2i(850, 500);
	glVertex2i(1000, 500);
	glVertex2i(1000, 400);
	glEnd();
	string name = "+Edge";
	glRasterPos2i(862,445);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, name[i]);
}

void button_3()
{
	// Кнопка отвечающая за добавление вершины
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2i(850, 300);
	glVertex2i(850, 400);
	glVertex2i(1000, 400);
	glVertex2i(1000, 300);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(850, 300);
	glVertex2i(850, 400);
	glVertex2i(1000, 400);
	glVertex2i(1000, 300);
	glEnd();
	string name = "+Vertex";
	glRasterPos2i(862, 345);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, name[i]);
}

void button_4()
{
	// Кнопка отвечающая за удаление вершины
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2i(850,200);
	glVertex2i(850,300);
	glVertex2i(1000,300);
	glVertex2i(1000,200);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(850, 200);
	glVertex2i(850, 300);
	glVertex2i(1000, 300);
	glVertex2i(1000, 200);
	glEnd();
	string name = "-Vertex";
	glRasterPos2i(862,245);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, name[i]);
}

void button_5()
{
	// Кнопка отвечающая за создание нового графа
	glColor3f(0.5922, 0.5922, 0.5922);
	glBegin(GL_QUADS);
	glVertex2i(0, 400);
	glVertex2i(0, 500);
	glVertex2i(150, 500);
	glVertex2i(150, 400);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(0, 400);
	glVertex2i(0, 500);
	glVertex2i(150, 500);
	glVertex2i(150, 400);
	glEnd();
	string name = "SetNewGraph";
	glRasterPos2i(12,445);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, name[i]);
}

void button_6()
{
	// Кнопка отвечающая за решение задачи Комивояжёра
	glColor3f(0.5922, 0.5922, 0.5922);
	glBegin(GL_QUADS);
	glVertex2i(0,300);
	glVertex2i(0, 400);
	glVertex2i(150, 400);
	glVertex2i(150, 300);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(0, 300);
	glVertex2i(0, 400);
	glVertex2i(150, 400);
	glVertex2i(150, 300);
	glEnd();
	string name = "Commivoyager";
	glRasterPos2i(12,345);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, name[i]);
}

void drawCircle(int x, int y, int R) // Функция для отрисовки круга
{
	glColor3f(0.51, 0.93, 0.99);
	float x1, y1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) // Цикл что бы отрисовать все 360 точек
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y1 = R * cos(theta) + y;
		x1 = R * sin(theta) + x;;
		glVertex2f(x1, y1);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	float x2, y2;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) // Цикл что бы отрисовать все 360 точек
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = R * cos(theta) + y;
		x2 = R * sin(theta) + x;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawThisCircle(int x, int y, int R)
{
	glColor3f(0.0, 1.0, 0.0);
	float x1, y1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y1 = R * cos(theta) + y;
		x1 = R * sin(theta) + x;;
		glVertex2f(x1, y1);
	}
	glEnd();

	glColor3f(0.0, 0.392, 0.0);
	float x2, y2;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = R * cos(theta) + y;
		x2 = R * sin(theta) + x;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawText(int text, int x1, int y1) // функция для отрисовки текста
{
	glColor3f(0.0, 0.0, 0.0);
	GLvoid* font = GLUT_BITMAP_HELVETICA_18;
	string s = to_string(text);
	glRasterPos2i(x1 - 5, y1 - 5);
	for (size_t j = 0; j < s.length(); j++)
		glutBitmapCharacter(font, s[j]);
}

void drawLine(int text, int x0, int y0, int x1, int y1) //ребро неориентированного взвешенного графа
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2i(x0, y0); // Координаты начальной вершины
	glVertex2i(x1, y1); // Координаты конечной вершины
	glEnd();

	drawText(text, (x0 + x1) / 2 + 10, (y0 + y1) / 2 + 10); // Отрисовка текста для данного ребра
}

void drawVertex(int n) // Рисуем вершину
{
	for (int i = 0; i < n; i++) // Цикл от количества вершин
	{
		if (Vert_ON[i])
			drawThisCircle(vertC[i].x, vertC[i].y, R); //Функция отрисовки круга с заданными координатами и радиусом
		else
			drawCircle(vertC[i].x, vertC[i].y, R);
		drawText(i + 1, vertC[i].x, vertC[i].y); //Функция отрисовки текста в вершинах и на рёбрах
	}
}

void setCoords(int i, int n) // Задаём координаты
{
	int R_;
	int x0 = WinW / 2; // Расположение по центру
	int y0 = WinH / 2;
	if (WinW > WinH)
	{
		R = 5 * (WinH / 13) / n;
		R_ = WinH / 2 - R - 10; // Вычисление радиуса
	}
	else
	{
		R = 5 * (WinW / 13) / n;
		R_ = WinW / 2 - R - 10; // Вычисление радиуса
	}
	float theta = 2.0f * 3.1415926f * i / n; //Вычисление угла для положения вершины
	int y1 = R_ * cos(theta) + y0;// координаты вершин
	int x1 = R_ * sin(theta) + x0;
	vertC[i].x = x1; //Присваивание координат
	vertC[i].y = y1;
}

void makeGraph() // Создание графа
{
	int amountVerts, amountEdges, sourceVertex, targetVertex, edgeWeight;
	cout << "Введите количество вершин в графе: "; cin >> amountVerts;
	cout << "Введите количество ребер в графе: "; cin >> amountEdges;
	for (int i = 1; i <= amountVerts; i++) {

		graph.InsertVertex(i);
	}
	for (int i = 0; i < amountEdges; i++)
	{
		cout << "Исходная вершина: "; cin >> sourceVertex;
		cout << "Конечная вершина: "; cin >> targetVertex;
		cout << "Вес ребра: "; cin >> edgeWeight;
		graph.InsertEdge(sourceVertex, targetVertex, edgeWeight);
	}
	cout << endl;
	MovingMode = false;
	graph.PrintGraph();
}

int** TransMatrix() // Создание матрицы.
{
	int n = graph.GetAmountVerts();
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int elem = graph.GetAdjMatrixElement(i, j);
			if (elem == 0 || i == j)
				matrix[i][j] = -1;
			else
				matrix[i][j] = elem;
		}
	}
	return matrix;
}

int* Find_Min(int* line, int n) // Поиск минимального элемента в строке матрицы
{
	int min = 1000000;
	for (int j = 0; j < n; j++)
		if (line[j] >= 0 && line[j] < min)
			min = line[j];
	for (int j = 0; j < n; j++)
		if (line[j] >= 0)
			line[j] -= min;
	return line;
}

int** Reduct_Matrix(int** oldmatrix) // Редукция матрицы
{
	int** matrix = oldmatrix;
	int n = graph.GetAmountVerts();
	for (int i = 0; i < n; i++)
		matrix[i] = Find_Min(matrix[i], n);
	for (int i = 0; i < n; i++)
	{
		int min = 1000000;
		for (int j = 0; j < n; j++)
		{
			if (matrix[j][i] >= 0 && matrix[j][i] < min)
				min = matrix[j][i];
		}
		for (int j = 0; j < n; j++)
		{
			if (matrix[j][i] >= 0)
				matrix[j][i] -= min;
		}
	}
	return matrix;
}

int** b_and_b(int** oldmatrix) //Метод ветвей и границ
{
	int n = graph.GetAmountVerts();
	int** matrix = Reduct_Matrix(oldmatrix);
	int max = -1;
	int line, column;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] == 0)
			{
				int minLine = 1000000;
				int minColumn = 1000000;
				for (int k = 0; k < n; k++)
				{
					if (matrix[i][k] != -1 && k != j && matrix[i][k] < minLine)
						minLine = matrix[i][k];
				}
				for (int k = 0; k < n; k++)
				{
					if (matrix[k][j] != -1 && k != i && matrix[k][j] < minColumn)
						minColumn = matrix[k][j];
				}
				if (max < minColumn + minLine)
				{
					max = minColumn + minLine;
					line = i;
					column = j;
				}
			}
		}
	}

	pair<int, int> p;
	p.first = line + 1;
	p.second = column + 1;
	pathParts.push_back(p);

	matrix[line][column] = -1;
	matrix[column][line] = -1;

	for (int i = 0; i < n; i++)
	{
		matrix[line][i] = -1;
		matrix[i][column] = -1;
	}
	return matrix;
}

void Comy(int n) // Решение задачи Комивояжёра
{
	int second = pathParts[0].second;
	int i = 2;
	fullWay.push_back(pathParts[0].first);
	fullWay.push_back(pathParts[0].second);
	while (i != graph.GetAmountVerts() + 1) 
		for (int j = 1; j < graph.GetAmountVerts(); j++)
			if (pathParts[j].first == second)
			{
				second = pathParts[j].second;
				fullWay.push_back(second);
				i++;
			}
	fullWay.pop_back();
	cout << "Ответ: ";
	int j = 0;
	for (int i = 0; i < fullWay.size(); i++)
	{
		if (fullWay[i] == n)
			j = i;
	}
	for (int i = 0; i < fullWay.size() + 1; i++) // По какому маршруту проходит путь
	{
		cout << fullWay[j % fullWay.size()];
		if (i != fullWay.size())
			cout << " -> ";
		j++;
	}
	int sum = 0;
	for (int i = 0; i < pathParts.size(); i++) // Считаем сумму всего пути
	{
		int line = pathParts[i].first - 1;
		int column = pathParts[i].second - 1;
		sum += graph.GetAdjMatrixElement(line, column);
	}
	cout << "\nS = " << sum << endl;;
}

bool Cheking(int** matrix) // Проверка на возможность решения задачи Комвояжёра
{
	if (graph.IsEmpty())
		return false;
	for (int i = 0; i < graph.GetAmountVerts(); i++)
	{
		int cnt = 0;
		for (int j = 0; j < graph.GetAmountVerts(); j++)
		{
			if (matrix[i][j] > 0)
				cnt++;
		}
		if (cnt < 1)
			return false;
	}
	return true;
}

int Circle_Check(int x, int y)
{
	for (int i = 0; i < graph.GetAmountVerts(); i++)
		if (pow(x - vertC[i].x, 2) + pow(y - vertC[i].y, 2) <= R * R)
			return i;
	return -1;
}

void Move(int x, int y) // передвижение вершин
{
	y = WinH - y;
	CursorX = x;
	CursorY = y;
	int i = Circle_Check(x, y);
	if (i != -1)
		Vert_ON[i] = true;
	else
		for (int j = 0; j < graph.GetAmountVerts(); j++)
			Vert_ON[j] = false;
	if (Vert_Move)
	{
		vertC[Moving_Vertex].x = CursorX;
		vertC[Moving_Vertex].y = CursorY;
	}
	glutPostRedisplay();
}

void Click(int button, int state, int x, int y) // действия с кнопками 
{
	int j = Circle_Check(x, WinH - y); 
	if (Vert_Move) // Если вершина перемещается
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			Vert_Move = false; // То нажатие на неё остановит перещение
			return;
		}
	}
	if (j != -1)// Если вершина не перемещается
	{
		MovingMode = true; // Вершины перемещены
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			Vert_Move = true; // Если нажать то вершину можно перемещать
			Moving_Vertex = j;
			return;
		}
	}

	if (x <= 1000 && x >= 850 && y >= 400 && y <= 500)
	{
		// Кнопка добавления вершины
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int cur = graph.GetAmountVerts();
			graph.InsertVertex(cur + 1);
			vertC[cur].x = WinW / 2;
			vertC[cur].y = WinH / 2;
			cout << "\nДобавлена вершина: " << cur + 1 << endl;
			return;
		}
	}
	if (x <= 1000 && x >= 850  && y >= 500 && y <= 600)
	{
		// Кнопка удаления вершины
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			graph.DeleteVertex();
			int cur = graph.GetAmountVerts();
			cout << "\nУдалена вершина: " << cur << endl;
			return;
		}
	}
	if (x <= 1000 && x >= 850 && y >= 300 && y <= 400)
	{
		// Кнопка добавления ребра
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int sourceVertex, targetVertex, edgeWeight, vertNum;
			cout << "Количество добавляемых ребер: "; cin >> vertNum;
			for (int i = 0; i < vertNum; i++)
			{
				cout << "Исходная вершина: "; cin >> sourceVertex;
				cout << "Конечная вершина: "; cin >> targetVertex;
				cout << "Вес ребра: "; cin >> edgeWeight;
				graph.InsertEdge(sourceVertex, targetVertex, edgeWeight);
			}
			return;
		}
	}
	if (x <= 1000 && x >= 850 && y >=200  && y <= 300)
	{
		// Кнопка удаления ребра
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int sourceVertex, targetVertex;
			cout << "Исходная вершина: "; cin >> sourceVertex;
			cout << "Конечная вершина: "; cin >> targetVertex;
			graph.DeleteEdge(sourceVertex, targetVertex);
			return;
		}
	}
	if (x <= 150 && x >= 0 && y >= 300 && y <= 400)
	{
		// Кнопка создания нового графа
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			fullWay.clear();
			pathParts.clear();
			Graph New;
			graph = New;
			makeGraph();
			return;
		}
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
			MovingMode = false;
			return;
		}
	}
	if (x <= 150 && x >= 0 && y >= 400 && y <= 500)
	{
		// Кнопка решения задачи Комивояжёра
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int num;
			fullWay.clear();
			pathParts.clear();
			cout << "Введите исходную вершину: ";
			cin >> num;
			cout << endl;
			cout << "Решение задачи коммивояжера: \n";
			int** matrix = TransMatrix();
			bool tsp = Cheking(matrix);
			if (!tsp)
			{
				cout << "\nЗадача Коммивояжера не может быть решена\n\n";
				return;
			}
			int n = graph.GetAmountVerts();
			while (pathParts.size() < n)
				matrix = b_and_b(matrix);
			cout << endl;
			Comy(num);
			return;
		}
	}
}

void reshape(int w, int h) // Изменение формы окна 
{
	WinW = w;
	WinH = h;
	glViewport(0, 0, (GLsizei)WinW, (GLsizei)WinH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)WinW, 0, (GLdouble)WinH);
	glutPostRedisplay();
}

void display() //вывод изображения на экран
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WinW, 0, WinH);
	glViewport(0, 0, WinW, WinH);
	glClearColor(1.0, 1.0, 0.86, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	graph.drawGraph();

	button_1();
	button_2();
	button_3();
	button_4();
	button_5();
	button_6();

	glutSwapBuffers();
}