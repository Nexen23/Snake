#ifndef SCORE_H
#define SCORE_H

#include <QObject>

class Score
{
public:
    explicit Score();
    Score(int amount);
		~Score();

	int amount = 0;
};

#endif // SCORE_H
