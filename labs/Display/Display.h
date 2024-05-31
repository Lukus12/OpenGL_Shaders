#pragma once

#include "..\General_Heading.h"

#include <algorithm>


#include "..\Data\Data.h"



// функция вызывается при перерисовке окна
// в том числе и принудительно, по команде glutPostRedisplay
void display(void);
// функция, вызываемая при изменении размеров окна
void reshape(int w, int h);