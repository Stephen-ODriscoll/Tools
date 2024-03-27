#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>

#define SEPARATOR " | "

#define HEADER_CHAR '-'
#define HEADER_SEP "-+-"

#define DEC_TITLE "Decimal    "
#define HEX_TITLE "Hexadecimal"
#define OCT_TITLE "Octal      "
#define BIN_TITLE "Binary     "

#define DEC_COLUMN "Decimal"
#define HEX_COLUMN "Hexadecimal"
#define OCT_COLUMN "Octal"
#define IND_COLUMN "Index"
#define BIN_COLUMN "Bit"

enum class ListBits : unsigned char
{
    None = 0,
    Enabled,
    All
};

template<typename T>
T max(T left, T right)
{
    return (left < right) ? right : left;
}

std::string toOct(unsigned long long number)
{
    std::stringstream ss{};
    ss << std::oct << number;
    return "0" + ss.str();
}

std::string toDec(unsigned long long number)
{
    std::stringstream ss{};
    ss << number;
    return ss.str();
}

std::string toHex(unsigned long long number)
{
    std::stringstream ss{};
    ss << std::hex << number;
    return "0x" + ss.str();
}

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2)
        {
            throw std::exception("Not enough arguments");
        }
        
        unsigned long long number{};
        ListBits listBits{ ListBits::All };
        for (int i{ 1 }; i < argc; ++i)
        {
            if (!stricmp(argv[i], "-la") || !stricmp(argv[i], "--list-all"))
            {
                listBits = ListBits::All;
            }
            else if (!stricmp(argv[i], "-le") || !stricmp(argv[i], "--list-enabled"))
            {
                listBits = ListBits::Enabled;
            }
            else if (!stricmp(argv[i], "-ln") || !stricmp(argv[i], "--list-none"))
            {
                listBits = ListBits::None;
            }
            else if (!stricmp(argv[i], "-d") || !stricmp(argv[i], "--dec"))
            {
                if (++i < argc)
                {
                    number = std::stoull(argv[i]);
                }
            }
            else if (!stricmp(argv[i], "-h") || !stricmp(argv[i], "--hex"))
            {
                if (++i < argc)
                {
                    number = std::stoull(argv[i], nullptr, 16);
                }
            }
            else if (!stricmp(argv[i], "-o") || !stricmp(argv[i], "--oct"))
            {
                if (++i < argc)
                {
                    number = std::stoull(argv[i], nullptr, 8);
                }
            }
            else if (!stricmp(argv[i], "-b") || !stricmp(argv[i], "--bin"))
            {
                if (++i < argc)
                {
                    number = std::stoull(argv[i], nullptr, 2);
                }
            }
            else if (!strnicmp(argv[i], "0x", 2))
            {
                number = std::stoull(argv[i], nullptr, 16);
            }
            else if (!strnicmp(argv[i], "0", 1))
            {
                number = std::stoull(argv[i], nullptr, 8);
            }
            else
            {
                number = std::stoull(argv[i]);
            }
        }

        if (number == 0)
        {
            throw std::exception("No argument found for number or 0 was given");
        }

        std::string binString{};
        const auto octString{ toOct(number) };
        const auto decString{ toDec(number) };
        const auto hexString{ toHex(number) };

        const auto indSize{ strlen(IND_COLUMN) };
        const auto binSize{ strlen(BIN_COLUMN) };
        const auto octSize{ max(strlen(OCT_COLUMN), octString.size()) };
        const auto decSize{ max(strlen(DEC_COLUMN), decString.size()) };
        const auto hexSize{ max(strlen(HEX_COLUMN), hexString.size()) };

        std::vector<std::string> rows{};
        for (
            unsigned long long bit{ 1 }, index{};
            bit != 0 && bit <= number;
            bit <<= 1, ++index)
        {
            const auto hasBit{ !!(number & bit) };

            binString.insert(binString.begin(), (hasBit ? '1' : '0'));

            if (listBits == ListBits::All || (listBits == ListBits::Enabled && hasBit))
            {
                std::stringstream ss{};
                ss
                    << std::left << std::setw(indSize) << index << SEPARATOR
                    << std::left << std::setw(binSize) << hasBit << SEPARATOR
                    << std::left << std::setw(octSize) << toOct(bit) << SEPARATOR
                    << std::left << std::setw(decSize) << toDec(bit) << SEPARATOR
                    << std::left << std::setw(hexSize) << toHex(bit);

                rows.push_back(ss.str());
            }
        }

        if (binString.empty())
        {
            binString = "0";
        }

        // Actual numbers
        std::cout
            << BIN_TITLE " = " << binString << "\n"
            << OCT_TITLE " = " << octString << "\n"
            << DEC_TITLE " = " << decString << "\n"
            << HEX_TITLE " = " << hexString << std::endl;

        if (!rows.empty())
        {
            // Header column labels
            std::cout
                << "\n"
                << std::left << std::setw(indSize) << IND_COLUMN << SEPARATOR
                << std::left << std::setw(binSize) << BIN_COLUMN << SEPARATOR
                << std::left << std::setw(octSize) << OCT_COLUMN << SEPARATOR
                << std::left << std::setw(decSize) << DEC_COLUMN << SEPARATOR
                << std::left << std::setw(hexSize) << HEX_COLUMN << std::endl;

            // Underline for the header
            std::cout
                << std::left << std::setw(indSize) << std::setfill(HEADER_CHAR) << "" << HEADER_SEP
                << std::left << std::setw(binSize) << std::setfill(HEADER_CHAR) << "" << HEADER_SEP
                << std::left << std::setw(octSize) << std::setfill(HEADER_CHAR) << "" << HEADER_SEP
                << std::left << std::setw(decSize) << std::setfill(HEADER_CHAR) << "" << HEADER_SEP
                << std::left << std::setw(hexSize) << std::setfill(HEADER_CHAR) << "" << std::endl;

            // Rows, each row represents information about a bit
            for (auto it{ rows.rbegin() }; it < rows.rend(); ++it)
            {
                std::cout << *it << std::endl;
            }
        }
    }
    catch (const std::exception& ex)
    {
        std::cout
            << ex.what() << "\n"
            << "\n"
            << "Usage: BitChecker.exe [bit list] [format] <unsigned number>\n"
            << "\n"
            << "    bit list\n"
            << "        -la / --list-all (default)\n"
            << "        -le / --list-enabled\n"
            << "        -ln / --list-none\n"
            << "\n"
            << "    format\n"
            << "        -d / --dec (default)\n"
            << "        -h / --hex / 0x...\n"
            << "        -o / --oct / 0...\n"
            << "        -b / --bin" << std::endl;
        return -1;
    }

    return 0;
}
