#include "pch.h"

std::optional<std::string> try_convert_to_sjis_loosely(const wchar_t input) {
	BOOL failed = false;
	int len = WideCharToMultiByte(932, 0, &input, 1, nullptr, 0, nullptr, &failed);
	assert(GetLastError() != ERROR_INVALID_PARAMETER);
	if (failed) {
		return std::nullopt;
	}
	std::string output(len, 0);
	WideCharToMultiByte(932, 0, &input, 1, output.data(), len, nullptr, nullptr);
	return output;
}
std::optional<std::string> try_convert_to_sjis_strictly(const wchar_t input) {
	BOOL failed = false;
	int len = WideCharToMultiByte(932, WC_NO_BEST_FIT_CHARS, &input, 1, nullptr, 0, nullptr, &failed);
	assert(GetLastError() != ERROR_INVALID_PARAMETER);
	if (failed) {
		return std::nullopt;
	}
	std::string output(len, 0);
	WideCharToMultiByte(932, WC_NO_BEST_FIT_CHARS, &input, 1, output.data(), len, nullptr, nullptr);
	return output;
}

////////////////////////////////////////////////////////////////////////////////

TEST(AlreadyPassed, Yen) {
	const auto result = try_convert_to_sjis_loosely(L'\u00A5');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "\\");
	ASSERT_FALSE(try_convert_to_sjis_strictly(L'\u00A5').has_value());
}
TEST(AlreadyPassed, FullWidthTilde) {
	const auto result = try_convert_to_sjis_strictly(L'\uFF5E');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "\x81\x60");
}
TEST(AlreadyPassed, ParallelTo) {
	const auto result = try_convert_to_sjis_strictly(L'\u2225');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "\x81\x61");
}
TEST(AlreadyPassed, FullWidthHypen) {
	const auto result = try_convert_to_sjis_strictly(L'\uFF0D');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "\x81\x7c");
}
TEST(AlreadyPassed, HorizontalBar) {
	const auto result = try_convert_to_sjis_strictly(L'\u2015');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "\x81\x5c");
}
TEST(AlreadyPassed, FullWidthCent) {
	const auto result = try_convert_to_sjis_strictly(L'\uFFE0');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "\x81\x91");
}
TEST(AlreadyPased, HalfWidthCent) {
	const auto result = try_convert_to_sjis_loosely(L'\u00A2');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "\x81\x91");
	ASSERT_FALSE(try_convert_to_sjis_strictly(L'\u00A2').has_value());
}
TEST(AlreadyPassed, FullWidthPound) {
	const auto result = try_convert_to_sjis_strictly(L'\uFFE1');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "\x81\x92");
}
TEST(AlreadyPassed, HalfWidthPound) {
	const auto result = try_convert_to_sjis_loosely(L'\u00A3');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "\x81\x92");
	ASSERT_FALSE(try_convert_to_sjis_strictly(L'\u00A3').has_value());
}
TEST(AlreadyPassed, FullWidthNotSign) {
	const auto result = try_convert_to_sjis_strictly(L'\uFFE2');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "\x81\xCA");
}
TEST(AlreadyPassed, HalfWidthNotSign) {
	const auto result = try_convert_to_sjis_loosely(L'\u00AC');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "\x81\xCA");
	ASSERT_FALSE(try_convert_to_sjis_strictly(L'\u00AC').has_value());
}

////////////////////////////////////////////////////////////////

TEST(NotPassed, WaveDash) {
	const auto result = try_convert_to_sjis_loosely(L'\u301C');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "\x81\x60");
}
TEST(NotPassed, OverLine) {
	const auto result = try_convert_to_sjis_loosely(L'\u203E');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "~");
}
TEST(NotPassed, DoubleVerticalLine) {
	const auto result = try_convert_to_sjis_loosely(L'\u2016');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "\x81\x61");
}
TEST(NotPassed, Minus) {
	const auto result = try_convert_to_sjis_loosely(L'\u2212');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "\x81\x7c");
}
TEST(NotPassed, EmDash) {
	const auto result = try_convert_to_sjis_loosely(L'\u2014');
	ASSERT_TRUE(result.has_value());
	ASSERT_STREQ(result.value().c_str(), "\x81\x5c");
}