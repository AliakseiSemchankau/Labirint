#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__


#define WEIGHT 1280
#define HEIGHT 720
#define SQUARE_SIZE 80
#define PARTITION_WIDTH 20
#define PARTITION_HEIGHT SQUARE_SIZE
#define MOVES std::vector<std::pair<int, int> > {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}
#define MOVES_MAP std::map<std::pair<int, int>, bool> {{{1, 0},true},{{0, 1},true},{{-1, 0},true},{{0, -1},true}}
#define COLUMN 1
#define ROW 2
#define VELOCITY 300.0/1.0
#define EPS5 0.00001
#define EPS1 1e-1
#define EPS3 1e-3
#define layerTaq 3
#define MoveByAction 2
#define pi 3.1415926
#define itemsFontWidth 10
#define itemsFontHeight
enum tags{ FLOOR_TAG, WALL_TAG, START_TAG, FINISH_TAG};

#endif //__CONSTANTS_H__