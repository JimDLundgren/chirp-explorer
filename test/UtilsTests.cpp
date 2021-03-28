#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TokenVault.hpp"
#include "Utils.hpp"

using ::testing::Eq;
using ::testing::NiceMock;
using ::testing::Return;

namespace chirpexplorer {

class MockVault : public TokenVault
{
public:
	MOCK_METHOD((std::pair<Token, bool>), load, (), (override));
	MOCK_METHOD(bool, store, (Token token), (override));
};

TEST(TestUtils, getStoredBearerToken) {
	auto vault = std::make_shared<NiceMock<MockVault>>();

	Token expToken("token");
	EXPECT_CALL(*vault, load())
		.Times(1)
		.WillOnce(Return(std::make_pair(expToken, true)));

	auto token = getBearerToken(*vault);

	EXPECT_EQ(token, expToken);
}

TEST(TestUtils, parseTweetSearchResultBody) {
	Tweets expTweets = { "text1", "text2", "text3" };

	std::string rawTweets =
	"{"
		"\"data\":["
			"{\"id\":\"01\",\"text\":\"" + expTweets[0] + "\"},"
			"{\"id\":\"02\",\"text\":\"" + expTweets[1] + "\"},"
			"{\"id\":\"03\",\"text\":\"" + expTweets[2] + "\"}"
		"],"
		"\"meta\":{"
			"\"newest_id\":\"02\",\"oldest_id\":\"01\",\"result_count\":3,\"next_token\":\"blah\""
		"}"
	"}";

	auto tweets = parseTweetSearchResult(rawTweets);

	EXPECT_EQ(tweets, expTweets);
}

}