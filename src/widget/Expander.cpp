#include <QPropertyAnimation>

#include "Expander.h"

Expander::Expander(const QString & title, const int animationDuration, QWidget *parent) : QWidget(parent), animationDuration(animationDuration) {
    toggleButton.setStyleSheet("QToolButton { border: none; }");
    toggleButton.setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toggleButton.setArrowType(Qt::ArrowType::RightArrow);
    toggleButton.setText(title);
    toggleButton.setCheckable(true);
    toggleButton.setChecked(false);

    headerLine.setFrameShape(QFrame::HLine);
    headerLine.setFrameShadow(QFrame::Plain);
    headerLine.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    headerLine.setStyleSheet("color: rgb(200, 200, 200)");

    contentArea.setStyleSheet("QScrollArea { border: 0px solid lightgray }");
    contentArea.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    contentArea.setMaximumHeight(0);
    contentArea.setMinimumHeight(0);

#define ADD_ANIM(target, prop) { \
    auto anim = new QPropertyAnimation(target, prop); \
    anim->setEasingCurve(QEasingCurve::InOutQuad); \
    toggleAnimation.addAnimation(anim); \
}

    // let the entire widget grow and shrink with its content
    ADD_ANIM(this, "minimumHeight");
    ADD_ANIM(this, "maximumHeight");
    ADD_ANIM(&contentArea, "maximumHeight");

#undef ADD_ANIM

    mainLayout.setVerticalSpacing(0);
    mainLayout.setContentsMargins(0, 0, 0, 0);

    int row = 0;
    mainLayout.addWidget(&toggleButton, row, 0, 1, 1, Qt::AlignLeft);
    mainLayout.addWidget(&headerLine, row++, 2, 1, 1);
    mainLayout.addWidget(&contentArea, row, 0, 1, 3);
    setLayout(&mainLayout);
    QObject::connect(&toggleButton, &QToolButton::clicked, [this](const bool checked) {
        toggleButton.setArrowType(checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
        toggleAnimation.setDirection(checked ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
        toggleAnimation.start();
        emit stateChanged(checked);
    });

}

void Expander::setContentLayout(QLayout & contentLayout) {
    delete contentArea.layout();
    contentArea.setLayout(&contentLayout);
    const auto collapsedHeight = sizeHint().height() - contentArea.maximumHeight();
    auto contentHeight = contentLayout.sizeHint().height();
    for (int i = 0; i < toggleAnimation.animationCount() - 1; ++i) {
        QPropertyAnimation * spoilerAnimation = static_cast<QPropertyAnimation *>(toggleAnimation.animationAt(i));
        spoilerAnimation->setDuration(animationDuration);
        spoilerAnimation->setStartValue(collapsedHeight);
        spoilerAnimation->setEndValue(collapsedHeight + contentHeight);
    }
    QPropertyAnimation * contentAnimation = static_cast<QPropertyAnimation *>(toggleAnimation.animationAt(toggleAnimation.animationCount() - 1));
    contentAnimation->setDuration(animationDuration);
    contentAnimation->setStartValue(0);
    contentAnimation->setEndValue(contentHeight);
}

void Expander::setState(bool state)
{
    if(toggleButton.isChecked() == state)
        return;

    toggleButton.setChecked(state);
    toggleButton.setArrowType(state ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
    toggleAnimation.setDirection(state ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
    toggleAnimation.start();
}
