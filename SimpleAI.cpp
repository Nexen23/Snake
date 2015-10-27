#include "SimpleAI.h"

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

int SimpleAI::getCostsOfDirection(QPoint head,MoveDirection moveDirection, int*kof, Map* map) //moveDirection направление движения в текущий момент
{
	/*
    QVector<QVector<Entity*>> buf_field;
    int x=0,y=0, buf_sizeX = sizeX = map->sizeX-1, buf_sizeY = sizeY = map->sizeY-1;
    int byf_head_x=head.x(),byf_head_y=head.y();

    switch(moveDirection){
    case UP:
    {
        for(x=0;x<sizeX;x++)
            for(y=0;y<sizeY;y++) {
                buf_field[x][y]=map->field[x][y];

            }

    } break;
    case DOWN:
    {
        for(x=0;x<sizeX;x++)
            for(y=0;y<sizeY;y++) {
                buf_field[sizeX-1-x][sizeY-1-y]=map->field[x][y];

            }
        byf_head_x=buf_sizeX-head.x();
        byf_head_y=buf_sizeY-head.y();

    } break;
    case RIGHT: //270
    {
        Entity* temp =NULL;
        for(x=0;x<sizeX;x++)
            for(y=0;y<sizeY;y++)
                 buf_field[sizeX-1-x][sizeY-1-y]=map->field[x][y];

        for(int r=0;r<3;r++){


            int min=0;
            if (sizeX == sizeY)
                        min = sizeX;
                    else
                    {   //rows-sizeX
                        if (sizeX < sizeY)
                        {
                            min = sizeX;

                            for (int j = 0; j < sizeX; j++)
                                buf_field[sizeY - 1][j] = buf_field[j][sizeY - 1];
                        }
                        else
                        {
                            if (sizeX > sizeY)
                            {
                                min = sizeY;

                                for (int i = 0; i < sizeY; i++)
                                    buf_field[i][sizeX - 1] = buf_field[sizeX - 1][i];
                            }
                        }
                    }


                    for (int i = 0; i < min; i++)
                    {
                        for (int j = i + 1; j < min; j++)
                        {
                            temp = buf_field[i][j];
                            buf_field[i][j] = buf_field[j][i];
                            buf_field[j][i] = temp;
                        }
                    }

                    int tmp = sizeX;
                    sizeX = sizeY;
                    sizeY = tmp;

                    for (int k = 0; k < sizeX; k++)
                    {
                        for (int i = 0, j = sizeY - 1; i <= j; i++, j--)
                        {
                            temp = buf_field[k][i];
                            buf_field[k][i] = buf_field[k][j];
                            buf_field[k][j] = temp;
                        }
                    }
        }

        int tmp=sizeX;
        buf_sizeX=buf_sizeY;
        buf_sizeY=tmp;

        byf_head_y=head.x();

        byf_head_x=buf_sizeY-head.y();

    } break;
    case LEFT:
    {
        Entity* temp =NULL;

        for(x=0;x<sizeX;x++)
            for(y=0;y<sizeY;y++)
                buf_field[sizeX-1-x][sizeY-1-y]=map->field[x][y];


        int min=0;
        if (sizeX == sizeY)
                    min = sizeX;
                else
                {   //rows-sizeX
                    if (sizeX < sizeY)
                    {
                        min = sizeX;

                        for (int j = 0; j < sizeX; j++)
                            buf_field[sizeY - 1][j] = buf_field[j][sizeY - 1];
                    }
                    else
                    {
                        if (sizeX > sizeY)
                        {
                            min = sizeY;

                            for (int i = 0; i < sizeY; i++)
                                buf_field[i][sizeX - 1] = buf_field[sizeX - 1][i];
                        }
                    }
                }


                for (int i = 0; i < min; i++)
                {
                    for (int j = i + 1; j < min; j++)
                    {
                        temp = buf_field[i][j];
                        buf_field[i][j] = buf_field[j][i];
                        buf_field[j][i] = temp;
                    }
                }

                int tmp = sizeX;
                sizeX = sizeY;
                sizeY = tmp;

                for (int k = 0; k < sizeX; k++)
                {
                    for (int i = 0, j = sizeY - 1; i <= j; i++, j--)
                    {
                        temp = buf_field[k][i];
                        buf_field[k][i] = buf_field[k][j];
                        buf_field[k][j] = temp;
                    }
                }
        int tmp=sizeX;
        buf_sizeX=buf_sizeY;
        buf_sizeY=tmp;

        byf_head_x=head.y();

        byf_head_y=buf_sizeX-head.x();
    } break;

}


kof[DOWN]=-2;

int n=1;

for(y=byf_head_y; y<byf_head_y+6;y++)
{

 if(y == buf_sizeY)
     break;

    for(x=byf_head_x-n; x<=byf_head_x+n; x++)
    {
        if(byf_head_x<0)
        {
            kof[UP]-=10;
            continue;
        }
        if(byf_head_x>buf_sizeX)
        {
            kof[UP]-=10;
            break;
        }

        if(buf_field[byf_head_x][byf_head_y]==NULL)
            continue;

        if(buf_field[byf_head_x][byf_head_y]->getId()==FOOD_ITEM){
            kof[UP]+=10;
            continue;
        }
        if(buf_field[byf_head_x][byf_head_y]->getId()==BOMB_ITEM){
             kof[UP]+=20;
             continue;
            }
        if(buf_field[byf_head_x][byf_head_y]->getId()==HOLE_OBJECT){
              kof[UP]-=20;
              continue;
        }
        if(buf_field[byf_head_x][byf_head_y]->getId()==SNAKE){
              kof[UP]-=20;
              continue;
        }


    }

 n++;
    }

//LEFT!!!!!
n=0;
for(x=byf_head_x-1; x<byf_head_x-6;x++)
{

 if(x <= buf_sizeX)
     break;

    for(y=byf_head_y-3; y<=byf_head_y+n; y++)
    {
        if(byf_head_y<0)
        {
            kof[LEFT]-=10;
            continue;
        }
        if(byf_head_y>buf_sizeY)
        {
            kof[LEFT]+=10;
            break;
        }

        if(buf_field[byf_head_x][byf_head_y]==NULL)
            continue;

        if(buf_field[byf_head_x][byf_head_y]->getId()==FOOD_ITEM){
            kof[LEFT]+=10;
            continue;
        }
        if(buf_field[byf_head_x][byf_head_y]->getId()==BOMB_ITEM){
             kof[LEFT]+=20;
             continue;
            }
        if(buf_field[byf_head_x][byf_head_y]->getId()==HOLE_OBJECT){
              kof[LEFT]-=20;
              continue;
        }
        if(buf_field[byf_head_x][byf_head_y]->getId()==SNAKE){
              kof[LEFT]-=20;
              continue;
        }


    }

 n++;
    }

//RIGHT
n=0;
for(x=byf_head_x+1; x<byf_head_x+6;x++)
{

 if(x >= buf_sizeX)
     break;

    for(y=byf_head_y-3; y<=byf_head_y+n; y++)
    {
        if(byf_head_y<0)
        {
            kof[RIGHT]-=10;
            continue;
        }
        if(byf_head_y>buf_sizeY)
        {
            kof[RIGHT]+=10;
            break;
        }

        if(buf_field[byf_head_x][byf_head_y]==NULL)
            continue;

        if(buf_field[byf_head_x][byf_head_y]->getId()==FOOD_ITEM){
            kof[RIGHT]+=10;
            continue;
        }
        if(buf_field[byf_head_x][byf_head_y]->getId()==BOMB_ITEM){
             kof[RIGHT]+=20;
             continue;
            }
        if(buf_field[byf_head_x][byf_head_y]->getId()==HOLE_OBJECT){
              kof[RIGHT]-=20;
              continue;
        }
        if(buf_field[byf_head_x][byf_head_y]->getId()==SNAKE){
              kof[RIGHT]-=20;
              continue;
        }


    }

 n++;
    }

kof[DOWN]=-1000;

switch (moveDirection) {
case UP:

    break;
case DOWN:
    int tmp = kof[UP];
    kof[UP]=kof[DOWN];
    kof[DOWN]=tmp;
    tmp=kof[RIGHT];
    kof[RIGHT]=kof[LEFT];
    kof[LEFT]=tmp;

    break;
case RIGHT:
    kof[DOWN]=kof[RIGHT];
    kof[RIGHT]=kof[UP];
    kof[UP]=kof[LEFT];
    kof[LEFT]=-1000;

    break;
case LEFT:
    kof[DOWN]=kof[LEFT];
    kof[LEFT]=kof[UP];
    kof[UP]=kof[RIGHT];
    kof[RIGHT]=-1000;

    break;


}
*/
	return -1;
} //не забыть про поворот коэффициентов

MoveDirection SimpleAI::getNextMove(Snake *controllerSnake, Map *map){
		/*
    QPoint head = controllerSnake->position , second = controllerSnake->tail.first();

    if(controllerSnake->tail.size()==NULL)
        second=head;
    QPoint buf = head - second;

    int *kof = new int [4];
    for(int i=0;i<n;i++){   kof[i] =100;  }

    //учет положения первого за головой хвоста
    if(buf.x()==0)
        if(buf.y()>0){
            kof[UP]=getCostsOfDirection(head,UP,kof,map);
        }   else    {

            kof[DOWN]=getCostsOfDirection(head,DOWN,kof,map);;
        }
    else
        if(buf.x()>0){
            kof[RIGHT]=getCostsOfDirection(head,RIGHT,kof,map);;
        }   else    {
            kof[LEFT]=getCostsOfDirection(head,LEFT,kof,map);;
        }

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

    return 2;
		*/
	return UP;
}

QString SimpleAI::getName()
{
	return "SimpleAI";
}
