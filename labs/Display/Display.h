#pragma once

#include "..\General_Heading.h"

#include <algorithm>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "..\Data\Data.h"

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� ������� glutPostRedisplay
void display(void);
// �������, ���������� ��� ��������� �������� ����
void reshape(int w, int h);