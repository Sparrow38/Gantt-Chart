#ifndef FORM_H
#define FORM_H
#include <QWidget>
#include <vector>


const int row = 15; // количество деталей
const int col = 9; // количество станков

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(int s1[], int f1[], int s2[], int f2[], int ff[], int tf[], int firstStanok[], int secondStanok[], /*int s,*/ int mas[],/* int t, int d,*/ QWidget *parent = 0);
    ~Form();

    std::vector<int> s1 = std::vector<int>(15);
    std::vector<int> f1 = std::vector<int>(15);
    std::vector<int> s2 = std::vector<int>(15);
    std::vector<int> f2 = std::vector<int>(15);
    std::vector<int> ff = std::vector<int>(15);
    std::vector<int> tf = std::vector<int>(15);
    std::vector<int> firstStanok = std::vector<int>(15);
    std::vector<int> secondStanok = std::vector<int>(15);
    std::vector<int> mas = std::vector<int>(15);
    int s,t,d,N=15;

    /*
    int arr[row][col] = {
        {  5, 8, 1},
        { 3,  4, 10},
        { 5, 10,  4},
        { 2, 8,  6},
        {7, 2, 7},
        {8, 3, 4}
    };
    */

    /*
    //int *s1=new int[15];
    //int *f1=new int[15];
    //int s2[15];
    //int f2[15];
    //int ff[15];
    //int tf[15];
    //int *i=new int[15];
    //int *j=new int[15];
    int t;
    //int mas[15];
    int d;
    int N = 15; */
    void make_table();

private slots:
    void makePlot();
    void on_makeGraph_clicked();
    void on_insertRow_clicked();
    void on_removeRow_clicked();

private:
    Ui::Form *ui;
};
#endif
