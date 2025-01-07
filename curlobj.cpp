/** curlobj.cpp
 *  Implementation file for the CurlObj class, which handles HTTP requests using libcurl
 *  Fetches data from URL and provides it as string
 *  @author by Josh Hannah
 */

#include "curlobj.h"

// Constructor initializes CURL object and sets options for fetching data
CurlObj::CurlObj(const std::string &url) {
    curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Curl did not initialize.");
    }

    // Set libcurl options
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CurlObj::curlWriter);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3");

    // Perform request and check for errors
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        curl_easy_cleanup(curl); // cleanup on failure
        throw std::runtime_error("Curl request failed: " + std::string(curl_easy_strerror(res)));
    }
}

// Destructor cleans up CURL object
CurlObj::~CurlObj() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
}

// Returns fetched data as string
std::string CurlObj::getData() const {
    return curlBuffer;
}

/**
 * @brief Callback function to write data fetched by libcurl.
 * @param data Pointer to the data fetched.
 * @param size Size of a single data element.
 * @param nmemb Number of data elements.
 * @param buffer Pointer to the buffer to store the data.
 * @return The number of bytes written.
 */
size_t CurlObj::curlWriter(char *data, size_t size, size_t nmemb, std::string *buffer) {
    if (buffer) {
        buffer->append(data, size * nmemb);
        return size * nmemb;
    }
    return 0;
}
