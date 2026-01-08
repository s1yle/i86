#include "game.h"
#include "spawn.h"

#ifdef FALSE
void test_spawn_item() {
	/* 测试边界检测功能 */
	position p1 = { 110, 0 };
	spawn_item(SHAPE_O, &p1, NULL);
	
	position p2 = { 110, 4 };
	spawn_item(SHAPE_T, &p2, NULL);

	position pp2 = { 110, 8 };
	spawn_item(SHAPE_I, &pp2, NULL);
	
	position pp3 = { 110, 12 };
	spawn_item(SHAPE_J, &pp3, NULL);
	
	position p3 = { 110, 16 };
	spawn_item(SHAPE_L, &p3, NULL);
	
	position p4 = { 110, 20 };
	spawn_item(SHAPE_Z, &p4, NULL);

	position p5 = { 110, 24 };
	spawn_item(SHAPE_S, &p5, NULL);

	
	/* 测试边界检测功能 */
	position o1 = { 0, 0 };
	spawn_item(SHAPE_O, &o1, NULL);
	
	position o2 = { 0, 4 };
	spawn_item(SHAPE_T, &o2, NULL);

	position o3 = { 0, 8 };
	spawn_item(SHAPE_I, &o3, NULL);
	
	position o4 = { 0, 12 };
	spawn_item(SHAPE_J, &o4, NULL);
	
	position o5 = { 0, 16 };
	spawn_item(SHAPE_L, &o5, NULL);
	
	position o6 = { 0, 20 };
	spawn_item(SHAPE_Z, &o6, NULL);

	position o7 = { 0, 24 };
	spawn_item(SHAPE_S, &o7, NULL);
}

#else
#endif