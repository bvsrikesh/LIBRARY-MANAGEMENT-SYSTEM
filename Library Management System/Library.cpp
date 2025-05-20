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