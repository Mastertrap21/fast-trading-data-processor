#include <windows.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <chrono>
#include "LoadTradingDataDynamicVisitor.h"
#include "LoadTradingDataStaticVisitor.h"
#include "ComputeDaySummaryDynamicVisitor.h"
#include "ComputeDaySummaryStaticVisitor.h"
#include "SaveDaySummaryDynamicVisitor.h"
#include "SaveDaySummaryStaticVisitor.h"

// Function that maps a file into memory and loads the data using a functor passed argument
template<typename Functor>
void loadMemoryMappedData(const char *filename, Functor loadData) noexcept {
    SYSTEM_INFO systemInfo = {0};
    GetSystemInfo(&systemInfo); // We need the systemInfo for the granularity
    DWORD granularity = systemInfo.dwAllocationGranularity; // the allocation granularity of the system
    unsigned long long bufferSize = granularity * sizeof(TradeTransactionInfoT); // we need the size to be a multiple of granularity for the offset to work and of our structure in order to make sure it fits in one view
    HANDLE fileHandle = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL); // open the file for reading
    if(fileHandle != INVALID_HANDLE_VALUE){ // if valid file handle
        LARGE_INTEGER fSize = {0};
        GetFileSizeEx(fileHandle, &fSize); // we need to know the file size
        auto fileSize = static_cast<unsigned long long>(fSize.QuadPart); // cast the file size to long long
        HANDLE fileMapHandle = CreateFileMappingW(fileHandle, NULL, PAGE_READONLY, 0, 0, NULL); // we need a map file handler
        if(fileMapHandle != NULL) { // the map handler is valid
            for(unsigned long long offset = 0; offset < fileSize; offset += bufferSize){ // loop the windows
                DWORD high = static_cast<DWORD>((offset >> 32) & 0xFFFFFFFF); // compute high offset using bitwise ops
                DWORD low  = static_cast<DWORD>(offset & 0xFFFFFFFF); // compute low offset using bitwise ops
                if(offset + bufferSize > fileSize){ // last window could be smaller than normal
                    bufferSize = fileSize - offset; // make the new buffer size for last window
                }
                auto bufferAddress = MapViewOfFile(fileMapHandle, FILE_MAP_READ, high, low, bufferSize); // get the address of the window mapped
                if (bufferAddress != NULL) { // if the address is valid
                    for(auto i = 0; i < bufferSize / sizeof(TradeTransactionInfoT); i++) { // loop window memory one structure at a time
                        auto tradeTransactionAddress = (const char*) bufferAddress + (i * sizeof(TradeTransactionInfoT)); // calculate the address of the pointer towards the structure
                        auto tradeTransactionInfo = *(TradeTransactionInfoT *) tradeTransactionAddress; // read the structure and dereference the pointer
                        loadData(tradeTransactionInfo); // use the functor to load the structure
                    }
                }
                UnmapViewOfFile(bufferAddress); // unmap the view of the file
            }
            CloseHandle(fileMapHandle); // close the map file handle
        }
        CloseHandle(fileHandle); // close the file handle
    }
}

// Function that reads a file using a file stream and loads the data using a functor passed argument
template<typename Functor>
int loadStreamedData(const char *filename, Functor loadData) noexcept {
    std::fstream myFile(filename, std::ios::in | std::ios::binary); // create the stream using filename, input and binary flags
    myFile.seekg(0, std::ios::end); // go to the end of the file
    long long int file_size = myFile.tellg(); // read the position aka file size
    auto noOfElements = file_size / sizeof(TradeTransactionInfoT); // compute the number of elements
    myFile.seekg(0, std::ios::beg); // go to the beginning
    for(auto i = 0; i < noOfElements; i++){ // loop the structures
        auto *tradeTransactionInfo = new TradeTransactionInfoT; // create a structure and get a pointer to it
        myFile.read((char*) tradeTransactionInfo, sizeof(TradeTransactionInfoT)); // read the structure in the newly created object
        loadData(*tradeTransactionInfo); // use the functor to load the structure
        delete tradeTransactionInfo; // delete the structure
        myFile.seekg(sizeof(TradeTransactionInfoT) * i + sizeof(TradeTransactionInfoT), std::ios::beg); // advance in the stream to the next structure
    }
}

// The function that will test the implemented use case visitor using dynamic polymorhpism
void dynamicPolymorphism() noexcept {
    auto t0 = std::chrono::high_resolution_clock::now();
    std::map<std::string, std::unique_ptr<DynamicStockT>> dynamicStocks; // keep a map of the stocks
    LoadTradingDataDynamicVisitor loadTradingDataDynamicVisitor{&dynamicStocks}; // create the visitor
    // Use the file memory mapper function to load the data and pass the dynamic polymorphism loading implementation as lambda
    loadMemoryMappedData("stocks.bin", [&loadTradingDataDynamicVisitor] (const TradeTransactionInfoT &tradeTransactionInfo){
        // create the visitable structure
        auto dynamicTradeTransactionInfo = new DynamicTradeTransactionInfoT(tradeTransactionInfo.timestamp, tradeTransactionInfo.amount, tradeTransactionInfo.price);
        strcpy(dynamicTradeTransactionInfo->stock, tradeTransactionInfo.stock); // this could maybe be in constructor as well but it is array of chars :(
        dynamicTradeTransactionInfo->accept(loadTradingDataDynamicVisitor); // make the structure accept the visitor
        delete dynamicTradeTransactionInfo; // remove the structure
    });
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Dynamic polymorphism load: " << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << "msec\n";
    ComputeDaySummaryDynamicVisitor computeDaySummaryDynamicVisitor; // create the visitor
    for(auto &stockPair : dynamicStocks){ // loop the loaded stocks
        stockPair.second.get()->accept(computeDaySummaryDynamicVisitor); // make the structure accept the visitor
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Dynamic polymorphism compute: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << "msec\n";
    SaveDaySummaryDynamicVisitor saveDaySummaryDynamicVisitor; // create the visitor
    for(auto &stockPair : dynamicStocks){ // loop the stocks
        stockPair.second.get()->accept(saveDaySummaryDynamicVisitor); // make the structure accept the visitor
    }
    auto t3 = std::chrono::high_resolution_clock::now();
    std::cout << "Dynamic polymorphism save: " << std::chrono::duration_cast<std::chrono::milliseconds>(t3-t2).count() << "msec\n";
}

// The function that will test the implemented use case visitor using static polymorhpism
void staticPolymorphism() noexcept {
    auto t0 = std::chrono::high_resolution_clock::now();
    std::map<std::string, std::unique_ptr<StockT>> staticStocks;
    LoadTradingDataStaticVisitor loadTradingDataStaticVisitor{&staticStocks};
    loadMemoryMappedData("stocks.bin", [&loadTradingDataStaticVisitor] (const TradeTransactionInfoT &tradeTransactionInfo){
        auto staticTradeTransactionInfo = new StaticTradeTransactionInfoT(tradeTransactionInfo.timestamp, tradeTransactionInfo.amount, tradeTransactionInfo.price);
        strcpy(staticTradeTransactionInfo->stock, tradeTransactionInfo.stock);
        visitor_traits<TradeTransactionInfoT>::accept(loadTradingDataStaticVisitor, *staticTradeTransactionInfo); // make the structure accept the visitor
        delete staticTradeTransactionInfo;
    });
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Static polymorphism load: " << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << "msec\n";
    ComputeDaySummaryStaticVisitor computeDaySummaryStaticVisitor; // create the visitor
    for(auto &stockPair : staticStocks){ // loop the stocks
        auto stock = stockPair.second.get(); // get a pointer to the stock
        visitor_traits<StockT>::accept(computeDaySummaryStaticVisitor, *stock); // make the structure accept the visitor
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Static polymorphism compute: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << "msec\n";
    SaveDaySummaryStaticVisitor saveDaySummaryStaticVisitor; // create the visitor
    for(auto &stockPair : staticStocks){ // loop the stocks
        auto stock = stockPair.second.get();
        visitor_traits<StockT>::accept(saveDaySummaryStaticVisitor, *stock); // make the structure accept the visitor
    }
    auto t3 = std::chrono::high_resolution_clock::now();
    std::cout << "Static polymorphism save: " << std::chrono::duration_cast<std::chrono::milliseconds>(t3-t2).count() << "msec\n";
}

int main() noexcept {
    staticPolymorphism(); // test static polymorphism
    dynamicPolymorphism(); // test dynamic polymorphism
    return 0;
}