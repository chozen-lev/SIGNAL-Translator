#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include "token.h"
#include "lexicalanalyzer.h"

void initializeTables(std::map<std::string,int> &keyword, std::map<std::string,int>, std::map<std::string,int>)
{
    keyword.clear();
    keyword["PROGRAM"] = 301;
    keyword["PROCEDURE"] = 302;
    keyword["BEGIN"] = 303;
    keyword["END"] = 304;
    keyword["LABEL"] = 305;
}

int main(int argc, char* argv[])
{
    std::string path_source;

    if (argc >= 2) {
        path_source = *(argv + 1);
    }

    path_source = "test2";

    while (path_source.empty())
    {
        std::cout << "Source filename [.sig]: ";
        std::getline(std::cin, path_source);

        if (path_source.empty()) {
            std::cout << "Line invalid, start again" << std::endl << std::endl;
        }
    }

    if (path_source.rfind(".sig") == std::string::npos) {
        path_source += ".sig";
    }

    std::ifstream FileSource(path_source);
    if (!FileSource.is_open()) {
        std::cout << "Unable to open input file: " + path_source << std::endl;
        return 0;
    }

    std::map<std::string,int> keywordsTable;
    std::map<std::string,int> identifiersTable;
    std::map<std::string,int> constantsTable;
    initializeTables(keywordsTable, identifiersTable, constantsTable);

    LexicalAnalyzer LexAnalyzer(&keywordsTable, &identifiersTable, &constantsTable);
    std::vector<Token*> lexOutput = LexAnalyzer.analyze(FileSource);
    FileSource.close();

    for (unsigned i = 0; i < lexOutput.size(); ++i) {
        std::cout << lexOutput[i]->y() << "\t" << lexOutput[i]->x() << "\t" << lexOutput[i]->type() << "\t" << lexOutput[i]->name() << std::endl;
    }

    std::cout << std::endl;

    return 0;
}