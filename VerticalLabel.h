#ifndef VERTICALLABEL_H
#define VERTICALLABEL_H

#pragma once
#include <QLabel>
#include <QPainter>

class VerticalLabel : public QLabel {
    Q_OBJECT
public:
    explicit VerticalLabel(QWidget* parent = nullptr) : QLabel(parent) {}

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.translate(0, height());
        painter.rotate(-90);

        painter.drawText(0, 0, height(), width(), alignment(), text());
    }

    QSize sizeHint() const override {
        QSize s = QLabel::sizeHint();
        return QSize(s.height(), s.width());
    }
};


#endif // VERTICALLABEL_H
