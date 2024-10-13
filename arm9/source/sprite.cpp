/*
    sprite.cpp
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "sprite.h"
#include <nds.h>

cSprite::cSprite(u8 id) {
    init(id);
}

cSprite::~cSprite() {}

void cSprite::sysinit() {
    oamInit(&oamMain, SpriteMapping_Bmp_1D_128, true);

    for (int i = 0; i < 128; i++) {
        oamMain.oamMemory[i].attribute[0] = ATTR0_DISABLED;
        oamMain.oamMemory[i].attribute[1] = 0;
        oamMain.oamMemory[i].attribute[2] = 0;
        oamMain.oamMemory[i].filler = 0;
    }

    oamUpdate(&oamMain);
    oamEnable(&oamMain);
}

void cSprite::init(u16 id) {
    _id = id;

    _size = SS_SIZE_32;

    _shape = SS_SHAPE_SQUARE;

    _bufferOffset = 0;

    _priority = 2;

    _entry = &oamMain.oamMemory[_id];
    _affine = &oamMain.oamRotationMemory[_id];

    // initial x = 0, hidden, bitmap obj mode, square shape
    _entry->attribute[0] = ATTR0_DISABLED | ATTR0_BMP | ATTR0_SQUARE | 0;

    // initial y = 0, size = 32x32, Affine Transformation Parameter group 0
    _entry->attribute[1] = ATTR1_SIZE_32 | ATTR1_ROTDATA(_id) | 0;

    // initial alpha = 15, buffer offset = 0, display priority 0
    _entry->attribute[2] = ATTR2_ALPHA(15) | ATTR2_PRIORITY(0) | 0;

    setScale(1, 1);
}

void cSprite::show() {
    _entry->attribute[0] = (_entry->attribute[0] & (~0x0300)) | ATTR0_ROTSCALE_DOUBLE | ATTR0_BMP;
}

void cSprite::hide() {
    _entry->attribute[0] = (_entry->attribute[0] & (~0x0300)) | ATTR0_DISABLED;
}

void cSprite::setAlpha(u8 alpha) {
    oamSetAlpha(&oamMain, _id, alpha);
}

void cSprite::setPosition(u16 x, u8 y) {
    u8 offset = 0;
    switch (_size) {
        case SS_SIZE_8:
            offset = 4;
            break;
        case SS_SIZE_16:
            offset = 8;
            break;
        case SS_SIZE_32:
            offset = 16;
            break;
        case SS_SIZE_64:
            offset = 32;
            break;
        default:
            offset = 0;
    };
    x -= offset;
    _x = x & 0x1FF;
    y -= offset;
    _y = y & 0xFF;

    oamSetXY(&oamMain, _id, _x, _y);
}

void cSprite::setSize(SPRITE_SIZE size) {
    _size = size;
    _entry->attribute[1] = (_entry->attribute[1] & (~0xC000)) | _size;
}

void cSprite::setShape(SPRITE_SHAPE shape) {
    _shape = shape;
    _entry->attribute[1] = (_entry->attribute[0] & (~0xC000)) | _shape;
}

u16* cSprite::buffer() {
    return SPRITE_GFX + (_bufferOffset * 64);
}

void cSprite::setBufferOffset(u32 offset) {
    _bufferOffset = offset;
    _entry->attribute[2] = (_entry->attribute[2] & (~0x3FF)) | offset;
}

void cSprite::setScale(float scaleX, float scaleY) {
    _scaleX = scaleX;
    _scaleY = scaleY;

    scaleX = 1 / scaleX;
    scaleY = 1 / scaleY;

    u8 decimalX = (u8)((scaleX - (int)scaleX) * 256);
    u8 integerX = (u8)((int)scaleX) & 0x7f;
    u8 decimalY = (u8)((scaleY - (int)scaleY) * 256);
    u8 integerY = (u8)((int)scaleY) & 0x7f;

    _affine->hdx = (integerX << 8) | decimalX;
    _affine->hdy = 0;
    _affine->vdx = 0;
    _affine->vdy = (integerY << 8) | decimalY;
}

void cSprite::setPriority(u8 priority) {
    _priority = priority;
    oamSetPriority(&oamMain, _id, _priority);
}

bool cSprite::visible() {
    return (_entry->attribute[0] & 0x0300) != 0x0200;
}
