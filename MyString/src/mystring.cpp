#include "mystring.h"
#include "Aho-Corasick/aho.h"

#define LL_MAX_SIGNS 20

static long str2subrange(
    const char *s, char **endptr, int base, 
    long min, long max) 
{
    long y = strtol(s, endptr, base);
    if (y > max) {
        errno = ERANGE;
        return max;
    }

    if (y < min) {
        errno = ERANGE;
        return min;
    }

    return y;
}

int str2i(const char *s, char **endptr, int base) {
    #if INT_MAX == LONG_MAX && INT_MIN == LONG_MIN
        return (int) strtol(s, endptr, base);
    #else
        return (int) str2subrange(s, endptr, base, INT_MIN, INT_MAX);
    #endif
}

short str2short(const char *s, char **endptr, int base) {
    return (short) str2subrange(s, endptr, base, SHRT_MIN, SHRT_MAX);
}

signed char str2schar(const char *s, char **endptr, int base) {
    return (signed char) str2subrange(s, endptr, base, SCHAR_MIN, SCHAR_MAX);
}

int16_t str2int16(const char *s, char **endptr, int base) {
    return (int16_t) str2subrange(s, endptr, base, INT16_MIN, INT16_MAX);
}

int strcheck(char* cstr)
{
    for (int i = 0; i < strlen(cstr); i++)
    {
        if (!isdigit(cstr[i]))
        {
            return 0;
        }
    }
    
    return 1;
}

void MyString::init_from_cstr(const char* cstr)
{
    while (*cstr != '\0')
    {
        this->charList.append(*cstr);
        cstr++;
    }
}

MyString::MyString(char *cstr)
{
    this->charList = CharList();
    this->init_from_cstr(cstr);
}

MyString::MyString(std::string str) 
{
    const char* cstr = str.c_str();
    this->init_from_cstr(cstr);
}

MyString::MyString(char* cstr, int n)
{
    if(strlen(cstr) < n)
    {
        throw std::invalid_argument("n must be equal or less then the lenght of cstr!");
        n = strlen(cstr);
    }

    for (int i = 0; i < n; i++)
    {
        this->charList.append(cstr[i]);
    }
}

MyString::MyString(int n, char c)
{
    for (int i = 0; i < n; i++)
    {
        this->charList.append(c);
    }
    
}

MyString::MyString(long long x)
{
    char* buf = new char[LL_MAX_SIGNS];
    sprintf(buf, "%lld", x);
    this->init_from_cstr(buf);

    delete[] buf;
}

MyString::MyString(float x)
{
    char* buf = new char[LL_MAX_SIGNS];
    sprintf(buf, "%f", x);
    this->init_from_cstr(buf);

    delete[] buf;
}

MyString::MyString(double x)
{
    char* buf = new char[LL_MAX_SIGNS];
    sprintf(buf, "%f", x);
    this->init_from_cstr(buf);

    delete[] buf;
}

MyString::MyString(MyString && s) noexcept
{
    s.charList = std::move(this->charList);
}

MyString &MyString::operator=(MyString &&s) noexcept
{
    s.charList = std::move(this->charList);
    return *this;
}

MyString::MyString(const MyString & myString)
{
    // this->charList = CharList(myString.charList);
    const char* cstr = myString.c_str();
    this->init_from_cstr(cstr);
}

MyString::~MyString()
{
    // delete[] this->charList;
}

char MyString::operator[](int index) const
{
    if (index >= this->size())
    {
        throw std::invalid_argument("invalid index!");
        exit(OUTBOUND_ERR);
    }

    return this->charList[index];
}

MyString MyString::operator+(MyString const str)
{
    return (*this + str.c_str());
}

MyString MyString::operator+(char* cstr)
{
    MyString result;
    result.append(this->c_str());
    result.append(cstr);

    return result;
}

MyString MyString::operator+(std::string str)
{
    return this->operator+(str.c_str());
}

MyString& MyString::operator+=(char * cstr)
{
    this->append(cstr);
    return *this;
}

MyString& MyString::operator+=(std::string str)
{
    return this->operator+=(str.c_str());
}

MyString& MyString::operator=(char * cstr)
{
    this->clear();
    this->append(cstr);

    return *this;
}

MyString& MyString::operator=(std::string str)
{
    return this->operator=(str.c_str());
}

MyString& MyString::operator=(char c)
{
    this->clear();
    this->append(1, c);
    return *this;
}

bool MyString::operator>(MyString mystr)
{
    if (strcmp(this->c_str(), mystr.c_str()) > 0)
    {
        return true;
    }

    else return false;
}

bool MyString::operator<(MyString mystr)
{
    if (strcmp(this->c_str(), mystr.c_str()) < 0)
    {
        return true;
    }

    else return false;
}

bool MyString::operator>=(MyString mystr)
{
    return (bool)(this->operator>(mystr) || this->operator==(mystr));
}

bool MyString::operator<=(MyString mystr)
{
    return (bool)(this->operator<(mystr) || this->operator==(mystr));
}

bool MyString::operator==(MyString mystr)
{
    if (strcmp(this->c_str(), mystr.c_str()) == 0)
    {
        return true;
    }

    else return false;
}

bool MyString::operator!=(MyString mystr)
{
    return !this->operator==(mystr);
}

char *MyString::c_str() const
{
    return this->charList.toString();
}

char *MyString::data() const
{
    return c_str();
}

int MyString::size() const
{
    return this->charList.getLength();
}

bool MyString::empty() const
{
    if (this->size()) return false;
    else return true;
}

int MyString::capacity() const
{
    return this->charList.getMemoryUnits();
}

void MyString::shrink_to_fit()
{
    this->charList.allocListFree();
}

void MyString::clear()
{
    for (int i = this->size() - 1; i >= 0; i--)
    {
        this->charList.removeAt(i);
    }
    
}

void MyString::insert(int index, int count, char c)
{
    if (index < 0 || index > this->length())
    {
       throw std::out_of_range("invalid index!");
       return;
    }

    for (int i = 0; i < count; i++)
    {
        this->charList.appendAt(c, index);
    }
}

void MyString::insert(int index, char *cstr)
{
    if (index < 0 || index > this->length())
    {
       throw std::out_of_range("invalid index!");
       return;
    }

    int cstr_len = strlen(cstr);

    for (int i = cstr_len - 1; i >= 0; i--)
    {
        this->charList.appendAt(cstr[i], index);
    }
}

void MyString::insert(int index, char *cstr, int count)
{
    for(int i = 0; i < count; i++)
    {
        this->insert(index, cstr);
    }
}

void MyString::insert(int index, std::string str)
{
    this->insert(index, (char*)str.c_str());
}

void MyString::insert(int index, std::string str, int count)
{
    for (int i = 0; i < count; i++)
    {
        this->insert(index, str);
    }
}

void MyString::erase(int index, int count)
{
    if (index < 0 || index + count > this->length())
    {
       throw std::out_of_range("invalid index or (and) count!");
       return;
    }

    for (int i = 0; i < count; i++)
    {
        this->charList.removeAt(index);
    }
}

void MyString::append(int count, char c)
{
    this->insert(this->length(), count, c);
}

void MyString::append(char *cstr)
{
    this->insert(this->length(), cstr);
}

void MyString::append(char *cstr, int count)
{
    this->insert(this->length(), cstr, count);
}

void MyString::append(std::string str)
{
    this->insert(this->length(), str);
}

void MyString::append(std::string str, int count)
{
    this->insert(this->length(), str, count);
}

void MyString::replace(int index, int count, char *cstr)
{
    int len = this->length();
    if (index + count > len)
    {
        throw std::out_of_range("invalid index or (and) count!");
        return;
    }

    this->erase(index, count);
    this->insert(index, cstr);
}

void MyString::replace(int index, int count, std::string str)
{
    if (index + count > this->length())
    {
        throw std::out_of_range("invalid index or (and) count!");
        return;
    }

    this->erase(index, count);
    this->insert(index, str);
}

MyString MyString::substr(int index) const
{
    if (index < 0 || index  >= this->length())
    {
       throw std::out_of_range ("invalid index!");
       exit(OUTBOUND_ERR);
    }

    MyString newString;

    for (int i = index; i < this->length(); i++)
    {
        newString.charList.append(this->charList[i]);
    }

    return newString;
}

MyString MyString::substr(int index, int count) const
{
    if (index < 0 || index + count  >= this->length())
    {
       throw std::out_of_range("invalid index or (and) count!");
       exit(OUTBOUND_ERR);
    }

    MyString newString;

    for (int i = index; i < index + count; i++)
    {
        newString.charList.append(this->charList[i]);
    }

    return newString;
}

int MyString::find(const char *cstr) const
{
    // use higher find(char*, int) -> find(char*, 0)
    return find(cstr, 0);
}

int MyString::find(const char *cstr, int index) const
{
    int result;
    char* cur_cstr = this->c_str();

    if (index)
    {
        char* cut = substr(index).c_str();
        result = quick_search_aho(cut, cstr) + index;
        free(cut);
    }

    else
    {
        result = quick_search_aho(cur_cstr, cstr);
    }

    free(cur_cstr);
    return result;
}

int MyString::find(std::string str) const
{
    const char* cstr = str.c_str();

    return find(cstr);
}

int MyString::find(std::string str, int index) const
{
    const char* cstr = str.c_str();

    return find(cstr, index);
}

std::unordered_multimap<char*, int> MyString::trie_find(std::vector<char*>& strings, int index)
{
    Trie t;
    std::unordered_multimap<char*, int> results;

    for (auto& it : strings)
    {
        t.insert(it);
    }

    struct Vertex* current_vertex = t.get_root();

    for (int i = 0; i <= this->length(); i++)
    {
        current_vertex = t.go(current_vertex, this->at(i));
        if (current_vertex->is_terminal)
        {
            // occurence
            char* assbl = t.terminal_assemble(current_vertex);
            results.insert({assbl, i - strlen(assbl) + 1});
        }
    }

    return results;
}

short MyString::to_short() const
{
    char* cstr = this->c_str();
    char* pEnd;

    if (!strcheck(cstr))
    {
        // throw std::overflow_error("invalid sequence");
        throw InvalidConversionException();
        return 0;
    }

    long result = str2schar(cstr, &pEnd, 10);

    if ((result == SHRT_MAX|| result == SHRT_MIN) && errno == ERANGE)
    {
        throw std::overflow_error("the value read is out of the range of representable values by a long");
        return 0;
    }

    return result;
}

char MyString::to_char() const
{
    char* cstr = this->c_str();
    char* pEnd;

    if (!strcheck(cstr))
    {
        throw InvalidConversionException();
        return 0;
    }

    long result = str2schar(cstr, &pEnd, 10);

    if ((result == SCHAR_MAX|| result == SCHAR_MIN) && errno == ERANGE)
    {
        throw std::overflow_error("the value read is out of the range of representable values by a long");
        return 0;
    }

    return result;
}

int MyString::to_int() const
{
    char* cstr = this->c_str();
    char* pEnd;

    if (!strcheck(cstr))
    {
        throw InvalidConversionException();
        return 0;
    }

    long result = str2i(cstr, &pEnd, 10);

    if ((result == INT_MAX || result == INT_MIN) && errno == ERANGE)
    {
        throw std::overflow_error("the value read is out of the range of representable values by a long");
        return 0;
    }

    return result;
}

long MyString::to_long() const
{
    char* cstr = this->c_str();
    char* pEnd;

    if (!strcheck(cstr))
    {
        // throw std::overflow_error("invalid sequence");
        throw InvalidConversionException();
        return 0;
    }

    long result = strtol(cstr, &pEnd, 10);

    if ((result == LONG_MAX || result == LONG_MIN) && errno == ERANGE)
    {
        throw std::overflow_error("the value read is out of the range of representable values by a long");
        return 0;
    }

    return result;
}

float MyString::to_float() const
{
    char* cstr = this->c_str();
    return (float)atof(cstr);
}

double MyString::to_double() const
{
    char* cstr = this->c_str();
    return atof(cstr);
}

char MyString::at(int index) const
{
    if (index <= this->length())
    {
        char c = this->c_str()[index];
        return c;
    }

    else
    {
        throw std::out_of_range("wrong index!");
        exit(0);
    }
}

int MyString::length() const
{
    return size();
}

std::ostream &operator<<(std::ostream &out, const MyString &s)
{
    return out << s.c_str();
}

std::istream &operator>>(std::istream &in, MyString &s)
{
    bool if_skiws_set = std::cin.flags() & std::ios_base::skipws;
    char temp;
    unsigned int i = 0;

    in >> std::noskipws >> temp;
    while(!in.eof() && temp != '\n')
    {
        s.append(1, temp);
        in >> temp;
    }

    if(!if_skiws_set)
        in >> std::skipws;

    return in;
}
