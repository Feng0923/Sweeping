#ifndef MMAP_H
#define MMAP_H


class mMap
{
public:
    mMap();
    void create(int row = 15,int column = 10,int mine = 10);
    bool isWin();
    void restart();
     int **map;
     ~mMap();
     int row;
     int column;
     int mineNumber;
     int win;
     int sum = row*column;
private:

};

#endif // MMAP_H
