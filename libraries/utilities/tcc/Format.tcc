////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Rockmill
//  File:     StringFormat.tcc (utilities)
//  Authors:  Ofer Dekel
//
//  [copyright]
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Parser.h"

// stl
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <type_traits>

namespace utilities
{
    Match::Match(const char* pStr) : _pStr(pStr)
    {}

    Match::Match(const std::string & str) : _pStr(str.c_str())
    {}

    Match::operator const char*()
    {
        return _pStr;
    }

    template<typename ArgType, typename ... ArgTypes>
    void PrintFormat(std::ostream& os, const char* format, const ArgType& arg, const ArgTypes& ...args)
    {
        if(*format == '\0')
        {
            return;
        }

        while(*format != substitutionSymbol && *format != '\0')
        {
            if(*format != whitespaceSymbol)
            {
                os << *format;
            }
            ++format;
        }

        if(*format == substitutionSymbol)
        {
            ++format;
            os << arg;
        }

        PrintFormat(os, format, args...);
    }

    template<typename ... ArgTypes>
    std::string PrintFormat(const char* format, const ArgTypes& ...args)
    {
        std::stringstream ss;
        PrintFormat(ss, format, args...);
        return ss.str();
    }

    template<typename ... ArgTypes>
    MatchResult MatchFormat(const char*& content, const char* format, Match match, ArgTypes& ...args)
    {
        auto matchResult = MatchToSubstitutionSymbol(content, format);

        if(matchResult != MatchResult::success)
        {
            return matchResult;
        }
        if(*format == '\0')
        {
            return MatchResult::success;
        }

        // *format = substitutionSymbol
        ++format;

        const char* cStr = match;
        matchResult = MatchToSubstitutionSymbol(content, cStr);
        if(matchResult != MatchResult::success)
        {
            return matchResult;
        }
        if(*cStr != '\0')
        {
            return MatchResult::unexpectedPercentSymbol;
        }

        return MatchFormat(content, format, args...);
    }

    template<typename ArgType, typename ... ArgTypes>
    MatchResult MatchFormat(const char*& content, const char* format, ArgType& arg, ArgTypes& ...args)
    {
        auto matchResult = MatchToSubstitutionSymbol(content, format);

        if(matchResult != MatchResult::success)
        {
            return matchResult;
        }
        if(*format == '\0')
        {
            return MatchResult::success;
        }

        // *format = substitutionSymbol
        ++format;

        auto parserResult = Parse<std::remove_reference_t<ArgType>>(content, arg);
        if(parserResult != ParseResult::success)
        {
            return MatchResult::parserError;
        }

        return MatchFormat(content, format, args...);
    }

    template<typename ... ArgTypes>
    void MatchFormatThrowsExceptions(const char*& content, const char* format, ArgTypes&& ...args)
    {
        auto result = MatchFormat(content, format, args...);

        if(result == MatchResult::success)
        {
            return;
        }

        std::string contentSnippet(content, 30);
        std::string formatSnippet(format,30);
        auto snippets = "\"" + contentSnippet + "\" and \"" + formatSnippet + "\"";

        switch(result)
        {
        case MatchResult::earlyEndOfContent:
            throw std::runtime_error("Error scanning text: content ended before format near: \"" + formatSnippet + "\"");

        case MatchResult::mismatch:
            throw std::runtime_error("Error scanning text: mismatch between content and format near: " + snippets);

        case MatchResult::parserError:
            throw std::runtime_error("Error scanning text: parser error near: " + snippets);

        case MatchResult::missingArgument:
            throw std::runtime_error("Error scanning text: missing argument near: " + snippets);

        case MatchResult::unexpectedPercentSymbol:
            throw std::runtime_error("Error scanning text: unexpected symbol '" + std::to_string(substitutionSymbol) + "' in string argument near: " + snippets);

        case MatchResult::success:
            ; // nothing
        }
    }
}
