#ifndef CELLLABEL_H
#define CELLLABEL_H

#include <QLabel>

class CellLabel : public QLabel
{
public:
    explicit CellLabel();
    ~CellLabel();

    void Set();
};

#endif // CELLLABEL_H
