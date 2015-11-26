#include "SimpleAI.h"
#include "Snake.h"
/**
 * @author MGerasimchuk
 * 25.10
 */
SimpleAI::SimpleAI()
{

}

/**
 * @author MGerasimchuk
 * 25.10
 */
SimpleAI::~SimpleAI()
{

}

//0-Left; 1-Right; 2-up; 3-down;
// LEFT, RIGHT, UP, DOWN

/*
FOOD_ITEM,
BOMB_ITEM,

WALL_OBJECT,
HOLE_OBJECT,

SNAKE*/
MoveDirection SimpleAI::getDirection(QPoint buf,int x1,int y1)
{
    int x=x1-buf.x();
    int y=y1-buf.y();
    if( x-y>=0 && y+x<0)//if( x+y>0 && y-x>=0)
        return UP;
    if(y+x>=0 && x-y>0)//(y-x<0 && y+x>=0)
        return RIGHT;
    if(x-y<=0 && y+x>0)//(y+x<0 && y-x<=0)
        return DOWN;
    if(y+x<=0 && x-y<0)//(y-x>0 && y+x<=0)
        return LEFT;

		qFatal("Impossible condition reach!");
		return UP;
}

MoveDirection SimpleAI::getNextMove(const Snake *controllerSnake, const Map *map)
{
    QMap<MoveDirection, int> forKof;
    forKof[LEFT]=0;
    forKof[RIGHT]=1;
    forKof[UP]=2;
    forKof[DOWN]=3;
    QPoint second;
    QPoint head = controllerSnake->position;
    if(controllerSnake->tail.size()==NULL)
        second=head;
    else
        second = controllerSnake->tail.first();



    QPoint buf = head - second;
    int kof[4] = {10,10,10,10};
    //for(int i=0;i<4;i++){   kof[i] =100;  }

    //учет положения первого за головой хвоста
    if(buf.x()!=buf.y())
        if(buf.x()==0)
            if(buf.y()<0){
                kof[forKof[DOWN]]-=45200;
                kof[forKof[UP]]+=20;
            }   else    {
                kof[forKof[UP]]-=45200;
                kof[forKof[DOWN]]+=20;
            }
        else
            if(buf.x()>0){
                kof[forKof[RIGHT]]+=20;
                kof[forKof[LEFT]]-=45200;
            }   else    {
                kof[forKof[LEFT]]+=20;
                kof[forKof[RIGHT]]-=45200;
            }


int /*x=0,y=0, */sizeX = map->getSizeX()-1, sizeY = map->getSizeY()-1;
    if(head.x()-2<0)
        kof[forKof[LEFT]]-=50;
    if(head.x()+2>sizeX)
        kof[forKof[RIGHT]]-=50;
    if(head.y()-2<0)
        kof[forKof[UP]]-=50;
    if(head.y()+2>sizeY)
        kof[forKof[DOWN]]-=50;
    if(head.x()-1<0)
        kof[forKof[LEFT]]-=10050;
    if(head.x()+1>sizeX)
        kof[forKof[RIGHT]]-=10050;
    if(head.y()-1<0)
        kof[forKof[UP]]-=10050;
    if(head.y()+1>sizeY)
        kof[forKof[DOWN]]-=10050;
MoveDirection buf1;
for(int i=(head.y()-5);i<(head.y()+5);i++)
    for(int j=(head.x()-5);j<(head.x()+5);j++)
    {

        if(j<0 || j>sizeX){
            //kof[forKof[buf1]]+=1;
            continue;
        }
        if(i<0 || i>sizeY){
            //kof[forKof[buf1]]+=1;
            continue;
        }
        if(head.x()==j && head.y()==i)
            continue;
        buf1=getDirection(head,j,i);
        if(map->getField()[j][i]==NULL)
            kof[forKof[buf1]]+=1;
        else
        {
            if(map->getField()[j][i]->getType()==OBJECT || map->getField()[j][i]->getType()==SNAKE)
            {

                kof[forKof[buf1]]-=(abs(kof[forKof[buf1]])/(abs(head.x()-j)+abs(head.y()-i))+5);
                if(abs(head.x()-j)<=1 && abs(head.y()-i)<=1)
                    kof[forKof[buf1]]-=400;
            }
            else
            {
                if(map->getField()[j][i]->getType()==ITEM)
                {
                    kof[forKof[buf1]]+=(kof[forKof[buf1]]/(abs(head.x()-j)+abs(head.y()-i))+5);
                    if(abs(head.x()-j)<=1 && abs(head.y()-i)<=1)
                        kof[forKof[buf1]]+=800;

                }
            }
        }

    }





    int ForRand=0, Rand;
    for(int i=0;i<4;i++)
        if(kof[i]>0)
            ForRand+=kof[i];

    QMap<int,MoveDirection > bufK;
    bufK[0]=LEFT;
    bufK[1]=RIGHT;
    bufK[2]=UP;
    bufK[3]=DOWN;



    if(ForRand==0) //выхода нет :)
    {
        Rand=rand()%4;
        if(kof[Rand]<=-20000)
            return bufK[((Rand+1)%4)];
        else return bufK[Rand];
    }

    Rand=rand()%ForRand+1;

    int t=0;
    for(int i=0;i<4;i++)
        if(kof[i]>0){
            if(Rand>=t && Rand <=t+kof[i])
                return bufK[i];
            t+=kof[i];
        }

    return UP;


}

QString SimpleAI::getName() const
{
	return "SimpleAI";
}
