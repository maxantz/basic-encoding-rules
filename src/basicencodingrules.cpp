#include "basicencodingrules.h"
#include "utils.hpp"

#include <vector>
#include <cstdint>
#include <cstddef>
#include <stdexcept>

std::vector<uint8_t> size_t_to_msb_vector(size_t value)
{
    std::vector<uint8_t> result;

    // On parcourt de MSB (octet le plus à gauche) vers LSB
    bool significant_found = false;
    for (int i = static_cast<int>(sizeof(size_t)) - 1; i >= 0; --i) {
        uint8_t byte = static_cast<uint8_t>((value >> (i * 8)) & 0xFF);
        if (byte != 0 || significant_found) {
            result.push_back(byte);
            significant_found = true;
        }
    }

    // Si la valeur est zéro, ajouter explicitement un zéro
    if (!significant_found) {
        result.push_back(0);
    }

    return result;
}

size_t vector_to_size_t(const std::vector<uint8_t>& bytes)
{
    if (bytes.size() > sizeof(size_t)) {
        throw std::runtime_error("Vector too large to convert to size_t");
    }

    size_t value = 0;
    for (uint8_t byte : bytes) {
        value = (value << 8) | byte;
    }

    return value;
}


BasicEncodingRules::BasicEncodingRules() : m_value(0ull)
{
    //ctor
}

BasicEncodingRules::BasicEncodingRules(size_t value) : m_value(value)
{
    //ctor
}

BasicEncodingRules::~BasicEncodingRules()
{
    //dtor
}

void BasicEncodingRules::SetValue(size_t value)
{
    m_value = value;
}

size_t BasicEncodingRules::GetValue() const
{
    return m_value;
}

size_t BasicEncodingRules::GetLength() const
{
    size_t l_result = 0ull;

    if (m_value > 127)
    {
        size_t l_tmp = m_value;
        while (l_tmp > 0)
        {
            l_result++;
            l_tmp >>= 8;
        }
    }

    return l_result + 1ull;
}

size_t BasicEncodingRules::FromBytes(const std::vector<uint8_t>& value)
{
    const size_t l_value_length = value.size();
    if (0ull == l_value_length)
    {
        m_value = 0ull;
        return 0ull;
    }

    const uint8_t l_first = value.at(0);
    if (0u == (l_first & 0x80))
    {
        m_value = l_first;
	return 1ull;
    }
    else
    {
        const size_t l_num_bytes = static_cast<size_t>(l_first & 0x7F);
	if ((0ull == l_num_bytes) || (sizeof(size_t) < l_num_bytes) || ((l_value_length - 1) < l_num_bytes))
        {
             m_value = 0ull;
	     return 0ull;
        }

	size_t l_length = 0ull;
	for (size_t i = 0ull; i < l_num_bytes; i++)
        {
            l_length = (l_length << 8) | value.at(i + 1);
        }
	m_value = l_length;
	return l_num_bytes + 1ull;
    }

    m_value = 0ull;
    return 0ull;
}

std::vector<uint8_t> BasicEncodingRules::ToBytes() const
{
    std::vector<uint8_t> l_result;

    if (m_value <= 127)
    {
        l_result.push_back(static_cast<uint8_t>(m_value));
    }
    else
    {
        size_t l_tmp = m_value;
        std::vector<uint8_t> l_length_bytes;
        while (l_tmp > 0)
        {
            l_length_bytes.insert(l_length_bytes.begin(), static_cast<uint8_t>(l_tmp & 0xFF));
            l_tmp >>= 8;
        }
        l_result.push_back(static_cast<uint8_t>(0x80 | l_length_bytes.size()));
        l_result.insert(l_result.end(), l_length_bytes.begin(), l_length_bytes.end());
    }

    return l_result;
}

