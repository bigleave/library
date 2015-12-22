function Bookshelf(){
    this.num_Book = 0;
 	this.book_list=new Array(5);
}

Bookshelf.prototype.add = function(book)
{
  	this.book_list[this.num_Book]=book;
  	//alert(this.book_list[this.num_Book].title);
  	this.num_Book++;
};
Bookshelf.prototype.print = function(book)
{
  	for(var i=0;i<this.num_Book;i++){
  		$("#show").html($("#show").html()+this.book_list[i].title+","
  			+this.book_list[i].ISBN+","
  			+this.book_list[i].author+","
  			+this.book_list[i].language+"<br/>");
  	}
};