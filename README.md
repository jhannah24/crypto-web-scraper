# Crypto Web Scraper

This crypto web scraper is a Qt-based desktop application that displays real-time cryptocurrency data, including names, prices, and market capitalizations, with a responsive and user-friendly interface. The project employs multithreading, periodic data fetching, and regex-based HTML parsing to provide accurate and up-to-date information.

## Features

- **Real-time Updates:** Fetches cryptocurrency data continously from [CoinMarketCap](https://coinmarketcap.com/).
- **Dynamic UI:** Displays top 10 cryptocurrencies with progress bars for market capitalization comparisons.
- **Error Handling:** Handles network and parsing errors gracefully with user notifications.
- **Multithreading:** Background data fetching ensures a smooth and responsive UI.

## Technologies Used

- **C++**: Core programming language.
- **Qt Framework**: For building the graphical user interface and managing threads.
- **libcurl**: For HTTP requests to fetch cryptocurrency data.
- **Regex**: To parse cryptocurrency names, prices, and market capitalizations from HTML.

## Installation and Setup

1. **Clone the repository:**
   ```bash
   git clone https://github.com/jhannah24/crypto-web-scraper.git
    ```
2. **Install Libcurl if using a Linux distribution (curl is pre-installed with mac OS and Windows):**
   ```bash
   sudo apt install libcurl4-openssl-dev
   ```
3. **Install Qt for your specific platform from the official Qt documentation:**
   [How to Install Qt](https://doc.qt.io/qt-6/get-and-install-qt.html)
   
5. **Build**: This project is built using Qt 6.8.1. Make sure you have this version or a compatible one installed.
