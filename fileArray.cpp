#include <fstream>
#include <string>
#include "fileArray.h"
#include "exception.h"

FileArray::FileArray(const std::string& name, Mode mode, bool tmp) :_name(name), _mode(CLOSE), _tmp(tmp), _size(0), _read(0)
{
	switchMode(mode);
	reload();
}

FileArray::FileArray(const std::string& name, Mode mode) :FileArray(name, mode, false)
{
}

FileArray::FileArray(const std::string& name, bool tmp) :FileArray(name, CLOSE, tmp)
{
}

FileArray::FileArray(const std::string& name) :FileArray(name, CLOSE, false)
{
}

FileArray::~FileArray()
{
	switchMode(CLOSE);
	if (_tmp)
	{
		std::ifstream file(_name);
		if (file.good())
		{
			std::remove(_name.c_str());
		}
	}
}

void FileArray::reload()noexcept
{
	const Mode mode = _mode;

	_size = 0;

	if (switchMode(IN))
	{
		bool isNumber = false;
		while (!_fs.eof())
		{
			char c = _fs.get();

			if (c == '-' || (c >= '0' && c <= '9'))
			{
				if (!isNumber)
				{
					++_size;
					isNumber = true;
				}
			}
			else if (isNumber)
			{
				isNumber = false;
			}
		}
	}
	switchMode(_mode);
}

bool FileArray::add(FileArray& that)
{
	that.switchMode(IN);

	while (!that.empty())
	{
		if (!push(that.next()))
		{
			return false;
		}
	}

	return true;
}

bool FileArray::empty()const noexcept
{
	return _mode == IN && _size == _read;
}

Mode FileArray::mode()const noexcept
{
	return _mode;
}

bool FileArray::finalise()
{
	if (!switchMode(APP))
	{
		return false;
	}

	_fs << '\n';

	return true;
}

const std::string& FileArray::name()const noexcept
{
	return _name;
}

int FileArray::next()
{
	if (_mode != IN)
	{
		switchMode(IN);
	}

	if (empty())
	{
		EndOfFileException endOfFileException;
		throw endOfFileException;
	}

	int res;

	_fs >> res;
	++_read;

	return res;
}

bool FileArray::push(int value)
{
	if ((_mode == IN || _mode == CLOSE) && !switchMode(APP))
	{
		return false;
	}

	if (_size)
	{
		_fs << " ";
	}

	_fs << value;

	++_size;

	return true;
}

size_t FileArray::size()const noexcept
{
	return _size;
}
bool FileArray::switchMode(Mode mode)noexcept
{
	if (_fs.is_open())
	{
		_fs.close();
	}

	try
	{
		switch (mode)
		{
		case IN:
			_fs.open(_name, std::ios::in);
			_read = 0;
			break;
		case APP:
			_fs.open(_name, std::ios::app);
			break;
		case OUT:
			_fs.open(_name, std::ios::out);
			_size = 0;
			break;
		case TRUNC:
			_fs.open(_name, std::ios::trunc);
			_size = 0;
		}
	}
	catch (...)
	{
		_mode = CLOSE;
		return false;
	}

	_mode = mode;
	return true;
}
