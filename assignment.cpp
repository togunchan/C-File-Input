#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class GradesDataEntry
{
public:
    std::string lastName;
    std::string firstName;
    std::string ssn;
    double test1, test2, test3, test4, final;
    std::string grade;

    GradesDataEntry(){};

    GradesDataEntry(std::string _lastName, std::string _firstName, std::string _ssn, double _test1, double _test2, double _test3, double _test4, double _final, std::string _grade) : lastName{_lastName}, firstName{_firstName}, ssn{_ssn}, test1{_test1}, test2{_test2}, test3{_test3}, test4{_test4}, final{_final}, grade{_grade} {};
};

std::vector<std::string> tokenise(std::string csvLine, char seperator)
{
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    start = csvLine.find_first_not_of(seperator, 0);
    do
    {
        end = csvLine.find_first_of(seperator, start);
        if (start == csvLine.length() || start == end)
        {
            break;
        }

        // if end>= 0 then we found the separator
        if (end >= 0)
        {
            token = csvLine.substr(start, end - start);
        }
        else
        {
            token = csvLine.substr(start, csvLine.length() - start);
        }
        tokens.push_back(token);
        start = end + 1;

    } while (end > 0);

    return tokens;
}

int main()
{
    std::fstream csvFile{"grades.csv"};
    std::string line;
    std::vector<std::string> tokens;
    std::vector<GradesDataEntry> data;
    int validLines = 0;
    if (csvFile.is_open())
    {
        std::cout << "File open " << std::endl;
        std::getline(csvFile, line);
        while (std::getline(csvFile, line))
        {
            std::cout << "Read line: " << line << std::endl;
            tokens = tokenise(line, ',');
            if (tokens.size() != 9)
            {
                std::cout << "Bad line" << std::endl;
                continue;
            }
            try
            {
                GradesDataEntry entry(tokens[0], tokens[1], tokens[2], std::stod(tokens[3]), std::stod(tokens[4]), std::stod(tokens[5]), std::stod(tokens[6]), std::stod(tokens[7]), tokens[8]);
                data.push_back(entry);
                validLines++;
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Error converting to double: " << e.what() << std::endl;
            }
        }
        for (const auto &entry : data)
        {
            std::cout << "Name: " << entry.firstName << " " << entry.lastName << ", Grade: " << entry.grade << std::endl;
        }
        std::cout << "Number of valid lines: " << validLines << std::endl;
    }

    return 0;
}
