#include "spawn.h"
#include "../drivers/screen.h"
#include "game.h"

void draw_square(position *p, int size);
void draw_shape(shape *s);
shape create_shape(shape_type type, int x, int y);

/* Shape definitions - 4x4 grids for each shape type */
static const int shapes[SHAPE_COUNT][SHAPE_GRID_HEIGHT][SHAPE_GRID_WIDTH] = {
    /* SHAPE_I */
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /* SHAPE_J */
    {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /* SHAPE_L */
    {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /* SHAPE_O */
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /* SHAPE_S */
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /* SHAPE_T */
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /* SHAPE_Z */
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};
/*
uint8_t get_width(shape_type t) {
    int temp[4] = {-1, -1, -1, -1};
    uint8_t wid = 0;
    const int (*shape_grid)[4] = shapes[t];
    for(int y = 0 ; y < 4; y++) {
        for(int x = 0 ; x < 4; x++) {
            if(shape_grid[y][x] != 0 && temp[x] != x) {
                temp[x] = x;
                wid++;
            }
        }
    }

    return wid;
}
*/


uint8_t get_width(shape_type t) {
    uint8_t wid = 0;
    const int (*shape_grid)[4] = shapes[t];
    
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (shape_grid[y][x] != 0) {
                wid++;      // 该列有方块，计数并跳出内层循环
                break;
            }
        }
    }
    
    return wid;
}


void spawn_item(shape_type t, position *p) {
    /* 创建副本，不修改原始坐标 */
    position adjusted_pos = *p;
    
    /* 计算可玩区域边界（避开边界墙） */
    int playable_left = width_min + 1;    /* 左墙内测 */
    int playable_right = width_max - 1;   /* 右墙内测 */
    
    /* 1. 处理x轴边界 */
    int shape_right = adjusted_pos.x + 3;  /* 4列形状，索引0-3 */
    int shape_left = adjusted_pos.x;
    
    /* 如果形状超出右边界，向左调整 */
    if (shape_right > playable_right) {
        uint8_t wid = get_width(t);
        adjusted_pos.x = playable_right - wid;
    }
    
    /* 如果形状超出左边界，向右调整 */
    if (shape_left < playable_left) {
        adjusted_pos.x = playable_left;
    }
    
    /* 2. 处理y轴边界 */
    int shape_bottom = adjusted_pos.y + 3;  /* 4行形状，索引0-3 */
    
    /* 如果形状超出底部边界，向上调整 */
    if (shape_bottom >= MAX_ROWS) {
        adjusted_pos.y = MAX_ROWS - 3;
    }
    /* 确保y坐标不为负数 */
    if (adjusted_pos.y < 0) {
        adjusted_pos.y = 0;
    }

    /* 根据形状类型调用相应的绘制函数 */
    switch (t) {
        case SHAPE_T:
            draw_sT(&adjusted_pos);
            break;
        case SHAPE_J:
            draw_sJ(&adjusted_pos);
            break;
        case SHAPE_I:
            draw_sI(&adjusted_pos);
            break;
        case SHAPE_O:
            draw_sO(&adjusted_pos);
            break;
        case SHAPE_L:
            draw_sL(&adjusted_pos);
            break;
        case SHAPE_S:
            draw_sS(&adjusted_pos);
            break;
        case SHAPE_Z:
            draw_sZ(&adjusted_pos);
            break;
        default:
            /* 不应该到达这里，因为SHAPE_COUNT不是有效的形状类型 */
            break;
    }
}

void draw_sT(position *p) {
    shape s = create_shape(SHAPE_T, p->x, p->y);
    draw_shape(&s);
}
void draw_sJ(position *p) {
    shape s = create_shape(SHAPE_J, p->x, p->y);
    draw_shape(&s);
}
void draw_sI(position *p) {
    shape s = create_shape(SHAPE_I, p->x, p->y);
    draw_shape(&s);
}
void draw_sL(position *p) {
    shape s = create_shape(SHAPE_L, p->x, p->y);
    draw_shape(&s);
}
void draw_sO(position *p) {
    shape s = create_shape(SHAPE_O, p->x, p->y);
    draw_shape(&s);
}
void draw_sS(position *p) {
    shape s = create_shape(SHAPE_S, p->x, p->y);
    draw_shape(&s);
}
void draw_sZ(position *p) {
    shape s = create_shape(SHAPE_Z, p->x, p->y);
    draw_shape(&s);
}

/*
void draw_square(position *p, int size) {
    char block[] = {'█', 0};
    char hash[] = "#";
    
    for(int i = 0 ; i < size; i++) {
        int horizontal = p->x + i;
        kprint_at(block, horizontal, p->y);i
        kprint_at(block, horizontal, p->y + size - 1);
    }

    for(int i = 0 ; i < size; i++) {
        int vertical = p->y + i;
        kprint_at(hash, p->x, vertical);
        kprint_at(hash, p->x + size - 1, vertical);
    }
}
*/

void draw_shape(shape *s) {
    char block[] = {'#', 0};  /* Create null-terminated string */
    const int (*shape_grid)[SHAPE_GRID_HEIGHT] = shapes[s->type];
    
    for (int y = 0; y < SHAPE_GRID_WIDTH; y++) {
        for (int x = 0; x < SHAPE_GRID_HEIGHT; x++) {
            if (shape_grid[y][x]) {
                int screen_x = s->pos.x + x;
                int screen_y = s->pos.y + y;
                kprint_at(block, screen_x, screen_y);
            }
        }
    }
}

shape create_shape(shape_type type, int x, int y) {
    shape s;
    s.type = type;
    s.rotation = 0;
    s.pos.x = x;
    s.pos.y = y;
    return s;
}

void rotate_shape(shape *s, int clockwise) {
    if (clockwise) {
        s->rotation = (s->rotation + 1) % 4;
    } else {
        s->rotation = (s->rotation + 3) % 4;  /* +3 is same as -1 mod 4 */
    }
}

/* Helper function to get rotated shape cell */
int get_shape_cell(shape *s, int x, int y) {
    /* For now, return the base shape cell */
    /* TODO: Implement proper rotation using rotation matrices */
    return shapes[s->type][y][x];
}
