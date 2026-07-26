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

std::unique_ptr<RansacFitResultDTO> initialize_from_csv(const std::string& path)
{
    //auto builder = std::make_unique<ConsoleAppRansacIINamespace::IO::CsvTableBuilder>(path, 1);
    //builder->buildTable();
    //Table tableFromCsv { builder->getTable() };
    // constexpr char tableName[] = "Initial result";
    // TableFacade facade(tableName, builder.get());


    std::cout << "Building Table from the File" << std::endl;
    constexpr std::size_t HEADER_LINES_COUNT {1};
	std::unique_ptr<ITableBuilder> tableBuilder = std::make_unique<CsvTableBuilder>(path, HEADER_LINES_COUNT);
	constexpr char tableName[] = "Test Table";
	TableFacade tableFacade{ tableName, tableBuilder };

    Column abcissa = tableFacade.getColumn(0);
	Column ordinate = tableFacade.getColumn(1);
	std::vector<double> abcissaValues = abcissa.getAllRows();
    
    // RANSAC Fit
	cout << "Performing RANSAC Fit" << endl;
	RANSACFitStrategy ransacFitStrategy;
	LinearModel ransacLinearFit;
	ransacLinearFit = ransacFitStrategy.fitLinearModel(abcissa, ordinate);

    // Create result and turn it back
    auto ransacResult = std::make_unique<RansacFitResultDTO>(std::move(tableFacade), std::move(ransacLinearFit));
    
    return std::move(ransacResult);
}

// double run_ransac(Table& table, double treshold)
// {
//     return 0.0;
// } 