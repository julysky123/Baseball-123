#include "gmock/gmock.h"
#include "baseball.cpp"
using namespace::testing;
using std::string;
using std::exception;

class BaseballFixture : public Test {
public:
	Baseball game{ "123" };
	void assertIllegalArgument(string guessNumber) {
		try {
			game.guess(guessNumber);
			FAIL();
		}
		catch (exception e) {
			//PASS
		}
	}
};

TEST_F(BaseballFixture, ThrowExceptionWhenInvalidCase) {
	assertIllegalArgument("12");
	assertIllegalArgument("12s");
	assertIllegalArgument("121");
}

TEST_F(BaseballFixture, ReturnSolvedResultIfMatchedNumber) {
	GuessResult result = game.guess("123");

	EXPECT_TRUE(result.solved);
	EXPECT_EQ(3, result.strikes);
	EXPECT_EQ(0, result.balls);
}

TEST_F(BaseballFixture, ReturnNoStrikeAndNoBallWhenNoDigitsMatch) {
	GuessResult result = game.guess("456");
	EXPECT_FALSE(result.solved);
	EXPECT_EQ(0, result.strikes);
	EXPECT_EQ(0, result.balls);
}

TEST_F(BaseballFixture, ReturnTwoBallWhenTwoMatchingDigitsInWrongPosition) {
	GuessResult result = game.guess("234");
	EXPECT_FALSE(result.solved);
	EXPECT_EQ(0, result.strikes);
	EXPECT_EQ(2, result.balls);
}

TEST_F(BaseballFixture, ReturnOneStrikeWhenOneDigitMatches) {
	GuessResult result = game.guess("145");
	EXPECT_FALSE(result.solved);
	EXPECT_EQ(1, result.strikes);
	EXPECT_EQ(0, result.balls);
}

TEST_F(BaseballFixture, ReturnOneStrikeAndTwoBall) {
	GuessResult result = game.guess("132");
	EXPECT_FALSE(result.solved);
	EXPECT_EQ(1, result.strikes);
	EXPECT_EQ(2, result.balls);
}


int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}