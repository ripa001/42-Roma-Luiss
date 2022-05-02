#include "Account.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>


int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit) : _amount(initial_deposit){
	_accountIndex = Account::_nbAccounts;
	++Account::_nbAccounts;
	Account::_totalAmount += _amount;
	_nbDeposits = 0;
	_nbWithdrawals = 0;
	_displayTimestamp();
	std::cout << " index:" << _accountIndex << ";amount:" << _amount << ";created" << std::endl;
}

Account::~Account()
{
	_nbAccounts--;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";closed" << std::endl;
}

void Account::_displayTimestamp(void)
{
	time_t now = time(0);
	tm *t = localtime(&now);
	std::cout << "[" << std::setfill('0') << 1900 + t->tm_year << std::setw(2) <<
	1 + t->tm_mon << std::setw(2) << t->tm_mday << "_" << std::setw(2) << 
	t->tm_hour << std::setw(2) << t->tm_min << std::setw(2) << t->tm_sec << "] ";
}