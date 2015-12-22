#include <iostream>
#include<fstream>
#include <sstream>
using namespace std;

class Book
{
public:
    Book()
    {

    }
    void setBorrow();
    void setTitle(string Name_book)
    {
        Title = Name_book;
    }
    void setISBN(string ISBN_book)
    {
        ISBN = ISBN_book;
    }
    void setAuthor(string Author_book)
    {
        author = Author_book;
    }
    void setType(string type)
    {
        Type = type;
    }
    string getType()
    {
        return Type;
    }
    string getTitle()
    {
        return Title;
    }
    void print()
    {
        cout << Title <<"   "<< ISBN <<"   "<< author<<"   "<< Type << endl;
    }
private:
    string Title;
	string ISBN;
	bool borrow;
	string author;
	string Type;
};

class Bookshelf
{
public:
    Bookshelf()
    {
        num_Book=0;
    }
    Book *book_list[5];
    void add (Book *t)
    {
        book_list[num_Book]=t;
        num_Book++;
    }
    void setID(string id){
        ID=id;
    }
    Book *Search_book(string name){
        for(int i=0;i<num_Book;i++){
            if(book_list[i]->getTitle()==name){
                return book_list[i];
            }
        }
        return NULL;
    }
    void del(Book *b){
        for(int i=0;i<num_Book;i++){
            if(book_list[i]->getTitle()==b->getTitle()){
                Book *t=book_list[i];
                book_list[i]=book_list[num_Book-1];
                book_list[num_Book-1]=t;
                delete t;
                num_Book--;
            }
        }
    }
    int getNum(){
        return num_Book;
    }
private:
    int num_Book;
    string ID;

};
class Library
{
private:
    int i;
    int num_book;
    fstream file;
    Bookshelf CN[100],EN[100];
    string line,token;
    int num,cn,en;
public:
    Library()
    {
        num = 0;
        file.open("Book.txt", ios::in);
        file>>num_book;
        Book *temp=new Book[num_book];
        int a=0;
        while(getline(file,line))
        {
            stringstream ss(line);
            while(getline(ss,token,','))
            {

                if(a == 0)temp[num-1].setTitle(token);
                else if(a == 1)temp[num-1].setISBN(token);
                else if(a == 2)temp[num-1].setAuthor(token);
                else if(a == 3){
                    temp[num-1].setType(token);
                }
                a=(a+1)%4;
            }
            num++;
        }
        for(num=0;num<num_book;num++){
            Insert_book(&temp[num]);
        }
    }
    void Insert_book(Book *t)
    {
        int i;
        if(t->getType()=="CN"){

            for(i=0;i<100;i++){
                if(CN[i].getNum()<5){
                    CN[i].add(t);
                    break;
                }
            }
        }else{
            for(i=0;i<100;i++){
                if(EN[i].getNum()<5){
                    EN[i].add(t);
                    break;
                }
            }
        }

    }
    void delete_book(string name){
        for(int i=0;i<100;i++){
            if(EN[i].getNum()==0){
                break;
            }
            else if(EN[i].getNum()!=0){
                Book *temp=EN[i].Search_book(name);
                if(temp!=NULL){
                    EN[i].del(temp);
                }
            }
        }
        for(int i=0;i<100;i++){
            if(CN[i].getNum()==0){
                break;
            }
            else if(CN[i].getNum()!=0){
                Book *temp=CN[i].Search_book(name);
                if(temp!=NULL){
                    CN[i].del(temp);
                }
            }
        }
    }
    void Search_book(string name){
        for(int i=0;i<100;i++){
            if(EN[i].getNum()==0){
                break;
            }
            else if(EN[i].getNum()!=0){
                Book *temp=EN[i].Search_book(name);
                if(temp!=NULL){
                    temp->print();
                    cout<<"at EN "<<i<<" Bookshelf"<<endl;
                }
            }
        }
        for(int i=0;i<100;i++){
            if(CN[i].getNum()==0){
                break;
            }
            else if(CN[i].getNum()!=0){
                Book *temp=CN[i].Search_book(name);
                if(temp!=NULL){
                    temp->print();
                    cout<<"at CN "<<i<<" Bookshelf"<<endl;
                }
            }
        }
    }


};




int main()
{
    Library lib;
    int ib=0;
    while(1){
        cout<<"1)查詢\n2)新增\n3)刪除\n4)離開\n";
        int ch;
        cin>>ch;
        if(ch==1){
            string name;
            cout<<"輸入書名: ";
            cin>>name;
            lib.Search_book(name);
        }else if(ch==2){
            string a,aa,aaa,aaaa;
            cin>>a>>aa>>aaa>>aaaa;
            Book insertB;
            insertB.setTitle(a);
            insertB.setISBN(aa);
            insertB.setAuthor(aaa);
            insertB.setType(aaaa);
            lib.Insert_book(&insertB);
        }else if(ch==3){
            string a;
            cin>>a;
            lib.delete_book(a);
        }else if(ch==4)break;
    }

    return 0;
}
