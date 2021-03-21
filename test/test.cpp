#include "gtest/gtest.h"

#include <filesystem>
#include <fstream>
#include <limits>
#include <random>

#include "FileVault.hpp"

namespace fs = std::filesystem;

namespace {

int getRandomNumber() {
	static std::random_device dev;
	static std::mt19937 rng(dev());
	static std::uniform_int_distribution<std::mt19937::result_type> dist(
		0, std::numeric_limits<int>::max());

	return dist(rng);
}

}

namespace chirpexplorer {

class TestFileVault : public testing::Test {
protected:
	fs::path _tempFile;

public:
	void SetUp() override {
		auto tempDir = fs::temp_directory_path();
		do {
			_tempFile = tempDir;
			_tempFile /= "file_" + std::to_string(getRandomNumber());
		} while (fs::exists(_tempFile));
	}

	void TearDown() override {
		fs::remove(_tempFile);
	}
};

TEST_F(TestFileVault, loadNonExisting) {
	FileVault vault(_tempFile);
	auto res = vault.load();

	EXPECT_FALSE(res.second);
	EXPECT_EQ(res.first, Token());
}

TEST_F(TestFileVault, loadExisting) {
	Token token("token");

	std::ofstream ofs(_tempFile);
	if (ofs.is_open()) {
		ofs << token;
	}
	ofs.close();

	FileVault vault(_tempFile);
	auto res = vault.load();

	EXPECT_TRUE(res.second);
	EXPECT_EQ(res.first, token);
}

TEST_F(TestFileVault, storeInvalidPath) {
	_tempFile /= "_=+*&%£$!@[]{}()#~/,,,\<>`";
	FileVault vault(_tempFile);

	Token token("token");
	auto res = vault.store(token);

	EXPECT_FALSE(res);
}

TEST_F(TestFileVault, storeNonExistingCreatesFile) {
	FileVault vault(_tempFile);
	Token token("token");
	auto res = vault.store(token);

	EXPECT_TRUE(res);
	ASSERT_TRUE(fs::exists(_tempFile));

	Token storedToken;
	std::ifstream ifs(_tempFile);
	if (ifs.is_open()) {
		std::getline(ifs, storedToken);
	}

	EXPECT_EQ(storedToken, token);
}

TEST_F(TestFileVault, storeExistingOverwritesFile) {
	Token token("token");
	FileVault vault(_tempFile);
	auto storeRes = vault.store(token);
	ASSERT_TRUE(storeRes);

	auto loadRes = vault.load();
	EXPECT_TRUE(loadRes.second);
	ASSERT_EQ(loadRes.first, token);

	Token newToken("newtoken");
	storeRes = vault.store(newToken);
	ASSERT_TRUE(storeRes);

	loadRes = vault.load();
	EXPECT_TRUE(loadRes.second);
	ASSERT_EQ(loadRes.first, newToken);
}

}