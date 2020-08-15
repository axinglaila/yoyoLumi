#include <iostream>
#include <fstream>

constexpr const char* usage = "usage [n2v/v2n] src dst";
constexpr size_t step = 4096u * 4096u;

int main(int argc, char** argv)
{
	if(argc != 4)
	{
		std::cout << usage << std::endl;
		return -2;
	}

	std::ifstream ifs(argv[2], std::ios::binary);
	if(!ifs.is_open())
	{
		std::cout << "�������ļ�ʧ��\n";
		return -4;
	}

	std::ofstream ofs(argv[3], std::ios::binary);
	if(!ofs.is_open())
	{
		std::cout << "������ļ�ʧ��";
		return -16;
	}


	if(!strcmp(argv[1], "n2v"))
	{
		ifs.seekg(2, std::ios::beg);
	}
	else if(!strcmp(argv[1], "v2n"))
	{
		char head[2] = { (char)0xFF,(char)0x95 };
		ofs.write(head, 2);
	}
	else
	{
		std::cout << "��������\n";
		return -32;
	}


	std::cout << argv[2] << " --> " << argv[3] << std::endl;
	char* buf = new char[step + 1u];
	while(!ifs.eof())
	{
		ifs.read(buf, step);
		ofs.write(buf, ifs.gcount());
	};


	delete[] buf;
	buf = nullptr;

	ifs.close();
	ofs.close();
	std::cout << "ת�����\n";

	return 0;
}