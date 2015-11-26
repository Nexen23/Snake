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
MoveDirection RandomAI::getNextMove(const Snake *controllerSnake, const Map *map){
    QMap<MoveDirection, int> forKof;
    forKof[LEFT]=0;
    forKof[RIGHT]=1;
    forKof[UP]=2;
    forKof[DOWN]=3;
    int kof[4] = {1,1,1,1};
    QPoint second;
    QPoint head = controllerSnake->position;
    if(controllerSnake->tail.size()==NULL)
        second=head;
    else
        second = controllerSnake->tail.first();



    QPoint buf = head - second;


    //учет положения первого за головой хвоста
    if(buf.x()!=buf.y())
        if(buf.x()==0)
            if(buf.y()<0){
                kof[forKof[DOWN]]-=4;
                kof[forKof[UP]]+=1;
            }   else    {
                kof[forKof[UP]]-=4;
                kof[forKof[DOWN]]+=1;
            }
        else
            if(buf.x()>0){
                kof[forKof[RIGHT]]+=1;
                kof[forKof[LEFT]]-=4;
            }   else    {
                kof[forKof[LEFT]]+=1;
                kof[forKof[RIGHT]]-=4;
            }


   //учет стен, дырок, остального хвоста
    if((head.x()-1)<0)
        kof[forKof[LEFT]]-=2;
    else
        if(map->getField()[head.x()-1][head.y()]!=NULL)
            if(map->getField()[head.x()-1][head.y()]->getType()==OBJECT || map->getField()[head.x()-1][head.y()]->getType()==SNAKE)
                kof[forKof[LEFT]]-=2;

    if((head.x()+1)>=map->getSizeX())
        kof[forKof[RIGHT]]-=2;
    else
        if(map->getField()[head.x()+1][head.y()]!=NULL)
            if(map->getField()[head.x()+1][head.y()]->getType()==OBJECT || map->getField()[head.x()+1][head.y()]->getType()==SNAKE)
                kof[forKof[RIGHT]]-=2;

    if((head.y()+1) >= map->getSizeY())
        kof[forKof[DOWN]]-=2;
    else
        if(map->getField()[head.x()][head.y()+1]!=NULL)
            if(map->getField()[head.x()][head.y()+1]->getType()==OBJECT || map->getField()[head.x()][head.y()+1]->getType()==SNAKE)
                kof[forKof[DOWN]]-=2;

    if((head.y()-1) <0)
        kof[forKof[UP]]-=2;
    else
        if(map->getField()[head.x()][head.y()-1]!=NULL)
            if(map->getField()[head.x()][head.y()-1]->getType()==OBJECT || map->getField()[head.x()][head.y()-1]->getType()==SNAKE)
            kof[forKof[UP]]-=2;


    int ForRand=0, Rand;
    for(int i=0;i<4;i++)
        if(kof[i]>0)
            ForRand+=kof[i];

    if(ForRand==0) //выхода нет :)
    {
        Rand=rand()%4;
        if(kof[Rand]==-5)
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
