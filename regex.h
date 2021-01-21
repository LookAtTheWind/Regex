#ifndef REGEX_H
#define REGEX_H

#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Regex; }
QT_END_NAMESPACE

class Regex : public QMainWindow
{
    Q_OBJECT

public:
    Regex(QWidget *parent = nullptr);
    ~Regex();

    void setTextColor(int pos, const QString &string);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_match_clicked();

private:
    Ui::Regex *ui;
};
#endif // REGEX_H
