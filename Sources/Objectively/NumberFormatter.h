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

#ifndef _Objectively_NumberFormatter_h
#define _Objectively_NumberFormatter_h

#include <Objectively/Number.h>
#include <Objectively/String.h>

/**
 * @file
 *
 * @brief Number formatting and parsing.
 */

/**
 * @brief Currency format.
 */
#define NUMBERFORMAT_CURRENCY "%'.2lf"

/**
 * @brief Decimal format.
 */
#define NUMBERFORMAT_DECIMAL "%lf"

/**
 * @brief Integer format.
 */
#define NUMBERFORMAT_INTEGER "%ld"

typedef struct NumberFormatter NumberFormatter;
typedef struct NumberFormatterInterface NumberFormatterInterface;

/**
 * @brief The NumberFormatter type.
 */
struct NumberFormatter {

	/**
	 * @brief The parent.
	 */
	Object object;

	/**
	 * @brief The typed interface.
	 */
	NumberFormatterInterface *interface;

	/**
	 * @brief The format string.
	 */
	const char *fmt;
};

/**
 * @brief The NumberFormatter type.
 */
struct NumberFormatterInterface {

	/**
	 * @brief The parent.
	 */
	ObjectInterface objectInterface;

	/**
	 * Parses a Number from `chars`.
	 *
	 * @param chars The characters to parse.
	 *
	 * @return A Number instance, or `NULL` on error.
	 */
	Number *(*numberFromCharacters)(const NumberFormatter *self, const char *chars);

	/**
	 * Parses a Number from the specified String.
	 *
	 * @param string The String to parse.
	 *
	 * @return A Number instance, or `NULL` on error.
	 */
	Number *(*numberFromString)(const NumberFormatter *self, const String *string);

	/**
	 * Initializes a NumberFormatter with the specified format string.
	 *
	 * @param fmt The format string.
	 *
	 * @return The initialized NumberFormatter, or `NULL` on error.
	 *
	 * @see strftime
	 */
	NumberFormatter *(*initWithFormat)(NumberFormatter *self, const char *fmt);

	/**
	 * Yields a String representation of the specified Number instance.
	 *
	 * @param number The Number to format.
	 *
	 * @return The String representation of the Number, or `NULL` on error.
	 */
	String *(*stringFromNumber)(const NumberFormatter *self, const Number *number);
};

/**
 * @brief The NumberFormatter Class.
 */
extern Class __NumberFormatter;

#endif