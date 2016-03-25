////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Rockmill
//  File:     TypeName.h (utilities)
//  Authors:  Ofer Dekel
//
//  [copyright]
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// stl
#include <cstdint>
#include <vector>
#include <memory>
#include <string>
#include <cstdint>

namespace utilities
{

    const char typeNameLeftBracket = '(';
    const char typeNameRightBracket = ')';

    /// <summary> Class used to get information about class types. </summary>
    ///
    /// <typeparam name="T"> Generic type parameter. </typeparam>
    template<typename T>
    struct TypeName
    {
        /// <summary> Gets the serialization name of the type. </summary>
        ///
        /// <returns> The serialization name. </returns>
        static std::string GetName();
    };

    /// <summary> Class used to get information about unique_ptr types. </summary>
    ///
    /// <typeparam name="T"> Generic type parameter. </typeparam>
    template<typename T>
    struct TypeName<std::unique_ptr<T>>
    {
        /// <summary> Gets the serialization name of the type. </summary>
        ///
        /// <returns> The serialization name. </returns>
        static std::string GetName();
    };

    /// <summary> Class used to get information about std::vector types. </summary>
    ///
    /// <typeparam name="T"> Generic type parameter. </typeparam>
    template<typename T>
    struct TypeName<std::vector<T>>
    {
        /// <summary> Gets the serialization name of the type. </summary>
        ///
        /// <returns> The serialization name. </returns>
        static std::string GetName();
    };

    /// <summary> Class used to get information about the 8-bit integer type. </summary>
    ///
    /// <typeparam name="T"> Generic type parameter. </typeparam>
    template<>
    struct TypeName<int8_t>
    {
        /// <summary> Gets the serialization name of the type. </summary>
        ///
        /// <returns> The serialization name. </returns>
        static std::string GetName() { return "int8"; }
    };

    /// <summary> Class used to get information about the unsigned 8-bit integer type. </summary>
    ///
    /// <typeparam name="T"> Generic type parameter. </typeparam>
    template<>
    struct TypeName<uint8_t>
    {
        /// <summary> Gets the serialization name of the type. </summary>
        ///
        /// <returns> The serialization name. </returns>
        static std::string GetName() { return "uint8"; }
    };

    /// <summary> Class used to get information about the 16-bit integer type. </summary>
    ///
    /// <typeparam name="T"> Generic type parameter. </typeparam>
    template<>
    struct TypeName<int16_t>
    {
        /// <summary> Gets the serialization name of the type. </summary>
        ///
        /// <returns> The serialization name. </returns>
        static std::string GetName() { return "int16"; }
    };

    /// <summary> Class used to get information about the unsigned 16-bit integer type. </summary>
    ///
    /// <typeparam name="T"> Generic type parameter. </typeparam>
    template<>
    struct TypeName<uint16_t>
    {
        /// <summary> Gets the serialization name of the type. </summary>
        ///
        /// <returns> The serialization name. </returns>
        static std::string GetName() { return "uint16"; }
    };


    /// <summary> Class used to get information about the 32-bit integer type. </summary>
    ///
    /// <typeparam name="T"> Generic type parameter. </typeparam>
    template<>
    struct TypeName<int32_t>
    {
        /// <summary> Gets the serialization name of the type. </summary>
        ///
        /// <returns> The serialization name. </returns>
        static std::string GetName() { return "int32"; }
    };

    /// <summary> Class used to get information about the unsigned 32-bit integer type. </summary>
    ///
    /// <typeparam name="T"> Generic type parameter. </typeparam>
    template<>
    struct TypeName<uint32_t>
    {
        /// <summary> Gets the serialization name of the type. </summary>
        ///
        /// <returns> The serialization name. </returns>
        static std::string GetName() { return "uint32"; }
    };

    /// <summary> Class used to get information about the 64-bit integer type. </summary>
    ///
    /// <typeparam name="T"> Generic type parameter. </typeparam>
    template<>
    struct TypeName<int64_t>
    {
        /// <summary> Gets the serialization name of the type. </summary>
        ///
        /// <returns> The serialization name. </returns>
        static std::string GetName() { return "int64"; }
    };

    /// <summary> Class used to get information about the unsigned 64-bit integer type. </summary>
    ///
    /// <typeparam name="T"> Generic type parameter. </typeparam>
    template<>
    struct TypeName<uint64_t>
    {
        /// <summary> Gets the serialization name of the type. </summary>
        ///
        /// <returns> The serialization name. </returns>
        static std::string GetName() { return "uint64"; }
    };

    /// <summary> Class used to get information about the float type. </summary>
    ///
    /// <typeparam name="T"> Generic type parameter. </typeparam>
    template<>
    struct TypeName<float>
    {
        /// <summary> Gets the serialization name of the type. </summary>
        ///
        /// <returns> The serialization name. </returns>
        static std::string GetName() { return "float"; }
    };

    /// <summary> Class used to get information about the double type. </summary>
    ///
    /// <typeparam name="T"> Generic type parameter. </typeparam>
    template<>
    struct TypeName<double>
    {
        /// <summary> Gets the serialization name of the type. </summary>
        ///
        /// <returns> The serialization name. </returns>
        static std::string GetName() { return "double"; }
    };
}

#include "../tcc/TypeName.tcc"
