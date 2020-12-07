/*************************************************************************/
/*  rectangle_shape_2d.cpp                                               */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2020 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "rectangle_shape_2d.h"

#include "servers/physics_server_2d.h"
#include "servers/rendering_server.h"
void RectangleShape2D::_update_shape() {
	PhysicsServer2D::get_singleton()->shape_set_data(get_rid(), size / 2);
	emit_changed();
}

void RectangleShape2D::set_size(const Vector2 &p_size) {
	size = p_size;
	_update_shape();
}

Vector2 RectangleShape2D::get_size() const {
	return size;
}

void RectangleShape2D::draw(const RID &p_to_rid, const Color &p_color) {
	RenderingServer::get_singleton()->canvas_item_add_rect(p_to_rid, Rect2(-size / 2, size), p_color);
}

Rect2 RectangleShape2D::get_rect() const {
	return Rect2(-size / 2, size);
}

real_t RectangleShape2D::get_enclosing_radius() const {
	return size.length() / 2;
}

void RectangleShape2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_size", "size"), &RectangleShape2D::set_size);
	ClassDB::bind_method(D_METHOD("get_size"), &RectangleShape2D::get_size);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "size"), "set_size", "get_size");
}

RectangleShape2D::RectangleShape2D() :
		Shape2D(PhysicsServer2D::get_singleton()->rectangle_shape_create()) {
	size = Vector2(20, 20);
	_update_shape();
}
