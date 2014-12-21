/*
 * Objectively: Ultra-lightweight object oriented framework for GNU C.
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

#ifndef _Objectively_String_h_
#define _Objectively_String_h_

#include <ctype.h>
#include <xlocale.h>

#include <Objectively/Array.h>
#include <Objectively/Data.h>

/**
 * @file
 *
 * @brief Immutable UTF-8 strings.
 */

typedef struct StringInterface StringInterface;

/**
 * @brief Immutable UTF-8 strings.
 *
 * @extends Object
 */
struct String {

	/**
	 * @brief The parent.
	 *
	 * @private
	 */
	Object object;

	/**
	 * @brief The typed interface.
	 *
	 * @private
	 */
	StringInterface *interface;

	/**
	 * @brief The backing character array length.
	 */
	size_t length;

	/**
	 * @brief The locale.
	 */
	locale_t locale;

	/**
	 * @brief The backing character array.
	 */
	char *chars;
};

/**
 * @brief The String interface.
 */
struct StringInterface {

	/**
	 * @brief The parent interface.
	 */
	ObjectInterface objectInterface;

	/**
	 * @brief Compares this String lexicographically to another.
	 *
	 * @param other The String to compare to.
	 * @param range The character range to compare.
	 *
	 * @return The ordering of this String compared to `other`.
	 *
	 * @relates String
	 */
	ORDER (*compareTo)(const String *self, const String *other, const RANGE range);

	/**
	 * Returns the components of this String that were separated by `chars`.
	 *
	 * @param chars The separating characters.
	 *
	 * @return An Array of substrings that were separated by `chars`.
	 *
	 * @relates String
	 */
	Array *(*componentsSeparatedByCharacters)(const String *self, const char *chars);

	/**
	 * Returns the components of this String that were separated by `string`.
	 *
	 * @param string The separating string.
	 *
	 * @return An Array of substrings that were separated by `string`.
	 *
	 * @relates String
	 */
	Array *(*componentsSeparatedByString)(const String *self, const String *string);

	/**
	 * @brief Checks this String for the given prefix.
	 *
	 * @param prefix The Prefix to check.
	 *
	 * @return YES if this String starts with prefix, NO otherwise.
	 *
	 * @relates String
	 */
	BOOL (*hasPrefix)(const String *self, const String *prefix);

	/**
	 * @brief Checks this String for the given suffix.
	 *
	 * @param suffix The suffix to check.
	 *
	 * @return YES if this String ends with suffix, NO otherwise.
	 *
	 * @relates String
	 */
	BOOL (*hasSuffix)(const String *self, const String *suffix);

	/**
	 * @brief Initializes this String by copying `length` of `bytes`.
	 *
	 * @param bytes The bytes.
	 * @param length The length of `bytes` to copy.
	 *
	 * @return The initialized String, or `NULL` on error.
	 *
	 * @remark `length + 1` bytes are allocated so that the resulting String
	 * is always null-terminated.
	 *
	 * @relates String
	 */
	String *(*initWithBytes)(String *self, const byte *bytes, size_t length);

	/**
	 * @brief Initializes this String with the specified characters.
	 *
	 * @param chars The characters.
	 *
	 * @return The initialized String, or `NULL` on error.
	 *
	 * @relates String
	 */
	String *(*initWithCharacters)(String *self, const char *chars);

	/**
	 * @brief Initializes this String with the contents of the FILE at `path`.
	 *
	 * @param path The path of the file to load.
	 *
	 * @return The initialized String, or `NULL` on error.
	 *
	 * @relates String
	 */
	String *(*initWithContentsOfFile)(String *self, const char *path);

	/**
	 * @brief Initializes this String with the given Data.
	 *
	 * @param data The Data object.
	 *
	 * @return The initialized String, or `NULL` on error.
	 *
	 * @relates String
	 */
	String *(*initWithData)(String *self, const Data *data);

	/**
	 * @brief Initializes this String with the specified format string.
	 *
	 * @param fmt The formatted string.
	 *
	 * @return The initialized String, or `NULL` on error.
	 *
	 * @relates String
	 */
	String *(*initWithFormat)(String *self, const char *fmt, ...);

	/**
	 * @brief Initializes this String with the specified buffer.
	 *
	 * @param mem The null-terminated, dynamically allocated memory.
	 * @param length The length of the String in characters.
	 *
	 * @return The initialized String, or `NULL` on error.
	 *
	 * @remark `length` should *not* account for the terminating character.
	 *
	 * @relates String
	 */
	String *(*initWithMemory)(String *self, id mem, size_t length);

	/**
	 * @return A lowercase representation of this String.
	 *
	 * @relates String
	 */
	String *(*lowercaseString)(const String *self);

	/**
	 * Finds and returns the first occurrence of `chars` in this String.
	 *
	 * @param chars The characters to search for.
	 * @param range The range in which to search.
	 *
	 * @return A RANGE specifying the first occurrence of `chars` in this String.
	 *
	 * @relates String
	 */
	RANGE (*rangeOfCharacters)(const String *self, const char *chars, const RANGE range);

	/**
	 * Finds and returns the first occurrence of `string` in this String.
	 *
	 * @param string The String to search for.
	 * @param range The range in which to search.
	 *
	 * @return A RANGE specifying the first occurrence of `string` in this String.
	 *
	 * @relates String
	 */
	RANGE (*rangeOfString)(const String *self, const String *string, const RANGE range);

	/**
	 * @brief Returns a new String by copying `length` of `bytes`.
	 *
	 * @param bytes The bytes.
	 * @param length The length of `bytes` to copy.
	 *
	 * @return The new String, or `NULL` on error.
	 *
	 * @remark `length + 1` bytes are allocated so that the resulting String
	 * is always null-terminated.
	 *
	 * @relates String
	 */
	String *(*stringWithBytes)(const byte *bytes, size_t length);

	/**
	 * @brief Returns a new String with the given characters.
	 *
	 * @param chars A null-terminated C string.
	 *
	 * @return The new String, or `NULL` on error.
	 *
	 * @relates String
	 */
	String *(*stringWithCharacters)(const char *chars);

	/**
	 * @brief Returns a new String with the contents of the FILE at `path`.
	 *
	 * @param path The path name.
	 *
	 * @return The new String, or `NULL` on error.
	 *
	 * @relates String
	 */
	String *(*stringWithContentsOfFile)(const char *path);

	/**
	 * @brief Returns a new String with the the given Data.
	 *
	 * @param data A Data.
	 *
	 * @return The new String, or `NULL` on error.
	 *
	 * @relates String
	 */
	String *(*stringWithData)(const Data *data);

	/**
	 * @brief Returns a new String with the given format string.
	 *
	 * @param fmt The formatted string.
	 *
	 * @return The new String, or `NULL` on error.
	 *
	 * @relates String
	 */
	String *(*stringWithFormat)(const char *fmt, ...);

	/**
	 * @brief Creates a new String from a subset of this one.
	 *
	 * @param range The character range.
	 *
	 * @return The new String.
	 *
	 * @relates String
	 */
	String *(*substring)(const String *self, RANGE range);

	/**
	 * @return An uppercase representation of this String.
	 *
	 * @relates String
	 */
	String *(*uppercaseString)(const String *self);

	/**
	 * @brief Writes this String to `path`.
	 *
	 * @param path The path of the file to write.
	 *
	 * @return `YES` on success, `NO` on error.
	 *
	 * @relates String
	 */
	BOOL (*writeToFile)(const String *self, const char *path);
};

/**
 * @brief The String Class.
 */
extern Class _String;

/**
 * @brief A convenience function built around `vasprintf`.
 *
 * @param mem The pointer to receive the dynamically allocated string.
 * @param fmt The format string.
 * @param args The format arguments.
 *
 * @return The length of the allocated string, in bytes.
 */
size_t vaStringPrintf(id *mem, const char *fmt, va_list args);

#endif
