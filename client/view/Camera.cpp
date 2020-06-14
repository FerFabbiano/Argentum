#include "Camera.h"

#define TILE_SIZE 32

Camera::Camera() {}

void Camera::init(int x, int y, int w, int h){
	this->renderRect.x = x;
	this->renderRect.y = y;
	this->renderRect.w = w;
	this->renderRect.h = h;
}

bool Camera::isInCameraRange(const SDL_Rect &destrect) const {
	/*if((destrect.x >= renderRect.x && 
		destrect.y >= renderRect.y && 
		destrect.x <= renderRect.x + renderRect.w &&
		destrect.y <= renderRect.y + renderRect.h) ||
		(destrect.x + destrect.w >= renderRect.x &&
		destrect.y + destrect.h >= renderRect.y &&
		destrect.x + destrect.w <= renderRect.x + renderRect.w &&
		destrect.y + destrect.h <= renderRect.y + renderRect.h)){
			return true;
	}*/

	//quizas se puede hacer mejor, pero no se me ocurre como
	if(destrect.x >= renderRect.x - TILE_SIZE && 
		destrect.y >= renderRect.y - TILE_SIZE && 
		destrect.x <= renderRect.x + renderRect.w + TILE_SIZE &&
		destrect.y <= renderRect.y + renderRect.h + TILE_SIZE){
			return true;
	}
	return false;
}

bool Camera::isInCameraRange(int x, int y) const {
	if(x >= renderRect.x - TILE_SIZE && 
		y >= renderRect.y - TILE_SIZE && 
		x <= renderRect.x + renderRect.w + TILE_SIZE &&
		y <= renderRect.y + renderRect.h + TILE_SIZE){
			return true;
	}
	return false;
}

void Camera::setX(int newX){
	this->renderRect.x = newX;
<<<<<<< HEAD
	if (renderRect.x < 0){
    renderRect.x = 0;
	}
  if (renderRect.x > 58 * 16 - renderRect.w){
    renderRect.x = 58 * 16 - renderRect.w;
  }
=======
	if (renderRect.x < 0) {
    renderRect.x = 0; }
  if (renderRect.x > 58 * 16 - renderRect.w) {
    renderRect.x = 58 * 16 - renderRect.w; }
>>>>>>> f1d84ef7724ce3ec4352541424eb6be672b53fb2
}

void Camera::setY(int newY){
	this->renderRect.y = newY;
<<<<<<< HEAD
	if (renderRect.y < 0){
    renderRect.y = 0;
	}
  if (renderRect.y > 47 * 16 - renderRect.h){
=======
	if (renderRect.y < 0) {
    renderRect.y = 0; }
  if (renderRect.y > 47 * 16 - renderRect.h)
>>>>>>> f1d84ef7724ce3ec4352541424eb6be672b53fb2
    renderRect.y = 47 * 16 - renderRect.h;
  }
}

int Camera::getX() const {
	return renderRect.x;
}

int Camera::getY() const {
	return renderRect.y;
}