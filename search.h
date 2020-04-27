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

public slots:
    void display();

private slots:
    void on_Find_clicked();

    void on_plainTextEdit_cursorPositionChanged();

private:
    Ui::search *ui;
    void loadTextFile();
    void displayFile();
};

#endif // SEARCH_H
