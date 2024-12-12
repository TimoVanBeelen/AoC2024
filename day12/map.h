#include <stdexcept>

class map
{
private:
    int height;         // Height of the matrix
    int width;          // Width of the matrix
    char **val;         // Character of the map
    char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};


public:
    // Constructors
    map(int height, int width);
    ~map();

    // Setters
    void set_size(int height, int width);
    void set_val(int h, int w, char value);

    // Getters
    int get_height();
    int get_width();
    char get_val(int h, int w);

    // Public variables
    bool **is_visited;
};

map::map(int height, int width)
{
    this->height = height;
    this->width = width;
    
    this->val = new char*[height];
    this->is_visited = new bool*[height];
    for (int i=0; i<height; i++) {
        this->val[i] = new char[width];
        this->is_visited[i] = new bool[width];
    }
}

map::~map()
{
}

// SETTERS
inline void map::set_size(int height, int width)
{
    if (height<=0 || width<=0) {
        throw std::invalid_argument("Cannot make negative maps");
    }

    this->height = height;
    this->width = width;
}

inline void map::set_val(int h, int w, char value)
{
    // Check if the value is actually allowed
    bool in_alphabet = false;
    for (char c: alphabet) {
        if (c == value) 
            in_alphabet = true;
    }
    if (!in_alphabet) throw std::invalid_argument("Value of the field set is not an uppercase letter");

    // Check whether the h and w are in the map size
    if (h<0 || w<0 || h>=this->height || w>=this->width)
        throw std::invalid_argument("Height and width can't be beyond the map or negative");

    this->val[h][w] = value;
}

// GETTERS
inline int map::get_height()
{
    return this->height;
}

inline int map::get_width()
{
    return this->width;
}

inline char map::get_val(int h, int w)
{
    if (h<0 || h>=this->height || w<0 || w>=this->width)
        throw std::invalid_argument("Height and width can't be beyond the map or negative");
    return this->val[h][w];
}
