#include "RandomAI.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
RandomAI::RandomAI()
{
    return;
}

/**
 * @author MGerasimchuk
 * 25.10
 */
RandomAI::~RandomAI()
{

}
//0-Left; 1-Right; 2-up; 3-down;
// LEFT, RIGHT, UP, DOWN
RandomAI::getNextMove(Snake *controllerSnake, Map *map){

    QPoint head = controllerSnake->position , second = controllerSnake->tail.first();

    if(controllerSnake->tail.size()==NULL)
        second=head;

    QPoint buf = head - second;

    int kof[4] = {1,1,1,1};
    //учет положения первого за головой хвоста
    if(buf.x()!=buf.y())
        if(buf.x()==0)
            if(buf.y()>0){
                kof[DOWN]=-2;
                kof[UP]=2;
            }   else    {
                kof[UP]=-2;
                kof[DOWN]=2;
            }
        else
            if(buf.x()>0){
                kof[RIGHT]=2;
                kof[LEFT]=-2;
            }   else    {
                kof[LEFT]=2;
                kof[RIGHT]=-2;
            }
   //учет стен, дырок, остального хвоста
    if(map->field[head.x()-1][head.y()]->getId()>=WALL_OBJECT && map->field[head.x()-1][head.y()]<=SNAKE)
        kof[LEFT]=-1;

    if(map->field[head.x()+1][head.y()]->getId()>=WALL_OBJECT && map->field[head.x()+1][head.y()]<=SNAKE)
        kof[RIGHT]=-1;

    if(map->field[head.x()][head.y()+1]->getId()>=WALL_OBJECT && map->field[head.x()][head.y()+1]<=SNAKE)
        kof[UP]=-1;

    if(map->field[head.x()][head.y()-1]->getId()>=WALL_OBJECT && map->field[head.x()][head.y()-1]<=SNAKE)
        kof[DOWN]=-1;


    int ForRand=0, Rand;
    for(int i=0;i<4;i++)
        if(kof[i]>0)
            ForRand+=kof[i];

    if(ForRand==0) //выхода нет :)
    {
        Rand=rand()%4;
        if(Rand==-2)
            return (Rand+1)%4;
        else return Rand;
    }

    Rand=rand()%ForRand+1;

    int t=0;
    for(int i=0;i<4;i++)
        if(kof[i]>0){
            if(Rand>=t && Rand <=t+kof[i])
                return i;
            t+=kof[i];
        }

    return 1;

}
