function Library(){
    this.cnBookShelf = new Array(100);
    this.enBookShelf = new Array(100);
    this.num_Book=0;
    this.cn=0;
    this.en=0;
    var n;
    for(var i=0;i<100;i++){
    	this.cnBookShelf[i]=new Bookshelf();
    	this.enBookShelf[i]=new Bookshelf();
    }
    $.ajax({ 
        type : 'get', dataType : 'text', async: false,
        url : 'Book.txt', 
        success : function(data){
            var datas=data.split("\n");
            loadBook=new Array(datas.length);
            n=datas.length;
            var i=0;
            for(var key in datas){
                //$("#show").html($("#show").html()+datas[key]+"<br/>");
                var elemt=datas[key].split(",");
                loadBook[i]=new Book(elemt[0],elemt[1],elemt[2],elemt[3].substring(0, 2));
                i++;
            }
        }, 
        error : function(){alert("load Book file error");}
    });
    this.num_Book=n;
    for(var i=0;i<n;i++){
		this.insertBook(loadBook[i]);
    }
}
Library.prototype.insertBook = function(book)
{
  	if(book.language=="CN"){
  		for(var i=0;i<100;i++){
  			if(this.cnBookShelf[i].num_Book<5){
  				this.cnBookShelf[i].add(book);
  				this.cn++;
  				break;
  			}
  		}
  	}
  	else if(book.language=="EN"){
  		for(var i=0;i<100;i++){
  			if(this.enBookShelf[i].num_Book<5){
  				this.enBookShelf[i].add(book);
  				this.en++;
  				break;
  			}
  		}
  	}
};
Library.prototype.print = function(){
	$("#show").html($("#show").html()+"CN:"+this.cn+"<br/>");
	for(var i=0;i<100;i++){
		if(this.cnBookShelf[i].num_Book>0){
			this.cnBookShelf[i].print();
		}
	}
$("#show").html($("#show").html()+"EN:"+this.en+"<br/>");
	for(var i=0;i<100;i++){
		if(this.enBookShelf[i].num_Book>0){
			this.enBookShelf[i].print();
		}
	}
}