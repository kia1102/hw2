#include "gtest/gtest.h"
#include "../ip_filter_detail.h"
#include <algorithm>

TEST(IPcompare, byValueBytes)
{
    std::vector<std::string> ip;

    ASSERT_TRUE(compareByValueBytes({"10", "10", "10", "2"}, {"10", "10", "10", "1"}));
    ASSERT_TRUE(compareByValueBytes({"10", "10", "10", "2"}, {"10", "10", "1", "2"}));
    ASSERT_TRUE(compareByValueBytes({"10", "10", "10", "2"}, {"10", "1", "11", "2"}));
    ASSERT_TRUE(compareByValueBytes({"10", "10", "10", "2"}, {"1", "21", "11", "2"}));
    ASSERT_TRUE(compareByValueBytes({"10", "10", "10", "2"}, {"2", "15", "11", "20"}));

    ASSERT_FALSE(compareByValueBytes({"1", "10", "10", "2"}, {"2", "15", "11", "20"}));

    ASSERT_DEATH(compareByValueBytes({"10", "10"}, {"1", "1"}), "");
}

TEST(filter, serialFilter)
{
    std::vector<std::vector<std::string>> ip_pool{{"1", "1", "3", "3"},
                                                  {"1", "1", "3", "4"},
                                                  {"12", "2", "3", "5"},
                                                  {"12", "2", "4", "4"},
                                                  {"13", "2", "4", "5"},
                                                  {"13", "2", "5", "3"},
                                                  {"14", "2", "6", "3"},
                                                  {"14", "2", "7", "3"},
                                                  {"15", "2", "8", "3"}};

    {
        auto res = filter(ip_pool, {"1"});
        EXPECT_TRUE(res.size() == 2);
        EXPECT_TRUE(std::find(res.begin(), res.end(), "1.1.3.3") != res.end());
        EXPECT_TRUE(std::find(res.begin(), res.end(), "1.1.3.4") != res.end());
    }

    {
        auto res = filter(ip_pool, {"12", "2"});
        EXPECT_TRUE(res.size() == 2);
        EXPECT_TRUE(std::find(res.begin(), res.end(), "12.2.3.5") != res.end());
        EXPECT_TRUE(std::find(res.begin(), res.end(), "12.2.4.4") != res.end());
    }

    {
        auto res = filter(ip_pool, {"122", "2"});
        EXPECT_TRUE(res.size() == 0);
       
    }

     {
        auto res = filter(ip_pool, {"15", "2","8"});
        EXPECT_TRUE(res.size() == 1);   
    }

}

TEST(filter, anyFilter)
{
    std::vector<std::vector<std::string>> ip_pool{{"1", "1", "3", "3"},
                                                  {"1", "1", "3", "4"},
                                                  {"12", "2", "3", "5"},
                                                  {"12", "2", "4", "4"},
                                                  {"13", "2", "4", "5"},
                                                  {"13", "2", "5", "3"},
                                                  {"14", "2", "6", "3"},
                                                  {"14", "2", "7", "3"},
                                                  {"15", "2", "8", "3"}};

    {
        auto res = filter(ip_pool, 1);
        EXPECT_TRUE(res.size() == 2);
        EXPECT_TRUE(std::find(res.begin(), res.end(), "1.1.3.3") != res.end());
        EXPECT_TRUE(std::find(res.begin(), res.end(), "1.1.3.4") != res.end());
    }

    {
        auto res = filter(ip_pool, 12);
        EXPECT_TRUE(res.size() == 2);
        EXPECT_TRUE(std::find(res.begin(), res.end(), "12.2.3.5") != res.end());
        EXPECT_TRUE(std::find(res.begin(), res.end(), "12.2.4.4") != res.end());
    }

    {
        auto res = filter(ip_pool, 122);
        EXPECT_TRUE(res.size() == 0);
       
    }

     {
        auto res = filter(ip_pool, 2);
        EXPECT_TRUE(res.size() == 7);   
    }

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}