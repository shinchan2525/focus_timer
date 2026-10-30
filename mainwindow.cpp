#include "mainwindow.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QApplication>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , m_modeLabel(new QLabel("作業中",this))
    , m_timeLabel(new QLabel(this))
    , m_taskEdit(new QLineEdit(this))
    , m_startButton(new QPushButton("スタート", this))
    , m_resetButton(new QPushButton("リセット", this))
    , m_timer(new QTimer(this))
    , m_mode(Mode::Work)
    , m_remainingSeconds(kWorkSeconds)
{
    setWindowTitle("作業タイマー");

    QFont font = m_timeLabel->font();
    font.setPointSize(48);
    m_taskEdit->setPlaceholderText("作業内容を入力");
    m_timeLabel->setFont(font);
    m_timeLabel->setAlignment(Qt::AlignCenter);
    m_modeLabel->setAlignment(Qt::AlignCenter);

    auto *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_startButton);
    buttonLayout->addWidget(m_resetButton);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_modeLabel);
    mainLayout->addWidget(m_timeLabel);
    mainLayout->addWidget(m_taskEdit);
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
    m_mode = Mode::Work;
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
        if(m_mode == Mode::Work) {
            m_mode = Mode::Break;
            m_remainingSeconds = kBreakSeconds;
        } else {
            m_mode = Mode::Work;
            m_remainingSeconds = kWorkSeconds;
        }
        QApplication::beep();
        updateDisplay();
    }
}

void MainWindow::updateDisplay()
{
    const int minutes = m_remainingSeconds / 60;
    const int seconds = m_remainingSeconds % 60;
    m_timeLabel->setText(QString("%1:%2")
                             .arg(minutes, 2, 10, QChar('0'))
                             .arg(seconds, 2, 10, QChar('0')));

    if(m_mode == Mode::Work) {
        m_modeLabel->setText("作業中");
    } else {
        m_modeLabel->setText("休憩中");
    }
}