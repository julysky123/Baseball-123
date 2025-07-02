#include "gmock/gmock.h"
#include "baseball.cpp"
using namespace::testing;
using std::string;
using std::exception;

class BaseballFixture : public Test {
public:
	Baseball game;
	void assertIllegalArgument(string guessNumber) {
		Baseball game;
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
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}