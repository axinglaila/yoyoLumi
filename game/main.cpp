#include <iostream>
#include <fstream>
#include <memory>

constexpr const char* usage = "usage:\t[n2v/v2n] src dst\ne.g.\tlumi n2v a.ndf a.mp4\t��a.ndfת��Ϊa.mp4\n\tlumi v2n a.mp4 a.ndf\t��a.mp4ת��Ϊa.ndf\n";

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		std::cout << usage << std::endl;
		return -2;
	}

	std::ifstream ifs(argv[2], std::ios::binary);
	if (!ifs.is_open())
	{
		std::cout << "�������ļ�ʧ��\n";
		return -4;
	}

	std::ofstream ofs(argv[3], std::ios::binary);
	if (!ofs.is_open())
	{
		std::cout << "������ļ�ʧ��";
		return -16;
	}


	if (!strcmp(argv[1], "n2v"))		// ndf -> mp4
	{
		ifs.seekg(2, std::ios::beg);
	}
	else if (!strcmp(argv[1], "v2n"))		// mp4 -> ndf
	{
		char head[] = { (char)0xFF, (char)0x95 };
		ofs.write(head, 2);
	}
	else
	{
		std::cout << "��������\n" << usage << std::endl;
		return -32;
	}


	std::cout << argv[2] << " --> " << argv[3] << std::endl;
	constexpr long buffer_size = 0x4000;
	auto buffer = std::unique_ptr<char>(new char[buffer_size]);
	while (!ifs.eof())
	{
		ifs.read(buffer.get(), buffer_size);
		ofs.write(buffer.get(), ifs.gcount());
	};

	ifs.close();
	ofs.close();
	std::cout << "ת�����\n";

	return 0;
}