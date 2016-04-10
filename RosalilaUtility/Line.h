class Point
{
public:
    int x;
    int y;
    Point()
    {
        this->x=0;
        this->y=0;
    }
    Point(int x,int y)
    {
        this->x=x;
        this->y=y;
    }
};

class Line
{
public:
    Point p1;
    Point p2;
    Line()
    {
    }
    Line(Point p1,Point p2)
    {
        this->p1=p1;
        this->p2=p2;
    }

    void set(Point p1,Point p2)
    {
        this->p1=p1;
        this->p2=p2;
    }
};
