#pragma once
#include "observation.hpp"
#include <vector>
#include <string>

std::vector<Observation> ObsFromCSV(const std::string& filename);
