#include "basetest.h"

#include <basicencodingrules.h>

#include <sstream>

TEST_F(TestBasicEncodingRules, SetTest) {
    const std::vector<size_t> l_expected_values = { 98, 144, 23298, 0 };

    BasicEncodingRules l_ber;

    EXPECT_EQ(0u, l_ber.GetValue()) << "Valeur par defaut";

    for (auto &iter : l_expected_values)
    {
        std::stringstream l_ss;
        l_ss << "Valeur modifiee a " << iter;

        l_ber.SetValue(iter);

        EXPECT_EQ(iter, l_ber.GetValue()) << l_ss.str();
    }
}

TEST_F(TestBasicEncodingRules, ToTest) {
    const std::map< size_t, std::vector< uint8_t > > l_expected_values = {
        { 0, { 0b00000000 } },
        { 98, { 0b01100010 } },
        { 144, { 0b10000001, 0b10010000 } },
        { 23298, { 0b10000010, 0b01011011, 0b00000010 } } };

    for (auto &iter : l_expected_values)
    {
        BasicEncodingRules l_ber;
        l_ber.SetValue(iter.first);

        std::vector< uint8_t > l_result = l_ber.ToBytes();
        EXPECT_EQ(l_result.size(), iter.second.size()) << "Taille differente";

        auto e = iter.second.begin();
        auto r = l_result.begin();
        for (; e != iter.second.end() && r != l_result.end(); ++e, ++r  )
        {
            EXPECT_EQ(*e, *r) << "Contenu different";
        }
    }
}

TEST_F(TestBasicEncodingRules, FromTest) {
    const std::map< size_t, std::vector< uint8_t > > l_expected_values = {
        { 0, { 0b00000000 } },
        { 98, { 0b01100010 } },
        { 144, { 0b10000001, 0b10010000 } },
        { 23298, { 0b10000010, 0b01011011, 0b00000010 } } };

    for (auto &iter : l_expected_values)
    {
        BasicEncodingRules l_ber;
        l_ber.FromBytes(iter.second);

        EXPECT_EQ(iter.first, l_ber.GetValue()) << "Contenu different";
    }
}

