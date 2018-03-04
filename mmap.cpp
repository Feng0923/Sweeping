#include "mmap.h"
/*
 *
 * 0-8:周围雷数
 * +100:已翻开的块
 * 9:雷
 * +200:插旗
*/
#include<cstdlib>
#include<ctime>
mMap::mMap()
{
    row = 15;
    column = 10;
    mineNumber = 10;
}

void mMap::create(int row ,int column ,int mine )
{
    this->row = row;
    this->column = column;
    this->mineNumber = mine;
    sum = row*column;
    map = new int*[row];
      for (int i = 0; i < row; i++)
      {
          map[i] = new int[column];
      }
       restart();
}

void mMap::restart()
{
    for(int i = 0;i<row;i++){
        for(int j = 0;j<column;j++){
            map[i][j] = 0;
        }
    }
    int mine = 0;
    while(mine<mineNumber){
        int x = rand()%row;
        int y = rand()%column;
        if(map[x][y]!=9){
            map[x][y] = 9;
            for(int i=-1;i<2;i++){
                for(int j=-1;j<2;j++){
                    if(x+i>=0&&x+i<row&&y+j>=0&&y+j<column){
                        if(map[x+i][y+j]<9){
                            map[x+i][y+j]++;
                        }
                    }
                }
            }
            mine++;
        }
    }
}

mMap::~mMap()
{
    //    delete map;
}

