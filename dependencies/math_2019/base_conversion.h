#pragma once
#ifndef BASE_CONVERSION_H
#define BASE_CONVERSION_H

class base_conversion
{
public:
	/*	\brief Converts string of 1's and 0's to interger.
		\param The null therminated string to convert.
		\return The integer value of the converted string.
	*/
	static int binary_string_to_integer(const char * a_binary_string);

	/*	\brief Converts interger to string of 1's and 0's.
		\param The destination char*.
		\param The interger to cinvert
		\note The char* should be sizeof(int) * 8 + 1 characters long
	*/
	static void integer_to_binary_string(char * a_binary_string, int value);

	/*	\brief Sets the bit at the given index to the passed state.
		\param The bitfield to edit by regerence.
		\param THe index of the bit to change.
		\param THe desired state of the bit at the index.
	*/
	static void set_bit(int & a_bit_field, char a_bit_index, bool a_state);

	/*	\brief Reads the state of the bit at tht eindex from a given bitfield.
		\param The bitfield, read only, to check.
		\paran The index of the bit to check.
		\return The current state of the bit at te index.
	*/
	static bool get_bit(const int & a_bit_field, char a_bit_index);

	/*	\brief Dumps the binary of the given int to iostream.
		\param The interger to display, bitwise.
	*/
	static void print_int_as_binary(const int a_bit_field, bool a_spaced = false);
};

#endif // !BASE_CONVERSION_H
