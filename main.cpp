#include <QApplication>
#include <QDebug>
#include <form.h>
//#include <vector>

int n = 10; /*Количество станков*/

/* Функция для вычисления критического пути и параметров сетевого графика */



void PSMethod()
{

}

void Critical_Path (int n, int firstStanok[], int secondStanok[], int dij[],
               int *s1, int *s2, int *f1, int *f2, int *tf, int *ff)
{
  int k,index,max,min;
  //int ti[n],te[n];
  std::vector<int> ti(n);
  std::vector<int> te(n);
  index = 0;
  for (k=0;k<n;k++)
  {
    if ( firstStanok[k]==index+1 )  index = firstStanok[k];
    ti[k] = 0; te[k] = INT_MAX;
  }
  for (k=0;k<n;k++)
  {
    max = ti[firstStanok[k]] + dij[k];
    if ( ti[secondStanok[k]]<max ) ti[secondStanok[k]] = max;
  }
  te[secondStanok[n-1]] = ti[secondStanok[n-1]];
  for (k=n-1;k>=0;k--)
  {
    min = te[secondStanok[k]] - dij[k];
    if ( te[firstStanok[k]]>min ) te[firstStanok[k]] = min;
  }
  for (k=0;k<n;k++)
  {
    s1[k] = ti[firstStanok[k]]; f1[k] = s1[k] + dij[k];
    f2[k] = te[secondStanok[k]]; s2[k] = f2[k] - dij[k];
    tf[k] = f2[k] - f1[k]; ff[k] = ti[secondStanok[k]] - f1[k];
  }
}

/* Алгоритм Дейкстры */

void Deikstra(int i[], int j[], int dij[],int *d)
{
    n=9;    //количество вершин в графе
    //int a[n][n]; // матрица связей
    std::vector<std::vector<int>>  a(n,std::vector<int>(n)); // матрица связей
    //int v[n]; // посещенные вершины
    std::vector<int> visit(n); //посещенные вершины
    int temp=0;
    int minindex, min;
// Инициализация матрицы связей
    for (int i = 0; i<n; i++)
    {
        for (int j = 0; j<n; j++)
        {
            a[i][j] = 0;
        }
     }

    for (int z = 0; z<15; z++)
    {
        int kkk=i[z]-1;
        int qqq=j[z]-1;
        a[kkk][qqq] = dij[z];
    }

//Инициализация вершин и расстояний
    for (int i = 0; i<n; i++)
    {
        d[i] = INT_MAX;
        visit[i] = 1;
    }
    d[0] = 0;
// Шаг алгоритма
    do
    {
        minindex = INT_MAX;
        min = INT_MAX;
        for (int i = 0; i<n; i++)
        { // Если вершину ещё не обошли и вес меньше min
            if ((visit[i] == 1) && (d[i]<min))
            { // Переприсваиваем значения
                min = d[i];
                minindex = i;
            }
        }
  // Добавляем найденный минимальный вес
  // к текущему весу вершины
  // и сравниваем с текущим минимальным весом вершины
        if (minindex != INT_MAX)
        {
            for (int i = 0; i<n; i++)
            {
                if (a[minindex][i] > 0)
                {
                    temp = min + a[minindex][i];
                    if (temp < d[i]) d[i] = temp;
                }
            }
        visit[minindex] = 0;
        }
    }
    while (minindex < INT_MAX);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setlocale(LC_CTYPE, "Russian");
    std::vector<int> invisible; // невидимая полоска для сокрытия шлака, ДОБАВИТЬ

    std::vector<int> firstStanok = {3,3,1,1,2,3,5,5,4,4,6,6,6,8,7}; // 1 станок
    std::vector<int> secondStanok = {1,2,3,5,4,5,4,6,6,7,7,8,9,9,12}; // 2 станок

              // Граф задан массивом ребер:
              // (i[0],j[0]),(i[1],j[1]),...,(i[n-1],j[n-1])
              // Должно быть выполнено:
              // i[0]=1, i[k]<i[k+1], i[k]<j[k].

    std::vector<int> dij = {4,6,2,5,3,4,7,6,4,3,5,8,6,4,3};//dij[k] - продолжительность k-й операции.
    std::vector<int> s1(n); //самый ранний срок начала k-й операции
    std::vector<int> s2(n); //самый поздний срок начала k-й
    std::vector<int> f1(n); //самый ранний срок завершения k-й
    std::vector<int> f2(n); //самый поздний срок завершения k-й операции
    std::vector<int> tf(n); //полный резерв времени k-й операции
    std::vector<int> ff(n); //свободный резерв времени k-й операции
    std::vector<int> d(n);
  //Critical_Path (n,&firstStanok[0],&j[0],&dij[0],&s1[0],&s2[0],&f1[0],&f2[0],&tf[0],&ff[0]);

  int s = 0;
  for (int k=0;k<n;k++)
   if ( tf[k]==0 ) s=s+dij[k];

  Deikstra(&firstStanok[0],&secondStanok[0],&dij[0],&d[0]);
  int mas[n]; //массив с номерами вершин критического пути
  for(int k=0;k<n;k++)
      if (tf[k]==0)
      {
          mas[k]=secondStanok[k];
      }

  int t = (3*d[8]+2*s)/5; //ожидаемое время выполнения (продолжительность проекта)

  Form graph(&s1[0],&f1[0],&s2[0],&f2[0],&ff[0],&tf[0],&firstStanok[0],&secondStanok[0],/*s,*/&mas[0]/*,t,d[8]*/);
  graph.show();
  return a.exec();
}
