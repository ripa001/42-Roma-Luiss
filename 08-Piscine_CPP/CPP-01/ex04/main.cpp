#include <iostream>
#include <fstream>

void replace(char *argv[])
{
	int	i;
	std::string filename;
	std::string s1 = argv[1];
	std::string s2 = argv[2];
	std::string tmp;
	std::fstream file;

	file.open(argv[0], std::fstream::in);
	filename = argv[0];
	i = -1;
	while (argv[0][++i])
		if (argv[0][i] == '.')
			break ;
	filename = filename.substr(0, i) + ".replace";
	std::ofstream output(filename, std::fstream::out);
	while (std::getline(file, tmp))
	{
		while (true)
		{
			size_t found;
			found = tmp.find(s1);
			if (found != std::string::npos)
			{
				tmp.erase(found, s1.length());
				tmp.insert(found, s2);
			}
			else
				break;
		}
		output << tmp << std::endl;
	}
	output.close();
	file.close();
}

int main (int argc, char *argv[])
{
	if (argc == 4)
		replace(&argv[1]);
	return (0);
}