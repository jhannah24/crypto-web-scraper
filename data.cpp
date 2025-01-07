/** data.cpp
 *  Implementation file for Data class, which parses cryptocurrency data from HTML using regex
 *  Extracts cryptocurrency data and stores them in a struct
 *  @author by Josh Hannah
 */

#include "data.h"

// Constructor initializes the Data object by parsing HTML using default regex patterns
Data::Data(const std::string &HTML) : html(HTML) {
    // Default regex patterns for names, prices, and market caps.
    const std::regex defaultNamePattern(R"(<p class="sc-65e7f566-0 iPbTJf coin-item-name">(.+?)</p>)");
    const std::regex defaultPricePattern(R"(<div class="sc-b3fc6b7-0 dzgUIj"><span>(.+?)</span>)");
    const std::regex defaultMarketCapPattern(R"(<span data-nosnippet="true" class="sc-11478e5d-1 jfwGHx">(.+?)</span>)");

    // Fill data using provided patterns
    fillData(defaultNamePattern, defaultPricePattern, defaultMarketCapPattern);

    // No valid cryptocurrency data found
    if (cryptoList.empty()) {
        throw std::runtime_error("No valid cryptocurrency data found in the provided HTML.");
    }
}

// Extracts cryptocurrency data using regex patterns
void Data::fillData(const std::regex &namePattern, const std::regex &pricePattern, const std::regex &marketCapPattern) {
    std::smatch matchesName, matchesPrice, matchesMarketCap;
    std::string::const_iterator searchStartName(html.cbegin());
    std::string::const_iterator searchStartPrice(html.cbegin());
    std::string::const_iterator searchStartMarketCap(html.cbegin());

    // Extract names
    std::vector<std::string> names;
    while (std::regex_search(searchStartName, html.cend(), matchesName, namePattern)) {
        names.push_back(matchesName[1]);
        searchStartName = matchesName.suffix().first;
    }

    // Extract prices
    std::vector<std::string> prices;
    while (std::regex_search(searchStartPrice, html.cend(), matchesPrice, pricePattern)) {
        prices.push_back(matchesPrice[1]);
        searchStartPrice = matchesPrice.suffix().first;
    }

    // Extract market caps
    std::vector<std::string> marketCaps;
    while (std::regex_search(searchStartMarketCap, html.cend(), matchesMarketCap, marketCapPattern)) {
        marketCaps.push_back(matchesMarketCap[1]);
        searchStartMarketCap = matchesMarketCap.suffix().first;
    }

    // Combine data into cryptoList
    for (size_t i = 0; i < names.size() && i < prices.size() && i < marketCaps.size(); ++i) {
        cryptoList.push_back({names[i], prices[i], marketCaps[i]});
    }
}

// Returns the list of parsed cryptocurrency data
const std::vector<CryptoData> &Data::getCryptoList() const {
    return cryptoList;
}
