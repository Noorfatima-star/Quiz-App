#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMessageBox>
#include <QStackedWidget>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Quiz App");
    setMinimumSize(700, 500);

    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    // ============ PAGE 1: START PAGE ============
    startPage = new QWidget();
    startPage->setStyleSheet(
        "border-image: url(C:/Users/HF/source/repos/Quiz-App/QuizApp/front.jpg) 0 0 0 0 stretch stretch;"
        );
    QVBoxLayout *startLayout = new QVBoxLayout(startPage);
    startLayout->setAlignment(Qt::AlignCenter);
    startLayout->setSpacing(20);

    titleLabel = new QLabel("✨ Famous Women in History & Science ✨");
    titleLabel->setWordWrap(true);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "font-size: 26px; font-weight: bold; color: #6A1B9A;"
        "background-color: rgba(255,255,255,180);"
        "padding: 20px; border-radius: 10px;"
        );

    startButton = new QPushButton("Start Quiz");
    startButton->setFixedWidth(200);
    startButton->setStyleSheet(
        "font-size: 16px; padding: 12px;"
        "background-color: #AB47BC; color: white;"
        "border-radius: 10px;"
        );

    startLayout->addWidget(titleLabel);
    startLayout->addWidget(startButton, 0, Qt::AlignCenter);

    // ============ PAGE 2: QUIZ PAGE ============
    quizPage = new QWidget();
    quizPage->setStyleSheet("background-color: #F3E5F5;");
    QVBoxLayout *mainLayout = new QVBoxLayout(quizPage);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(40, 30, 40, 30);

    scoreLabel = new QLabel("Score: 0");
    scoreLabel->setAlignment(Qt::AlignRight);
    scoreLabel->setStyleSheet("font-size: 14px; color: #7B1FA2; font-weight: bold;");
    mainLayout->addWidget(scoreLabel);

    questionLabel = new QLabel("Press Start to begin!");
    questionLabel->setWordWrap(true);
    questionLabel->setAlignment(Qt::AlignCenter);
    questionLabel->setStyleSheet(
        "font-size: 18px; font-weight: bold;"
        "background-color: #CE93D8; color: white;"
        "padding: 20px; border-radius: 10px;"
        );
    mainLayout->addWidget(questionLabel);

    buttonGroup = new QButtonGroup(this);
    optionA = new QRadioButton("A)");
    optionB = new QRadioButton("B)");
    optionC = new QRadioButton("C)");
    optionD = new QRadioButton("D)");

    QString optionStyle = "font-size: 15px; padding: 5px; color: #7B1FA2;";
    optionA->setStyleSheet(optionStyle);
    optionB->setStyleSheet(optionStyle);
    optionC->setStyleSheet(optionStyle);
    optionD->setStyleSheet(optionStyle);

    buttonGroup->addButton(optionA, 0);
    buttonGroup->addButton(optionB, 1);
    buttonGroup->addButton(optionC, 2);
    buttonGroup->addButton(optionD, 3);

    mainLayout->addWidget(optionA);
    mainLayout->addWidget(optionB);
    mainLayout->addWidget(optionC);
    mainLayout->addWidget(optionD);

    nextButton = new QPushButton("Next Question");
    nextButton->setStyleSheet(
        "font-size: 16px; padding: 10px;"
        "background-color: #AB47BC; color: white;"
        "border-radius: 8px;"
        );
    mainLayout->addWidget(nextButton);

    // ============ PAGE 3: RESULT PAGE ============
    resultPage = new QWidget();
    resultPage->setStyleSheet(
        "border-image: url(C:/Users/HF/source/repos/Quiz-App/QuizApp/back.jpg) 0 0 0 0 stretch stretch;"
        );
    QVBoxLayout *resultLayout = new QVBoxLayout(resultPage);
    resultLayout->setAlignment(Qt::AlignCenter);
    resultLayout->setSpacing(20);

    resultLabel = new QLabel("Quiz Complete!");
    resultLabel->setWordWrap(true);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setStyleSheet(
        "font-size: 24px; font-weight: bold; color: #6A1B9A;"
        "background-color: rgba(255,255,255,180);"
        "padding: 20px; border-radius: 10px;"
        );

    restartButton = new QPushButton("Play Again");
    restartButton->setFixedWidth(200);
    restartButton->setStyleSheet(
        "font-size: 16px; padding: 12px;"
        "background-color: #AB47BC; color: white;"
        "border-radius: 10px;"
        );

    resultLayout->addWidget(resultLabel);
    resultLayout->addWidget(restartButton, 0, Qt::AlignCenter);

    // Add all pages to stack
    stack->addWidget(startPage);   // index 0
    stack->addWidget(quizPage);    // index 1
    stack->addWidget(resultPage);  // index 2
    stack->setCurrentIndex(0);

    // Connections
    connect(startButton, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::onNextClicked);
    connect(restartButton, &QPushButton::clicked, this, &MainWindow::onStartClicked);

    currentQuestion = 0;
    quizGame.loadQuestions("C:/Users/HF/source/repos/Quiz-App/QuizApp/questions.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStartClicked()
{
    currentQuestion = 0;
    player = ::player();
    optionA->show(); optionB->show();
    optionC->show(); optionD->show();
    scoreLabel->setText("Score: 0");
    stack->setCurrentIndex(1);
    showQuestion();
}

void MainWindow::onNextClicked()
{
    int selected = buttonGroup->checkedId();
    if(selected == -1) {
        QMessageBox::warning(this, "Warning", "Please select an answer!");
        return;
    }

    char answers[] = {'A', 'B', 'C', 'D'};
    char correct = quizGame.question[currentQuestion].correctAnswer;

    if(answers[selected] == correct) {
        player.addScore();
        QMessageBox::information(this, "Correct! ✅", "Great job! That's right!");
    } else {
        QMessageBox::information(this, "Oops! ❌",
                                 QString("Wrong answer!\nCorrect answer was: ") + correct);
    }

    currentQuestion++;
    scoreLabel->setText("Score: " + QString::number(player.getScore()));

    if(currentQuestion >= quizGame.tq) {
        resultLabel->setText(
            "🎉 Quiz Complete! 🎉\n\nYour Score: " +
            QString::number(player.getScore()) + " / " +
            QString::number(quizGame.tq)
            );
        stack->setCurrentIndex(2);
        return;
    }

    showQuestion();
}

void MainWindow::showQuestion()
{
    questionLabel->setText(
        QString::fromStdString(quizGame.question[currentQuestion].text)
        );
    optionA->setText(QString::fromStdString(quizGame.question[currentQuestion].options[0]));
    optionB->setText(QString::fromStdString(quizGame.question[currentQuestion].options[1]));
    optionC->setText(QString::fromStdString(quizGame.question[currentQuestion].options[2]));
    optionD->setText(QString::fromStdString(quizGame.question[currentQuestion].options[3]));
    buttonGroup->setExclusive(false);
    optionA->setChecked(false);
    optionB->setChecked(false);
    optionC->setChecked(false);
    optionD->setChecked(false);
    buttonGroup->setExclusive(true);
}