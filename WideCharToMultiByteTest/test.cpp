#include "pch.h"

static std::optional<std::string> try_convert_to_sjis_loosely(const wchar_t input) {
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
static std::optional<std::string> try_convert_to_sjis_strictly(const wchar_t input) {
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

namespace AlreadyPassed {
	static TEST(StrictConversion, FullWidthTilde_FF5E) {
		const auto result = try_convert_to_sjis_strictly(L'\uFF5E');
		ASSERT_TRUE(result.has_value()) << "U+FF5E must be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
		ASSERT_STREQ(result.value().c_str(), "\x81\x60") << "The converted result for U+FF5E is different.";
	}
	static TEST(StrictConversion, ParallelTo_2225) {
		const auto result = try_convert_to_sjis_strictly(L'\u2225');
		ASSERT_TRUE(result.has_value()) << "U+2225 must be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
		ASSERT_STREQ(result.value().c_str(), "\x81\x61") << "The converted result for U+2225 is different.";
	}
	static TEST(StrictConversion, FullWidthHypen_FF0D) {
		const auto result = try_convert_to_sjis_strictly(L'\uFF0D');
		ASSERT_TRUE(result.has_value()) << "U+FF0D must be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
		ASSERT_STREQ(result.value().c_str(), "\x81\x7c") << "The converted result for U+FF0D is different.";
	}
	static TEST(StrictConversion, HorizontalBar_2015) {
		const auto result = try_convert_to_sjis_strictly(L'\u2015');
		ASSERT_TRUE(result.has_value()) << "U+2015 must be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
		ASSERT_STREQ(result.value().c_str(), "\x81\x5c") << "The converted result for U+2015 is different.";
	}
	static TEST(StrictConversion, FullWidthCent_FFE0) {
		const auto result = try_convert_to_sjis_strictly(L'\uFFE0');
		ASSERT_TRUE(result.has_value()) << "U+FFE0 must be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
		ASSERT_STREQ(result.value().c_str(), "\x81\x91") << "The converted result for U+FFE0 is different.";
	}
	static TEST(StrictConversion, FullWidthPound_FFE1) {
		const auto result = try_convert_to_sjis_strictly(L'\uFFE1');
		ASSERT_TRUE(result.has_value()) << "U+FFE1 must be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
		ASSERT_STREQ(result.value().c_str(), "\x81\x92") << "The converted result for U+FFE1 is different.";
	}

	static TEST(LooseConversion, HalfWidthCent_00A2) {
		const auto result = try_convert_to_sjis_loosely(L'\u00A2');
		ASSERT_TRUE(result.has_value()) << "U+00A2 must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS.";
		ASSERT_STREQ(result.value().c_str(), "\x81\x91") << "The converted result for U+00A2 is different.";
		ASSERT_FALSE(try_convert_to_sjis_strictly(L'\u00A2').has_value()) << "U+00A2 must not be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
	}
	static TEST(LooseConversion, HalfWidthPound_00A3) {
		const auto result = try_convert_to_sjis_loosely(L'\u00A3');
		ASSERT_TRUE(result.has_value()) << "U+00A3 must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS.";
		ASSERT_STREQ(result.value().c_str(), "\x81\x92") << "The converted result for U+00A3 is different.";
		ASSERT_FALSE(try_convert_to_sjis_strictly(L'\u00A3').has_value()) << "U+00A3 must not be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
	}
	static TEST(LooseConversion, FullWidthNotSign_FFE2) {
		const auto result = try_convert_to_sjis_strictly(L'\uFFE2');
		ASSERT_TRUE(result.has_value()) << "U+FFE2 must be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
		ASSERT_STREQ(result.value().c_str(), "\x81\xCA") << "The converted result for U+FFE2 is different.";
	}
	static TEST(LooseConversion, HalfWidthNotSign_00AC) {
		const auto result = try_convert_to_sjis_loosely(L'\u00AC');
		ASSERT_TRUE(result.has_value()) << "U+00AC must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS.";
		ASSERT_STREQ(result.value().c_str(), "\x81\xCA") << "The converted result for U+00AC is different.";
		ASSERT_FALSE(try_convert_to_sjis_strictly(L'\u00AC').has_value()) << "U+00AC must not be able to be converted to Shift_JIS with WC_NO_BEST_FIT_CHARS.";
	}
}

////////////////////////////////////////////////////////////////

namespace MustBeFixed {
	static TEST(LooseConversion, WaveDash_301C) {
		const auto result = try_convert_to_sjis_loosely(L'\u301C');
		ASSERT_TRUE(result.has_value()) << "U+301C must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS";
		ASSERT_STREQ(result.value().c_str(), "\x81\x60") << "The converted result for U+301C is different";
	}
	static TEST(LooseConversion, OverLine_203E) {
		const auto result = try_convert_to_sjis_loosely(L'\u203E');
		ASSERT_TRUE(result.has_value()) << "U+203E must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS";
		ASSERT_STREQ(result.value().c_str(), "~") << "The converted result for U+203E is different";
	}
	static TEST(LooseConversion, DoubleVerticalLine_2016) {
		const auto result = try_convert_to_sjis_loosely(L'\u2016');
		ASSERT_TRUE(result.has_value()) << "U+2016 must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS";
		ASSERT_STREQ(result.value().c_str(), "\x81\x61") << "The converted result for U+2016 is different";
	}
	static TEST(LooseConversion, Minus_2212) {
		const auto result = try_convert_to_sjis_loosely(L'\u2212');
		ASSERT_TRUE(result.has_value()) << "U+2212 must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS";
		ASSERT_STREQ(result.value().c_str(), "\x81\x7c") << "The converted result for U+2212 is different";
	}
	static TEST(LooseConversion, EmDash_2014) {
		const auto result = try_convert_to_sjis_loosely(L'\u2014');
		ASSERT_TRUE(result.has_value()) << "U+2014 must be able to be converted to Shift_JIS even without WC_NO_BEST_FIT_CHARS";
		ASSERT_STREQ(result.value().c_str(), "\x81\x5c") << "The converted result for U+2014 is different";
	}
}