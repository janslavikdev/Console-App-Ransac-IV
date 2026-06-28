#pragma once
#include <memory>
#include <string>
#include "../../../StaticLibrary/include/Table.h"
#include "../../../StaticLibrary/include/RANSACFitResult.h"

using RansacFitResultDTO = ::ConsoleAppRansacIINamespace::RustInterface::RansacFitResultDTO;

std::unique_ptr<RansacFitResultDTO> initialize_from_csv(const std::string& path);

//double run_ransac(Table& table, double treshold); 