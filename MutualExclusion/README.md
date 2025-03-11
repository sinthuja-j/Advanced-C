🏦 Bank Account Mutual Exclusion Program 🏦

This program simulates bank transactions (deposits and withdrawals) using threads and mutexes to ensure safe, concurrent access to shared resources (bank accounts).

🔑 Key Features:

Account Balances & Transactions 💰:

5 bank accounts initialized to zero balance.
Clients can deposit or withdraw money from these accounts.
Thread synchronization ensures no data corruption when multiple clients access accounts simultaneously.
Thread Synchronization with Mutex 🔒:

Uses pthread_mutex_t to ensure mutual exclusion during account updates. Only one thread can modify an account at a time.
Critical section protection for safe concurrent transactions.

Transaction Logic 💵:

Clients can perform deposits or withdrawals.
Account flags track which accounts have been accessed, allowing calculation of the number of unique clients.
The program reads an input file containing transaction details and processes them with corresponding threads for each deposit/withdrawal action.

Dynamic Thread Creation 🚀:

For each deposit or withdrawal, a new thread is created to process the transaction, ensuring parallel execution.
Thread joining (pthread_join) ensures threads complete before moving on to the next transaction, preventing race conditions.

Error Handling & File I/O 📂:

Reads transaction instructions from an external file (assignment_5_input.txt).
If the file is missing, it outputs an error message.
U
nique Client Tracking 👥:

Tracks the number of unique clients interacting with the accounts using flags for each account.
Provides a final count of accounts and clients along with their balances.

🚀 C Programming Highlights:

Threading: Utilizes the pthread library for creating and managing threads.
Mutex Locks: Prevents race conditions when multiple threads access shared resources (bank accounts).
File Handling: Reads data from a file to dynamically process transactions.
String Manipulation: Utilizes strtok to tokenize transaction commands and handle client interactions.
