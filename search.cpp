#include "solution.h"
#include "search.h"
#include "ui_search.h"
#include <QFile>
#include <QTextStream>
#include <map>
#include <QLabel>
#include <QDesktopServices>
#include <QInputDialog>

std::vector<string> lines;

search::search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::search)
{
    loadTextFile();
    ui->setupUi(this);
}

search::~search()
{
    delete ui;
}


void search::on_Find_clicked()
{
    BST b(lines);
    QString searchQString = ui->lineEdit->text();
    std::string searchstring = searchQString.toUtf8().constData();

    b.find(searchstring);
    std::vector<pair<std::string, std::string>> v = b.results;
    string results = std::to_string(v.size()) + " results found";
    QString qresults = QString::fromStdString(results);
    ui->textBrowser->setText(qresults);

    for (auto it=v.rbegin();it!=v.rend();it++) {
        string output = it->first;
        QString qoutput = QString::fromStdString(output);
        string urllink = it->second;
        QString qurllink = QString::fromStdString(urllink);
        QString outputdata = "<a href=\"" + qurllink + "\">" + qoutput + "</a>";
        ui->textBrowser->setOpenExternalLinks(true);
        if (it == v.rbegin())
            ui->textBrowser->setText(outputdata);
        else
            ui->textBrowser->append(outputdata);
    }
}

void search::loadTextFile() {
    QFile inputFile(":/title_url.txt");
    inputFile.open(QIODevice::ReadOnly);
    QTextStream in(&inputFile);
    while (!in.atEnd()) {
        QString Qline = in.readLine();
        std::string line = Qline.toUtf8().constData();
        lines.push_back(line);
    }
    inputFile.close();
}
