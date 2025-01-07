/** data.h
 * Header file for the Data class, which processes and extracts cryptocurrency information from HTML content
 * @author Josh Hannah
 */

#ifndef DATA_H
#define DATA_H

#include <regex>

// Struct to hold cryptocurrency data
struct CryptoData {
    std::string name;      // Name of the cryptocurrency
    std::string price;     // Current price of the cryptocurrency
    std::string marketCap; // Market capitalization of the cryptocurrency
};

// Class to process and store cryptocurrency data from HTML
class Data {
public:
    // Constructor taking HTML content to process
    explicit Data(const std::string &HTML);

    // Returns the parsed cryptocurrency data list
    const std::vector<CryptoData> &getCryptoList() const;

private:
    std::string html;                   // The raw HTML content
    std::vector<CryptoData> cryptoList; // Extracted cryptocurrency data

    // Extracts cryptocurrency data from HTML using regex patterns
    void fillData(const std::regex &namePattern, const std::regex &pricePattern, const std::regex &marketCapPattern);
};

#endif // DATA_H
