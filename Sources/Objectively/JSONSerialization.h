/*
 * Objectively: Ultra-lightweight object oriented framework for c99.
 * Copyright (C) 2014 Jay Dolan <jay@jaydolan.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef _Objectively_JSONSerialization_h_
#define _Objectively_JSONSerialization_h_

#include <Objectively/Data.h>
#include <Objectively/Object.h>

/**
 * @file
 *
 * @brief JSON serialization.
 */

/**
 * @defgroup JSON JSON
 *
 * @brief JSON serialization and introspection.
 */

/**
 * @brief Enables pretty (indented) formatting of JSON output.
 */
#define JSON_WRITE_PRETTY 1

typedef struct JSONSerialization JSONSerialization;
typedef struct JSONSerializationInterface JSONSerializationInterface;

/**
 * @brief JSON serialization.
 *
 * @extends Object
 *
 * @ingroup JSON
 */
struct JSONSerialization {

	/**
	 * @brief The parent.
	 */
	Object object;

	/**
	 * @brief The typed interface.
	 */
	JSONSerializationInterface *interface;
};

/**
 * @brief The JSONSerialization interface.
 *
 * @ingroup JSON
 */
struct JSONSerializationInterface {

	/**
	 * @brief The parent.
	 */
	ObjectInterface objectInterface;

	/**
	 * @brief Serializes the given Object to JSON Data.
	 *
	 * @param obj The Object to serialize.
	 * @param options A bitwise-or of `JSON_WRITE_*`.
	 *
	 * @return The resulting JSON Data.
	 *
	 * @relates JSONSerialization
	 */
	Data *(*dataFromObject)(const id obj, int options);

	/**
	 * @brief Parses an Object from the specified Data.
	 *
	 * @param data The JSON Data.
	 * @param options A bitwise-or of `JSON_READ_*`.
	 *
	 * @return The Object, or `NULL` on error.
	 *
	 * @relates JSONSerialization
	 */
	id (*objectFromData)(const Data *data, int options);
};

/**
 * @brief The JSONSerialization Class.
 */
extern Class _JSONSerialization;

#endif
