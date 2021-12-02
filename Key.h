typedef int Key;

class Key{
    private:
    int key;
    public:
    // Add any constructors and methods for key data.
    static int comparisons;
    Key (int x = 0);
    int the_key() const;
};

 
bool operator== (const Key &x, const Key &y);
bool operator> (const Key &x, const Key &y);
bool operator< (const Key &x, const Key &y);
bool operator>= (const Key &x, const Key &y);
bool operator<= (const Key &x, const Key &y);
bool operator!= (const Key &x, const Key &y);