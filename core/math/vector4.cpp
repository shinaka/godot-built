/*************************************************************************/
/*  vector4.cpp                                                          */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
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

#include "vector4.h"

#include "core/math/basis.h"
#include "core/string/print_string.h"

void Vector4::set_axis(const int p_axis, const real_t p_value) {
	ERR_FAIL_INDEX(p_axis, 4);
	components[p_axis] = p_value;
}

real_t Vector4::get_axis(const int p_axis) const {
	ERR_FAIL_INDEX_V(p_axis, 4, 0);
	return operator[](p_axis);
}

Vector4::Axis Vector4::min_axis_index() const {
	uint32_t min_index = 0;
	real_t min_value = x;
	for (uint32_t i = 1; i < 4; i++) {
		if (operator[](i) <= min_value) {
			min_index = i;
			min_value = operator[](i);
		}
	}
	return Vector4::Axis(min_index);
}

Vector4::Axis Vector4::max_axis_index() const {
	uint32_t max_index = 0;
	real_t max_value = x;
	for (uint32_t i = 1; i < 4; i++) {
		if (operator[](i) > max_value) {
			max_index = i;
			max_value = operator[](i);
		}
	}
	return Vector4::Axis(max_index);
}

bool Vector4::is_equal_approx(const Vector4 &p_vec4) const {
	return Math::is_equal_approx(x, p_vec4.x) && Math::is_equal_approx(y, p_vec4.y) && Math::is_equal_approx(z, p_vec4.z) && Math::is_equal_approx(w, p_vec4.w);
}

real_t Vector4::length() const {
	return Math::sqrt(length_squared());
}

void Vector4::normalize() {
	*this /= length();
}

Vector4 Vector4::normalized() const {
	return *this / length();
}

bool Vector4::is_normalized() const {
	return Math::is_equal_approx(length_squared(), 1, (real_t)UNIT_EPSILON); // Use less epsilon.
}

real_t Vector4::distance_to(const Vector4 &p_to) const {
	return (p_to - *this).length();
}

Vector4 Vector4::direction_to(const Vector4 &p_to) const {
	Vector4 ret(p_to.x - x, p_to.y - y, p_to.z - z, p_to.w - w);
	ret.normalize();
	return ret;
}

Vector4 Vector4::abs() const {
	return Vector4(Math::abs(x), Math::abs(y), Math::abs(z), Math::abs(w));
}

Vector4 Vector4::sign() const {
	return Vector4(SIGN(x), SIGN(y), SIGN(z), SIGN(w));
}

Vector4 Vector4::floor() const {
	return Vector4(Math::floor(x), Math::floor(y), Math::floor(z), Math::floor(w));
}

Vector4 Vector4::ceil() const {
	return Vector4(Math::ceil(x), Math::ceil(y), Math::ceil(z), Math::ceil(w));
}

Vector4 Vector4::round() const {
	return Vector4(Math::round(x), Math::round(y), Math::round(z), Math::round(w));
}

Vector4 Vector4::lerp(const Vector4 &p_to, const real_t p_weight) const {
	return Vector4(
			x + (p_weight * (p_to.x - x)),
			y + (p_weight * (p_to.y - y)),
			z + (p_weight * (p_to.z - z)),
			w + (p_weight * (p_to.w - w)));
}

Vector4 Vector4::cubic_interpolate(const Vector4 &p_b, const Vector4 &p_pre_a, const Vector4 &p_post_b, const real_t p_weight) const {
	Vector4 res = *this;
	res.x = Math::cubic_interpolate(res.x, p_b.x, p_pre_a.x, p_post_b.x, p_weight);
	res.y = Math::cubic_interpolate(res.y, p_b.y, p_pre_a.y, p_post_b.y, p_weight);
	res.z = Math::cubic_interpolate(res.z, p_b.z, p_pre_a.z, p_post_b.z, p_weight);
	res.w = Math::cubic_interpolate(res.w, p_b.w, p_pre_a.w, p_post_b.w, p_weight);
	return res;
}

Vector4 Vector4::posmod(const real_t p_mod) const {
	return Vector4(Math::fposmod(x, p_mod), Math::fposmod(y, p_mod), Math::fposmod(z, p_mod), Math::fposmod(w, p_mod));
}

Vector4 Vector4::posmodv(const Vector4 &p_modv) const {
	return Vector4(Math::fposmod(x, p_modv.x), Math::fposmod(y, p_modv.y), Math::fposmod(z, p_modv.z), Math::fposmod(w, p_modv.w));
}

void Vector4::snap(const Vector4 &p_step) {
	x = Math::snapped(x, p_step.x);
	y = Math::snapped(y, p_step.y);
	z = Math::snapped(z, p_step.z);
	w = Math::snapped(w, p_step.w);
}

Vector4 Vector4::snapped(const Vector4 &p_step) const {
	Vector4 v = *this;
	v.snap(p_step);
	return v;
}

Vector4 Vector4::inverse() const {
	return Vector4(1.0f / x, 1.0f / y, 1.0f / z, 1.0f / w);
}

Vector4 Vector4::clamp(const Vector4 &p_min, const Vector4 &p_max) const {
	return Vector4(
			CLAMP(x, p_min.x, p_max.x),
			CLAMP(y, p_min.y, p_max.y),
			CLAMP(z, p_min.z, p_max.z),
			CLAMP(w, p_min.w, p_max.w));
}

Vector4::operator String() const {
	return "(" + String::num_real(x, false) + ", " + String::num_real(y, false) + ", " + String::num_real(z, false) + ", " + String::num_real(w, false) + ")";
}
