#include <cstring>
#include <cstdlib>

class N
{
	private:
		int value;
		char annotation[100];

	public:
		N(int param) : value(param) {}

		int operator+(N& other)
		{
			return other.value + this->value;
		}

		int operator-(N& other)
		{
			return this->value - other.value;
		}

		void setAnnotation(char* str)
		{
			std::memcpy(this->annotation, str, std::strlen(str));
		}
};

int main(int argc, char **argv)
{
	if (argc < 2)
		exit(1);

	N* n1 = new N(5);
	N* n2 = new N(6);

	n1->setAnnotation(argv[1]);

	(*n1 + *n2);

	return 0;
}
