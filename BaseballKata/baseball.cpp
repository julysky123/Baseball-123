#include <stdexcept>
#include <string>
using std::string;
using std::length_error;
using std::invalid_argument;

class Baseball {
public:
	void guess(const string& guessNumber) {
		if (guessNumber.length() != 3) {
			throw length_error("Must be three letters.");
		}

		for (char ch : guessNumber) {
			if (ch < '0' || ch >'9') {
				throw invalid_argument("Must be number.");
			}
		}
	}
};