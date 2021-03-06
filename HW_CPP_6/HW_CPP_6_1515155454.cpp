#include <string>
#include <iostream> 
#include <iomanip> 
#include <filesystem> 
#include <map>
#include <io.h>
#include <stdio.h>
#include <fstream>

namespace fs = std::experimental::filesystem::v1;

_fsize_t round_dir(const fs::path& p);
void display_content_of_path(fs::path & work_path, std::multimap<_fsize_t, fs::path> &files);


int main(int argv, char *argc[])
{
	if (argv < 3)
	{
		std::cout << "ERROR: invalid argument count" << std::endl;
	}
	else
	{
		fs::path _path(argc[1]);
		std::multimap<_fsize_t, fs::path> map_out;
		display_content_of_path(_path, map_out);
		std::ofstream fout;
		std::string file_name(argc[2]);
		_path /= file_name + ".txt";
		fout.open(_path);

		for (auto& pr : map_out)
		{
			std::wcout << std::setw(8) << pr.first << " : " << pr.second << std::endl;
			fout << std::setw(8) << pr.first << " : " << pr.second << std::endl;
		}
		fout.close();
	}

    return 0;
}

_fsize_t round_dir(const fs::path& p)
{
	_fsize_t dir_size = 0;
	struct _wfinddata_t c_file;
	intptr_t hFile;
	for (const auto& entry : fs::directory_iterator{ p })
	{
		if ((hFile = _wfindfirst(entry.path().c_str(), &c_file)) == -1L)
			return 0;
		else
		{
			if (fs::is_regular_file(entry.status()))
			{
				dir_size += c_file.size;
			}
			else if (fs::is_directory(entry.status()))
			{
				dir_size += round_dir(entry.path());
			}
		}
		_findclose(hFile);
	}
	return dir_size;
}

void display_content_of_path(fs::path & work_path, std::multimap<_fsize_t, fs::path>& files)
{
	struct _wfinddata_t c_file;
	intptr_t hFile;


	for (fs::recursive_directory_iterator it(work_path), end; it != end; ++it)
	{
		if ((hFile = _wfindfirst(it->path().c_str(), &c_file)) == -1L)
			return;
		else
		{
			if (fs::is_regular_file(it->status()))
			{
				files.emplace(c_file.size, it->path());
			}
			else if (fs::is_directory(it->status()))
			{
				files.emplace(round_dir(it->path()), it->path());
			}
		}
		_findclose(hFile);
	}

}
