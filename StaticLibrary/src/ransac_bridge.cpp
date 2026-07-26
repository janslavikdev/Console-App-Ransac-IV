#include "ransac_bridge.h"
#include "TableBuilder.h"
#include "Table.h"
#include "RANSACFitStrategy.h"

#include <string>

// Local aliases using global namespace qualifiers so we don't expose
// dependent names in the header consumed by cxxbridge.
using Table = ::ConsoleAppRansacIINamespace::Core::Table;
using TableFacade = ::ConsoleAppRansacIINamespace::IO::TableFacade;
using ITableBuilder = ::ConsoleAppRansacIINamespace::IO::ITableBuilder;
using CsvTableBuilder = ::ConsoleAppRansacIINamespace::IO::CsvTableBuilder;
using Column = ::ConsoleAppRansacIINamespace::Core::Column;
using LinearModel = ::ConsoleAppRansacIINamespace::Core::LinearModel;
using RANSACFitStrategy = ::ConsoleAppRansacIINamespace::Fitting::RANSACFitStrategy;

std::unique_ptr<AppState> create_app_state()
{
    return std::make_unique<AppState>();
}

std::unique_ptr<RansacFitResultDTO> initialize_from_csv(AppState& state, const std::string& path)
{
    std::cout << "Building Table from the File" << std::endl;
    constexpr std::size_t HEADER_LINES_COUNT {1};
	std::unique_ptr<ITableBuilder> tableBuilder = std::make_unique<CsvTableBuilder>(path, HEADER_LINES_COUNT);
	constexpr char tableName[] = "Test Table";
    state.tableFacade = std::make_shared<TableFacade>(tableName, tableBuilder);

    Column abcissa = state.tableFacade->getColumn(0);
	Column ordinate = state.tableFacade->getColumn(1);
	std::vector<double> abcissaValues = abcissa.getAllRows();
    
    // RANSAC Fit
	cout << "Performing RANSAC Fit" << endl;
	RANSACFitStrategy ransacFitStrategy;
    state.model = ransacFitStrategy.fitLinearModel(abcissa, ordinate);

    // Create result and turn it back
    auto ransacResult = std::make_unique<RansacFitResultDTO>(
        state.tableFacade, std::move(state.model));
    
    return std::move(ransacResult);
}

// double run_ransac(Table& table, double treshold)
// {
//     return 0.0;
// } 