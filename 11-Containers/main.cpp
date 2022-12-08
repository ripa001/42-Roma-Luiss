#include "vector.hpp"
#include "iterator.hpp"
// #include "map.hpp"
// #include "stack.hpp"
// #include "set.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <set>
#include <map>


int main()
{
	std::ofstream fileout ("mine.txt");
	fileout << "************** TESTING VECTOR **************\n" << std::endl;

	ft::vector<int> vec1(5,100);
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	ft::vector<int> vec2(arr, arr+10);

	fileout << "Printing content: \n";
	ft::vector<int>::iterator it1;
	fileout << "size : " << vec1.size() << std::endl;
	fileout << "max_size : " << vec1.max_size() << std::endl;

	for(it1 = vec1.begin(); it1 != vec1.end(); ++it1)
		fileout << "[vec1] : " << *it1 << std::endl;

	fileout << std::endl;
	fileout << "size : " << vec2.size() << std::endl;
	fileout << "max_size : " << vec2.max_size() << std::endl;
	for(it1 = vec2.begin(); it1 != vec2.end(); ++it1)
		fileout << "[vec2] : " << *it1 << std::endl;
	
	fileout << "\n\nTESTING COPY COSTRUCTOR\n" << std::endl;

	ft::vector<int> vec3(vec2);
	fileout << "Printing content: \n";
	fileout << "size : " << vec3.size() << std::endl;
	fileout << "max_size : " << vec3.max_size() << std::endl;
	for(it1 = vec3.begin(); it1 != vec3.end(); ++it1)
		fileout << "[vec3] : " << *it1 << std::endl;

	
	fileout << "\n\nTESTING ASSIGN\n" << std::endl;
	// vec2.assign(20, 20);
	fileout << "Printing content: \n";
	fileout << "size : " << vec2.size() << std::endl;
	fileout << "max_size : " << vec2.max_size() << std::endl;
	for(it1 = vec2.begin(); it1 != vec2.end(); ++it1)
		fileout << "[vec2] : " << *it1 << std::endl;

// 	fileout << "\n\nTESTING ERASE\n" << std::endl;
// 	vec3.erase(++(++(++vec3.begin())), --(--(--vec3.end())));
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << vec3.size() << std::endl;
// 	fileout << "max_size : " << vec3.max_size() << std::endl;
// 	for(it1 = vec3.begin(); it1 != vec3.end(); ++it1)
// 		fileout << "[vec3] : " << *it1 << std::endl;

	
// 	fileout << "\n\nTESTING INSERT\n" << std::endl;
// 	vec3.insert(++(++(++vec3.begin())), vec2.begin(), vec2.begin()+4);
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << vec3.size() << std::endl;
// 	fileout << "max_size : " << vec3.max_size() << std::endl;
// 	for(it1 = vec3.begin(); it1 != vec3.end(); ++it1)
// 		fileout << "[vec3] : " << *it1 << std::endl;


// 	fileout << "\n\nTESTING OPERATORS\n" << std::endl;
// 	fileout << "vec3 at(5) = " << vec3.at(5) << std::endl;
// 	fileout << "vec3 [9] = " << vec3[9] << std::endl;
// 	fileout << "vec3 front = " << vec3.front() << std::endl;
// 	fileout << "vec3 back = " << vec3.back() << std::endl;

// 	fileout << "\n\nTESTING SWAP\n" << std::endl;
// 	vec2.swap(vec3);
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << vec2.size() << std::endl;
// 	fileout << "max_size : " << vec2.max_size() << std::endl;
// 	for(it1 = vec2.begin(); it1 != vec2.end(); ++it1)
// 		fileout << "[vec2] : " << *it1 << std::endl;
// 	fileout << "\n\n";
// 	fileout << "size : " << vec3.size() << std::endl;
// 	fileout << "max_size : " << vec3.max_size() << std::endl;
// 	for(it1 = vec3.begin(); it1 != vec3.end(); ++it1)
// 		fileout << "[vec3] : " << *it1 << std::endl;


// 	fileout << "\n\n************** TESTING STACK **************\n" << std::endl;
// 	ft::stack<int, ft::vector<int> > stack1 (vec2);

// 	fileout << "Printing content: \n";
// 	fileout << "size : " << stack1.size() << std::endl;
// 	while(stack1.size() != 0)
// 	{
// 		fileout << "[stack1] : " << stack1.top() << std::endl;
// 		stack1.pop();
// 	}
	
// 	fileout << "\n\n************** TESTING MAP **************\n" << std::endl;
// 	ft::map<int, std::string> map1;
// 	map1.insert(ft::pair<int, std::string>(1, "a"));
// 	map1.insert(ft::pair<int, std::string>(2, "b"));
// 	map1.insert(ft::pair<int, std::string>(3, "c"));
// 	map1.insert(ft::pair<int, std::string>(4, "d"));
// 	map1.insert(ft::pair<int, std::string>(5, "e"));
// 	map1.insert(ft::pair<int, std::string>(6, "f"));
// 	map1.insert(ft::pair<int, std::string>(7, "g"));
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << map1.size() << std::endl;
// 	fileout << "max_size : " << map1.max_size() << std::endl;
// 	ft::map<int, std::string>::iterator it;
// 	for(it = map1.begin(); it != map1.end(); ++it)
// 		fileout << "[map1] key = " << it->first << "  value = " << it->second << std::endl;
	
// 	fileout << "\n\n TESTING OPERATOR[] \n" << std::endl;
// 	map1[6] = "changed";
// 	map1[2] = "changed";
// 	map1[10] = "added with operator[]";
// 	for(it = map1.begin(); it != map1.end(); ++it)
// 		fileout << "[map1] key = " << it->first << "  value = " << it->second << std::endl;


// 	fileout << "\n\n TESTING COPY COSTRUCTOR \n" << std::endl;
// 	ft::map<int, std::string> map2(map1);
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << map2.size() << std::endl;
// 	fileout << "max_size : " << map2.max_size() << std::endl;
// 	for(it = map2.begin(); it != map2.end(); ++it)
// 		fileout << "[map2] key = " << it->first << "  value = " << it->second << std::endl;

// 	fileout << "\n\n TESTING ERASE \n" << std::endl;
// 	map1.erase(map1.begin(), ++(++(map1.begin())));
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << map1.size() << std::endl;
// 	fileout << "max_size : " << map1.max_size() << std::endl;
// 	for(it = map1.begin(); it != map1.end(); ++it)
// 		fileout << "[map1] key = " << it->first << "  value = " << it->second << std::endl;

// 	fileout << "\n\n TESTING SWAP\n" << std::endl;
// 	ft::map<int, std::string> map3(map2);
// 	map3.find(5)->second = "changed with find()";
// 	map3.lower_bound(9)->second = "changed with lower()";
// 	map3.swap(map2);
// 	fileout << "Printing content: \n";
// 	it = map2.begin();
// 	ft::map<int, std::string>::iterator it2;
// 	for(it = map2.begin(); it != map2.end(); ++it)
// 		fileout << "[map2] key = " << it->first << "  value = " << it->second << std::endl;
// 	fileout << std::endl;
// 	for(it2 = map3.begin(); it2 != map3.end(); ++it2)	
// 		fileout << "[map3] key = " << it2->first << "  value = " << it2->second << std::endl;

	

// 	fileout << "\n\n************** TESTING SET **************\n" << std::endl;
// 	ft::set<int> set1;
// 	set1.insert(100);
// 	set1.insert(200);
// 	set1.insert(300);
// 	set1.insert(400);
// 	set1.insert(500);
// 	set1.insert(600);
// 	set1.insert(700);
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << set1.size() << std::endl;
// 	fileout << "max_size : " << set1.max_size() << std::endl;
// 	ft::set<int>::iterator ite;
// 	for(ite = set1.begin(); ite != set1.end(); ++ite)
// 		fileout << "[set1] = " << *ite << std::endl;


// 	fileout << "\n\n TESTING COPY COSTRUCTOR \n" << std::endl;
// 	ft::set<int> set2(set1);
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << set2.size() << std::endl;
// 	fileout << "max_size : " << set2.max_size() << std::endl;
// 	for(ite = set2.begin(); ite != set2.end(); ++ite)
// 		fileout << "[set2] = " << *ite << std::endl;

// 	fileout << "\n\n TESTING ERASE \n" << std::endl;
// 	set1.erase(set1.begin(), ++(++(set1.begin())));
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << set1.size() << std::endl;
// 	fileout << "max_size : " << set1.max_size() << std::endl;
// 	for(ite = set1.begin(); ite != set1.end(); ++ite)
// 		fileout << "[set1] = " << *ite << std::endl;

// 	fileout << "\n\n TESTING SWAP\n" << std::endl;
// 	ft::set<int> set3;
// 	set3.insert(1);
// 	set3.insert(2);
// 	set3.insert(3);
// 	set3.insert(4);
// 	set3.insert(5);
// 	set3.insert(6);
// 	set3.insert(7);
// 	set3.swap(set2);

// 	fileout << "Printing content: \n";
// 	fileout << "size : " << set2.size() << std::endl;
// 	fileout << "max_size : " << set2.max_size() << std::endl;
// 	for(ite = set2.begin(); ite != set2.end(); ++ite)
// 		fileout << "[set2] = " << *ite << std::endl;
// 	fileout << std::endl;
// 	for(ite = set3.begin(); ite != set3.end(); ++ite)
// 		fileout << "[set3] = " << *ite << std::endl;
// }


// void testing_std()
// {
// 	std::ofstream fileout ("real.txt");
// 	fileout << "************** TESTING VECTOR **************\n" << std::endl;

// 	std::vector<int> vec1(5,100);
// 	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
// 	std::vector<int> vec2(arr, arr+10);

// 	fileout << "Printing content: \n";
// 	std::vector<int>::iterator it1;
// 	fileout << "size : " << vec1.size() << std::endl;
// 	fileout << "max_size : " << vec1.max_size() << std::endl;

// 	for(it1 = vec1.begin(); it1 != vec1.end(); ++it1)
// 		fileout << "[vec1] : " << *it1 << std::endl;

// 	fileout << std::endl;
// 	fileout << "size : " << vec2.size() << std::endl;
// 	fileout << "max_size : " << vec2.max_size() << std::endl;
// 	for(it1 = vec2.begin(); it1 != vec2.end(); ++it1)
// 		fileout << "[vec2] : " << *it1 << std::endl;
	
// 	fileout << "\n\nTESTING COPY COSTRUCTOR\n" << std::endl;

// 	std::vector<int> vec3(vec2);
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << vec3.size() << std::endl;
// 	fileout << "max_size : " << vec3.max_size() << std::endl;
// 	for(it1 = vec3.begin(); it1 != vec3.end(); ++it1)
// 		fileout << "[vec3] : " << *it1 << std::endl;

	
// 	fileout << "\n\nTESTING ASSIGN\n" << std::endl;
// 	vec2.assign(20, 20);
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << vec2.size() << std::endl;
// 	fileout << "max_size : " << vec2.max_size() << std::endl;
// 	for(it1 = vec2.begin(); it1 != vec2.end(); ++it1)
// 		fileout << "[vec2] : " << *it1 << std::endl;

// 	fileout << "\n\nTESTING ERASE\n" << std::endl;
// 	vec3.erase(++(++(++vec3.begin())), --(--(--vec3.end())));
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << vec3.size() << std::endl;
// 	fileout << "max_size : " << vec3.max_size() << std::endl;
// 	for(it1 = vec3.begin(); it1 != vec3.end(); ++it1)
// 		fileout << "[vec3] : " << *it1 << std::endl;

	
// 	fileout << "\n\nTESTING INSERT\n" << std::endl;
// 	vec3.insert(++(++(++vec3.begin())), vec2.begin(), vec2.begin()+4);
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << vec3.size() << std::endl;
// 	fileout << "max_size : " << vec3.max_size() << std::endl;
// 	for(it1 = vec3.begin(); it1 != vec3.end(); ++it1)
// 		fileout << "[vec3] : " << *it1 << std::endl;


// 	fileout << "\n\nTESTING OPERATORS\n" << std::endl;
// 	fileout << "vec3 at(5) = " << vec3.at(5) << std::endl;
// 	fileout << "vec3 [9] = " << vec3[9] << std::endl;
// 	fileout << "vec3 front = " << vec3.front() << std::endl;
// 	fileout << "vec3 back = " << vec3.back() << std::endl;

// 	fileout << "\n\nTESTING SWAP\n" << std::endl;
// 	vec2.swap(vec3);
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << vec2.size() << std::endl;
// 	fileout << "max_size : " << vec2.max_size() << std::endl;
// 	for(it1 = vec2.begin(); it1 != vec2.end(); ++it1)
// 		fileout << "[vec2] : " << *it1 << std::endl;
// 	fileout << "\n\n";
// 	fileout << "size : " << vec3.size() << std::endl;
// 	fileout << "max_size : " << vec3.max_size() << std::endl;
// 	for(it1 = vec3.begin(); it1 != vec3.end(); ++it1)
// 		fileout << "[vec3] : " << *it1 << std::endl;


// 	fileout << "\n\n************** TESTING STACK **************\n" << std::endl;
// 	std::stack<int, std::vector<int> > stack1 (vec2);

// 	fileout << "Printing content: \n";
// 	fileout << "size : " << stack1.size() << std::endl;
// 	while(stack1.size() != 0)
// 	{
// 		fileout << "[stack1] : " << stack1.top() << std::endl;
// 		stack1.pop();
// 	}
	
// 	fileout << "\n\n************** TESTING MAP **************\n" << std::endl;
// 	std::map<int, std::string> map1;
// 	map1.insert(std::pair<int, std::string>(1, "a"));
// 	map1.insert(std::pair<int, std::string>(2, "b"));
// 	map1.insert(std::pair<int, std::string>(3, "c"));
// 	map1.insert(std::pair<int, std::string>(4, "d"));
// 	map1.insert(std::pair<int, std::string>(5, "e"));
// 	map1.insert(std::pair<int, std::string>(6, "f"));
// 	map1.insert(std::pair<int, std::string>(7, "g"));
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << map1.size() << std::endl;
// 	fileout << "max_size : " << map1.max_size() << std::endl;
// 	std::map<int, std::string>::iterator it;
// 	for(it = map1.begin(); it != map1.end(); ++it)
// 		fileout << "[map1] key = " << it->first << "  value = " << it->second << std::endl;
	
// 	fileout << "\n\n TESTING OPERATOR[] \n" << std::endl;
// 	map1[6] = "changed";
// 	map1[2] = "changed";
// 	map1[10] = "added with operator[]";
// 	for(it = map1.begin(); it != map1.end(); ++it)
// 		fileout << "[map1] key = " << it->first << "  value = " << it->second << std::endl;


// 	fileout << "\n\n TESTING COPY COSTRUCTOR \n" << std::endl;
// 	std::map<int, std::string> map2(map1);
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << map2.size() << std::endl;
// 	fileout << "max_size : " << map2.max_size() << std::endl;
// 	for(it = map2.begin(); it != map2.end(); ++it)
// 		fileout << "[map2] key = " << it->first << "  value = " << it->second << std::endl;

// 	fileout << "\n\n TESTING ERASE \n" << std::endl;
// 	map1.erase(map1.begin(), ++(++(map1.begin())));
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << map1.size() << std::endl;
// 	fileout << "max_size : " << map1.max_size() << std::endl;
// 	for(it = map1.begin(); it != map1.end(); ++it)
// 		fileout << "[map1] key = " << it->first << "  value = " << it->second << std::endl;

// 	fileout << "\n\n TESTING SWAP\n" << std::endl;
// 	std::map<int, std::string> map3(map2);
// 	map3.find(5)->second = "changed with find()";
// 	map3.lower_bound(9)->second = "changed with lower()";
// 	map3.swap(map2);
// 	fileout << "Printing content: \n";
// 	it = map2.begin();
// 	std::map<int, std::string>::iterator it2;
// 	for(it = map2.begin(); it != map2.end(); ++it)
// 		fileout << "[map2] key = " << it->first << "  value = " << it->second << std::endl;
// 	fileout << std::endl;
// 	for(it2 = map3.begin(); it2 != map3.end(); ++it2)	
// 		fileout << "[map3] key = " << it2->first << "  value = " << it2->second << std::endl;

	

// 	fileout << "\n\n************** TESTING SET **************\n" << std::endl;
// 	std::set<int> set1;
// 	set1.insert(100);
// 	set1.insert(200);
// 	set1.insert(300);
// 	set1.insert(400);
// 	set1.insert(500);
// 	set1.insert(600);
// 	set1.insert(700);
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << set1.size() << std::endl;
// 	fileout << "max_size : " << set1.max_size() << std::endl;
// 	std::set<int>::iterator ite;
// 	for(ite = set1.begin(); ite != set1.end(); ++ite)
// 		fileout << "[set1] = " << *ite << std::endl;


// 	fileout << "\n\n TESTING COPY COSTRUCTOR \n" << std::endl;
// 	std::set<int> set2(set1);
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << set2.size() << std::endl;
// 	fileout << "max_size : " << set2.max_size() << std::endl;
// 	for(ite = set2.begin(); ite != set2.end(); ++ite)
// 		fileout << "[set2] = " << *ite << std::endl;

// 	fileout << "\n\n TESTING ERASE \n" << std::endl;
// 	set1.erase(set1.begin(), ++(++(set1.begin())));
// 	fileout << "Printing content: \n";
// 	fileout << "size : " << set1.size() << std::endl;
// 	fileout << "max_size : " << set1.max_size() << std::endl;
// 	for(ite = set1.begin(); ite != set1.end(); ++ite)
// 		fileout << "[set1] = " << *ite << std::endl;

// 	fileout << "\n\n TESTING SWAP\n" << std::endl;
// 	std::set<int> set3;
// 	set3.insert(1);
// 	set3.insert(2);
// 	set3.insert(3);
// 	set3.insert(4);
// 	set3.insert(5);
// 	set3.insert(6);
// 	set3.insert(7);
// 	set3.swap(set2);

// 	fileout << "Printing content: \n";
// 	fileout << "size : " << set2.size() << std::endl;
// 	fileout << "max_size : " << set2.max_size() << std::endl;
// 	for(ite = set2.begin(); ite != set2.end(); ++ite)
// 		fileout << "[set2] = " << *ite << std::endl;
// 	fileout << std::endl;
// 	for(ite = set3.begin(); ite != set3.end(); ++ite)
// 		fileout << "[set3] = " << *ite << std::endl;
return (0);
}
