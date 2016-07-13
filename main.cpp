#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

std::vector<std::string> read_lines(std::string filename)
{
    std::ifstream infile(filename.c_str(), std::ios::in);
    std::string line;
    std::vector<std::string> vect;
    
    while (std::getline(infile, line))
    {
        vect.push_back(line);
    }
    
    return vect;
}

std::vector<std::string> reorder_lines(std::vector<std::string>& vect)
{
    std::vector<std::string> new_vect;

    int current = 0;
    for (int ii = 0; ii < vect.size(); ii++)
    {
        if (vect[ii].substr(0, 4) == "FILE")
        {
            auto start = new_vect.begin();
            std::advance(start, current);
            auto insert_pos = std::find_if(start, new_vect.end(), [](std::string& s){return s.substr(0, 7) == "  TRACK";});
            if (insert_pos != vect.end())
            {
                new_vect.insert(insert_pos, vect[ii]);
                current = ii + 1;
            }
        }
        else
        {
            new_vect.push_back(vect[ii]);
        }
    }

    return new_vect;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: dbpa-cuesheet-formatter input.cue" << std::endl;
        return -1;
    }

    auto lines = read_lines(argv[1]);
    auto ordered_lines = reorder_lines(lines);
    
    for (auto line : ordered_lines)
    {
        std::cout << line << std::endl;
    }

    return 0;
}
