#pragma once

#include <QWidget>

class QLabel;
class QPushButton;
class QLineEdit;
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
    enum class Mode{Work, Break};
    void updateDisplay();
    void appendWorkLog();

    static constexpr int kWorkSeconds = 25 * 60;
    static constexpr int kBreakSeconds = 5 * 60;

    QLabel *m_modeLabel;
    QLabel *m_timeLabel;
    QLineEdit *m_taskEdit;
    QPushButton *m_startButton;
    QPushButton *m_resetButton;
    QTimer *m_timer;
    Mode m_mode; // 現在のモード　(　作業中 or 休憩中　)
    int m_remainingSeconds;
};