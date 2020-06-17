#include "TextEntity.h"

TextEntity::TextEntity() {}

void TextEntity::init(int x, int y, LTexture* texture, TTF_Font* font) {
	this->texture = texture;
	this->font = font;
	this->x = x;
	this->y = y;
	previousText = "";
}

void TextEntity::update(std::string text) {
	if(text == previousText) return;

	SDL_Color white = {255, 255, 255, 255};
	texture->loadFromRenderedText(font, text, white);
	previousText = text;
}

void TextEntity::paint(double scaleW, double scaleH){
	int w, h;
	texture->queryTexture(w, h);
	SDL_Rect destRect = {x, y, w, h};
	texture->paint(destRect, scaleW, scaleH);
}