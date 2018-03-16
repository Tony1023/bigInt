#include <stdexcept>
#include <string>

class NegativeExcept: public std::exception {
public:
	NegativeExcept();
	virtual ~NegativeExcept();
	virtual const char* what() const noexcept;
private:
	std::string msg;
};