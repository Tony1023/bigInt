#include "negativeExcept.h"

NegativeExcept::NegativeExcept()
	:msg("Result cannot be negative") {};

NegativeExcept::~NegativeExcept() {};

const char* NegativeExcept::what() const noexcept {
	return msg.c_str();
}