#pragma once
#include <memory>
#include <string>
#include "../../../StaticLibrary/include/Table.h"
#include "../../../StaticLibrary/include/RANSACFitResult.h"

using RansacFitResultDTO = ::ConsoleAppRansacIINamespace::RustInterface::RansacFitResultDTO;

struct AppState {
    std::shared_ptr<ConsoleAppRansacIINamespace::IO::TableFacade> tableFacade;
    ConsoleAppRansacIINamespace::Core::LinearModel model;
};

std::unique_ptr<AppState> create_app_state();
std::unique_ptr<RansacFitResultDTO> initialize_from_csv(AppState& state, const std::string& path);

//double run_ransac(Table& table, double treshold); 