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
    Publication b(lines);
    QString searchQString = ui->lineEdit->text();
    std::string searchstring = searchQString.toUtf8().constData();

    b.find(searchstring);
    std::map <int, std::vector<pair<std::string, std::string>>> v = b.results;
    unordered_set<string> display_title;
    ui->textBrowser->clear();

    if (v.size() == 0) {
        ui->textBrowser->setText("No results found");
    }

    for (auto it = v.rbegin(); it != v.rend(); it++) {
        for (auto it1 : it->second) {
            if(!display_title.count((it1).first)) {
                string output = it1.first;
                QString qoutput = QString::fromStdString(output);
                string urllink = it1.second;
                QString qurllink = QString::fromStdString(urllink);
                QString outputdata = "<a href=\"" + qurllink + "\">" + qoutput + "</a>";
                ui->textBrowser->setOpenExternalLinks(true);
                ui->textBrowser->append(outputdata);

                display_title.insert((it1).first);
            }
        }
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
