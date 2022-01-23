#pragma once
#include <vector>
#include <string>
#include <cassert>


/// \brief return true if ip1 less than ip2
auto compareByValueBytes = [](const std::vector<std::string> &ip1, const std::vector<std::string> &ip2){
     assert(ip1.size()==4);
     assert(ip2.size()==4);
     for (int i = 0; i < 4; ++i)
                      {
                          int a = atoi(ip1[i].data());
                          int b = atoi(ip2[i].data());

                          if (a != b)
                          {
                              return a < b;
                          }
                      }
                      return false;
};



std::vector<std::string> filter(const std::vector<std::vector<std::string>> &ip_pool, std::vector<std::string> bytes_seq)
{
    assert(bytes_seq.size() <= 4);
    std::vector<std::string> res;

    auto compare = [&bytes_seq](auto &ip)
    {
        assert(ip.size() <= 4);
        int j = 0;
        for (const auto &i : bytes_seq)
        {
            if (i != ip[j++])
            {
                return false;
            }
        }
        return true;
    };
    for (const auto &ip : ip_pool)
    {
        if (compare(ip))
        {
            res.emplace_back(ip[0] + "." + ip[1] + "." + ip[2] + "." + ip[3]);
        }
    }
    return res;
}

std::vector<std::string> filter(const std::vector<std::vector<std::string>> &ip_pool, uint8_t byteAny)
{
    std::vector<std::string> res;
    auto anyByte = std::to_string(byteAny);
    for (const auto &ip : ip_pool)
    {
        assert(ip.size() <= 4);
        if (ip[0] == anyByte || ip[1] == anyByte || ip[2] == anyByte || ip[3] == anyByte)
        {
            res.emplace_back(ip[0] + "." + ip[1] + "." + ip[2] + "." + ip[3]);
        }
    }
    return res;
}

