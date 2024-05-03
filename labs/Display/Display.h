#pragma once

#include "..\General_Heading.h"

#include <algorithm>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "..\Data\Data.h"
#include "..\Scene\Object\GraphicObject\RenderManager\RenderManager.h"

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� ������� glutPostRedisplay
void display(void);
// �������, ���������� ��� ��������� �������� ����
void reshape(int w, int h);