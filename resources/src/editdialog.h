#pragma once
#include <QDialog>
#include "models.h"
#include <Qt>

class QLineEdit; class QSpinBox; class QDoubleSpinBox; class QCheckBox; class QDialogButtonBox;


class EditDialog : public QDialog {
    Q_OBJECT
public:
    explicit EditDialog(QWidget* parent = nullptr);
    void setItem(const Item& it);
    Item item() const { return item_; }


private slots:
    void onNameChanged(const QString&); // handler 13
    void onQuantityChanged(int); // handler 14
    void onPriceChanged(double); // handler 15
    void onActiveChanged(Qt::CheckState); // handler 16
    void onAccept(); // handler 17


private:
    void setupUi();
    void syncToUi();


    Item item_{};
    QLineEdit* nameEdit_{};
    QSpinBox* qtySpin_{};
    QDoubleSpinBox* priceSpin_{};
    QCheckBox* activeBox_{};
    QDialogButtonBox* buttons_{};
};
