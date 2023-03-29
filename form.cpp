#include "form.h"
#include "ui_form.h"
#include <QVector>
#include <QFont>
#include <QString>

Form::Form(int s1[], int f1[], int s2[], int f2[], int tf[], int ff[], int firstStanok[], int secondStanok[],/* int s,*/ int mas[],/* int t, int d,*/ QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    /* Присвоение значений переменным класса из переменных конструктора */

    //this->s=s;
    //this->t=t;
    //this->d=d;

    for (int n=0;n<15;n++)
    {
        this->s1[n]=s1[n]; //s1
        this->f1[n]=f1[n];//f1
        this->f2[n]=f2[n];//f2
        this->s2[n]=s2[n];//s2
        this->tf[n]=tf[n];//tf
        this->ff[n]=ff[n];//ff
        this->firstStanok[n]=firstStanok[n];//i
        this->secondStanok[n]=secondStanok[n];//j
        this->mas[n]=mas[n];//mas
    }

    make_table(); //создать таблицу

/* Заполнение таблицы числами из массивов s1, s2, f1, f2, tf, ff, i, j, mas */
    for (int i=0;i<15;i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(firstStanok[i])));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(secondStanok[i])));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(f1[i]-s1[i])));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(s1[i])));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(f1[i])));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(s2[i])));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(f2[i])));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(QString::number(ff[i])));
        ui->tableWidget->setItem(i,8,new QTableWidgetItem(QString::number(tf[i])));
    }
}

Form::~Form()
{
    delete ui;
}

/* Построение графика */

void Form::makePlot()               // ДОДЕЛАТЬ ШЛАК
{
    ui->customPlot->clearPlottables();//очистить поле от предыдущего графика
    ui->customPlot->yAxis->setPadding(30); //насколько график по оси Y отходит от края виджета
    ui->customPlot->xAxis->setPadding(30); //насколько график по оси Х отходит от края виджета

    /*
    int x_max=0;

    for(int x=0;x<N;x++) if(f1[x]>x_max) x_max=f1[x]; // МАСШТАБ ШЛАКА
    */

    QCPBars *BarFirst = new QCPBars(ui->customPlot->yAxis, ui->customPlot->xAxis);//видимая полоска
    QCPBars *BarSecond = new QCPBars(ui->customPlot->yAxis, ui->customPlot->xAxis);// невидимая полоска
    QVector<double> ticks;//массив значения x
    QVector<double> first;//массив значений x
    QVector<double> second;//массив значений y
    QVector<QString> labels;
    for (int tempN = N;tempN>=1;tempN--) ticks << tempN; // порядок вывода диаграмм
    //рисуется полоска до даты финиша, после чего рисуется полоска невидимого цвета до даты старта
    for (int n=0;n<N;n++) first << firstStanok[n]; // f1[n] было
    for (int n=0;n<N;n++) second <<secondStanok[n];   //s1[n] было
    /* Задание значений для оси Y (подписи на оси) */
    for(int x=0;x<N;x++) labels << "(" + QString::number(firstStanok[x])+ "," + QString::number(secondStanok[x]) + ")";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks,labels);

    ui->customPlot->yAxis->setTicker(textTicker);
    ui->customPlot->yAxis->setBasePen(QPen(Qt::black)); //установка белого цвета цифр
    ui->customPlot->xAxis->setBasePen(QPen(Qt::black)); //для осей Х и Y
    ui->customPlot->xAxis->setTickPen(QPen(Qt::black)); //установка белого цвета черточек
    ui->customPlot->yAxis->setTickPen(QPen(Qt::black)); //для осей Х и Y
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::black)); //белые черточки на оси Y
    ui->customPlot->xAxis->setSubTickPen(QPen(Qt::black)); //белые черточки на оси Х
    ui->customPlot->yAxis->setTickLabelColor(Qt::black); //белые надписи на оси Y
    ui->customPlot->xAxis->setTickLabelColor(Qt::black); //белые надписи на оси X

    //ui->customPlot->setBackground(QBrush(QColor(70, 70, 70))); //задний фон

    ui->customPlot->yAxis->setPadding(30); //насколько график по оси Y отходит от края виджета
    ui->customPlot->xAxis->setPadding(30); //насколько график по оси Х отходит от края виджета
    ui->customPlot->xAxis->setLabel("Время");   //задание названия оси Х
    ui->customPlot->xAxis->setLabelColor(QColor(Qt::black));    //цвет для названия оси Х
    ui->customPlot->xAxis->setLabelPadding(20); //отступ для названия оси Х
    QFont f("Times",14,QFont::Bold);    //выбор шрифта
    //ui->customPlot->xAxis->setLabelFont(f); //задание шрифта для надписи оси Х
    ui->customPlot->yAxis->setLabel("Работы");  //задание названия оси Y
    //ui->customPlot->yAxis->setLabelColor(QColor(Qt::black));    //цвет для названий оси Y
    //ui->customPlot->yAxis->setLabelPadding(20); //отступ для названия оси Y
    //ui->customPlot->yAxis->setLabelFont(f);     //задание шрифта для надписи оси Y
    BarFirst->setBrush(QColor(80, 120, 204)); //цвет диаграммы
    BarFirst->setPen(QPen(QColor(255, 255, 255,255))); //цвет контура диаграммы
    BarSecond->setBrush(QColor(128,255,0)); //цвет невидимой диаграммы
    BarSecond->setPen(QPen(QColor(255, 255, 255,255))); //контур невидимой диаграммы


    //ui->customPlot->xAxis->grid()->setVisible(false);   //сделать невидимой сетку для оси Х
    //ui->customPlot->yAxis->grid()->setVisible(false);   //сделать невидимой сетку для оси Y

    // Данные:



    BarSecond->setData(ticks, second); //нарисовать график, каждому ticks сопоставится fossilData
    BarFirst->setData(ticks,first); //


    int x_max=0;

    for(int x=0;x<N;x++) // МАСШТАБ ШЛАКА (ось икс)
    {
        if (firstStanok[x] > x_max)
        {
            x_max=firstStanok[x];
        }
        else if(secondStanok[x]>x_max)
        {
            x_max=secondStanok[x];
        }
    }
    if (x_max%5 != 0)
        {
            x_max += 5 - x_max%5; // ось икс кратна 5
        }


    ui->customPlot->yAxis->setRange(0, 16*N/15);//установка оси x графика
    ui->customPlot->xAxis->setRange(0, x_max);//установка оси y графика
    ui->customPlot->replot();//нарисовать график
}

/* Построение таблицы */

void Form::make_table()
{
    ui->tableWidget->setColumnCount(col); //число столбцов
    ui->tableWidget->setRowCount(row);   //число строк
    /*
    ui->tableWidget->setColumnWidth(0,100); //задание ширины столбца 1
    ui->tableWidget->setColumnWidth(1,100); //задание ширины столбца 1
    ui->tableWidget->setColumnWidth(2,100);  //задание ширины столбца 2
    ui->tableWidget->setColumnWidth(3,100);  //задание ширины столбца 3
    ui->tableWidget->setColumnWidth(4,100);  //задание ширины столбца 4
    ui->tableWidget->setColumnWidth(5,10);  //задание ширины столбца 5
    */
    for (int i=0;i<row;i++)
    {
     ui->tableWidget->setColumnWidth(i,100);
    }
    //ui->label->setText("Сроки начала и окончания работ"); //задание надписи над таблицей
    //ui->label_2->setText("Резервы времени работ");  //задание надписи над таблицей
    /* Задание названий всех столбцов */
#define UIset (ui->tableWidget->setHorizontalHeaderItem)
    UIset(0, new QTableWidgetItem(tr("1 деталь")));
    UIset(1, new QTableWidgetItem(tr("2 деталь")));
    UIset(2, new QTableWidgetItem(tr("3 деталь")));
    UIset(3, new QTableWidgetItem(tr("4 деталь")));
    UIset(4, new QTableWidgetItem(tr("5 деталь")));
    UIset(5, new QTableWidgetItem(tr("6 деталь")));
    UIset(6, new QTableWidgetItem(tr("7 деталь")));
    UIset(7, new QTableWidgetItem(tr("8 деталь")));
    UIset(8, new QTableWidgetItem(tr("9 деталь")));
    /* Задание надписей под таблицей */

    ui->label_3->setText(QString("Продолжительность критического пути: %1").arg(s));
    ui->label_3->adjustSize();
    ui->label_5->setText(QString("Критический путь: 1->%1->%2->%3->%4->%5->%6").arg(mas[2]).arg(mas[5]).arg(mas[6]).arg(mas[8]).arg(mas[11]).arg(mas[13]));
    ui->label_5->adjustSize();
    ui->label_4->setText(QString("Ожидаемое время выполнения работ (продолжительность проекта): %1").arg(t));
    ui->label_4->adjustSize();
    ui->label_6->setText(QString("Продолжительность минимального пути: %1").arg(d));
    ui->label_6->adjustSize();
}

/* Построить график */
void Form::on_makeGraph_clicked()
{
    /* Считывание чисел из таблицы. Если в таблице поменять значения,
       то при нажатии на кнопку график перестроится с новыми значениями */
    QString number;
    /*
    delete[] i;
    delete[] j;
    delete[] s1;
    delete[] f1;
    */
    std::vector<int> firstStanok(N);
    std::vector<int> secondStanok(N);
    std::vector<int> s1(N);
    std::vector<int> f1(N);
    //старый вывод

    for(int k=0;k<N;k++)
    {
        number=ui->tableWidget->item(k,0)->text();
        firstStanok[k]=number.toInt();
        number=ui->tableWidget->item(k,1)->text();
        secondStanok[k]=number.toInt();
        number=ui->tableWidget->item(k,3)->text();
        firstStanok[k]=number.toInt();
        number=ui->tableWidget->item(k,4)->text();
        secondStanok[k]=number.toInt();
        makePlot(); // временная постройка
        //number=ui->tableWidget->item(k,5)->text();
        /*s2[k]=number.toInt();
        number=ui->tableWidget->item(k,6)->text();
        f2[k]=number.toInt();
        number=ui->tableWidget->item(k,7)->text();
        tf[k]=number.toInt();
        number=ui->tableWidget->item(k,8)->text();
        ff[k]=number.toInt(); */
    }


    makePlot(); //построить график
}

/* Добавление строки в таблицу */
void Form::on_insertRow_clicked()
{
    //int i;
    N = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(N);
    N++;
}

/* Удаление строки из таблицы */
void Form::on_removeRow_clicked()
{
 //   int i;
    N = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(N-1);
    N--;
}
