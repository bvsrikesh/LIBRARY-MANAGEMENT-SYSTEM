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