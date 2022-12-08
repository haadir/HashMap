#ifndef BOGGLE_H
#define BOGGLE_H
std::vector<std::vector<char> > genBoard(unsigned int n, int seed);
void printBoard(const std::vector<std::vector<char> >& board);
std::pair<std::set<std::string>, std::set<std::string> > parseDict(std::string fname);
std::set<std::string> boggle(const std::set<std::string>& dict, const std::set<std::string>& prefix, const std::vector<std::vector<char> >& board);
bool boggleHelper(const std::set<std::string>& dict, const std::set<std::string>& prefix, const std::vector<std::vector<char> >& board, std::string word, std::set<std::string>& result, unsigned int r, unsigned int c, int dr, int dc);
#endif