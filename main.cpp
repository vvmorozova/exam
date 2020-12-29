#include <iostream>
#include <fstream>
#include <string>



std::string GetCSV(std::istream &in)
{
    std::string cell;
    char c;
    while (!in.eof())
    {
        c = in.get();
        if (c != ',' && c != '\n')
        {
            cell += c;
        }
        else break;
    }
    return cell;
}
int CodeSum(const std::string &str)
{
    int sum = 0;
    for (int i = 0; i < str.size(); i++)
        sum += (unsigned char)str[i];
    return sum;
}

class Student
{
private:
    std::string Group_;
    std::string FIO;

public:
    Student() { }
    Student(std::istream &is)
    {
        GetCSV(is);
        Group_ = GetCSV(is);
        FIO = GetCSV(is);
        GetCSV(is);
        GetCSV(is);
        GetCSV(is);
    }

    Student &operator=(const Student &s)
    {
        FIO = s.FIO;
        Group_ = s.Group_;
        return *this;
    }

    bool operator<(const Student &s) const
    {
        return CodeSum(FIO) < CodeSum(s.FIO);
    }

    const std::string &GetGroup() const
    {
        return Group_;
    }
    const std::string &GetFIO() const
    {
        return FIO;
    }
};
class Group
{
    Group *Next;
    Student *Students;
    int Length;
    std::string Name;

public:
    Group(const std::string &n) : Name(n), Students(nullptr), Length(0), Next(nullptr) { }
    ~Group()
    {
        delete[] Students;
        Students = nullptr;
        Length = 0;
    }

    int Size()
    {
        return Length;
    }
    Student *GetStudents()
    {
        return Students;
    }

    void SetNext(Group *n)
    {
        Next = n;
    }
    Group *GetNext()
    {
        return Next;
    }

    void Add(const Student &s)
    {
        auto b = new Student[Length + 1];
        for (int i = 0; i < Length; i++)
            b[i] = Students[i];
        b[Length] = s;
        delete[] Students;
        Students = b;
        Length++;
    }
    void Sort()
    {
        for (int i = 1; i < Length; i++)
        {
            for (int j = 0; j < Length - i; j++)
            {
                if (Students[j + 1] < Students[j])
                {
                    Student t = Students[j + 1];
                    Students[j + 1] = Students[j];
                    Students[j] = t;
                }
            }
        }
    }

    const std::string &GetName()
    {
        return Name;
    }
};



int main()
{
    //std::cout << CodeSum("Привет мир") << '\n';

    Group *start = nullptr;

    std::ifstream in("/home/vasuyan/sum/groups.csv");
    while (in.get() != '\n');
    while (in)
    {
        Student s(in);

        if (start)
        {
            Group *cur = start;
            while (cur->GetName() != s.GetGroup() && cur->GetNext()) cur = cur->GetNext();
            if (cur->GetName() == s.GetGroup()) cur->Add(s);
            else
            {
                cur->SetNext(new Group(s.GetGroup()));
                cur->GetNext()->Add(s);
            }
        }
        else
        {
            start = new Group(s.GetGroup());
            start->Add(s);
        }
    }



    Group *g = start;
    while (g)
    {
        g->Sort();

        for (int i = 0; i < g->Size(); i++)
        {
            std::cout << CodeSum(g->GetStudents()[i].GetFIO()) << '\n';
            if (g->GetStudents()[i].GetFIO() == "Морозова Василиса Витальевна")
            {
                if (i < g->Size() - 1) std::cout << CodeSum(g->GetStudents()[i + 1].GetFIO()) << '\n';
                else std::cout << CodeSum(g->GetStudents()[0].GetFIO()) << '\n';
                break;
            }
        }

        g = g->GetNext();
    }

    g = start;
    while (g)
    {
        Group *k = g;
        g = g->GetNext();
        delete k;
    }

    return 0;
}
