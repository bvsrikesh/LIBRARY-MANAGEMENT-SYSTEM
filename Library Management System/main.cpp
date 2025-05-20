#include "Library.cpp"

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