class Member
{
    private:
        std::string memberID;
        std::map < std::string, int > borrowedBooks;
        int borrowLimit;
        std::string name;
    public:
        Member (std::string& memberid, std::string& Name, int borrowlimit)
        {
            memberID = memberid;
            name = Name;
            borrowLimit = borrowlimit;
        }
        Member(std::string& memberid, std::string& Name)
        {
            memberID = memberid;
            name = Name;
            borrowLimit = 3;
        }
        ~Member(){}
        bool borrowBook (std::string& isbno);
        bool returnBook (std::string& isbno);
        void printDetails();
        std::string getName()
        {
            return name;
        }  
        std::string get_memid()
        {
            return memberID;
        }
};

bool Member :: borrowBook (std::string& isbno)
        {
            int nobookstaken = 0;
            for (auto m=borrowedBooks.begin(); m != borrowedBooks.end() ; m++)
            {
                nobookstaken += m -> second;
            }
            if (nobookstaken < borrowLimit)
            {
                auto ptr = borrowedBooks.find(isbno);
                if(ptr != borrowedBooks.end())
                {
                    borrowedBooks[isbno] += 1;
                    return true;
                }
                else
                {
                    borrowedBooks[isbno] = 1;
                    return true;
                }
            }
            else
            {
                std::cout << "Invalid request! Borrow limit exceeded \n" ;
                return false;
            }
        }

bool Member :: returnBook (std::string& isbno)
{
    auto ptr = borrowedBooks.find(isbno);
    if (ptr != borrowedBooks.end())
    {
        if (borrowedBooks[isbno] == 1)
        {
            borrowedBooks.erase(isbno);
        }
        else
        {
            borrowedBooks[isbno]--;
        }
        return true;
    }
    else
    {
        std::cout << "Invalid request! Book not borrowed \n" ;
        return false;
    }
}

void Member :: printDetails()
{
    for(auto ptr = borrowedBooks.begin(); ptr != borrowedBooks.end(); ptr++)
    {
        std::cout << memberID << " " << name << " " << ptr->first << " " << ptr->second << "\n";
    }
}