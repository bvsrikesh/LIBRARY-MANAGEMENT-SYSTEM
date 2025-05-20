#include <iostream>
#include <string>
#include <map>
#include <vector>

class Book
{
    private:
        std::string isbn;
        int copiesAvailable;
        int totalCopies;
    public:
        std::string title;
        std::string author;
        Book (std::string& name, std::string& author_name, std::string& isbno, int copies_available, int totalnocopies)
        {
            title = name;
            author = author_name;
            isbn = isbno;
            copiesAvailable = copies_available;
            totalCopies = totalnocopies;
        }
        Book()
        {
            title = "UnknownTitle";
            author = "UnknownAuthor";
            isbn = "ISBN";
            copiesAvailable = 0;
            totalCopies = 5;
        }
        Book (Book &b, std::string& isbno)
        {
            title = b.title;
            author = b.author;
            isbn = isbno;
            copiesAvailable = b.copiesAvailable;
            totalCopies = b.totalCopies;
        }
        ~Book(){}
        void updateCopies(int count);
        bool borrowBook();
        bool returnBook();
        void printDetails();
        std::string get_isbn()
        {
            return isbn;
        }
        int get_copiesAvailable()
        {
            return copiesAvailable;
        }
        int get_totoalCopies()
        {
            return totalCopies;
        }
};

void Book :: updateCopies(int count)
{
    if (copiesAvailable + count >= 0 && totalCopies+count >= 0)
    {
        copiesAvailable += count;
        totalCopies += count;
    }
    else 
    {
        std::cout << "Invalid request! Count becomes negative \n" ;
    }   
}

bool Book :: borrowBook()
{
    if(copiesAvailable >= 1)
    {
        copiesAvailable--;
        return true;
    }
    else
    {
        std::cout << "Invalid request! Copy of book not available \n" ;
        return false;
    }
}

bool Book :: returnBook()
{
    if (copiesAvailable < totalCopies)
    {
        copiesAvailable++;
        return true;
    }
    else
    {
        std::cout << "Invalid request! Copy of book exceeds total copies \n" ;
        return false;
    }
}

void Book :: printDetails()
{
    std::cout << title << " " << author << "\n" ;
}

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

class Library
{
    private:
        std::vector < Book > books;
        std::vector < Member > members;
    public:
        Library(){}
        ~Library(){}
        bool addBook (Book& b);
        bool registerMember (Member& m);
        bool borrowBook (std::string& memberID, std::string& isbn);
        bool returnBook (std::string& memberID, std::string& isbn);
        void printLibraryDetails();
        void copy_book (std::string& isbno1,std::string& isbno2);
        void update_copies (std::string& isbno,int count);
        void print_book (std::string& isbn);
        void print_members (std::string& memid);
};

bool Library :: addBook (Book& b)
{
    int booksize = books.size();
    for (int i = 0; i < booksize ; i++){
        if (b.get_isbn() == books[i].get_isbn())
        {
            std::cout << "Invalid request! Book with same isbn already exists \n" ;
            return false;
        }
    }
    books.push_back(b);
    return true;
}

bool Library :: registerMember (Member& m)
{
    int memsize = members.size();
    for (int i = 0; i < memsize; i++)
    {
        if (m.get_memid() == members[i].get_memid())
        {
            std::cout << "Invalid request! Member with same id already exists \n" ;
            return false;
        }
    }
    members.push_back(m);
    return true;
}

bool Library :: borrowBook (std::string& memberID, std::string& isbn)
{
    int booksize = books.size();
    int i;
    for (i = 0; i < booksize; i++)
    {
        if (books[i].get_isbn() == isbn)
        {
            if (!books[i].borrowBook())
            {
                return false;
            }
            else break;
        }
    }
    int memsize = members.size();
    for (int j = 0; j < memsize; j++)
    {
        if (members[j].get_memid() == memberID)
        {
            if (members[j].borrowBook(isbn))
            {
                return true;
            }
            else 
            {
                books[i].returnBook();
                return false;
            }
        }
    }
    return false;
}

bool Library :: returnBook (std::string& memberID, std::string& isbn)
{
    int booksize = books.size();
    int i;
    for (i = 0; i < booksize; i++)
    {
        if (books[i].get_isbn()==isbn)
        {
            if (!books[i].returnBook())
            {
                return false;
            }
            else break;
        }
    }
    int memsize = members.size();
    for (int j = 0; j < memsize; j++)
    {
        if (members[j].get_memid() == memberID)
        {
            if (members[j].returnBook(isbn))
            {
                return true;
            }
            else 
            {
                books[i].borrowBook();
                return false;
            }
        }
    }
    return false;
}

void Library :: printLibraryDetails()
{
    int booksize = books.size();
    for (int i = 0; i < booksize; i++)
    {
        std::cout << books[i].title << " " << books[i].author << " " << books[i].get_copiesAvailable() <<"\n" ;
    }
    int memsize = members.size();
    for(int j = 0; j < memsize; j++)
    {
        std::cout << members[j].get_memid() << " " << members[j].getName() <<"\n" ;
    }
}

void Library :: copy_book (std::string& isbno1,std::string& isbno2)
{
    int booksize = books.size();
    for (int i = 0; i < booksize; i++)
    {
        if (books[i].get_isbn() == isbno1)
        {
            Book b1(books[i],isbno2);
            addBook(b1);
        }
    }
}

void Library :: update_copies (std::string& isbno,int count)
{
    int booksize = books.size();
    for (int i = 0; i < booksize; i++)
    {
        if (books[i].get_isbn() == isbno)
        {
            books[i].updateCopies(count);
        }
    }
}

void Library :: print_book (std::string& isbn)
{
    int booksize = books.size();
    for (int i = 0; i < booksize; i++)
    {
        if (books[i].get_isbn() == isbn)
        {
            books[i].printDetails();
        }
    }
}

void Library :: print_members (std::string& memid)
{
    int memsize = members.size();
    for (int j = 0; j < memsize; j++)
    {
        if (members[j].get_memid() == memid)
        {
            members[j].printDetails();
        }
    }
}

int main(){

    Library lib;
    std::string m;
    while(true)
    {
        std::cin >> m;
        if (m == "Book")
        {
            std::string title,author,isbn;
            int m1,m2;
            std::cin >> title;
            if (title == "None")
            {
                Book b;
                lib.addBook(b);
            }
            else if (title == "ExistingBook")
            {
                std::cin >> author >> isbn;
                lib.copy_book(author,isbn);
            }
            else
            {
                std::cin >> author >> isbn;
                std::cin >> m1 >> m2;
                Book b(title,author,isbn,m1,m2);
                lib.addBook(b);
            }
        }
        else if (m == "UpdateCopiesCount")
        {
            std::string isbn;
            int newcount;
            std::cin >> isbn >> newcount;
            lib.update_copies(isbn,newcount);
        }
        else if (m == "Member")
        {
            std::string mv1;
            std::cin >> mv1;
            if (mv1 == "NoBorrowLimit")
            {
                std::string mv2,name;
                std::cin >> mv2 >> name;
                Member mm(mv2,name);
                lib.registerMember(mm);
            }
            else
            {
                std::string mv2;
                int bl;
                std::cin >> mv2 >> bl;
                Member mm(mv1,mv2,bl);
                lib.registerMember(mm);
            }
        }
        else if (m == "Borrow")
        {
            std::string memid,isbn;
            std::cin >> memid >> isbn;
            lib.borrowBook(memid,isbn);
        }
        else if (m == "Return")
        {
            std::string memid,isbn;
            std::cin >> memid >> isbn;
            lib.returnBook(memid,isbn);
        }
        else if (m == "PrintBook")
        {
            std::string m1;
            std::cin >> m1;
            lib.print_book(m1);
        }
        else if (m == "PrintMember")
        {
            std::string m1;
            std::cin >> m1;
            lib.print_members(m1);
        }
        else if (m == "PrintLibrary")
        {
            lib.printLibraryDetails();
        }
        else if (m == "Done")
        {
            break;
        }
    }
}