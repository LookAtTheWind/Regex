#include "regex.h"
#include "ui_regex.h"
#include <QDebug>
#include <QRegExp>
#include <vector>
#include <random>
#include <time.h>
#include <QDesktopWidget>

Regex::Regex(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Regex)
{
    ui->setupUi(this);
    srand(unsigned (time(nullptr)));

    // set the position of window
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move((desktop->width() - this->width())/2 + 200, (desktop->height() - this->height())/2 - 100);
}

Regex::~Regex()
{
    delete ui;
}

// respond the keyboard events.
void Regex::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
        on_match_clicked();
}

// set background color of text
void Regex::setTextColor(int pos, const QString &text)
{
    // set the position of current cursor
    QTextCursor tmpCursor = ui->buffer->textCursor();
    tmpCursor.setPosition(pos);
    ui->buffer->setTextCursor(tmpCursor);

    // set background color of text
    if (ui->buffer->find(text))
    {
        QTextCharFormat colorFormat(tmpCursor.charFormat());
        QColor color = rand() % 16777216;
        colorFormat.setBackground(color);
        ui->buffer->mergeCurrentCharFormat(colorFormat);
    }
}

// Regex match
void Regex::on_match_clicked()
{
    QString strExpression = ui->expression->text();
    if (strExpression.isEmpty())
        return;

    // set color of buffer
    ui->buffer->selectAll();
    ui->buffer->setTextBackgroundColor(Qt::white);

    ui->result->clear();

    // get the content of lineEdit
    QRegExp reg;
    reg.setPattern(strExpression);

    // get the content of buffer
    QString strBuffer = ui->buffer->toPlainText();

    std::vector<QString> resultList;
    int pos = 0;
    while (true)
    {
        // find a string from the specific pos.
        // Returns the position of the first match, or -1 if there was no match
        pos = reg.indexIn(strBuffer, pos);
        if (pos == -1)
            break;

        QString string = reg.cap();
        setTextColor(pos, string);
        pos += string.length();

        resultList.emplace_back(string);
    }

    // reset the position of cursor to be 0, that is begin.
    QTextCursor tmpCursor = ui->buffer->textCursor();
    tmpCursor.setPosition(0);
    ui->buffer->setTextCursor(tmpCursor);

    QString result = QString("matched result was %1:").arg(resultList.size());
    ui->labelResult->setText(result);

    // print resultList to the second textEdit.
    for (auto &e : resultList)
        ui->result->append(e);
}
