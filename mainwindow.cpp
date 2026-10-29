#include "mainwindow.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , m_timeLabel(new QLabel(this))
    , m_startButton(new QPushButton("スタート", this))
    , m_resetButton(new QPushButton("リセット", this))
    , m_timer(new QTimer(this))
    , m_remainingSeconds(kWorkSeconds)
{
    setWindowTitle("作業タイマー");

    QFont font = m_timeLabel->font();
    font.setPointSize(48);
    m_timeLabel->setFont(font);
    m_timeLabel->setAlignment(Qt::AlignCenter);

    auto *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_startButton);
    buttonLayout->addWidget(m_resetButton);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_timeLabel);
    mainLayout->addLayout(buttonLayout);

    m_timer->setInterval(1000);  // 1秒ごとに timeout を発生させる

    connect(m_timer, &QTimer::timeout, this, &MainWindow::onTick);
    connect(m_startButton, &QPushButton::clicked, this, &MainWindow::onStartPause);
    connect(m_resetButton, &QPushButton::clicked, this, &MainWindow::onReset);

    updateDisplay();
    resize(320, 200);
}

void MainWindow::onStartPause()
{
    if (m_timer->isActive()) {
        m_timer->stop();
        m_startButton->setText("再開");
        return;
    }
    if (m_remainingSeconds == 0) {
        m_remainingSeconds = kWorkSeconds;
        updateDisplay();
    }
    m_timer->start();
    m_startButton->setText("一時停止");
}

void MainWindow::onReset()
{
    m_timer->stop();
    m_remainingSeconds = kWorkSeconds;
    m_startButton->setText("スタート");
    updateDisplay();
}

void MainWindow::onTick()
{
    if (m_remainingSeconds > 0) {
        --m_remainingSeconds;
        updateDisplay();
    }
    if (m_remainingSeconds == 0) {
        m_timer->stop();
        m_startButton->setText("スタート");
        QMessageBox::information(this, "完了", "25分おつかれさまでした。休憩しましょう。");
    }
}

void MainWindow::updateDisplay()
{
    const int minutes = m_remainingSeconds / 60;
    const int seconds = m_remainingSeconds % 60;
    m_timeLabel->setText(QString("%1:%2")
                             .arg(minutes, 2, 10, QChar('0'))
                             .arg(seconds, 2, 10, QChar('0')));
}