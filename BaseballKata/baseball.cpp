#include <stdexcept>
#include <string>
using std::string;
using std::length_error;
using std::invalid_argument;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	explicit Baseball(const string& question)
		: question(question)
	{
	}
	GuessResult guess(const string& guessNumber) {
		assertIllegalArgument(guessNumber);
		return makeGuessResult(guessNumber);
	}


private:
	string question;
	void assertIllegalArgument(const std::string& guessNumber)
	{
		if (guessNumber.length() != 3) {
			throw length_error("Must be three letters.");
		}

		for (char ch : guessNumber) {
			if (ch >= '0' && ch <= '9') continue;
			throw invalid_argument("Must be number.");
		}

		if (isDuplicatedNumber(guessNumber)) {
			throw invalid_argument("Must not have the same number.");
		}
	}
	bool isDuplicatedNumber(const std::string& guessNumber)
	{
		return guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2];
	}

	const GuessResult makeGuessResult(const std::string& guessNumber)
	{
		if (isGuessCorrect(guessNumber)) {
			return { true, 3, 0 };
		}
		int strikes = countStrikes(guessNumber);
		int balls = countBalls(guessNumber);
		return { false, strikes, balls };
	}
	bool isGuessCorrect(const std::string& guessNumber)
	{
		return guessNumber == question;
	}
	int countBalls(const std::string& guessNumber)
	{
		int ballCount = 0;
		for (int index = 0; index < guessNumber.length(); index++) {
			char targetNumber = guessNumber[index];
			int position = static_cast<int>(question.find(targetNumber));
			if (position == -1) continue;
			if (position != index) ballCount++;
		}
		return ballCount;
	}
	
	int countStrikes(const std::string& guessNumber)
	{
		int strikeCount = 0;
		for (int index = 0; index < guessNumber.length(); index++) {
			char targetNumber = guessNumber[index];
			int position = static_cast<int>(question.find(targetNumber));
			if (position == -1) continue;
			if (position == index) strikeCount++;
		}
		return strikeCount;
	}
};