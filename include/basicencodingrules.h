#ifndef __BASICENCODINGRULES_H__
#define __BASICENCODINGRULES_H__

#include <cstddef>
#include <cstdint>
#include <vector>

class BasicEncodingRules
{
public:
    BasicEncodingRules();
    BasicEncodingRules(size_t value);
    ~BasicEncodingRules();

    void SetValue(size_t value);
    size_t GetValue() const;

    size_t GetLength() const;

    size_t FromBytes(const std::vector<uint8_t>& value);
    std::vector<uint8_t> ToBytes() const;

private:
    size_t m_value;
};

#endif // __BASICENCODINGRULES_H__

