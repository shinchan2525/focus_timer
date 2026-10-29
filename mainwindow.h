#pragma once

#include <QWidget>

class QLabel;
class QPushButton;
class QTimer;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onStartPause();
    void onReset();
    void onTick();

private:
    void updateDisplay();

    static constexpr int kWorkSeconds = 25 * 60;

    QLabel *m_timeLabel;
    QPushButton *m_startButton;
    QPushButton *m_resetButton;
    QTimer *m_timer;
    int m_remainingSeconds;
};