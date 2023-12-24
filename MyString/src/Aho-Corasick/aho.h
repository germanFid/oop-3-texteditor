#include <map>
#include <vector>

#define FIND_SUCCESS 100
#define FIND_FAIL -100
#define FIND_PREFIX_FAIL -200

struct Vertex
{
    std::map<char, struct Vertex*> next;
    bool is_terminal;
    struct Vertex* parent;
    char prev_char;

    struct Vertex* sufflink;
    std::map<char, struct Vertex*> go;

};


class Trie
{
private:
    struct Vertex* root;
    
    struct Vertex* initVertex(struct Vertex* parent);

public:
    Trie();
    ~Trie();

    void insert(char* cstr);
    int find(char* cstr);

    struct Vertex* get_root() const;

    struct Vertex* get_link(struct Vertex* vertex);
    struct Vertex* go(struct Vertex* vertex, char c);

    /// @brief Assembles cstr from terminal vertex
    /// @param v terminal vertex
    /// @return cstr. You MUST free/delete it after use. `nulltr` on error
    char* terminal_assemble(struct Vertex* v);
};

/// @brief quick search with Aho-Corasick algorithm
/// @param cstr string to search in
/// @param sub_cstr string to search
/// @return first index of first substring in cstr or `FIND_FAIL`
int quick_search_aho(const char* cstr, const char* sub_cstr);
