#include "GameObject.h"

void GameObject::setGraphicObject(shared_ptr<GraphicObject> graphicObject)
{
	this->graphicObject = graphicObject;
}

void GameObject::setPosition(int x, int y)
{
	this->position = vec2(x, y);
	graphicObject->setPosition(vec3(x - 10, 0, y - 10));
}

void GameObject::setPosition(int x, int y, float z)
{
	this->position = vec2(x, y);
	graphicObject->setPosition(vec3(x - 10, z, y - 10));
}

void GameObject::setPosition(ivec2 position)
{
	this->position = position;
	graphicObject->setPosition(vec3(position[0] - 10, 0, position[1] - 10));
}

ivec2 GameObject::getPosition()
{
	return position;
}

void GameObject::move(MoveDirection direction, float speed)
{
	if (isMoving()) return;
	this->sost = direction;
	this->speed = speed;
}

bool GameObject::isMoving()
{
	if (progress > 0) return true;
	return false;
}

void GameObject::simulate(float sec)
{
    // вычисление прогресса перемещени€
    if (sost != MoveDirection::STOP) progress += speed * sec;
    // если прогресс больше или равен единице
    if (progress >= 1.0){
        // расчитываем новую позицию
        ivec2 newPos = position;
        // в зависимости от направлени€ ме€ем координаты
        switch (sost){
            case MoveDirection::LEFT:
                newPos.x--;
                break;
            case MoveDirection::RIGHT:
                newPos.x++;
                break;
            case MoveDirection::UP:
                newPos.y--;
                break;
            case MoveDirection::DOWN:
                newPos.y++;
                break;
         }
        // установливем новые координаты объекта
        setPosition(newPos);
        //мен€ем состо€ние на неподвижное
        sost = MoveDirection::STOP;
        // обнул€ем прогресс
        progress = 0.0;
    }
    else{
        // вычисл€ем текущую позицию объекта
        vec3 currentPos = graphicObject->getPosition();
        // в зависимости от направлени€ измен€ем соответствующую координату
        switch (sost){
            case MoveDirection::LEFT: 
                currentPos[0] -= speed * sec;
                break;
            case MoveDirection::RIGHT:
                currentPos[0] += speed * sec;
                break;
            case MoveDirection::UP:
                currentPos[2] -= speed * sec;
                break;
            case MoveDirection::DOWN:
                currentPos[2] += speed * sec;
                break;
        }
        // установливаем новую позицию графического объекта
        graphicObject->setPosition(currentPos);
    }
}

void GameObject::draw(void)
{
	graphicObject->draw();
}
