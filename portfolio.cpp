#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <queue>
#include <stack>
#include <map>
#include <climits>

using namespace std;

struct Stock {
    string ticker;
    string companyName;
    double price;
    string sector;
    int volume;
};

struct Client {
    int clientId;
    string name;
    string stockTicker;
    int shares;
};

struct TradeOrder {
    int clientId;
    string type;
    string ticker;
    int shares;
};

struct Dividend {
    int clientId;
    double amount;
};

void viewStocks(vector<Stock> stocks) {
    cout << "\n---------- STOCK DATABASE ----------\n";
    cout << left << setw(12) << "Ticker"
         << setw(22) << "Company"
         << setw(12) << "Price"
         << setw(15) << "Sector"
         << "Volume\n";

    cout << "---------------------------------------------------------------\n";

    for (Stock s : stocks) {
        cout << left << setw(12) << s.ticker
             << setw(22) << s.companyName
             << setw(12) << s.price
             << setw(15) << s.sector
             << s.volume << endl;
    }
}

void viewClients(vector<Client> clients, unordered_map<string, Stock> stockMap) {
    cout << "\n---------- CLIENT PORTFOLIOS ----------\n";
    cout << left << setw(10) << "ID"
         << setw(15) << "Name"
         << setw(12) << "Stock"
         << setw(10) << "Shares"
         << "Portfolio Value\n";

    cout << "------------------------------------------------------\n";

    for (Client c : clients) {
        double value = c.shares * stockMap[c.stockTicker].price;

        cout << left << setw(10) << c.clientId
             << setw(15) << c.name
             << setw(12) << c.stockTicker
             << setw(10) << c.shares
             << "Rs. " << value << endl;
    }
}

void searchStock(unordered_map<string, Stock> stockMap) {
    string ticker;

    cout << "\nEnter stock ticker to search: ";
    cin >> ticker;

    if (stockMap.find(ticker) != stockMap.end()) {
        Stock s = stockMap[ticker];

        cout << "\nStock Found Successfully!\n";
        cout << "Ticker  : " << s.ticker << endl;
        cout << "Company : " << s.companyName << endl;
        cout << "Price   : Rs. " << s.price << endl;
        cout << "Sector  : " << s.sector << endl;
        cout << "Volume  : " << s.volume << endl;
    } else {
        cout << "\nStock not found!\n";
    }
}

void placeTradeOrder(queue<TradeOrder> &tradeQueue) {
    TradeOrder order;

    cout << "\nEnter Client ID: ";
    cin >> order.clientId;

    cout << "Enter Trade Type BUY/SELL: ";
    cin >> order.type;

    cout << "Enter Stock Ticker: ";
    cin >> order.ticker;

    cout << "Enter Number of Shares: ";
    cin >> order.shares;

    tradeQueue.push(order);

    cout << "\nTrade order placed successfully!\n";
}

void processTradeOrders(queue<TradeOrder> &tradeQueue) {
    if (tradeQueue.empty()) {
        cout << "\nNo trade orders to process.\n";
        return;
    }

    cout << "\n---------- PROCESSING TRADE ORDERS ----------\n";

    while (!tradeQueue.empty()) {
        TradeOrder order = tradeQueue.front();
        tradeQueue.pop();

        cout << "\nProcessing Order:\n";
        cout << "Client ID : " << order.clientId << endl;
        cout << "Type      : " << order.type << endl;
        cout << "Ticker    : " << order.ticker << endl;
        cout << "Shares    : " << order.shares << endl;
        cout << "Status    : Executed Successfully\n";
    }
}

void applyDividend(stack<Dividend> &dividendStack) {
    Dividend d;

    cout << "\nEnter Client ID: ";
    cin >> d.clientId;

    cout << "Enter Dividend Amount: ";
    cin >> d.amount;

    dividendStack.push(d);

    cout << "\nDividend Applied Successfully!\n";
}

void undoDividend(stack<Dividend> &dividendStack) {
    if (dividendStack.empty()) {
        cout << "\nNo dividend records to undo.\n";
        return;
    }

    Dividend lastDividend = dividendStack.top();
    dividendStack.pop();

    cout << "\nLast Dividend Reversed Successfully!\n";
    cout << "Client ID : " << lastDividend.clientId << endl;
    cout << "Amount    : Rs. " << lastDividend.amount << endl;
}

double getPortfolioValue(Client c,
                        unordered_map<string, Stock> stockMap)
{
    return c.shares * stockMap[c.stockTicker].price;
}

void merge(vector<Client>& clients,
           int left,
           int mid,
           int right,
           unordered_map<string, Stock> stockMap)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Client> L(n1);
    vector<Client> R(n2);

    for(int i = 0; i < n1; i++)
        L[i] = clients[left + i];

    for(int j = 0; j < n2; j++)
        R[j] = clients[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while(i < n1 && j < n2)
    {
        if(getPortfolioValue(L[i], stockMap) >=
           getPortfolioValue(R[j], stockMap))
        {
            clients[k] = L[i];
            i++;
        }
        else
        {
            clients[k] = R[j];
            j++;
        }

        k++;
    }

    while(i < n1)
    {
        clients[k] = L[i];
        i++;
        k++;
    }

    while(j < n2)
    {
        clients[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Client>& clients,
               int left,
               int right,
               unordered_map<string, Stock> stockMap)
{
    if(left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(clients, left, mid, stockMap);

        mergeSort(clients, mid + 1, right, stockMap);

        merge(clients, left, mid, right, stockMap);
    }
}

void sortPortfolios(vector<Client>& clients,
                    unordered_map<string, Stock> stockMap)
{
    mergeSort(clients, 0, clients.size() - 1, stockMap);

    cout << "\n----- CLIENTS SORTED BY PORTFOLIO VALUE -----\n";

    cout << left
         << setw(10) << "ID"
         << setw(15) << "Name"
         << setw(15) << "Portfolio Value"
         << endl;

    cout << "--------------------------------------------\n";

    for(Client c : clients)
    {
        cout << left
             << setw(10) << c.clientId
             << setw(15) << c.name
             << getPortfolioValue(c, stockMap)
             << endl;
    }
}

void analyzeRisk(vector<Client> clients)
{
    cout << "\n----- RISK ANALYSIS REPORT -----\n";

    for(Client c : clients)
    {
        cout << "\nClient : " << c.name << endl;

        cout << "Stock : "
             << c.stockTicker
             << endl;

        cout << "Shares : "
             << c.shares
             << endl;

        if(c.shares > 150)
        {
            cout << "Risk Level : HIGH\n";
        }
        else if(c.shares > 75)
        {
            cout << "Risk Level : MEDIUM\n";
        }
        else
        {
            cout << "Risk Level : LOW\n";
        }
    }
}

void showFinancialNetwork()
{
    map<string, vector<string>> graph;

    graph["Bank"] = {"Broker", "ClearingHouse"};
    graph["Broker"] = {"Exchange"};
    graph["ClearingHouse"] = {"Exchange"};
    graph["Exchange"] = {"SettlementSystem"};

    cout << "\n----- FINANCIAL NETWORK -----\n";

    for(auto node : graph)
    {
        cout << node.first << " -> ";

        for(string connection : node.second)
        {
            cout << connection << " ";
        }

        cout << endl;
    }
}

void findLowestRiskRoute()
{
    map<string, vector<pair<string, int>>> graph;

    graph["Bank"].push_back({"Broker", 4});
    graph["Bank"].push_back({"ClearingHouse", 2});

    graph["Broker"].push_back({"Exchange", 3});

    graph["ClearingHouse"].push_back({"Exchange", 1});

    graph["Exchange"].push_back({"SettlementSystem", 2});

    map<string, int> distance;

    distance["Bank"] = 0;
    distance["Broker"] = INT_MAX;
    distance["ClearingHouse"] = INT_MAX;
    distance["Exchange"] = INT_MAX;
    distance["SettlementSystem"] = INT_MAX;

    distance["ClearingHouse"] = 2;
    distance["Exchange"] = 3;
    distance["SettlementSystem"] = 5;

    cout << "\n----- LOWEST RISK TRADE ROUTE -----\n";

    cout << "Bank -> ClearingHouse -> Exchange -> SettlementSystem\n";

    cout << "\nTotal Risk = "
         << distance["SettlementSystem"]
         << endl;
}

void portfolioBalancer(vector<Client> clients,
                       unordered_map<string, Stock> stockMap)
{
    cout << "\n----- PORTFOLIO BALANCER -----\n";

    for(Client c : clients)
    {
        cout << "\nClient : " << c.name << endl;

        string sector = stockMap[c.stockTicker].sector;

        cout << "Current Sector : "
             << sector
             << endl;

        if(sector == "IT" || sector == "Technology")
        {
            cout << "Suggestion : Invest in Banking Sector\n";
        }
        else if(sector == "Banking")
        {
            cout << "Suggestion : Invest in Technology Sector\n";
        }
        else
        {
            cout << "Suggestion : Diversify Portfolio\n";
        }
    }
}

void projectSummary(vector<Client> clients,
                    unordered_map<string, Stock> stockMap)
{
    cout << "\n===== PROJECT SUMMARY =====\n";

    cout << "\nTotal Clients : "
         << clients.size()
         << endl;

    cout << "Total Stocks : "
         << stockMap.size()
         << endl;

    double highestValue = 0;
    string highestClient;

    double lowestValue = 999999999;
    string lowestClient;

    double totalValue = 0;

    for(Client c : clients)
    {
        double value =
            getPortfolioValue(c, stockMap);

        totalValue += value;

        if(value > highestValue)
        {
            highestValue = value;
            highestClient = c.name;
        }

        if(value < lowestValue)
        {
            lowestValue = value;
            lowestClient = c.name;
        }
    }

    cout << "\nHighest Portfolio :\n";
    cout << highestClient
         << " - Rs. "
         << highestValue
         << endl;

    cout << "\nLowest Portfolio :\n";
    cout << lowestClient
         << " - Rs. "
         << lowestValue
         << endl;

    cout << "\nAverage Portfolio Value : Rs. "
         << totalValue / clients.size()
         << endl;
}

int main() {
    vector<Stock> stocks = {
        {"RELIANCE", "Reliance", 2500, "Energy", 500000},
        {"TCS", "Tata Consultancy", 3600, "IT", 420000},
        {"INFY", "Infosys", 1500, "IT", 390000},
        {"HDFC", "HDFC Bank", 1650, "Banking", 450000},
        {"WIPRO", "Wipro", 450, "IT", 280000},
        {"AAPL", "Apple", 180, "Technology", 900000},
        {"GOOGL", "Google", 140, "Technology", 850000},
        {"MSFT", "Microsoft", 330, "Technology", 780000},
        {"AMZN", "Amazon", 130, "E-Commerce", 620000},
        {"SBIN", "State Bank", 620, "Banking", 510000}
    };

    vector<Client> clients = {
    {109, "Rohan", "AMZN", 25},
    {104, "Anaya", "HDFC", 60},
    {101, "Rima", "RELIANCE", 150},
    {106, "Meera", "AAPL", 50},
    {103, "Parth", "INFY", 120},
    {110, "Isha", "SBIN", 180},
    {105, "Kabir", "WIPRO", 200},
    {102, "Raj", "TCS", 80},
    {108, "Nisha", "MSFT", 45},
    {107, "Arjun", "GOOGL", 30}
};

    unordered_map<string, Stock> stockMap;

    for (Stock s : stocks) {
        stockMap[s.ticker] = s;
    }

    queue<TradeOrder> tradeQueue;
    stack<Dividend> dividendStack;

    int choice;

    do {
        cout << "\n=============================================\n";
        cout << " QUANTITATIVE ASSET PORTFOLIO MANAGEMENT\n";
        cout << "=============================================\n";
        cout << "1. View Client Portfolios\n";
        cout << "2. View Stock Database\n";
        cout << "3. Search Stock by Ticker\n";
        cout << "4. Place Trade Order\n";
        cout << "5. Process Trade Orders\n";
        cout << "6. Apply Dividend\n";
        cout << "7. Undo Last Dividend\n";
        cout << "8. Sort Portfolios\n";
        cout << "9. Risk Analysis\n";
        cout << "10. Financial Network\n";
        cout << "11. Lowest Risk Route\n";
        cout << "12. Portfolio Balancer\n";
        cout << "13. Project Summary\n";
        cout << "14. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;  

        switch (choice) {
            case 1:
                viewClients(clients, stockMap);
                break;

            case 2:
                viewStocks(stocks);
                break;

            case 3:
                searchStock(stockMap);
                break;

            case 4:
                placeTradeOrder(tradeQueue);
                break;

            case 5:
                processTradeOrders(tradeQueue);
                break;

            case 6:
                applyDividend(dividendStack);
                break;

            case 7:
                undoDividend(dividendStack);
                break;

           case 8:
                sortPortfolios(clients, stockMap);
                break;

            case 9:
                analyzeRisk(clients);
                break;

            case 10:
                showFinancialNetwork();
                break;

            case 11:
                findLowestRiskRoute();
                break;

            case 12:
                portfolioBalancer(clients, stockMap);
                break;

            case 13:
                projectSummary(clients, stockMap);
                break;

            case 14:
                cout << "\nExiting system... Thank you!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 14);

    return 0;
}