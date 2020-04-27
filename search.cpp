#include "solution.h"
#include "search.h"
#include "ui_search.h"
#include <QFile>
#include <QTextStream>
#include <map>
#include <QLabel>
#include <QDesktopServices>

void search::display() {
    //ui->plainTextEdit->setPlainText("Not Hello");
    ui->label->setText("https://www.usc.edu/");
    ui->label->setTextFormat(Qt::RichText);
    ui->label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    //ui->label->setOpenExternalLinks(true);
}

search::search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);
    //connect(ui->Find, SIGNAL (released()), this, SLOT(display()));
    QString link = "A time-multiplexed FPGA";
    //ui->label->setTextFormat(Qt::RichText);
    //ui->label->setOpenExternalLinks(true);
    //ui->label->setText("https://www.usc.edu/");
    //QObject::connect(ui->label, &QLabel::linkActivated, [](const QString & link) {
    QDesktopServices::openUrl(QUrl(link));
    //});
    loadTextFile();    
}

search::~search()
{
    delete ui;
}


void search::on_Find_clicked()
{
    publication p;
    QString searchString = ui->lineEdit->text();
    std::string searchKeyword = searchString.toUtf8().constData();
    vector<string> paper_title=p.format_input(searchKeyword);
    map<int,vector<vector<string>>> m1 = p.title_search(paper_title);
    //cout<<"Search results:==>>"<<endl;
    string out;
    QString output;
    if(m1.empty())
         ui->plainTextEdit->setPlainText("Not found");
    else
    {
        for(auto it=m1.rbegin();it!=m1.rend();it++) //highest frequency match displayed first
        {
            for(auto& it1:(*it).second)
            {
                for(auto& it2:it1) {
                    out += it2;
                }
            }
            //if(((*it).first)==int(paper_title.size())) //perfect frequency match found, only display that title
             //   break;
        }
        output = QString::fromStdString(out);
        ui->plainTextEdit->setPlainText(output);
        //ui->plainTextEdit->setPlainText("https://www.usc.edu/");
        //QLabel *myLabel = new QLabel(this);


        //connect (ui->Find, SIGNAL(search::on_Click()), ui->label, SLOT(search::displayFile()));
    }

    //ui->textEdit->find(searchString, QTextDocument::FindWholeWords);
    //connect(ui->Find, SIGNAL (released()), this, SLOT(displayFile()));

    //QString link = "https://www.usc.edu/";
    //ui->label->setTextFormat(Qt::RichText);
    //ui->label->setOpenExternalLinks(true);
    //ui->label->setText("https://www.usc.edu/");
    //QObject::connect(ui->label, &QLabel::linkActivated, [](const QString & link) {
    //QDesktopServices::openUrl(QUrl("https://www.usc.edu/"));
}

void search::loadTextFile()
{
    QFile inputFile(":/input_text.txt");
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();
    //ui->textEdit->setPlainText(line);
    //QTextCursor cursor = ui->textEdit->textCursor();
    //cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
}

void search::displayFile() {
    //ui->plainTextEdit->setPlainText("Not Hello");
    ui->label->setText("https://www.usc.edu/");
    ui->label->setTextFormat(Qt::RichText);
    ui->label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->label->setOpenExternalLinks(true);
    //ui->label->mousePressEvent();
}



//void search::on_Click() {

//}

void search::on_plainTextEdit_cursorPositionChanged()
{
    ui->label->setText("https://ieeexplore.ieee.org/abstract/document/624601");
    QObject::connect(ui->label, &QLabel::linkActivated, [](const QString & link) {
    QDesktopServices::openUrl(QUrl(link));
});
}
