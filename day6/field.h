class field
{
private:
    int *pos;
    int last_dir;
    char val;

public:
    // Constructors and destructor
    field();
    field(int x, int y);
    field(int x, int y, char v);
    ~field();

    // Setters
    void set_pos(int x, int y);
    void set_dir(int d);
    void set_val(char v);

    // Getters
    int *get_pos();
    int get_last_dir();
    char get_val();
};

field::field() 
{
    this->pos = new int[2];
}

field::field(int x, int y)
{
    this->pos = new int[2];
    this->pos[0] = x;
    this->pos[1] = y;
    this->val = '.';
    this->last_dir = -1;
}

inline field::field(int x, int y, char v)
{
    this->pos = new int[2];
    this->pos[0] = x;
    this->pos[1] = y;
    this->val = v;
    this->last_dir = -1;
}

field::~field()
{
}

inline void field::set_pos(int x, int y)
{
    this->pos[0] = x;
    this->pos[1] = y;
}

inline void field::set_dir(int d)
{
    if (d < 4 && d >= 0)
        this->last_dir = d;
}

inline void field::set_val(char v)
{
    if (v == '.' || v == '^' || v == '#' || v == 'O')
        this->val = v;
}

inline int *field::get_pos()
{
    return this->pos;
}

inline int field::get_last_dir()
{
    return this->last_dir;
}

inline char field::get_val()
{
    return this->val;
}
