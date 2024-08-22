#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

// Function to display the initial input screen and get user input
void getUserInput(double &initialInvestment, double &monthlyDeposit, double &annualInterest, int &years) {
    std::cout << "**********************************" << std::endl;
    std::cout << "********** Data Input ************" << std::endl;
    std::cout << "Initial Investment Amount: ";
    std::cin >> initialInvestment;
    std::cout << "Monthly Deposit: ";
    std::cin >> monthlyDeposit;
    std::cout << "Annual Interest: ";
    std::cin >> annualInterest;
    std::cout << "Number of Years: ";
    std::cin >> years;
    std::cout << "Press any key to continue..." << std::endl;
    std::cin.ignore(); // To ignore the newline character left in the buffer
    std::cin.get(); // To wait for any key press
}

// Function to calculate year-end balances and interests without monthly deposits
void calculateWithoutDeposits(double initialInvestment, double annualInterest, int years, std::vector<double> &yearEndBalances, std::vector<double> &yearEndInterests) {
    double balance = initialInvestment;
    for (int i = 0; i < years; ++i) {
        double interest = balance * (annualInterest / 100);
        balance += interest;
        yearEndInterests.push_back(interest);
        yearEndBalances.push_back(balance);
    }
}

// Function to calculate year-end balances and interests with monthly deposits
void calculateWithDeposits(double initialInvestment, double monthlyDeposit, double annualInterest, int years, std::vector<double> &yearEndBalances, std::vector<double> &yearEndInterests) {
    double balance = initialInvestment;
    for (int i = 0; i < years; ++i) {
        double yearlyInterest = 0;
        for (int j = 0; j < 12; ++j) {
            balance += monthlyDeposit;
            double interest = balance * ((annualInterest / 100) / 12);
            balance += interest;
            yearlyInterest += interest;
        }
        yearEndInterests.push_back(yearlyInterest);
        yearEndBalances.push_back(balance);
    }
}

// Function to display the reports
void displayReports(const std::vector<double> &balancesNoDeposits, const std::vector<double> &interestsNoDeposits, const std::vector<double> &balancesWithDeposits, const std::vector<double> &interestsWithDeposits) {
    std::cout << "************************************************************" << std::endl;
    std::cout << "********************** Annual Report ***********************" << std::endl;

    std::cout << "******************* No Monthly Deposits ********************" << std::endl;
    std::cout << std::setw(10) << "Year" << std::setw(20) << "   Year End Balance" << std::setw(20) << "      Year End Earned Interest" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    for (size_t i = 0; i < balancesNoDeposits.size(); ++i) {
        std::cout << std::setw(10) << (i + 1) << std::setw(20) << std::fixed << std::setprecision(2) << balancesNoDeposits[i] << std::setw(20) << interestsNoDeposits[i] << std::endl;
    }

    std::cout << "\n****************** With Monthly Deposits *******************" << std::endl;
    std::cout << std::setw(10) << "Year" << std::setw(20) << "    Year End Balance" << std::setw(20) << "      Year End Earned Interest" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    for (size_t i = 0; i < balancesWithDeposits.size(); ++i) {
        std::cout << std::setw(10) << (i + 1) << std::setw(20) << std::fixed << std::setprecision(2) << balancesWithDeposits[i] << std::setw(20) << interestsWithDeposits[i] << std::endl;
    }
}

int main() {
    double initialInvestment, monthlyDeposit, annualInterest;
    int years;

    getUserInput(initialInvestment, monthlyDeposit, annualInterest, years);

    std::vector<double> yearEndBalancesNoDeposits;
    std::vector<double> yearEndInterestsNoDeposits;
    calculateWithoutDeposits(initialInvestment, annualInterest, years, yearEndBalancesNoDeposits, yearEndInterestsNoDeposits);

    std::vector<double> yearEndBalancesWithDeposits;
    std::vector<double> yearEndInterestsWithDeposits;
    calculateWithDeposits(initialInvestment, monthlyDeposit, annualInterest, years, yearEndBalancesWithDeposits, yearEndInterestsWithDeposits);

    displayReports(yearEndBalancesNoDeposits, yearEndInterestsNoDeposits, yearEndBalancesWithDeposits, yearEndInterestsWithDeposits);

    return 0;
}
