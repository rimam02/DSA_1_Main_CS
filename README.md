# Quantitative Asset Portfolio Management

A Data Structures and Algorithms (DSA) project developed in C++ for portfolio management, stock analysis, trade processing, risk assessment, and financial network analysis.

## Features

- Client Portfolio Management
- Stock Database
- Stock Search using Hash Map
- Trade Processing using Queue
- Dividend Management using Stack
- Portfolio Sorting using Merge Sort
- Risk Analysis
- Financial Network Representation using Graph
- Lowest Risk Route using Dijkstra's Algorithm
- Portfolio Balancer
- Project Summary Dashboard

## Problem Statement

Develop a Quantitative Asset Portfolio Management System using C++ that allows users to manage client portfolios, analyze stock investments, process trade orders, evaluate investment risks, and visualize financial relationships using Data Structures and Algorithms.

The system should demonstrate efficient data management, portfolio analysis, trade processing, and decision-making through the implementation of various DSA concepts.

## Objectives

- Manage multiple client investment portfolios.
- Maintain a stock database for analysis.
- Enable fast stock searching using Hash Maps.
- Process trade orders using Queue.
- Manage dividend history using Stack.
- Sort portfolios using Merge Sort.
- Analyze portfolio risk levels.
- Represent financial relationships using Graphs.
- Find the lowest risk route using Dijkstra's Algorithm.
- Generate portfolio insights and project summaries.

## System Architecture

The system is designed as a menu-driven C++ application that manages client portfolios and stock market data.

### Workflow

Client Data
↓
Portfolio Management
↓
Stock Analysis
↓
Trade Processing
↓
Risk Evaluation
↓
Financial Network Analysis
↓
Portfolio Insights & Summary

The application integrates multiple Data Structures and Algorithms to efficiently perform portfolio operations and financial analysis.

## Data Structures Used

### 1. Hash Map (unordered_map)

Purpose:
- Fast stock lookup using ticker symbols.

Usage:
- Search stock information instantly.

### 2. Queue

Purpose:
- Manage trade orders in First-In-First-Out (FIFO) order.

Usage:
- Trade processing system.

### 3. Stack

Purpose:
- Manage dividend history and undo operations.

Usage:
- Undo last dividend action.

### 4. Vector

Purpose:
- Store client and stock records.

Usage:
- Portfolio and stock management.

### 5. Graph

Purpose:
- Represent financial institutions and their relationships.

Usage:
- Financial network visualization.

## Algorithms Used

### 1. Merge Sort

Purpose:
- Sort client portfolios based on portfolio value.

Time Complexity:
- O(n log n)

### 2. Dijkstra's Algorithm

Purpose:
- Find the lowest risk route in the financial network.

Time Complexity:
- O(V²)

### 3. Risk Analysis Algorithm

Purpose:
- Categorize portfolios into LOW, MEDIUM, and HIGH risk groups based on holdings.

### 4. Portfolio Balancer

Purpose:
- Provide investment diversification suggestions.

## Implementation Approach

The project follows a modular approach where each functionality is implemented using an appropriate Data Structure or Algorithm.

### Portfolio Management

Client portfolio records are stored using vectors. Each client record contains details such as client ID, name, stock ticker, and number of shares.

### Stock Management

Stock information is maintained in a stock database and stored using vectors and hash maps for efficient access.

### Trade Processing

Trade orders are placed and stored in a Queue. Orders are processed in the same sequence in which they are received.

### Dividend Management

Dividend operations are maintained using a Stack. The most recent dividend operation can be undone using the Last-In-First-Out (LIFO) principle.

### Portfolio Sorting

Client portfolios are sorted according to portfolio value using Merge Sort for efficient performance.

### Risk Analysis

Portfolio risk levels are determined based on the number of shares held by each client and categorized as LOW, MEDIUM, or HIGH.

### Financial Network Analysis

A Graph structure is used to model financial entities and their relationships.

### Lowest Risk Route

Dijkstra's Algorithm is applied to determine the minimum-risk path within the financial network.

### Portfolio Balancer

The system provides diversification suggestions based on the client's current investment sector.

### Project Summary Dashboard

The dashboard generates portfolio statistics such as:
- Total Clients
- Total Stocks
- Highest Portfolio Value
- Lowest Portfolio Value
- Average Portfolio Value

## Time and Space Complexity Analysis

| Operation | Data Structure / Algorithm | Time Complexity |
|------------|---------------------------|----------------|
| Stock Search | Hash Map | O(1) |
| Trade Insertion | Queue | O(1) |
| Trade Processing | Queue | O(1) |
| Dividend Push | Stack | O(1) |
| Dividend Undo | Stack | O(1) |
| Portfolio Sorting | Merge Sort | O(n log n) |
| Risk Analysis | Traversal | O(n) |
| Financial Network Display | Graph | O(V + E) |
| Lowest Risk Route | Dijkstra | O(V²) |
| Project Summary | Traversal | O(n) |

## Space Complexity

| Structure | Space Complexity |
|------------|------------------|
| Client Records | O(n) |
| Stock Records | O(n) |
| Queue | O(n) |
| Stack | O(n) |
| Graph | O(V + E) |
| Merge Sort | O(n) |
