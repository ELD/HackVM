#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

int main()
{
    boost::filesystem::path p{"."};

    for (const auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator{p},{})) {
        if (boost::filesystem::is_regular_file(entry)) {
            std::cout << entry.path() << std::endl;
        }
    }

    return 0;
}
