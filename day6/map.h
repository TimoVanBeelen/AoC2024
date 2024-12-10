#include "field.h"
#include <stdexcept>

class map
{
private:
    int height;         // Height of the matrix
    int width;          // Width of the matrix
    field **fld;        // Matrix (playing field)

public:
    // Constructors
    map(int height, int width);
    ~map();

    // Setters
    void set_size(int height, int width);

    // Getters
    int get_height();
    int get_width();
    field get_field(int x, int y);
};

map::map(int height, int width)
{
    this->height = height;
    this->width = width;
    this->fld = new field*[height];
    for (int i=0; i<width; i++)
        this->fld[i] = new field[width];
}

map::~map()
{
}

inline void map::set_size(int height, int width)
{
    if (height<=0 || width<=0) {
        throw std::invalid_argument("Cannot make negative maps");
    }

    this->height = height;
    this->width = width;
}

inline int map::get_height()
{
    return this->height;
}

inline int map::get_width()
{
    return this->width;
}

inline field map::get_field(int x, int y)
{
    return this->fld[x][y];
}
