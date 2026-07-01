#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QStackedWidget>
#include "Question.h"
#include "Player.h"
#include "Quiz.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onStartClicked();
    void onNextClicked();
    void showQuestion();

private:
    Ui::MainWindow *ui;
    quiz quizGame;
    player player;
    int currentQuestion;

    QStackedWidget *stack;

    // Page 1: Start Page
    QWidget *startPage;
    QLabel *titleLabel;
    QPushButton *startButton;

    // Page 2: Quiz Page
    QWidget *quizPage;
    QLabel *questionLabel;
    QRadioButton *optionA;
    QRadioButton *optionB;
    QRadioButton *optionC;
    QRadioButton *optionD;
    QPushButton *nextButton;
    QLabel *scoreLabel;
    QButtonGroup *buttonGroup;

    // Page 3: Result Page
    QWidget *resultPage;
    QLabel *resultLabel;
    QPushButton *restartButton;
};
#endif // MAINWINDOW_H