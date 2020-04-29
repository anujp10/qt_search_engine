#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>
#include <iostream>
#include <map>

namespace Ui {
class search;
}

class search : public QWidget
{
    Q_OBJECT

public:
    explicit search(QWidget *parent = 0);
    ~search();

private slots:
    void on_Find_clicked();

private:
    Ui::search *ui;
    void loadTextFile();
};

#endif // SEARCH_H
