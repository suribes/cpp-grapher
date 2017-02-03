#ifndef CPP_GRAPHER_H
#define CPP_GRAPHER_H

#include <vector>
#include <fstream>
#include "tinyutf8.h"

/// The application logic is written as a library to enable flexible packaging (static or dynamic linking) and
/// execution from a test runner, application driver (this class), or other driver.  Entry point for execution is
/// Main().
struct KalmanFilterDataPoint
{
    utf8_string name;
    double x, y;
};

class CppGrapher
{
public:
	/// Safe application Main() implementation.
	/// The traditional C-style practice of using argv + argc is an example of a "buffer + length" anti-pattern.
	/// Because the two must be manually coupled, this pattern has not only been shown to be a source of bugs (eg.
	/// off-by-one errors or buffer-a + length-of-buffer-b-errors) but also a security vulnerability (whenever the two
	/// are misaligned, we risk enabling an exploit).
	/// Using a buffer which manages its own length (ie. std::vector) ensures these kinds of issues cannot happen.
	/// @param args[in]         a const vector of UTF-8 strings representing the arguments given to the program.
	///                         Note: the system always provides the application's name as args[0].
	/// @returns                execution status code (typically EXIT_SUCCESS, as App will throw if it encounters an
	///                         error.)
	/// @throws                 May throw an InvalidArgumentException.
	int Main( const std::vector<utf8_string>& args );

private:
	void ValidateArgs( const std::vector<utf8_string>& args ) const;
    std::vector<KalmanFilterDataPoint> ParseKalmanFilterDataFile( const utf8_string& filename ) const;
	std::vector<KalmanFilterDataPoint> ParseKalmanFilterDataLine( std::ifstream& ifs ) const;

    KalmanFilterDataPoint ParseKalmanFilterDataTokens( const utf8_string& utf8_string ) const;

    utf8_string ParseKalmanFilterName( const utf8_string& utf8_string, utf8_string::size_type& pos ) const;

    double ParseKalmanFilterPoint( const utf8_string& utf8_string, utf8_string::size_type& pos ) const;

    std::tuple<utf8_string::size_type, utf8_string::size_type> FindNextToken( const utf8_string& utf8_string,
                                                                              utf8_string::size_type& pos ) const;
};

/// \example ../Tests/Unit/Lib.UnitTests.cpp
/// This is an example of how to use the CppGrapher class.

#endif //CPP_GRAPHER_H
