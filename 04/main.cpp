#include <iostream>

struct BigInt
{
	int* data = nullptr;
	bool minus;

	BigInt(int32_t x)
	{
		create_data(std::to_string(x));
	}

	BigInt(std::string s)
	{
		create_data(s);
	{

	BigInt operator=(int32_t x)
	{
	}
	
	
    void create_data(std::string s)
    {
        data = new int[s.length()];
        uint64_t start;
        if (s[0] == '-'){
            start = 1;
            minus = true;
        } else {
            start = 0;
            minus = false;
        }
        for (uint64_t i = start; i < s.length(); i++)
        {
            data[i] = (int)s[i] - 48;
        }
    }

};


int main()
{
	BigInt a(123);
	std::cout << a.data[0] << std::endl;
	
}
