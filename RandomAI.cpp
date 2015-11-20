#include "RandomAI.h"
#include "Snake.h"

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
MoveDirection RandomAI::getNextMove(Snake *controllerSnake, Map *map){
    int kof[4] = {1,1,1,1};
    QPoint head = controllerSnake->position;

    /*QPoint second = controllerSnake->tail.first();

    if(controllerSnake->tail.size()==NULL)
	second=head;

    QPoint buf = head - second;


    //учет положения первого за головой хвоста
/*    if(buf.x()!=buf.y())
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
            */

   //учет стен, дырок, остального хвоста
    if((head.x()-1)<0)
        kof[LEFT]=-1;
    else
        if(map->getField()[head.x()-1][head.y()]!=NULL)
            if((map->getField()[head.x()-1][head.y()]->getId()>=OBJECT_FIRST && map->getField()[head.x()-1][head.y()]->getId()<=SNAKE_NPC))
                kof[LEFT]=-1;

    if((head.x()+1)>=map->getSizeX())
        kof[RIGHT]=-1;
    else
        if(map->getField()[head.x()+1][head.y()]!=NULL)
            if((map->getField()[head.x()+1][head.y()]->getId()>=OBJECT_FIRST && map->getField()[head.x()+1][head.y()]->getId()<=SNAKE_NPC))
                kof[RIGHT]=-1;

    if((head.y()+1) >= map->getSizeY())
        kof[UP]=-1;
    else
        if(map->getField()[head.x()][head.y()+1]!=NULL)
            if((map->getField()[head.x()][head.y()+1]->getId()>=OBJECT_FIRST && map->getField()[head.x()][head.y()+1]->getId()<=SNAKE_NPC))
                kof[UP]=-1;

    if((head.y()-1) <0)
        kof[DOWN]=-1;
    else
        if(map->getField()[head.x()][head.y()-1]!=NULL)
            if((map->getField()[head.x()][head.y()-1]->getId()>=OBJECT_FIRST && map->getField()[head.x()][head.y()-1]->getId()<=SNAKE_NPC))
            kof[DOWN]=-1;


    int ForRand=0, Rand;
    for(int i=0;i<4;i++)
        if(kof[i]>0)
            ForRand+=kof[i];

    if(ForRand==0) //выхода нет :)
    {
        Rand=rand()%4;
        if(kof[Rand]==-2)
            return (MoveDirection)((Rand+1)%4);
        else return (MoveDirection)Rand;
    }

    Rand=rand()%ForRand+1;

    int t=0;
    for(int i=0;i<4;i++)
        if(kof[i]>0){
            if(Rand>=t && Rand <=t+kof[i])
                return (MoveDirection)i;
            t+=kof[i];
        }

    return UP;

}

QString RandomAI::getName() const
{
	return "RandomAI";
}
