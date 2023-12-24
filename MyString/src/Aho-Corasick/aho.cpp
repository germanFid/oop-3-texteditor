#include "aho.h"
#include <string.h>

//
// Check https://www.cs.usfca.edu/~galles/visualization/Trie.html
//
Vertex *Trie::initVertex(struct Vertex* parent)
{
    struct Vertex* result = new struct Vertex();

    result->next = std::map<char, struct Vertex*>();
    result->is_terminal = false;
    result->parent = parent;
    result->prev_char = '\0';

    result->sufflink = nullptr;
    result->go = std::map<char, struct Vertex*>();

    return result;
}

Trie::Trie()
{
    root = initVertex(nullptr);
}

Trie::~Trie()
{

}

void Trie::insert(char* cstr)
{
    struct Vertex* current = this->root;
    char* ptr = cstr;
    while (*ptr)
    {
        if (auto search = current->next.find(*ptr); search != current->next.end())
        {
            ptr++;
            current = search->second;
            continue;
        }

        current->next[*ptr] = initVertex(current);
        current->next[*ptr]->prev_char = *ptr;
        current = current->next[*ptr];
        ptr++;
    }

    current->is_terminal = true;
}

int Trie::find(char* cstr)
{
    struct Vertex* current = this->root;
    char* ptr = cstr;
    while (*ptr)
    {
        if (auto search = current->next.find(*ptr); search != current->next.end())
        {
            ptr++;
            current = search->second;
            continue;
        }

        return FIND_FAIL;
    }

    if(current->is_terminal) 
        return FIND_SUCCESS;
   
    else 
        return FIND_PREFIX_FAIL;
}

Vertex* Trie::get_root() const
{
    return this->root;
}

Vertex *Trie::get_link(struct Vertex* vertex)
{
    if (vertex->sufflink == nullptr)
    {
        if(vertex == this->root || vertex->parent == this->root)
        {
            vertex->sufflink = this->root;
        }

        else
        {
            vertex->sufflink = this->go(this->get_link(vertex->parent), vertex->prev_char);
        }
    }

    return vertex->sufflink;
}

Vertex *Trie::go(Vertex *vertex, char c)
{
    if (auto search = vertex->go.find(c); search == vertex->go.end())
    {
        if (auto search_next = vertex->next.find(c); search_next != vertex->next.end())
        {
            vertex->go[c] = vertex->next[c];
        }

        else if (vertex == this->root)
        {
            vertex->go[c] = this->root;
        }

        else
        {
            vertex->go[c] = this->go(this->get_link(vertex), c);
        }
    }
    
    return vertex->go[c];
}

char *Trie::terminal_assemble(Vertex *v)
{
    struct Vertex* root = this->get_root();
    struct Vertex* current = v;
    
    std::vector<char> vec;

    while (current != root)
    {
        vec.push_back(current->prev_char);
        current = current->parent;
    }

    int n = vec.size();
    char* result = new char[vec.size() + 1];
    result[vec.size()] = '\0';

    int i = 0;
    for (int j = vec.size() - 1; j >= 0; j--)
    {
        result[i] = vec[j];
        i++;
    }

    return result;
}

int quick_search_aho(const char *cstr, const char *sub_cstr)
{
    Trie t;
    int sub_cstr_len = strlen(sub_cstr);

    t.insert((char*)sub_cstr);
    struct Vertex* v = t.get_root();

    for (int i = 0; i < strlen(cstr); i++)
    {
        v = t.go(v, cstr[i]);
        if (v->is_terminal)
        {
            return i - sub_cstr_len + 1;
        }
    }
    
    return FIND_FAIL;
}
