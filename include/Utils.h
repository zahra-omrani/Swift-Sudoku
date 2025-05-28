#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

std::vector<std::string> loadBoards(const std::string& filename, int count);
void runWarmup(const std::vector<std::string>& boards, int threadCount);
double measureParallel(const std::vector<std::string>& boards, int threadCount);

#endif // UTILS_H
