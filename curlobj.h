/** curlobj.h
 *  Header file for the CurlObj class, which provides functionality to fetch HTML content using libcurl
 *  @author Josh Hannah
 */

#ifndef CURLOBJ_H
#define CURLOBJ_H

#include <stdexcept>
#include <curl/curl.h>

// Utility class to fetch HTML content using libcurl
class CurlObj {
public:
    explicit CurlObj(const std::string &url);   // Constructor taking URL to fetch
    ~CurlObj();                                 // Destructor to clean up resources

    // Returns fetched HTML content
    std::string getData() const;

private:
    CURL *curl;             // Pointer to curl objecct
    std::string curlBuffer; // Buffer to store fetched HTML

    /**
     * @brief Static callback function to write data fetched by libcurl
     * @param data Pointer to the data fetched
     * @param size Size of a single data element
     * @param nmemb Number of data elements
     * @param buffer Pointer to the buffer to store the data
     * @return The number of bytes written
     */
    static size_t curlWriter(char *data, size_t size, size_t nmemb, std::string *buffer);
};

#endif // CURLOBJ_H
