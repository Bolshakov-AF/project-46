#pragma once
#include <fstream>
#include<string>

enum Mode { CLOSE, IN, APP, OUT, TRUNC };

class FileArray final
{
private:
	std::fstream _fs;
	const std::string _name;
	Mode _mode;
	bool _tmp;
	size_t _size;
	size_t _read;

	void reload()noexcept;

public:
	FileArray(const std::string&, Mode, bool);
	FileArray(const std::string&, Mode);
	FileArray(const std::string&, bool);
	FileArray(const std::string&);
	FileArray(const FileArray&) = delete;
	FileArray(const FileArray&&) = delete;

	~FileArray();

	bool add(FileArray&);
	bool empty()const noexcept;
	bool finalise();
	Mode mode()const noexcept;
	const std::string& name()const noexcept;
	int next();
	bool push(int);
	size_t size()const noexcept;
	bool switchMode(Mode)noexcept;

	FileArray& operator=(FileArray&) = delete;
	FileArray&& operator=(FileArray&&) = delete;
};

