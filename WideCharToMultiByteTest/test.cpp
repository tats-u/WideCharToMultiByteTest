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
	ASSERT_TRUE(result.has_value()) << "U+00A5 must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS.";
	ASSERT_STREQ(result.value().c_str(), "\\") << "The converted result for U+00A5 is different.";
	ASSERT_FALSE(try_convert_to_sjis_strictly(L'\u00A5').has_value()) << "U+00A5 must not be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
}
TEST(AlreadyPassed, FullWidthTilde) {
	const auto result = try_convert_to_sjis_strictly(L'\uFF5E');
	ASSERT_TRUE(result.has_value()) << "U+FF5E must be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
	ASSERT_STREQ(result.value().c_str(), "\x81\x60") << "The converted result for U+FF5E is different.";
}
TEST(AlreadyPassed, ParallelTo) {
	const auto result = try_convert_to_sjis_strictly(L'\u2225');
	ASSERT_TRUE(result.has_value()) << "U+2225 must be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
	ASSERT_STREQ(result.value().c_str(), "\x81\x61") << "The converted result for U+2225 is different.";
}
TEST(AlreadyPassed, FullWidthHypen) {
	const auto result = try_convert_to_sjis_strictly(L'\uFF0D');
	ASSERT_TRUE(result.has_value()) << "U+FF0D must be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
	ASSERT_STREQ(result.value().c_str(), "\x81\x7c") << "The converted result for U+FF0D is different.";
}
TEST(AlreadyPassed, HorizontalBar) {
	const auto result = try_convert_to_sjis_strictly(L'\u2015');
	ASSERT_TRUE(result.has_value()) << "U+2015 must be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
	ASSERT_STREQ(result.value().c_str(), "\x81\x5c") << "The converted result for U+2015 is different.";
}
TEST(AlreadyPassed, FullWidthCent) {
	const auto result = try_convert_to_sjis_strictly(L'\uFFE0');
	ASSERT_TRUE(result.has_value())	<< "U+FFE0 must be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
	ASSERT_STREQ(result.value().c_str(), "\x81\x91") << "The converted result for U+FFE0 is different.";
}
TEST(AlreadyPassed, HalfWidthCent) {
	const auto result = try_convert_to_sjis_loosely(L'\u00A2');
	ASSERT_TRUE(result.has_value()) << "U+00A2 must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS.";
	ASSERT_STREQ(result.value().c_str(), "\x81\x91") << "The converted result for U+00A2 is different.";
	ASSERT_FALSE(try_convert_to_sjis_strictly(L'\u00A2').has_value()) << "U+00A2 must not be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
}
TEST(AlreadyPassed, FullWidthPound) {
	const auto result = try_convert_to_sjis_strictly(L'\uFFE1');
	ASSERT_TRUE(result.has_value()) << "U+FFE1 must be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
	ASSERT_STREQ(result.value().c_str(), "\x81\x92") << "The converted result for U+FFE1 is different.";
}
TEST(AlreadyPassed, HalfWidthPound) {
	const auto result = try_convert_to_sjis_loosely(L'\u00A3');
	ASSERT_TRUE(result.has_value()) << "U+00A3 must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS.";
	ASSERT_STREQ(result.value().c_str(), "\x81\x92") << "The converted result for U+00A3 is different.";
	ASSERT_FALSE(try_convert_to_sjis_strictly(L'\u00A3').has_value()) << "U+00A3 must not be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
}
TEST(AlreadyPassed, FullWidthNotSign) {
	const auto result = try_convert_to_sjis_strictly(L'\uFFE2');
	ASSERT_TRUE(result.has_value()) << "U+FFE2 must be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
	ASSERT_STREQ(result.value().c_str(), "\x81\xCA") << "The converted result for U+FFE2 is different.";
}
TEST(AlreadyPassed, HalfWidthNotSign) {
	const auto result = try_convert_to_sjis_loosely(L'\u00AC');
	ASSERT_TRUE(result.has_value()) << "U+00AC must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS.";
	ASSERT_STREQ(result.value().c_str(), "\x81\xCA") << "The converted result for U+00AC is different.";
	ASSERT_FALSE(try_convert_to_sjis_strictly(L'\u00AC').has_value()) << "U+00AC must not be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
}

////////////////////////////////////////////////////////////////

TEST(MustBeFixed, WaveDash) {
	const auto result = try_convert_to_sjis_loosely(L'\u301C');
	ASSERT_TRUE(result.has_value()) << "U+301C must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS";
	ASSERT_STREQ(result.value().c_str(), "\x81\x60") << "The converted result for U+301C is different";
}
TEST(MustBeFixed, OverLine) {
	const auto result = try_convert_to_sjis_loosely(L'\u203E');
	ASSERT_TRUE(result.has_value()) << "U+203E must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS";
	ASSERT_STREQ(result.value().c_str(), "~") << "The converted result for U+203E is different";
}
TEST(MustBeFixed, DoubleVerticalLine) {
	const auto result = try_convert_to_sjis_loosely(L'\u2016');
	ASSERT_TRUE(result.has_value()) << "U+2016 must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS";
	ASSERT_STREQ(result.value().c_str(), "\x81\x61") << "The converted result for U+2016 is different";
}
TEST(MustBeFixed, Minus) {
	const auto result = try_convert_to_sjis_loosely(L'\u2212');
	ASSERT_TRUE(result.has_value()) << "U+2212 must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS";
	ASSERT_STREQ(result.value().c_str(), "\x81\x7c") << "The converted result for U+2212 is different";
}
TEST(MustBeFixed, EmDash) {
	const auto result = try_convert_to_sjis_loosely(L'\u2014');
	ASSERT_TRUE(result.has_value()) << "U+2014 must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS";
	ASSERT_STREQ(result.value().c_str(), "\x81\x5c") << "The converted result for U+2014 is different";
}